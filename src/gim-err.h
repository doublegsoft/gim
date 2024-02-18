/*
**     o8o  o8o
**     `"'  `"'
**    oooo oooo  ooo. .oo.  .oo.
**    `888 `888  `888P"Y88bP"Y88b
**     888  888   888   888   888
**     888  888   888   888   888
**     888 o888o o888o o888o o888o
**     888
** .o. 88P
** `Y888P
*/

#define ERROR_SUCCESS                                 0
#define ERRMSG_SUCCESS                                "成功"
#define ERROR_MESSAGE_FORMAT                          40001
#define ERRMSG_MESSAGE_FORMAT                         "错误的消息格式"
#define ERROR_UNKNOWN_OPERATION                       40101
#define ERRMSG_UNKNOWN_OPERATION                      "未知的操作指令"
#define ERROR_NO_PAYLOAD                              40102
#define ERRMSG_NO_PAYLOAD                             "没有业务数据载体"
#define ERROR_UNAUTHORIZED_USER                       40103
#define ERRMSG_UNAUTHORIZED_USER                      "未授权的用户"
#define ERROR_NO_USER_ID                              40104
#define ERRMSG_NO_USER_ID                             "没有用户标识"
#define ERROR_NO_USER_TYPE                            40105
#define ERRMSG_NO_USER_TYPE                           "没有用户类型"

#define ERROR_PARAM_NO_MEMBER_ID                      40201
#define ERRMSG_PARAM_NO_MEMBER_ID                     "参数中没有成员标识"
#define ERROR_PARAM_NO_MEMBER_TYPE                    40202
#define ERRMSG_PARAM_NO_MEMBER_TYPE                   "参数中没有成员类型"
#define ERROR_PARAM_NOT_ENOUGH_MEMBERS                40203
#define ERRMSG_PARAM_NOT_ENOUGH_MEMBERS               "参数中没有足够的成员"
#define ERROR_PARAM_NO_CONVERSATION                   40304
#define ERRMSG_PARAM_NO_CONVERSATION                  "参数中没有会话相关信息，即没有会话标识也没有接收者的标识"
#define ERROR_PARAM_NO_CONVERSATION_ID                40204
#define ERRMSG_PARAM_NO_CONVERSATION_ID               "参数中没有会话标识"
#define ERROR_PARAM_NO_MESSAGE_TYPE                   40205
#define ERRMSG_PARAM_NO_MESSAGE_TYPE                  "参数中没有消息类型"
#define ERROR_PARAM_NO_MESSAGE_CONTENT                40206
#define ERRMSG_PARAM_NO_MESSAGE_CONTENT               "参数中没有消息内容"
#define ERROR_PARAM_NO_CONVERSATION_TYPE              40207
#define ERRMSG_PARAM_NO_CONVERSATION_TYPE             "参数中没有会话类型"
#define ERROR_PARAM_UNKNOWN_CONVERSATION_TYPE         40208
#define ERRMSG_PARAM_UNKNOWN_CONVERSATION_TYPE        "未知的会话类型"
#define ERROR_PARAM_NO_SENDER_ID                      40209
#define ERRMSG_PARAM_NO_SENDER_ID                     "参数中没有发送者标识"
#define ERROR_PARAM_NO_SENDER_TYPE                    40210
#define ERRMSG_PARAM_NO_SENDER_TYPE                   "参数中没有发送者类型"
#define ERROR_PARAM_UNKNOWN_MESSAGE_TYPE              40211
#define ERRMSG_PARAM_UNKNOWN_MESSAGE_TYPE             "未知的消息类型"
#define ERROR_PARAM_NO_CONVERSATION_NAME              40212
#define ERRMSG_PARAM_NO_CONVERSATION_NAME             "参数中没有会话名称"

#define ERROR_DB_COMMON                               40306
#define ERRMSG_DB_COMMON                              "数据库处理错误"

#define ERROR_BIZ_ILLEGAL_MEMBER                      40401
#define ERRMSG_BIZ_ILLEGAL_MEMBER                     "非法的会话成员"

#define ERROR_JSON_NOT_FOUND                          40501
#define ERRMSG_JSON_NOT_FOUND                         "非字符串数据"
#define ERROR_JSON_NOT_STRING_TYPE                    40502
#define ERRMSG_JSON_NOT_STRING_TYPE                   "非字符串数据"
#define ERROR_JSON_NOT_INT_TYPE                       40503
#define ERRMSG_JSON_NOT_INT_TYPE                      "非整型数据"
#define ERROR_JSON_NOT_ARRAY_TYPE                     40504
#define ERRMSG_JSON_NOT_ARRAY_TYPE                    "非数组数据"