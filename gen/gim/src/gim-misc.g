/*
**             o8o                    
**             `"'                    
**  .oooooooo oooo  ooo. .oo.  .oo.   
** 888' `88b  `888  `888P"Y88bP"Y88b  
** 888   888   888   888   888   888  
** `88bod8P'   888   888   888   888  
** `8oooooo.  o888o o888o o888o o888o 
** d"     YD                          
** "Y88888P'                          
*/

#include <json.h>

#include <gfc.h>

#include "gim-biz.h"
#include "gim-db.h"
#include "gim-model.h"
#include "gim-err.h"
#include "gim-util.h"

extern gfc_lru_p    g_sessions;
extern jim_db_p     g_db;

void
jim_biz_error(ws_cli_conn_t* client,
              int error,
              const char* message)
{
  char resp[256] = {'\0'};
  sprintf(resp, "{\"error\":{\"code\":%d,\"message\":\"%s\"}}", error, message);
  ws_sendframe_txt(client, resp);
}

void
jim_biz_success(ws_cli_conn_t* client)
{
  jim_biz_error(client, ERROR_SUCCESS, ERRMSG_SUCCESS);
}

/*!
** 登录。
*/
void
gim_biz_login(ws_cli_conn_t* client,
              json_object* payload)
{
  char member_id[1024] = {'\0'};
  char member_type[1024] = {'\0'};

  jim_util_get_string(payload, "memberId", member_id);
  jim_util_get_string(payload, "memberType", member_type);

  if (member_id[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_MEMBER_ID, ERRMSG_PARAM_NO_MEMBER_ID);
    return;
  }
  if (member_type[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_MEMBER_TYPE, ERRMSG_PARAM_NO_MEMBER_TYPE);
    return;
  }

  void* conn = jim_db_connect(g_db);
  gfc_map_p session_id = gfc_map_new();    
  int res = jim_model_select_conversation_member(
      conn, conversations, NULL, member_id, member_type);
  if (res != ERROR_SUCCESS)
  {
    
  }
  jim_db_release(g_db, conn);
}

/*!
** 登出。
*/
void
gim_biz_logout(ws_cli_conn_t* client,
               json_object* payload)
{
  char session_id[1024] = {'\0'};

  jim_util_get_string(payload, "sessionId", session_id);

  if (session_id[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_SESSION_ID, ERRMSG_PARAM_NO_SESSION_ID);
    return;
  }

  void* conn = jim_db_connect(g_db);
  int res = jim_model_select_conversation_member(
      conn, conversations, NULL, member_id, member_type);
  if (res != ERROR_SUCCESS)
  {
    
  }
  jim_db_release(g_db, conn);
}

/*!
** 创建会话。
*/
void
gim_biz_create_conversation(ws_cli_conn_t* client,
                            json_object* payload)
{
  char member_id[1024] = {'\0'};
  char member_type[1024] = {'\0'};

  jim_util_get_string(payload, "memberId", member_id);
  jim_util_get_string(payload, "memberType", member_type);

  if (member_id[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_MEMBER_ID, ERRMSG_PARAM_NO_MEMBER_ID);
    return;
  }
  if (member_type[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_MEMBER_TYPE, ERRMSG_PARAM_NO_MEMBER_TYPE);
    return;
  }

  void* conn = jim_db_connect(g_db);
  gfc_map_p conversation = gfc_map_new();    
  int res = jim_model_select_conversation_member(
      conn, conversations, NULL, member_id, member_type);
  if (res != ERROR_SUCCESS)
  {
    
  }
  jim_db_release(g_db, conn);
}

/*!
** 获取会话。
*/
void
gim_biz_get_conversations(ws_cli_conn_t* client,
                          json_object* payload)
{
  char member_id[1024] = {'\0'};
  char member_type[1024] = {'\0'};

  jim_util_get_string(payload, "memberId", member_id);
  jim_util_get_string(payload, "memberType", member_type);

  if (member_id[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_MEMBER_ID, ERRMSG_PARAM_NO_MEMBER_ID);
    return;
  }
  if (member_type[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_MEMBER_TYPE, ERRMSG_PARAM_NO_MEMBER_TYPE);
    return;
  }

  void* conn = jim_db_connect(g_db);
  gfc_list_p conversations = gfc_list_new();
  int res = jim_model_select_conversation_member(
      conn, conversations, NULL, member_id, member_type);
  if (res != ERROR_SUCCESS)
  {
    
  }
  jim_db_release(g_db, conn);
}

/*!
** 添加会话成员。
*/
void
gim_biz_add_conversation_member(ws_cli_conn_t* client,
                                json_object* payload)
{
  char conversation_id[1024] = {'\0'};
  char member_id[1024] = {'\0'};
  char member_type[1024] = {'\0'};

  jim_util_get_string(payload, "conversationId", conversation_id);
  jim_util_get_string(payload, "memberId", member_id);
  jim_util_get_string(payload, "memberType", member_type);

  if (conversation_id[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_CONVERSATION_ID, ERRMSG_PARAM_NO_CONVERSATION_ID);
    return;
  }
  if (member_id[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_MEMBER_ID, ERRMSG_PARAM_NO_MEMBER_ID);
    return;
  }
  if (member_type[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_MEMBER_TYPE, ERRMSG_PARAM_NO_MEMBER_TYPE);
    return;
  }

  void* conn = jim_db_connect(g_db);
  int res = jim_model_select_conversation_member(
      conn, conversations, NULL, member_id, member_type);
  if (res != ERROR_SUCCESS)
  {
    
  }
  jim_db_release(g_db, conn);
}

/*!
** 发送消息。
*/
void
gim_biz_send_message(ws_cli_conn_t* client,
                     json_object* payload)
{
  char conversation_id[1024] = {'\0'};
  char sender_id[1024] = {'\0'};
  char sender_type[1024] = {'\0'};
  char message_type[1024] = {'\0'};
  char message_content[1024] = {'\0'};

  jim_util_get_string(payload, "conversationId", conversation_id);
  jim_util_get_string(payload, "senderId", sender_id);
  jim_util_get_string(payload, "senderType", sender_type);
  jim_util_get_string(payload, "messageType", message_type);
  jim_util_get_string(payload, "messageContent", message_content);

  if (conversation_id[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_CONVERSATION_ID, ERRMSG_PARAM_NO_CONVERSATION_ID);
    return;
  }
  if (sender_id[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_SENDER_ID, ERRMSG_PARAM_NO_SENDER_ID);
    return;
  }
  if (sender_type[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_SENDER_TYPE, ERRMSG_PARAM_NO_SENDER_TYPE);
    return;
  }
  if (message_type[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_MESSAGE_TYPE, ERRMSG_PARAM_NO_MESSAGE_TYPE);
    return;
  }
  if (message_content[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_MESSAGE_CONTENT, ERRMSG_PARAM_NO_MESSAGE_CONTENT);
    return;
  }

  void* conn = jim_db_connect(g_db);
  int res = jim_model_select_conversation_member(
      conn, conversations, NULL, member_id, member_type);
  if (res != ERROR_SUCCESS)
  {
    
  }
  jim_db_release(g_db, conn);
}

/*!
** 获取会话消息。
*/
void
gim_biz_get_messages(ws_cli_conn_t* client,
                     json_object* payload)
{
  char conversation_id[1024] = {'\0'};
  char member_id[1024] = {'\0'};
  char member_type[1024] = {'\0'};
  char last_conversation_time[1024] = {'\0'};

  jim_util_get_string(payload, "conversationId", conversation_id);
  jim_util_get_string(payload, "memberId", member_id);
  jim_util_get_string(payload, "memberType", member_type);
  jim_util_get_string(payload, "lastConversationTime", last_conversation_time);

  if (conversation_id[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_CONVERSATION_ID, ERRMSG_PARAM_NO_CONVERSATION_ID);
    return;
  }
  if (member_id[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_MEMBER_ID, ERRMSG_PARAM_NO_MEMBER_ID);
    return;
  }
  if (member_type[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_MEMBER_TYPE, ERRMSG_PARAM_NO_MEMBER_TYPE);
    return;
  }
  if (last_conversation_time[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_LAST_CONVERSATION_TIME, ERRMSG_PARAM_NO_LAST_CONVERSATION_TIME);
    return;
  }

  void* conn = jim_db_connect(g_db);
  gfc_list_p messages = gfc_list_new();
  int res = jim_model_select_conversation_member(
      conn, conversations, NULL, member_id, member_type);
  if (res != ERROR_SUCCESS)
  {
    
  }
  jim_db_release(g_db, conn);
}

void
jim_biz_login(ws_cli_conn_t* client,
              json_object* payload)
{
  // 获取用户标识
  json_object *jval = json_object_object_get(payload, "userId");
  enum json_type jtype = json_object_get_type(jval);

  if (jtype != json_type_string)
  {
    jim_biz_error(client, ERROR_UNAUTHORIZED_USER, ERRMSG_UNAUTHORIZED_USER);
    return;
  }

  const char* user_id = json_object_get_string(jval);

  // 存入用户进入缓存
  gfc_lru_set(g_sessions,
              (void*) strdup(user_id), strlen(user_id),
              client, ws_size_of_cli_conn());

  char buff[1024] = {'\0'};
  sprintf(buff, "{\"userId\":\"%s\"}", user_id);
  ws_sendframe_txt(client, buff);
}

/*!
** 客户端用户登出。
*/
void
jim_biz_logout(ws_cli_conn_t* client,
               json_object* payload)
{
  // 获取用户标识
  json_object *jval = json_object_object_get(payload, "userId");
  enum json_type jtype = json_object_get_type(jval);

  if (jtype != json_type_string)
  {
    jim_biz_error(client, ERROR_UNAUTHORIZED_USER, ERRMSG_UNAUTHORIZED_USER);
    return;
  }

  const char* user_id = json_object_get_string(jval);

  // 删除用户缓存
  gfc_lru_remove(g_sessions,
                 (void*) user_id,
                 strlen(user_id));

  ws_close_client(client);
}

/*!
** 用户发送消息。
*/
void
jim_biz_send(ws_cli_conn_t* client,
             json_object* payload)
{
  // 用户验证
  json_object *jval = json_object_object_get(payload, "userId");
  enum json_type jtype = json_object_get_type(jval);

  if (jtype != json_type_string)
  {
    jim_biz_error(client, ERROR_UNAUTHORIZED_USER, ERRMSG_UNAUTHORIZED_USER);
    return;
  }
  const char* user_id = json_object_get_string(jval);

  jval = json_object_object_get(payload, "receiverId");
  jtype = json_object_get_type(jval);

  if (jtype != json_type_string)
  {
    jim_biz_error(client, ERROR_UNAUTHORIZED_USER, ERRMSG_UNAUTHORIZED_USER);
    return;
  }
  const char* receiver_id = json_object_get_string(jval);

  ws_cli_conn_t* receiver;
  gfc_lru_get(g_sessions,
              (void*) receiver_id,
              strlen(receiver_id),
              (void**) &receiver);

  if (receiver == NULL)
  {
    printf("receiver is null\n");
    return;
  }

  jval = json_object_object_get(payload, "message");
  const char* msg = json_object_to_json_string_ext(jval, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY);
  ws_sendframe_txt(receiver, msg);
  jim_biz_success(client);
}

void
jim_biz_create_conversation(ws_cli_conn_t* client,
                            json_object* payload)
{
  char conversation_id[37] = {'\0'};
  char conversation_name[128] = {'\0'};
  char conversation_type[16] = {'\0'};

  jim_util_id(conversation_id);
}

void
jim_biz_get_conversations(ws_cli_conn_t* client,
                          json_object* payload)
{
  char member_id[128] = {'\0'};
  char member_type[128] = {'\0'};

  jim_util_get_string(payload, "memberId", member_id);
  jim_util_get_string(payload, "memberType", member_id);

  if (member_id[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_MEMBER_ID, ERRMSG_PARAM_NO_MEMBER_ID);
    return;
  }
  if (member_type[0] == '\0')
  {
    jim_biz_error(client, ERROR_PARAM_NO_MEMBER_TYPE, ERRMSG_PARAM_NO_MEMBER_TYPE);
    return;
  }

  void* conn = jim_db_connect(g_db);
  gfc_list_p conversations = gfc_list_new();
  int res = jim_model_select_conversation_member(
      conn, conversations, NULL, member_id, member_type);
  if (res != ERROR_SUCCESS)
  {

  }

  jim_db_release(g_db, conn);
}
