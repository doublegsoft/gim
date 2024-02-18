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

#ifndef __gim_DB_H__
#define __gim_DB_H__

#include <stdlib.h>
#include <json.h>
#include <gfc.h>

#include "gim-err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct  gim_db_s   gim_db_t;
typedef         gim_db_t*  gim_db_p;

/*!
** 打开一个数据库连接。
**
** @param address
**        数据库地址
**
** @param port
**        数据库端口
**
** @param username
**        用户名
**
** @param password
**        密码
**
** @param dbname
**        数据库名称
**
** @param max_connections
**        最大连接数
**
** @return 0为成功，非0为错误代码
*/
int
gim_db_create(gim_db_p*         pdb,
              const char*  address, 
              int          port, 
              const char*  username, 
              const char*  password,
              const char*  dbname,
              int          max_connections);

/*!
** 获取一个数据库连接。
**
** @param db
**        数据库连接池实例
*/
void*
gim_db_connect(gim_db_p db);

/*!
** 释放数据库连接给连接池。
**
** @param conn
**        数据库连接
*/
void
gim_db_release(gim_db_p db,
               void* conn);

/*!
** 销毁数据库连接池，回收内存资源。
*/
void
gim_db_destroy(gim_db_p db);

/*!
** 查询返回多条数据。
*/
int
gim_db_many(void*         conn_inst,
            char*         errmsg,
            gfc_list_p    holder,
            const char*   sql);

#ifdef __cplusplus
}
#endif

#endif // __gim_DB_H__
