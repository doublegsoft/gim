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

#ifndef __GIM_BIZ_H__
#define __GIM_BIZ_H__

#include <ws.h>
#include <json.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OP_ERROR                       "error"
#define OP_LOGIN                       "login"
#define OP_LOGOUT                      "logout"
#define OP_CREATE_CONVERSATION         "createConversation"
#define OP_GET_CONVERSATIONS           "getConversations"
#define OP_ADD_CONVERSATION_MEMBER     "addConversationMember"
#define OP_SEND_MESSAGE                "sendMessage"
#define OP_GET_MESSAGES                "getMessages"

/*!
** 发送错误信息给客户端。
*/
void
gim_biz_error(ws_cli_conn_t*   client,
              const char*      op,
              int              error,
              const char*      message);

/*!
** 发送成功信息给客户端。
*/
void
gim_biz_success(ws_cli_conn_t* client,
                const char*      op);

/*!
** 登录。
*/
void
gim_biz_login(ws_cli_conn_t* client,
              json_object* payload);

/*!
** 登出。
*/
void
gim_biz_logout(ws_cli_conn_t* client,
               json_object* payload);

/*!
** 创建会话。
*/
void
gim_biz_create_conversation(ws_cli_conn_t* client,
                            json_object* payload);

/*!
** 获取会话。
*/
void
gim_biz_get_conversations(ws_cli_conn_t* client,
                          json_object* payload);

/*!
** 添加会话成员。
*/
void
gim_biz_add_conversation_member(ws_cli_conn_t* client,
                                json_object* payload);

/*!
** 发送消息。
*/
void
gim_biz_send_message(ws_cli_conn_t* client,
                     json_object* payload);

/*!
** 获取会话消息。
*/
void
gim_biz_get_messages(ws_cli_conn_t* client,
                     json_object* payload);

#ifdef __cplusplus
}
#endif

#endif // __GIM_BIZ_H__
