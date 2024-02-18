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
** 【获取会话请求】对象.
*/
@interface GetConversationsRequest : NSObject

/*!
** 【成员】属性.
*/
@property (nonatomic, strong) NSString* memberId;

/*!
** 【成员类型】属性.
*/
@property (nonatomic, strong) NSString* memberType;
@end
