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
** 【会话信息】对象.
*/
@interface Conversation : NSObject

/*!
** 【会话】属性.
*/
@property (nonatomic, strong) NSObject* conversationId;

/*!
** 【会话名称】属性.
*/
@property (nonatomic, strong) NSString* conversationName;

/*!
** 【会话类型】属性.
*/
@property (nonatomic, strong) NSString* conversationType;

/*!
** 【附加信息】属性.
*/
@property (nonatomic, strong) NSObject* options;

/*!
** 【业务状态】属性.
*/
@property (nonatomic, strong) NSString* status;
@end
