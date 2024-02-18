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
#import <Foundation/Foundation.h>

/*!
** 【会话消息信息】对象.
*/
@interface ConversationMessage : NSObject

/*!
** 【会话】属性.
*/
@property (nonatomic, strong) NSObject* conversationMessageId;

/*!
** 【会话】属性.
*/
@property (nonatomic, strong) NSObject* conversationId;

/*!
** 【发送者】属性.
*/
@property (nonatomic, strong) NSString* senderId;

/*!
** 【发送者类型】属性.
*/
@property (nonatomic, strong) NSString* senderType;

/*!
** 【接收者】属性.
*/
@property (nonatomic, strong) NSString* receiverId;

/*!
** 【接收者类型】属性.
*/
@property (nonatomic, strong) NSString* receiverType;

/*!
** 【消息时间】属性.
*/
@property (nonatomic, strong) NSObject* messageTime;

/*!
** 【消息内容】属性.
*/
@property (nonatomic, strong) NSString* messageType;

/*!
** 【消息内容】属性.
*/
@property (nonatomic, strong) NSString* messageContent;

/*!
** 【创建时间】属性.
*/
@property (nonatomic, strong) NSObject* createTime;

/*!
** 【附加选项】属性.
*/
@property (nonatomic, strong) NSString* status;
@end
