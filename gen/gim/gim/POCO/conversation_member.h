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
** 【会话成员信息】对象.
*/
@interface ConversationMember : NSObject

/*!
** 【会话】属性.
*/
@property (nonatomic, strong) NSObject* conversationId;

/*!
** 【成员】属性.
*/
@property (nonatomic, strong) NSString* memberId;

/*!
** 【成员类型】属性.
*/
@property (nonatomic, strong) NSString* memberType;

/*!
** 【会话别名】属性.
*/
@property (nonatomic, strong) NSString* alias;

/*!
** 【未读消息数量】属性.
*/
@property (nonatomic, strong) NSInteger unreadCount;

/*!
** 【最近会话时间】属性.
*/
@property (nonatomic, strong) NSObject* lastConversationTime;

/*!
** 【加入时间】属性.
*/
@property (nonatomic, strong) NSObject* joinedTime;

/*!
** 【离开时间】属性.
*/
@property (nonatomic, strong) NSObject* leaveTime;

/*!
** 【业务状态】属性.
*/
@property (nonatomic, strong) NSString* status;
@end
