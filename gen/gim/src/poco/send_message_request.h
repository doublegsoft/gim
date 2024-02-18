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
** 【发送消息请求】对象.
*/
@interface SendMessageRequest : NSObject

/*!
** 【会话】属性.
*/
@property (nonatomic, strong) NSString* conversationId;

/*!
** 【发送成员】属性.
*/
@property (nonatomic, strong) NSString* senderId;

/*!
** 【发送成员类型】属性.
*/
@property (nonatomic, strong) NSString* senderType;

/*!
** 【消息类型】属性.
*/
@property (nonatomic, strong) NSString* messageType;

/*!
** 【消息内容】属性.
*/
@property (nonatomic, strong) NSString* messageContent;
@end
