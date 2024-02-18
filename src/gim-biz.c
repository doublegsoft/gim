/*
**              o8o
**              `"'
**   .oooooooo oooo  ooo. .oo.  .oo.
**  888' `88b  `888  `888P"Y88bP"Y88b
**  888   888   888   888   888   888
**  `88bod8P'   888   888   888   888
**  `8oooooo.  o888o o888o o888o o888o
**  d"     YD
**  "Y88888P'
*/

#include <json.h>
#include <assert.h>
#include <gfc.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#include "gim-biz.h"
#include "gim-db.h"
#include "gim-model.h"
#include "gim-err.h"
#include "gim-util.h"

#define OP_RECEIVED_MESSAGE             "receivedMessage"

extern gfc_lru_p    g_sessions;
extern gim_db_p     g_db;

/*!
** 发送错误信息给客户端。
*/
void
gim_biz_error(ws_cli_conn_t*  client,
              const char*     op,
              int             error,
              const char*     message)
{
  char resp[256] = {'\0'};
  sprintf(resp, "{\"op\":\"%s\",\"error\":{\"code\":%d,\"message\":\"%s\"}}", op, error, message);
  ws_sendframe_txt(client, resp);
}

void
gim_biz_success(ws_cli_conn_t* client,
                const char*     op)
{
  gim_biz_error(client, op, ERROR_SUCCESS, ERRMSG_SUCCESS);
}

/*!
** 客户端用户登录。
*/
void
gim_biz_login(ws_cli_conn_t* client,
              const char* user_id,
              const char* user_type,
              json_object* payload)
{
  // 存入用户进入缓存
  void* existing = NULL;
  int len = strlen(user_id);

//  gfc_lru_get(g_sessions, (void*) user_id, len, &existing);
//  if (existing == NULL)
//  {
//    gfc_lru_set(g_sessions,
//                (void *) strdup(user_id), len,
//                client, ws_size_of_cli_conn());
//  }
  gfc_log_info("put sessions: %s", user_id);
  gfc_lru_set(g_sessions,
              (void *) strdup(user_id), len,
              client, ws_size_of_cli_conn());
  gfc_log_info("login: %s", user_id);
  gim_biz_success(client, OP_LOGIN);

  printf("%lu blocks %lu bytes\n", gfc_gc_length(), gfc_gc_total());
}

/*!
** 客户端用户登出。
*/
void
gim_biz_logout(ws_cli_conn_t* client,
               const char* user_id,
               const char* user_type,
               json_object* payload)
{
  // 删除用户缓存
  gfc_lru_remove(g_sessions,
                 (void*) user_id,
                 strlen(user_id));

  gim_biz_success(client, OP_LOGOUT);
  ws_close_client(client);
}

/*!
** 用户发送消息。
*/
void
gim_biz_send_message(ws_cli_conn_t*   client,
                     const char*      user_id,
                     const char*      user_type,
                     json_object*     payload)
{
  char            sender_id[128]              = {'\0'};
  char            sender_type[128]            = {'\0'};
  char            sender_alias[128]           = {'\0'};
  char            receiver_id[128]            = {'\0'};
  char            receiver_type[128]          = {'\0'};
  char            receiver_alias[128]         = {'\0'};
  char            conversation_id[128]        = {'\0'};
  char            errmsg[1024]                = {'\0'};
  char            now[64]                     = {'\0'};
  char            message_id[64]              = {'\0'};
  char            message_content[1024 * 4]   = {'\0'};
  char            message_type[16]            = {'\0'};
  int             i                           = 0;
  int             res                         = ERROR_SUCCESS;
  gfc_list_p      members                     = NULL;
  gfc_map_p       member                      = NULL;
  char*           member_id                   = NULL;
  char*           member_type                 = NULL;
  ws_cli_conn_t*  receiver                    = NULL;
  json_object*    jresp                       = NULL;
  json_object*    jdata                       = NULL;

  strcpy(sender_id, user_id);
  strcpy(sender_type, user_type);
  gim_util_get_string(payload, "conversationId", conversation_id);
  gim_util_get_string(payload, "messageContent", message_content);
  gim_util_get_string(payload, "messageType", message_type);
  gim_util_get_string(payload, "receiverId", receiver_id);
  gim_util_get_string(payload, "receiverType", receiver_type);
  gim_util_get_string(payload, "receiverAlias", receiver_alias);
  gim_util_get_string(payload, "senderAlias", sender_alias);

  void* conn = gim_db_connect(g_db);

  if (sender_id[0] == '\0')
  {
    gim_biz_error(client,
                  OP_SEND_MESSAGE,
                  ERROR_PARAM_NO_SENDER_ID,
                  ERRMSG_PARAM_NO_SENDER_ID);
    return;
  }
  if (sender_type[0] == '\0')
  {
    gim_biz_error(client,
                  OP_SEND_MESSAGE,
                  ERROR_PARAM_NO_SENDER_TYPE,
                  ERRMSG_PARAM_NO_SENDER_TYPE);
    return;
  }
  if (message_type[0] == '\0')
  {
    gim_biz_error(client,
                  OP_SEND_MESSAGE,
                  ERROR_PARAM_NO_MESSAGE_TYPE,
                  ERRMSG_PARAM_NO_MESSAGE_TYPE);
    return;
  }
  if (message_content[0] == '\0')
  {
    gim_biz_error(client,
                  OP_SEND_MESSAGE,
                  ERROR_PARAM_NO_MESSAGE_CONTENT,
                  ERRMSG_PARAM_NO_MESSAGE_CONTENT);
    return;
  }

  if (strcmp(message_type, "TEXT") != 0 &&
      strcmp(message_type, "IMAGE") != 0 &&
      strcmp(message_type, "PROFILE") != 0 &&
      strcmp(message_type, "AUDIO") != 0 &&
      strcmp(message_type, "VIDEO") != 0)
  {
    gim_biz_error(client,
                  OP_SEND_MESSAGE,
                  ERROR_PARAM_UNKNOWN_MESSAGE_TYPE,
                  ERRMSG_PARAM_UNKNOWN_MESSAGE_TYPE);
    return;
  }

  gim_util_id(message_id);
  gim_util_now(now);

  if (conversation_id[0] == '\0')
  {
    if (receiver_id[0] == '\0' || receiver_type[0] == '\0') {
      gim_biz_error(client,
                    OP_SEND_MESSAGE,
                    ERROR_PARAM_NO_CONVERSATION,
                    ERRMSG_PARAM_NO_CONVERSATION);
      return;
    }
    // 根据接收者的标识查询会话，如果没有则创建会话
    int cmp = strcmp(sender_id, receiver_id);
    if (cmp == -1) {
      strcpy(conversation_id, sender_id);
      strcat(conversation_id, "&");
      strcat(conversation_id, receiver_id);
    } else {
      strcpy(conversation_id, receiver_id);
      strcat(conversation_id, "&");
      strcat(conversation_id, sender_id);
    }
    gfc_list_p conversations = gfc_list_new();
    gim_model_select_conversation(conn,
                                  errmsg,
                                  conversations,
                                  conversation_id,
                                  NULL,
                                  NULL,
                                  NULL,
                                  NULL);
    if (gfc_list_size(conversations) == 0)
    {
      // 不存在，则先创建信息
      gfc_log_info("在数据库中创建会话：%s", conversation_id);
      gim_model_create_conversation(conn,
                                    errmsg,
                                    conversation_id,
                                    "",
                                    "P2P",
                                    "{}",
                                    "00");
      gim_model_create_conversation_member(conn,
                                           errmsg,
                                           conversation_id,
                                           sender_id,
                                           sender_type,
                                           receiver_alias,
                                           0,
                                           now,
                                           now,
                                           now,
                                           "P2P");
      gim_model_create_conversation_member(conn,
                                           errmsg,
                                           conversation_id,
                                           receiver_id,
                                           receiver_type,
                                           sender_alias,
                                           0,
                                           now,
                                           now,
                                           now,
                                           "P2P");
    }
    for (int i = 0; i < gfc_list_size(conversations); i++)
      gfc_map_deep_free(gfc_list_get(conversations, i));
    gfc_list_free(conversations);
  }

  members = gfc_list_new();
  gim_model_select_conversation_member(conn,
                                       errmsg,
                                       members,
                                       conversation_id,
                                       NULL,
                                       NULL,
                                       NULL,
                                       NULL);

  char resp[4096];
  sprintf(resp,
          "{"
          "\"op\":\"" OP_RECEIVED_MESSAGE "\","
          "\"data\":{"
          "\"conversationMessageId\":\"%s\","
          "\"messageTime\":\"%s\","
          "\"messageType\":\"%s\","
          "\"messageContent\":\"%s\","
          "\"senderId\":\"%s\","
          "\"senderType\":\"%s\","
          "\"conversationId\":\"%s\""
          "}"
          "}",
          message_id,
          now,
          message_type,
          message_content,
          sender_id,
          sender_type,
          conversation_id);

  /*!
  ** 给会话中的其他成员发送即时消息。
  */
  for (i = 0; i < gfc_list_size(members); i++)
  {
    member = gfc_list_get(members, i);
    gfc_map_get(member, "memberId", (void**) &member_id);
    gfc_map_get(member, "memberType", (void**) &member_type);
    gfc_lru_get(g_sessions,
                (void*) member_id,
                strlen(member_id),
                (void**) &receiver);
    if (strcmp(member_id, sender_id) != 0)
    {
      if (receiver != NULL)
      {
        int optval;
        socklen_t optlen = sizeof(optval);
        int result = getsockopt(receiver->client_sock, SOL_SOCKET, SO_ERROR, &optval, &optlen);
        if (ws_get_state(receiver) == WS_STATE_OPEN && result == 0 && optval == 0 /* STILL OPEN */)
        {
          gfc_log_info("向接收者发送消息：%s", member_id);
          ws_sendframe_txt(receiver, resp/*json_object_to_json_string(jresp)*/);
        }
        else
        {
          gfc_log_info("接收者套接字已断开：%s", member_id);
          gfc_lru_remove(g_sessions, (void *) member_id, strlen(member_id));
          ws_close_client(receiver);
        }
      }
      gim_model_update_conversation_member_last_conversation_time(conn,
                                                                  errmsg,
                                                                  conversation_id,
                                                                  member_id,
                                                                  member_type,
                                                                  now);
    }
    else if (strcmp(member_id, sender_id) == 0)
    {
      gim_model_update_conversation_member_last_conversation_time(conn,
                                                                  errmsg,
                                                                  conversation_id,
                                                                  member_id,
                                                                  member_type,
                                                                  now);
    }
    else
    {
      gim_model_update_conversation_member_unread_count(conn,
                                                        errmsg,
                                                        conversation_id,
                                                        member_id,
                                                        member_type,
                                                        0);
    }
  } // for (i = 0; i < gfc_list_size(members); i++)
  int member_size = gfc_list_size(members);
  for (i = 0; i < member_size; i++)
  {
    gfc_map_p member = gfc_list_get(members, i);
    gfc_map_deep_free(member);
//    gfc_map_free(member);
  }
  gfc_list_free(members);

  printf("%lu blocks %lu bytes after free\n", gfc_gc_length(), gfc_gc_total());

  res = gim_model_create_conversation_message(conn,
                                              errmsg,
                                              message_id,
                                              conversation_id,
                                              sender_id,
                                              sender_type,
                                              NULL,
                                              NULL,
                                              now,
                                              message_type,
                                              message_content,
                                              now,
                                              "00");

  gim_biz_success(client, OP_SEND_MESSAGE);

RELEASE:

  gim_db_release(g_db, conn);
}

void
gim_biz_get_messages(ws_cli_conn_t*   client,
                     const char*      user_id,
                     const char*      user_type,
                     json_object*     payload)
{
  char sender_id[128]           = {'\0'};
  char sender_type[128]         = {'\0'};
  char receiver_id[128]         = {'\0'};
  char receiver_type[128]       = {'\0'};
  char conversation_id[128]     = {'\0'};
  char errmsg[1024]             = {'\0'};
  char message_time[64]         = {'\0'};
  int i = 0;
  int res = ERROR_SUCCESS;

  strcpy(sender_id, user_id);
  strcpy(sender_type, user_type);
  gim_util_get_string(payload, "conversationId", conversation_id);
  gim_util_get_string(payload, "receiverId", receiver_id);
  gim_util_get_string(payload, "receiverType", receiver_type);
  gim_util_get_string(payload, "messageTime", message_time);

  printf("%lu blocks %lu bytes\n", gfc_gc_length(), gfc_gc_total());
  if (sender_id[0] == '\0')
  {
    gim_biz_error(client,
                  OP_GET_MESSAGES,
                  ERROR_PARAM_NO_MEMBER_ID,
                  ERRMSG_PARAM_NO_MEMBER_ID);
    return;
  }
  if (sender_type[0] == '\0')
  {
    gim_biz_error(client,
                  OP_GET_MESSAGES,
                  ERROR_PARAM_NO_MEMBER_TYPE,
                  ERRMSG_PARAM_NO_MEMBER_TYPE);
    return;
  }
  if (conversation_id[0] == '\0')
  {
    if (receiver_id[0] == '\0' || receiver_type[0] == '\0') {
      gim_biz_error(client,
                    OP_SEND_MESSAGE,
                    ERROR_PARAM_NO_CONVERSATION,
                    ERRMSG_PARAM_NO_CONVERSATION);
      return;
    }
    // 根据接收者的标识查询会话，如果没有则创建会话
    int cmp = strcmp(sender_id, receiver_id);
    if (cmp == -1) {
      strcpy(conversation_id, sender_id);
      strcat(conversation_id, "&");
      strcat(conversation_id, receiver_id);
    } else {
      strcpy(conversation_id, receiver_id);
      strcat(conversation_id, "&");
      strcat(conversation_id, sender_id);
    }
  }

  gfc_list_p messages = NULL;
  void* conn = gim_db_connect(g_db);
  gfc_list_p members = gfc_list_new();

  if (message_time[0] == '\0')
  {
    res = gim_model_select_conversation_member(conn,
                                               errmsg,
                                               members,
                                               conversation_id,
                                               sender_id,
                                               sender_type,
                                               NULL,
                                               NULL);
    if (res)
    {
      gim_biz_error(client,
                    OP_GET_MESSAGES,
                    ERROR_DB_COMMON,
                    errmsg);
      goto RELEASE;
    }
    if (gfc_list_size(members) == 0)
    {
      gim_biz_error(client,
                    OP_GET_MESSAGES,
                    ERROR_BIZ_ILLEGAL_MEMBER,
                    ERRMSG_BIZ_ILLEGAL_MEMBER);
      gfc_list_free(members);
      goto RELEASE;
    }
    gfc_map_p member = gfc_list_get(members, 0);
    user_data val;
    gfc_map_get(member, "lastConversationTime", &val);
    strcpy(message_time, (char*) val);
    gfc_map_deep_free(member);
    gfc_list_free(members);
  }

  char suffix[1024] = {'\0'};
  strcpy(suffix, " order by convomsg.msgtm desc ");
  if (strlen(message_time) > 0)
    strcat(suffix, " limit 20 ");

  messages = gfc_list_new();
  res = gim_model_select_conversation_message(conn,
                                              errmsg,
                                              messages,
                                              conversation_id,
                                              NULL,
                                              message_time,
                                              suffix);
  if (res != ERROR_SUCCESS)
  {
    gim_biz_error(client,
                  OP_GET_MESSAGES,
                  ERROR_DB_COMMON,
                  errmsg);
    goto RELEASE;
  }

  json_object*  jresp     = json_object_new_object();
  json_object*  jdata     = json_object_new_array();

  int           size  = gfc_list_size(messages);
  void*         value = NULL;

  for (i = 0; i < size; i++)
  {
    json_object* jmessage = json_object_new_object();
    gfc_map_p message = (gfc_map_p) gfc_list_get(messages, i);

    value = NULL;
    gfc_map_get(message, "conversationMessageId", &value);
    if (value != NULL)
      json_object_object_add(jmessage, "conversationMessageId", json_object_new_string((char*) value));
    value = NULL;
    gfc_map_get(message, "senderId", &value);
    if (value != NULL)
      json_object_object_add(jmessage, "senderId", json_object_new_string((char*) value));
    value = NULL;
    gfc_map_get(message, "senderType", &value);
    if (value != NULL)
      json_object_object_add(jmessage, "senderType", json_object_new_string((char*) value));
    value = NULL;
    gfc_map_get(message, "messageType", &value);
    if (value != NULL)
      json_object_object_add(jmessage, "messageType", json_object_new_string((char*) value));
    value = NULL;
    gfc_map_get(message, "messageContent", &value);
    if (value != NULL)
      json_object_object_add(jmessage, "messageContent", json_object_new_string((char*) value));
    value = NULL;
    gfc_map_get(message, "messageTime", &value);
    if (value != NULL)
      json_object_object_add(jmessage, "messageTime", json_object_new_string((char*) value));
    json_object_array_add(jdata, jmessage);
  }
  json_object_object_add(jresp, "data", jdata);
  json_object_object_add(jresp, "op", json_object_new_string(OP_GET_MESSAGES));

  ws_sendframe_txt(client, json_object_to_json_string(jresp));

RELEASE:

  if (messages != NULL)
  {
    for (i = 0; i < gfc_list_size(messages); i++)
      gfc_map_deep_free(gfc_list_get(messages, i));
    gfc_list_free(messages);
    json_object_put(jresp);
  }
  gim_db_release(g_db, conn);
}

void
gim_biz_create_conversation(ws_cli_conn_t*  client,
                            const char*     user_id,
                            const char*     user_type,
                            json_object*    payload)
{
  char conversation_id[128] = {'\0'};
  char conversation_name[128] = {'\0'};
  char conversation_type[16] = {'\0'};
  json_object* jmembers = NULL;
  int i = 0;

  gim_util_get_string(payload, "conversationId", conversation_id);
  gim_util_get_string(payload, "conversationName", conversation_name);
  gim_util_get_string(payload, "conversationType", conversation_type);
  gim_util_get_array(payload, "members", &jmembers);

  if (conversation_type[0] == '\0')
  {
    gim_biz_error(client,
                  OP_CREATE_CONVERSATION,
                  ERROR_PARAM_NO_CONVERSATION_TYPE,
                  ERRMSG_PARAM_NO_CONVERSATION_TYPE);
    return;
  }
  if (jmembers == NULL || json_object_array_length(jmembers) < 2)
  {
    gim_biz_error(client,
                  OP_CREATE_CONVERSATION,
                  ERROR_PARAM_NOT_ENOUGH_MEMBERS,
                  ERRMSG_PARAM_NOT_ENOUGH_MEMBERS);
    return;
  }
  if (strcmp(conversation_type, "P") != 0 && strcmp(conversation_type, "G") != 0)
  {
    gim_biz_error(client,
                  OP_CREATE_CONVERSATION,
                  ERROR_PARAM_UNKNOWN_CONVERSATION_TYPE,
                  ERRMSG_PARAM_UNKNOWN_CONVERSATION_TYPE);
    return;
  }

  json_object*    jmember;
  void*           conn = gim_db_connect(g_db);
  int             res = ERROR_SUCCESS;
  char            errmsg[1024];
  char            now[24];
  char            member_id[1024] = {'\0'};
  char            member_type[1024] = {'\0'};

  // 检查数据库中是否存在已有的会话
  gfc_list_p      existing = gfc_list_new();
  gfc_string_p    sql = gfc_string_new("select convoid from tn_gim_convo  "
                                       "where 1 = 1 ");
  char            sql_and[1024];
  void*           convoid = NULL;

  sprintf(sql_and, "and convotyp = '%s' ", conversation_type);
  gfc_string_concat(sql, sql_and);
  for (i = 0; i < json_object_array_length(jmembers); i++)
  {
    jmember = json_object_array_get_idx(jmembers, i);
    gim_util_get_string(jmember, "memberId", member_id);
    gim_util_get_string(jmember, "memberType", member_type);
    sprintf(sql_and, "and convoid in ("
                     "  select convoid "
                     "  from tv_gim_convombr "
                     "  where mbrid = '%s' and mbrtyp = '%s'"
                     ") ", member_id, member_type);
    gfc_string_concat(sql, sql_and);
  }

  res = gim_db_many(conn, errmsg, existing, sql->buffer);
  if (res)
  {
    gim_biz_error(client,
                  OP_CREATE_CONVERSATION,
                  ERROR_DB_COMMON,
                  errmsg);
    goto RELEASE;
  }

  if (gfc_list_size(existing) > 0)
  {
    gfc_map_p convo = gfc_list_get(existing, 0);
    gfc_map_get(convo, "convoid", &convoid);
  }
  else
  {
    gim_util_id(conversation_id);
    gim_util_now(now);

    res = gim_model_create_conversation(conn,
                                        errmsg,
                                        conversation_id,
                                        conversation_name,
                                        conversation_type,
                                        NULL,
                                        "00");

    for (i = 0; i < json_object_array_length(jmembers); i++)
    {
      jmember = json_object_array_get_idx(jmembers, i);
      gim_util_get_string(jmember, "memberId", member_id);
      gim_util_get_string(jmember, "memberType", member_type);

      res = gim_model_create_conversation_member(conn,
                                                 errmsg,
                                                 conversation_id,
                                                 member_id,
                                                 member_type,
                                                 NULL,
                                                 0,
                                                 NULL,
                                                 now,
                                                 NULL,
                                                 "00");
    }
  }

  if (convoid != NULL)
    strcpy(conversation_id, convoid);

  json_object* jresp = json_object_new_object();
  json_object* jdata = json_object_new_object();
  json_object_object_add(jdata, "conversationId", json_object_new_string(conversation_id));
  json_object_object_add(jresp, "data", jdata);
  json_object_object_add(jresp, "op", json_object_new_string(OP_CREATE_CONVERSATION));
  ws_sendframe_txt(client, json_object_to_json_string(jresp));

RELEASE:
  for (i = 0; i < gfc_list_size(existing); i++)
    gfc_map_deep_free(gfc_list_get(existing, i));
  gfc_list_free(existing);
  gfc_string_free(sql);
  json_object_put(jresp);

  gim_db_release(g_db, conn);
}

void
gim_biz_get_conversations(ws_cli_conn_t*  client,
                          const char*     user_id,
                          const char*     user_type,
                          json_object*    payload)
{
  char member_id[128] = {'\0'};
  char member_type[128] = {'\0'};
  char errmsg[1024] = {'\0'};
  int i = 0;

  strcpy(member_id, user_id);
  strcpy(member_type, user_type);
//  gim_util_get_string(payload, "memberId", member_id);
//  gim_util_get_string(payload, "memberType", member_type);

  if (member_id[0] == '\0')
  {
    gim_biz_error(client,
                  OP_GET_CONVERSATIONS,
                  ERROR_PARAM_NO_MEMBER_ID,
                  ERRMSG_PARAM_NO_MEMBER_ID);
    return;
  }
  if (member_type[0] == '\0')
  {
    gim_biz_error(client,
                  OP_GET_CONVERSATIONS,
                  ERROR_PARAM_NO_MEMBER_TYPE,
                  ERRMSG_PARAM_NO_MEMBER_TYPE);
    return;
  }

  void* conn = gim_db_connect(g_db);
  json_object*  jresp = NULL;
  json_object*  jdata = NULL;
  gfc_list_p conversations = gfc_list_new();
  int res = gim_model_select_conversation_member(
      conn, errmsg, conversations, NULL, member_id, member_type, NULL, NULL);
  if (res != ERROR_SUCCESS)
  {
    gim_biz_error(client,
                  OP_GET_CONVERSATIONS,
                  ERROR_DB_COMMON,
                  errmsg);
    goto RELEASE;
  }

  jresp     = json_object_new_object();
  jdata   = json_object_new_array();

  int           size  = gfc_list_size(conversations);
  void*         value = NULL;

  for (i = 0; i < size; i++)
  {
    json_object* jconvo = json_object_new_object();
    gfc_map_p convo = (gfc_map_p) gfc_list_get(conversations, i);

    value = NULL;
    gfc_map_get(convo, "conversationId", &value);
    if (value != NULL)
      json_object_object_add(jconvo, "conversationId", json_object_new_string((char*) value));
    value = NULL;
    gfc_map_get(convo, "conversationName", &value);
    if (value != NULL)
      json_object_object_add(jconvo, "conversationName", json_object_new_string((char*) value));
    gfc_map_get(convo, "alias", &value);
    if (value != NULL)
      json_object_object_add(jconvo, "alias", json_object_new_string((char*) value));
    value = NULL;
    gfc_map_get(convo, "conversationType", &value);
    if (value != NULL)
      json_object_object_add(jconvo, "conversationType", json_object_new_string((char*) value));
    value = NULL;
    gfc_map_get(convo, "conversationStatus", &value);
    if (value != NULL)
      json_object_object_add(jconvo, "conversationStatus", json_object_new_string((char*) value));
    gfc_map_get(convo, "unreadCount", &value);
    if (value != NULL)
      json_object_object_add(jconvo, "unreadCount", json_object_new_int(*((int*)value)));

    json_object_array_add(jdata, jconvo);
  }
  json_object_object_add(jresp, "data", jdata);
  json_object_object_add(jresp, "op", json_object_new_string(OP_GET_CONVERSATIONS));

  ws_sendframe_txt(client, json_object_to_json_string(jresp));

RELEASE:
  for (i = 0; i < gfc_list_size(conversations); i++)
    gfc_map_deep_free(gfc_list_get(conversations, i));
  gfc_list_free(conversations);
  if (jresp != NULL)
    json_object_put(jresp);
  gim_db_release(g_db, conn);
}

void
gim_biz_add_conversation_member(ws_cli_conn_t*  client,
                                const char*     user_id,
                                const char*     user_type,
                                json_object*    payload)
{
  char member_id[128] = {'\0'};
  char member_type[128] = {'\0'};
  char conversation_id[128] = {'\0'};
  char errmsg[1024] = {'\0'};
  char now[32] = {'\0'};
  int i = 0;
  int res = ERROR_SUCCESS;

  gim_util_get_string(payload, "memberId", member_id);
  gim_util_get_string(payload, "memberType", member_type);
  gim_util_get_string(payload, "conversationId", conversation_id);

  if (member_id[0] == '\0')
  {
    gim_biz_error(client,
                  OP_ADD_CONVERSATION_MEMBER,
                  ERROR_PARAM_NO_MEMBER_ID,
                  ERRMSG_PARAM_NO_MEMBER_ID);
    return;
  }
  if (member_type[0] == '\0')
  {
    gim_biz_error(client,
                  OP_ADD_CONVERSATION_MEMBER,
                  ERROR_PARAM_NO_MEMBER_TYPE,
                  ERRMSG_PARAM_NO_MEMBER_TYPE);
    return;
  }
  if (conversation_id[0] == '\0')
  {
    gim_biz_error(client,
                  OP_ADD_CONVERSATION_MEMBER,
                  ERROR_PARAM_NO_CONVERSATION_ID,
                  ERRMSG_PARAM_NO_CONVERSATION_ID);
    return;
  }

  void* conn = gim_db_connect(g_db);

  gim_util_now(now);
  res = gim_model_create_conversation_member(conn,
                                             errmsg,
                                             conversation_id,
                                             member_id,
                                             member_type,
                                             NULL,
                                             0,
                                             now,
                                             now,
                                             NULL,
                                             "00");
  gim_db_release(g_db, conn);

  if (res)
  {
    gim_biz_error(client,
                  OP_ADD_CONVERSATION_MEMBER,
                  ERROR_DB_COMMON,
                  errmsg);
    return;
  }

  gim_biz_success(client, OP_ADD_CONVERSATION_MEMBER);
}
