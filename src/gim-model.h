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

#ifndef __GIM_MODEL_H__
#define __GIM_MODEL_H__

#include <json.h>
#include <gfc.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!
** 创建【会话信息】数据。
*/
int
gim_model_create_conversation(void*        conn_inst,
                              char*        errmsg,
                              const char*  id,
                              const char*  name,
                              const char*  type,
                              const char*  options,
                              const char*  status);

/*!
** 删除【会话信息】数据。
*/
int
gim_model_delete_conversation(void*        conn_inst,
                              char*        errmsg,              
                              const char*  id);

/*!
** 更新【会话信息】中【业务状态】数据。
*/
int
gim_model_update_conversation_status(void*        conn_inst,
                               char*        errmsg,
                                     const char*  id,
                                     const char*  status);      

/*!
** 查询【会话信息】数据。
*/
int
gim_model_select_conversation(void*        conn_inst,
                              char*        errmsg,
                              gfc_list_p   list,
                              const char*  ,
                              const char*  ,
                              const char*  ,
                              const char*  ,
                              const char*  suffix);

/*!
** 创建【会话成员信息】数据。
*/
int
gim_model_create_conversation_member(void*        conn_inst,
                                     char*        errmsg,
                                     const char*  conversation,
                                     const char*  member_id,
                                     const char*  member_type,
                                     const char*  alias,
                                     int          unread_count,
                                     const char*  last_conversation_time,
                                     const char*  joined_time,
                                     const char*  leave_time,
                                     const char*  status);

/*!
** 删除【会话成员信息】数据。
*/
int
gim_model_delete_conversation_member(void*        conn_inst,
                                     char*        errmsg,              
                                     const char*  conversation,
                                     const char*  member_id,
                                     const char*  member_type);

/*!
** 更新【会话成员信息】中【未读消息数量】数据。
*/
int
gim_model_update_conversation_member_unread_count(void*        conn_inst,
                                      char*        errmsg,
                                                  const char*  conversation,
                                                  const char*  member_id,
                                                  const char*  member_type,
                                                  int          unread_count);      

/*!
** 更新【会话成员信息】中【最近会话时间】数据。
*/
int
gim_model_update_conversation_member_last_conversation_time(void*        conn_inst,
                                      char*        errmsg,
                                                            const char*  conversation,
                                                            const char*  member_id,
                                                            const char*  member_type,
                                                            const char*  last_conversation_time);      

/*!
** 更新【会话成员信息】中【离开时间】数据。
*/
int
gim_model_update_conversation_member_leave_time(void*        conn_inst,
                                      char*        errmsg,
                                                const char*  conversation,
                                                const char*  member_id,
                                                const char*  member_type,
                                                const char*  leave_time);      

/*!
** 更新【会话成员信息】中【业务状态】数据。
*/
int
gim_model_update_conversation_member_status(void*        conn_inst,
                                      char*        errmsg,
                                            const char*  conversation,
                                            const char*  member_id,
                                            const char*  member_type,
                                            const char*  status);      

/*!
** 查询【会话成员信息】数据。
*/
int
gim_model_select_conversation_member(void*        conn_inst,
                                     char*        errmsg,
                                     gfc_list_p   list,
                                     const char*  ,
                                     const char*  ,
                                     const char*  ,
                                     const char*  ,
                                     const char*  suffix);

/*!
** 创建【会话消息信息】数据。
*/
int
gim_model_create_conversation_message(void*        conn_inst,
                                      char*        errmsg,
                                      const char*  id,
                                      const char*  conversation,
                                      const char*  sender_id,
                                      const char*  sender_type,
                                      const char*  receiver_id,
                                      const char*  receiver_type,
                                      const char*  message_time,
                                      const char*  message_type,
                                      const char*  message_content,
                                      const char*  create_time,
                                      const char*  status);

/*!
** 更新【会话消息信息】中【附加选项】数据。
*/
int
gim_model_update_conversation_message_status(void*        conn_inst,
                                       char*        errmsg,
                                             const char*  id,
                                             const char*  status);      

/*!
** 查询【会话消息信息】数据。
*/
int
gim_model_select_conversation_message(void*        conn_inst,
                                      char*        errmsg,
                                      gfc_list_p   list,
                                      const char*  ,
                                      const char*  message_time0,
                                      const char*  message_time1,
                                      const char*  suffix);

#ifdef __cplusplus
}
#endif

#endif // __GIM_MODEL_H__
