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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>

#include <json.h>
#include <ws.h>
//#include <libwebsockets.h>
#include <gfc.h>

#include "ini.h"
#include "gim-err.h"
#include "gim-biz.h"
#include "gim-db.h"
#include "gim-util.h"

/*!
** 保持的最多会话数量。
*/
#define MAX_LRU_CACHE_SIZE        1024 * 100000
#define MAX_SESSION_NUMBER        100000

/*!
** 数据库连接
*/
gim_db_p    g_db;
/*!
** 活跃用户缓存
*/
gfc_lru_p   g_sessions;

/*!
** 数据库配置的数据结构。
*/
typedef struct gim_conf_db_s
{
  /*!
  ** 数据库地址。
  */
  const char*     address;

  /*!
  ** 数据库端口。
  */
  int             port;

  /*!
  ** 数据库名称。
  */
  const char*     name;

  /*!
  ** 用户名。
  */
  const char*     username;

  /*!
  ** 密码。
  */
  const char*     password;
}
gim_conf_db_t;

typedef struct gim_conf_app_s
{
  /*!
  ** 应用程序端口。
  */
  int             port;
}
gim_conf_app_t;

/*!
** 应用程序配置的数据结构。
*/
typedef struct gim_conf_s
{
  gim_conf_db_t*    db;

  gim_conf_app_t*   app;
}
gim_conf_t;

void
gim_sys_usage(void)
{
  struct rusage usage;
  int ret;
  ret = getrusage(RUSAGE_SELF, &usage);
  gfc_log_info("memory usage: %ld kb", usage.ru_maxrss / 1024);
}

void
gim_mem_usage(void)
{
  gfc_log_info("%d blocks allocated memory usage: %ld kb", gfc_gc_length(), gfc_gc_total() / 1024);
}

/**
 * @brief Called when a client connects to the server.
 *
 * @param client Client connection. The @p client parameter is used
 * in order to send messages and retrieve informations about the
 * client.
 */
static void
gim_ws_open(ws_cli_conn_t* client)
{
  char date[1024];
  gim_util_now(date);
  printf("%s open: %d\n", date, client->client_sock);
}

/**
 * @brief Called when a client disconnects to the server.
 *
 * @param client Client connection. The @p client parameter is used
 * in order to send messages and retrieve informations about the
 * client.
 */
static void
gim_ws_close(ws_cli_conn_t* client)
{
  char date[1024];
  gim_util_now(date);
  printf("%s closed: %d\n", date, client->client_sock);
//  const char* session_id = ws_get_session_id(client);
//  gfc_lru_remove(g_sessions,
//                 session_id,
//                 strlen(session_id));
}

/*!
** 处理客户端发送的消息，消息必须为JSON格式，否则返回{@code ERROR_UNKNOWN_FORMAT}
** 错误信息给客户端，具体操作包括登录，发送，
*/
static void
gim_ws_message(ws_cli_conn_t* client,
               const unsigned char* msg,
               uint64_t size,
               int type)
{
  if (msg == NULL)
    return;

  gfc_log_info("received: %s", msg);

  json_object*        jval        = NULL;
  enum json_type      jtype;
  json_object*        jobj        = json_tokener_parse((const char*) msg);
  char*               operation   = NULL;
  char                user_id[128] = {'\0'};
  char                user_type[128] = {'\0'};

  if (jobj == NULL)
  {
    json_object_put(jobj);
    gim_biz_error(client,
                  OP_ERROR,
                  ERROR_MESSAGE_FORMAT,
                  ERRMSG_MESSAGE_FORMAT);
    return;
  }

  jval = json_object_object_get(jobj, "operation");
  jtype = json_object_get_type(jval);
  if (jtype != json_type_string)
  {
    json_object_put(jobj);
    gim_biz_error(client,
                  OP_ERROR,
                  ERROR_UNKNOWN_OPERATION,
                  ERRMSG_UNKNOWN_OPERATION);
    return;
  }
  operation = (char*) json_object_get_string(jval);

  jval = json_object_object_get(jobj, "userId");
  jtype = json_object_get_type(jval);
  if (jtype != json_type_string)
  {
    json_object_put(jobj);
    gim_biz_error(client,
                  OP_ERROR,
                  ERROR_UNAUTHORIZED_USER,
                  ERRMSG_UNAUTHORIZED_USER);
    return;
  }
  strcpy(user_id, (char*) json_object_get_string(jval));

  jval = json_object_object_get(jobj, "userType");
  jtype = json_object_get_type(jval);
  if (jtype != json_type_string)
  {
    json_object_put(jobj);
    gim_biz_error(client,
                  OP_ERROR,
                  ERROR_UNAUTHORIZED_USER,
                  ERRMSG_UNAUTHORIZED_USER);
    return;
  }
  strcpy(user_type, (char*) json_object_get_string(jval));

  jval = json_object_object_get(jobj, "payload");
  if (jval == NULL)
  {
    json_object_put(jobj);
    gim_biz_error(client,
                  OP_ERROR,
                  ERROR_NO_PAYLOAD,
                  ERRMSG_NO_PAYLOAD);
    return;
  }
  json_object* payload = jval;
  if (strcmp(operation, OP_LOGIN) == 0)
    gim_biz_login(client, user_id, user_type, payload);
  else if (strcmp(operation, OP_LOGOUT) == 0)
    gim_biz_logout(client, user_id, user_type, payload);
  else if (strcmp(operation, OP_SEND_MESSAGE) == 0)
    gim_biz_send_message(client, user_id, user_type, payload);
  else if (strcmp(operation, OP_GET_MESSAGES) == 0)
    gim_biz_get_messages(client, user_id, user_type, payload);
  else if (strcmp(operation, OP_GET_CONVERSATIONS) == 0)
    gim_biz_get_conversations(client, user_id, user_type, payload);
  else if (strcmp(operation, OP_CREATE_CONVERSATION) == 0)
    gim_biz_create_conversation(client, user_id, user_type, payload);
  else if (strcmp(operation, OP_ADD_CONVERSATION_MEMBER) == 0)
    gim_biz_add_conversation_member(client, user_id, user_type, payload);
  else
    gim_biz_error(client,
                  OP_ERROR,
                  ERROR_UNKNOWN_OPERATION,
                  ERRMSG_UNKNOWN_OPERATION);

  // release json object resource
  json_object_put(jobj);

  gim_mem_usage();
  gim_sys_usage();
}

//static int
//gim_ws_message2(struct lws *wsi, enum lws_callback_reasons reason,
//                 void *user, void *in, size_t len)
//{
//
//}

/*!
** 读取ini配置文件。
*/
static int
gim_ini_read(void* user,
             const char* section,
             const char* name,
             const char* value)
{
  gim_conf_t* conf = (gim_conf_t*) user;

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0
  if (MATCH("database", "address"))
  {
    conf->db->address = strdup(value);
  } else if (MATCH("database", "port"))
  {
    conf->db->port = atoi(value);
  } else if (MATCH("database", "name"))
  {
    conf->db->name = strdup(value);
  } else if (MATCH("database", "username"))
  {
    conf->db->username = strdup(value);
  } else if (MATCH("database", "password"))
  {
    conf->db->password = strdup(value);
  } else if (MATCH("application", "port"))
  {
    conf->app->port = atoi(value);
  } else {
    return 0;
  }
  return 1;
}

/*!
** 主程序。
*/
int main(void)
{
  // 日志文件
  gfc_log_init("log", "gim");
  // 内存管理
  gfc_gc_init();

  // 配置文件
  gim_conf_t conf;
  conf.db = (gim_conf_db_t*) gfc_gc_malloc(sizeof(gim_conf_db_t), 1);
  conf.app = (gim_conf_app_t*) gfc_gc_malloc(sizeof(gim_conf_app_t), 1);

  if (ini_parse("conf/gim.conf", gim_ini_read, &conf) < 0)
  {
    printf("failed to read conf/gim.conf.\n");
    return 1;
  }

  g_sessions = gfc_lru_new(MAX_LRU_CACHE_SIZE, MAX_SESSION_NUMBER);

  gfc_log_info("\n%s",
      "            o8o                      \n"
      "            `\"'                     \n"
      " .oooooooo oooo  ooo. .oo.  .oo.     \n"
      "888' `88b  `888  `888P\"Y88bP\"Y88b  \n"
      "888   888   888   888   888   888    \n"
      "`88bod8P'   888   888   888   888    \n"
      "`8oooooo.  o888o o888o o888o o888o   \n"
      "d\"     YD                           \n"
      " Y88888P'                            \n");

  gfc_log_info("listening port: %d", conf.app->port);

  gim_db_create(&g_db,
                conf.db->address,
                conf.db->port,
                conf.db->username,
#ifdef __APPLE__
                "ganguo",
#else
                "sdic@cqffc2803",
#endif
                conf.db->name,
                8);

  struct ws_events evs;
  evs.onopen    = &gim_ws_open;
  evs.onclose   = &gim_ws_close;
  evs.onmessage = &gim_ws_message;
  ws_socket(&evs, conf.app->port, 0, 1000);

  // release resources
  gfc_gc_free(conf.db);
  gfc_gc_free(conf.app);

  gim_db_destroy(g_db);
  gfc_lru_free(g_sessions);

  return 0;
}