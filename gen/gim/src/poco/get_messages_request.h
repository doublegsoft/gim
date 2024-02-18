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
** 【获取会话消息请求】对象.
*/
@interface GetMessagesRequest : NSObject

/*!
** 【会话】属性.
*/
@property (nonatomic, strong) NSString* conversationId;

/*!
** 【成员】属性.
*/
@property (nonatomic, strong) NSString* memberId;

/*!
** 【成员类型】属性.
*/
@property (nonatomic, strong) NSString* memberType;

/*!
** 【最后会话时间】属性.
*/
@property (nonatomic, strong) NSString* lastConversationTime;
@end
