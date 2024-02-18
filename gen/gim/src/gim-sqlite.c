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

#include <stdio.h>
#include <sqlite3.h>
#include <pthread.h>

#include <gfc.h>

#include "gim-err.h"
#include "gim-db.h"
#include "gim-model.h"

extern jim_db_p         g_db;
/*!
** 【会话信息】的语句。
*/
#define SQL_INSERT_TN_GIM_CONVO    "insert into tn_gim_convo (convoid,convonm,convotyp,opt,sts)" \
                                   "values (?,?,?,?,?);"

#define SQL_DELETE_TN_GIM_CONVO    "delete from tn_gim_convo " \
                                   "where 1 = 1 "

#define SQL_UPDATE_TN_GIM_CONVO_STS    "update tn_gim_convo " \
                                       "set sts = ? " \
                                       "where 1 = 1 " \
                                       "and convoid = ? " \
                                       ";"

#define SQL_SELECT_TN_GIM_CONVO    "select " \
                                   "convo.convoid conversationId, " \
                                   "convo.convonm conversationName, " \
                                   "convo.convotyp conversationType, " \
                                   "convo.opt options, " \
                                   "convo.sts status, " \
                                   "0 " \
                                   "from tn_gim_convo convo " \
                                   "where 1 = 1 "
/*!
** 【会话成员信息】的语句。
*/
#define SQL_INSERT_TV_GIM_CONVOMBR    "insert into tv_gim_convombr (convoid,mbrid,mbrtyp,als,unrdcnt,lct,jdtm,lvtm,sts)" \
                                      "values (?,?,?,?,?,?,?,?,?);"

#define SQL_DELETE_TV_GIM_CONVOMBR    "delete from tv_gim_convombr " \
                                      "where 1 = 1 "

#define SQL_UPDATE_TV_GIM_CONVOMBR_UNRDCNT    "update tv_gim_convombr " \
                                              "set unrdcnt = coalesce(unrdcnt,0)+1 " \
                                              "where 1 = 1 " \
                                              "and convoid = ? " \
                                              "and mbrid = ? " \
                                              "and mbrtyp = ? " \
                                              ";"

#define SQL_UPDATE_TV_GIM_CONVOMBR_UNRDCNT_RESET    "update tv_gim_convombr " \
                                                    "set unrdcnt = 0 " \
                                                    "where 1 = 1 " \
                                                    "and convoid = ? " \
                                                    "and mbrid = ? " \
                                                    "and mbrtyp = ? " \
                                                    ";"

#define SQL_UPDATE_TV_GIM_CONVOMBR_LCT    "update tv_gim_convombr " \
                                          "set lct = current_timestamp " \
                                          "where 1 = 1 " \
                                          "and convoid = ? " \
                                          "and mbrid = ? " \
                                          "and mbrtyp = ? " \
                                          ";"

#define SQL_UPDATE_TV_GIM_CONVOMBR_LVTM    "update tv_gim_convombr " \
                                           "set lvtm = current_timestamp " \
                                           "where 1 = 1 " \
                                           "and convoid = ? " \
                                           "and mbrid = ? " \
                                           "and mbrtyp = ? " \
                                           ";"

#define SQL_UPDATE_TV_GIM_CONVOMBR_STS    "update tv_gim_convombr " \
                                          "set sts = ? " \
                                          "where 1 = 1 " \
                                          "and convoid = ? " \
                                          "and mbrid = ? " \
                                          "and mbrtyp = ? " \
                                          ";"

#define SQL_SELECT_TV_GIM_CONVOMBR    "select " \
                                      "convombr.convoid conversationId, " \
                                      "convombr.mbrid memberId, " \
                                      "convombr.mbrtyp memberType, " \
                                      "convombr.als alias, " \
                                      "convombr.unrdcnt unreadCount, " \
                                      "convombr.lct lastConversationTime, " \
                                      "convombr.jdtm joinedTime, " \
                                      "convombr.lvtm leaveTime, " \
                                      "convombr.sts status, " \
                                      "convoid_convo.convonm conversationName, " \
                                      "convoid_convo.convotyp conversationType, " \
                                      "convoid_convo.sts conversationStatus, " \
                                      "0 " \
                                      "from tv_gim_convombr convombr " \
                                      "left join tn_gim_convo convoid_convo on convoid_convo.convoid = convombr.convoid " \
                                      "where 1 = 1 "
/*!
** 【会话消息信息】的语句。
*/
#define SQL_INSERT_TN_GIM_CONVOMSG    "insert into tn_gim_convomsg (convomsgid,convoid,sndrid,sndrtyp,rcvrid,rcvrtyp,msgtm,msgtyp,msgcont,crttm,sts)" \
                                      "values (?,?,?,?,?,?,?,?,?,?,?);"

#define SQL_DELETE_TN_GIM_CONVOMSG    "delete from tn_gim_convomsg " \
                                      "where 1 = 1 "

#define SQL_UPDATE_TN_GIM_CONVOMSG_STS    "update tn_gim_convomsg " \
                                          "set sts = ? " \
                                          "where 1 = 1 " \
                                          "and convomsgid = ? " \
                                          ";"

#define SQL_SELECT_TN_GIM_CONVOMSG    "select " \
                                      "convomsg.convomsgid conversationMessageId, " \
                                      "convomsg.convoid conversationId, " \
                                      "convomsg.sndrid senderId, " \
                                      "convomsg.sndrtyp senderType, " \
                                      "convomsg.rcvrid receiverId, " \
                                      "convomsg.rcvrtyp receiverType, " \
                                      "convomsg.msgtm messageTime, " \
                                      "convomsg.msgtyp messageType, " \
                                      "convomsg.msgcont messageContent, " \
                                      "convomsg.crttm createTime, " \
                                      "convomsg.sts status, " \
                                      "convoid_convo.convonm conversationName, " \
                                      "convoid_convo.convotyp conversationType, " \
                                      "convoid_convo.sts conversationStatus, " \
                                      "0 " \
                                      "from tn_gim_convomsg convomsg " \
                                      "left join tn_gim_convo convoid_convo on convoid_convo.convoid = convomsg.convoid " \
                                      "where 1 = 1 "

struct gim_db_s
{
  int max_connections;

  int active_connections;

  void**  connections;

  pthread_mutex_t   mutex;

  pthread_cond_t    cond;
};

int
gim_db_create(gim_db_p*    pdb, 
              const char*  address, 
              int          port, 
              const char*  username, 
              const char*  password,
              const char*  dbname,
              int          max_connections)
{
  int         ret = ERROR_SUCCESS;
  sqlite3*    conn;

  sqlite3_open(address, &conn, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

  *pdb = (gim_db_p) malloc(sizeof(gim_db_t));
  (*pdb)->max_connections = max_connections;
  (*pdb)->connections = &conn;
  (*pdb)->active_connections = 0;

  pthread_mutex_init(&((*pdb)->mutex), NULL);
  pthread_cond_init(&((*pdb)->cond), NULL);

  return ret;
}

void*
gim_db_connect(gim_db_p db)
{
  void* ret = NULL;
  pthread_mutex_lock(&db->mutex);
  if (db->active_connections >= db->max_connections) 
    pthread_cond_wait(&db->cond, &db->mutex);
  db->active_connections++;
  ret = db->connections[0];
  pthread_mutex_unlock(&db->mutex);
  return ret;
}

void
gim_db_release(gim_db_p   db,
                  void*  conn)
{
  int i = 0;
  pthread_mutex_lock(&db->mutex);
  if (db->active_connections >= db->max_connections) 
  {
    pthread_cond_signal(&db->cond);
  }
  db->active_connections--;
  pthread_mutex_unlock(&db->mutex);
}

void
gim_db_destroy(gim_db_p db)
{
  if (db == NULL) return;
  
  sqlite3* conn = (sqlite3*) db->connections[i];
  sqlite3_close(conn);

  free(db);
}

int
gim_db_many(void*         conn_inst,
            char*         errmsg,
            gfc_list_p    holder,
            const char*   sql)
{
  int           ret           = ERROR_SUCCESS;
  MYSQL*        conn          = (MYSQL*) conn_inst;
  MYSQL_RES*    result        = NULL;
  MYSQL_FIELD*  field;
  MYSQL_ROW     row;
  uint          i;

  ret = mysql_query(conn, sql);
  if (ret)
  {
    sprintf(errmsg, "%s", mysql_error(conn));
    goto RELEASE;
  }
  result = mysql_store_result(conn);
  if (result != NULL)
  {
    while ((row = mysql_fetch_row (result)) != NULL)
    {
      gfc_map_p row_obj = gfc_map_new();
      for (i = 0; i < mysql_num_fields(result); i++)
      {
        field = mysql_fetch_field(result);
        if (field->type == MYSQL_TYPE_STRING ||
            field->type == MYSQL_TYPE_VAR_STRING ||
            field->type == MYSQL_TYPE_VARCHAR)
            gfc_map_put(row_obj, field->name, strdup(row[i]));
        else
          gfc_map_put(row_obj, field->name, row[i]);
      }
      gfc_list_append(holder, row_obj);
    }
  }

RELEASE:

  if (result != NULL)
    mysql_free_result(result);

  return ret;
}

int
gim_model_create_conversation(void*        conn_inst,
                              char*        errmsg,
                              const char*  id,
                              const char*  name,
                              const char*  type,
                              const char*  options,
                              const char*  status)
{
  sqlite3*        conn    = (sqlite3*) conn_inst;
  sqlite3_stmt*   stmt    = NULL;
  int             res     = ERROR_SUCCESS;  

  res = sqlite3_prepare_v3(db, 
                           SQL_INSERT_TN_GIM_CONVO, 
                           -1, 
                           0, 
                           &stmt, 
                           NULL);
  if (res)
  {
    sprintf(errmsg, "%s", sqlite3_errmsg(conn));
    goto RELEASE;
  }

  // 【会话】
  sqlite3_bind_text(stmt, 1, conversationId, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【会话名称】
  sqlite3_bind_text(stmt, 2, conversationName, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【会话类型】
  sqlite3_bind_text(stmt, 3, conversationType, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【附加信息】
  sqlite3_bind_text(stmt, 4, options, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【业务状态】
  sqlite3_bind_text(stmt, 5, status, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  

  res = sqlite3_step(stmt);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

RELEASE:

  if (stmt != NULL)
    sqlite3_finalize(stmt);

  return res;
}

int
gim_model_delete_conversation(void*        conn_inst,
                              char*        errmsg,
                              const char*  id)
{
  sqlite3*        conn    = (sqlite3*) conn_inst;
  sqlite3_stmt*   stmt    = NULL;
  int             res     = ERROR_SUCCESS;  

  gfc_string_p sql = gfc_string_new(SQL_DELETE_TN_GIM_CONVO);
  if (id != NULL) 
  {
    gfc_string_concat(sql, "and convoid = ? ");
    param_count++;
  }

  res = sqlite3_prepare_v3(db, 
                           sql->buffer, 
                           -1, 
                           0, 
                           &stmt, 
                           NULL);
  if (res)
  {
    sprintf(errmsg, "%s", sqlite3_errmsg(conn));
    goto RELEASE;
  }

  if (id != NULL) 
  {
    lengths[param_index] = strlen(id);
    params[param_index].buffer_type = MYSQL_TYPE_STRING;
    params[param_index].buffer = (char *) id;
    params[param_index].length = &lengths[param_index];
    params[param_index].is_null = 0;
    param_index++;
  }

  res = mysql_stmt_bind_param(stmt, params);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  res = mysql_stmt_execute(stmt);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

RELEASE:

  mysql_stmt_close(stmt);
  gfc_string_free(sql);
  if (params != NULL)
    free(params);
  if (lengths != NULL)
    free(lengths);

  return res;
}
      
/*!
** 更新【会话信息】中【业务状态】数据。
*/
int
gim_model_update_conversation_status(void*        conn_inst,
                               char*        errmsg,
                                     const char*  id,
                                     const char*  status)
{
  MYSQL*        conn = (MYSQL*) conn_inst;
  MYSQL_STMT*   stmt;
  MYSQL_BIND    params[2];
  ulong         lengths[2];    
  int           param_index = 0;
  int           res         = ERROR_SUCCESS;
  
  stmt    = mysql_stmt_init(conn);
  
  res = mysql_stmt_prepare(stmt, 
                           SQL_UPDATE_TN_GIM_CONVO_STS, 
                           strlen(SQL_UPDATE_TN_GIM_CONVO_STS));
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  memset(params, 0, sizeof(params)); 
  lengths[param_index] = strlen(status);
  params[param_index].buffer_type = MYSQL_TYPE_STRING;
  params[param_index].buffer = (char *) status;   
  params[param_index].length = &lengths[param_index];
  params[param_index].is_null = 0;   
  param_index++;     
  lengths[param_index] = strlen(id);
  params[param_index].buffer_type = MYSQL_TYPE_STRING;
  params[param_index].buffer = (char *) id;
  params[param_index].length = &lengths[param_index];
  params[param_index].is_null = 0;   
  param_index++;       
  
  res = mysql_stmt_bind_param(stmt, params);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  res = mysql_stmt_execute(stmt);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

RELEASE:

  mysql_stmt_close(stmt);  

  return res;
} 

int
gim_model_select_conversation(void*        conn_inst,
                              char*        errmsg,
                              gfc_list_p   list,
                              const char*  id,
                              const char*  name,
                              const char*  type,
                              const char*  status)
{
  int           res  = ERROR_SUCCESS;
  MYSQL*        conn = (MYSQL*) conn_inst;
  MYSQL_STMT*   stmt;
  MYSQL_BIND*   params;
  MYSQL_BIND    binds[6];
  MYSQL_FIELD*  field;
  MYSQL_ROW     row;
  MYSQL_RES*    result;
  ulong*        lengths;
  ulong         bindlens[6];
  bool          is_nulls[6];
  int           param_count = 0;
  int           param_index = 0;
  int           i = 0;
  stmt = mysql_stmt_init(conn);

  gfc_string_p sql = gfc_string_new(SQL_SELECT_TN_GIM_CONVO);
  if (id != NULL) 
  {
    gfc_string_concat(sql, "and convo.convoid = ? ");
    param_count++;
  }
  if (name != NULL) 
  {
    gfc_string_concat(sql, "and convo.convonm = ? ");
    param_count++;
  }
  if (type != NULL) 
  {
    gfc_string_concat(sql, "and convo.convotyp = ? ");
    param_count++;
  }
  if (status != NULL) 
  {
    gfc_string_concat(sql, "and convo.sts = ? ");
    param_count++;
  }

  params  = (MYSQL_BIND*) malloc(sizeof(MYSQL_BIND) * param_count);
  lengths = (ulong*) malloc(sizeof(ulong) * param_count);
  
  res = mysql_stmt_prepare(stmt, 
                           sql->buffer, 
                           gfc_string_length(sql));
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }                             
  memset(params, 0, sizeof(MYSQL_BIND) * param_count); 
  memset(binds, 0, sizeof(binds));  

  if (id != NULL) 
  {
    lengths[param_index] = strlen(id);
    params[param_index].buffer_type = MYSQL_TYPE_STRING;
    params[param_index].buffer = (char *) id;
    params[param_index].length = &lengths[param_index];
    params[param_index].is_null = 0;
    param_index++;
  }
  if (name != NULL) 
  {
    lengths[param_index] = strlen(name);
    params[param_index].buffer_type = MYSQL_TYPE_STRING;
    params[param_index].buffer = (char *) name;
    params[param_index].length = &lengths[param_index];
    params[param_index].is_null = 0;
    param_index++;
  }
  if (type != NULL) 
  {
    lengths[param_index] = strlen(type);
    params[param_index].buffer_type = MYSQL_TYPE_STRING;
    params[param_index].buffer = (char *) type;
    params[param_index].length = &lengths[param_index];
    params[param_index].is_null = 0;
    param_index++;
  }
  if (status != NULL) 
  {
    lengths[param_index] = strlen(status);
    params[param_index].buffer_type = MYSQL_TYPE_STRING;
    params[param_index].buffer = (char *) status;
    params[param_index].length = &lengths[param_index];
    params[param_index].is_null = 0;
    param_index++;
  }

  res = mysql_stmt_bind_param(stmt, params);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  res = mysql_stmt_execute(stmt);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  char buff_id[2048];  
  char buff_name[2048];  
  char buff_type[2048];  
  char buff_options[2048];  
  char buff_status[2048];  
  int buff_reserved;
  binds[0].buffer_type = MYSQL_TYPE_STRING;
  binds[0].buffer = (char *) buff_id;
  binds[0].buffer_length = 2048;
  binds[0].length = &bindlens[0];  
  binds[0].is_null = &is_nulls[0];  
  binds[1].buffer_type = MYSQL_TYPE_STRING;
  binds[1].buffer = (char *) buff_name;
  binds[1].buffer_length = 2048;
  binds[1].length = &bindlens[1];  
  binds[1].is_null = &is_nulls[1];  
  binds[2].buffer_type = MYSQL_TYPE_STRING;
  binds[2].buffer = (char *) buff_type;
  binds[2].buffer_length = 2048;
  binds[2].length = &bindlens[2];  
  binds[2].is_null = &is_nulls[2];  
  binds[3].buffer_type = MYSQL_TYPE_STRING;
  binds[3].buffer = (char *) buff_options;
  binds[3].buffer_length = 2048;
  binds[3].length = &bindlens[3];  
  binds[3].is_null = &is_nulls[3];  
  binds[4].buffer_type = MYSQL_TYPE_STRING;
  binds[4].buffer = (char *) buff_status;
  binds[4].buffer_length = 2048;
  binds[4].length = &bindlens[4];  
  binds[4].is_null = &is_nulls[4];  
  binds[5].buffer_type = MYSQL_TYPE_LONG;
  binds[5].buffer = (int *) &buff_reserved;
  binds[5].length = &bindlens[5];  

  mysql_stmt_bind_result(stmt, binds);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }
  while (!mysql_stmt_fetch(stmt))
  {
    gfc_map_p obj = gfc_map_new();
    if (!is_nulls[0])
    {
      gfc_map_put(obj, "conversationId", (void*) strdup(buff_id));
    }
    if (!is_nulls[1])
    {
      gfc_map_put(obj, "conversationName", (void*) strdup(buff_name));
    }
    if (!is_nulls[2])
    {
      gfc_map_put(obj, "conversationType", (void*) strdup(buff_type));
    }
    if (!is_nulls[3])
    {
      gfc_map_put(obj, "options", (void*) strdup(buff_options));
    }
    if (!is_nulls[4])
    {
      gfc_map_put(obj, "status", (void*) strdup(buff_status));
    }
    gfc_list_append(list, obj);
  }

RELEASE: 

  mysql_stmt_free_result(stmt);
  mysql_stmt_close(stmt);
  gfc_string_free(sql);
  if (params != NULL)
    free(params);
  if (lengths != NULL)
    free(lengths);

  return res;
}

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
                                     const char*  status)
{
  sqlite3*        conn    = (sqlite3*) conn_inst;
  sqlite3_stmt*   stmt    = NULL;
  int             res     = ERROR_SUCCESS;  

  res = sqlite3_prepare_v3(db, 
                           SQL_INSERT_TV_GIM_CONVOMBR, 
                           -1, 
                           0, 
                           &stmt, 
                           NULL);
  if (res)
  {
    sprintf(errmsg, "%s", sqlite3_errmsg(conn));
    goto RELEASE;
  }

  // 【会话】
  sqlite3_bind_text(stmt, 1, conversationId, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【成员】
  sqlite3_bind_text(stmt, 2, member_id, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【成员类型】
  sqlite3_bind_text(stmt, 3, member_type, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【会话别名】
  sqlite3_bind_text(stmt, 4, alias, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【未读消息数量】
  sqlite3_bind_text(stmt, 5, unread_count, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【最近会话时间】
  sqlite3_bind_text(stmt, 6, last_conversation_time, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【加入时间】
  sqlite3_bind_text(stmt, 7, joined_time, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【离开时间】
  sqlite3_bind_text(stmt, 8, leave_time, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【业务状态】
  sqlite3_bind_text(stmt, 9, status, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  

  res = sqlite3_step(stmt);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

RELEASE:

  if (stmt != NULL)
    sqlite3_finalize(stmt);

  return res;
}

int
gim_model_delete_conversation_member(void*        conn_inst,
                                     char*        errmsg,
                                     const char*  conversation,
                                     const char*  member_id,
                                     const char*  member_type)
{
  sqlite3*        conn    = (sqlite3*) conn_inst;
  sqlite3_stmt*   stmt    = NULL;
  int             res     = ERROR_SUCCESS;  

  gfc_string_p sql = gfc_string_new(SQL_DELETE_TV_GIM_CONVOMBR);
  if (conversation != NULL) 
  {
    gfc_string_concat(sql, "and convoid = ? ");
    param_count++;
  }
  if (member_id != NULL) 
  {
    gfc_string_concat(sql, "and mbrid = ? ");
    param_count++;
  }
  if (member_type != NULL) 
  {
    gfc_string_concat(sql, "and mbrtyp = ? ");
    param_count++;
  }

  res = sqlite3_prepare_v3(db, 
                           sql->buffer, 
                           -1, 
                           0, 
                           &stmt, 
                           NULL);
  if (res)
  {
    sprintf(errmsg, "%s", sqlite3_errmsg(conn));
    goto RELEASE;
  }

  if (conversation != NULL) 
  {
    lengths[param_index] = strlen(conversation);
    params[param_index].buffer_type = MYSQL_TYPE_STRING;
    params[param_index].buffer = (char *) conversation;
    params[param_index].length = &lengths[param_index];
    params[param_index].is_null = 0;
    param_index++;
  }
  if (member_id != NULL) 
  {
    lengths[param_index] = strlen(member_id);
    params[param_index].buffer_type = MYSQL_TYPE_STRING;
    params[param_index].buffer = (char *) member_id;
    params[param_index].length = &lengths[param_index];
    params[param_index].is_null = 0;
    param_index++;
  }
  if (member_type != NULL) 
  {
    lengths[param_index] = strlen(member_type);
    params[param_index].buffer_type = MYSQL_TYPE_STRING;
    params[param_index].buffer = (char *) member_type;
    params[param_index].length = &lengths[param_index];
    params[param_index].is_null = 0;
    param_index++;
  }

  res = mysql_stmt_bind_param(stmt, params);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  res = mysql_stmt_execute(stmt);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

RELEASE:

  mysql_stmt_close(stmt);
  gfc_string_free(sql);
  if (params != NULL)
    free(params);
  if (lengths != NULL)
    free(lengths);

  return res;
}
      
/*!
** 更新【会话成员信息】中【未读消息数量】数据。
*/
int
gim_model_update_conversation_member_unread_count(void*        conn_inst,
                                      char*        errmsg,
                                                  const char*  conversation,
                                                  const char*  member_id,
                                                  const char*  member_type,
                                                  int          unread_count)
{
  MYSQL*        conn = (MYSQL*) conn_inst;
  MYSQL_STMT*   stmt;
  MYSQL_BIND    params[3];
  ulong         lengths[3];
  int           param_index = 0;
  int           res         = ERROR_SUCCESS;
  
  stmt    = mysql_stmt_init(conn);
  
  res = mysql_stmt_prepare(stmt, 
                           SQL_UPDATE_TV_GIM_CONVOMBR_UNRDCNT, 
                           strlen(SQL_UPDATE_TV_GIM_CONVOMBR_UNRDCNT));
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  memset(params, 0, sizeof(params)); 
  lengths[param_index] = strlen(conversation);
  params[param_index].buffer_type = MYSQL_TYPE_STRING;
  params[param_index].buffer = (char *) conversation;
  params[param_index].length = &lengths[param_index];
  params[param_index].is_null = 0;   
  param_index++;       
  lengths[param_index] = strlen(member_id);
  params[param_index].buffer_type = MYSQL_TYPE_STRING;
  params[param_index].buffer = (char *) member_id;
  params[param_index].length = &lengths[param_index];
  params[param_index].is_null = 0;   
  param_index++;       
  lengths[param_index] = strlen(member_type);
  params[param_index].buffer_type = MYSQL_TYPE_STRING;
  params[param_index].buffer = (char *) member_type;
  params[param_index].length = &lengths[param_index];
  params[param_index].is_null = 0;   
  param_index++;       
  
  res = mysql_stmt_bind_param(stmt, params);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  res = mysql_stmt_execute(stmt);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

RELEASE:

  mysql_stmt_close(stmt);  

  return res;
} 
      
/*!
** 更新【会话成员信息】中【最近会话时间】数据。
*/
int
gim_model_update_conversation_member_last_conversation_time(void*        conn_inst,
                                      char*        errmsg,
                                                            const char*  conversation,
                                                            const char*  member_id,
                                                            const char*  member_type,
                                                            const char*  last_conversation_time)
{
  MYSQL*        conn = (MYSQL*) conn_inst;
  MYSQL_STMT*   stmt;
  MYSQL_BIND    params[3];
  ulong         lengths[3];
  int           param_index = 0;
  int           res         = ERROR_SUCCESS;
  
  stmt    = mysql_stmt_init(conn);
  
  res = mysql_stmt_prepare(stmt, 
                           SQL_UPDATE_TV_GIM_CONVOMBR_LCT, 
                           strlen(SQL_UPDATE_TV_GIM_CONVOMBR_LCT));
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  memset(params, 0, sizeof(params)); 
  lengths[param_index] = strlen(conversation);
  params[param_index].buffer_type = MYSQL_TYPE_STRING;
  params[param_index].buffer = (char *) conversation;
  params[param_index].length = &lengths[param_index];
  params[param_index].is_null = 0;   
  param_index++;       
  lengths[param_index] = strlen(member_id);
  params[param_index].buffer_type = MYSQL_TYPE_STRING;
  params[param_index].buffer = (char *) member_id;
  params[param_index].length = &lengths[param_index];
  params[param_index].is_null = 0;   
  param_index++;       
  lengths[param_index] = strlen(member_type);
  params[param_index].buffer_type = MYSQL_TYPE_STRING;
  params[param_index].buffer = (char *) member_type;
  params[param_index].length = &lengths[param_index];
  params[param_index].is_null = 0;   
  param_index++;       
  
  res = mysql_stmt_bind_param(stmt, params);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  res = mysql_stmt_execute(stmt);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

RELEASE:

  mysql_stmt_close(stmt);  

  return res;
} 
      
/*!
** 更新【会话成员信息】中【离开时间】数据。
*/
int
gim_model_update_conversation_member_leave_time(void*        conn_inst,
                                      char*        errmsg,
                                                const char*  conversation,
                                                const char*  member_id,
                                                const char*  member_type,
                                                const char*  leave_time)
{
  MYSQL*        conn = (MYSQL*) conn_inst;
  MYSQL_STMT*   stmt;
  MYSQL_BIND    params[3];
  ulong         lengths[3];
  int           param_index = 0;
  int           res         = ERROR_SUCCESS;
  
  stmt    = mysql_stmt_init(conn);
  
  res = mysql_stmt_prepare(stmt, 
                           SQL_UPDATE_TV_GIM_CONVOMBR_LVTM, 
                           strlen(SQL_UPDATE_TV_GIM_CONVOMBR_LVTM));
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  memset(params, 0, sizeof(params)); 
  lengths[param_index] = strlen(conversation);
  params[param_index].buffer_type = MYSQL_TYPE_STRING;
  params[param_index].buffer = (char *) conversation;
  params[param_index].length = &lengths[param_index];
  params[param_index].is_null = 0;   
  param_index++;       
  lengths[param_index] = strlen(member_id);
  params[param_index].buffer_type = MYSQL_TYPE_STRING;
  params[param_index].buffer = (char *) member_id;
  params[param_index].length = &lengths[param_index];
  params[param_index].is_null = 0;   
  param_index++;       
  lengths[param_index] = strlen(member_type);
  params[param_index].buffer_type = MYSQL_TYPE_STRING;
  params[param_index].buffer = (char *) member_type;
  params[param_index].length = &lengths[param_index];
  params[param_index].is_null = 0;   
  param_index++;       
  
  res = mysql_stmt_bind_param(stmt, params);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  res = mysql_stmt_execute(stmt);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

RELEASE:

  mysql_stmt_close(stmt);  

  return res;
} 
      
/*!
** 更新【会话成员信息】中【业务状态】数据。
*/
int
gim_model_update_conversation_member_status(void*        conn_inst,
                                      char*        errmsg,
                                            const char*  conversation,
                                            const char*  member_id,
                                            const char*  member_type,
                                            const char*  status)
{
  MYSQL*        conn = (MYSQL*) conn_inst;
  MYSQL_STMT*   stmt;
  MYSQL_BIND    params[4];
  ulong         lengths[4];    
  int           param_index = 0;
  int           res         = ERROR_SUCCESS;
  
  stmt    = mysql_stmt_init(conn);
  
  res = mysql_stmt_prepare(stmt, 
                           SQL_UPDATE_TV_GIM_CONVOMBR_STS, 
                           strlen(SQL_UPDATE_TV_GIM_CONVOMBR_STS));
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  memset(params, 0, sizeof(params)); 
  lengths[param_index] = strlen(status);
  params[param_index].buffer_type = MYSQL_TYPE_STRING;
  params[param_index].buffer = (char *) status;   
  params[param_index].length = &lengths[param_index];
  params[param_index].is_null = 0;   
  param_index++;     
  lengths[param_index] = strlen(conversation);
  params[param_index].buffer_type = MYSQL_TYPE_STRING;
  params[param_index].buffer = (char *) conversation;
  params[param_index].length = &lengths[param_index];
  params[param_index].is_null = 0;   
  param_index++;       
  lengths[param_index] = strlen(member_id);
  params[param_index].buffer_type = MYSQL_TYPE_STRING;
  params[param_index].buffer = (char *) member_id;
  params[param_index].length = &lengths[param_index];
  params[param_index].is_null = 0;   
  param_index++;       
  lengths[param_index] = strlen(member_type);
  params[param_index].buffer_type = MYSQL_TYPE_STRING;
  params[param_index].buffer = (char *) member_type;
  params[param_index].length = &lengths[param_index];
  params[param_index].is_null = 0;   
  param_index++;       
  
  res = mysql_stmt_bind_param(stmt, params);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  res = mysql_stmt_execute(stmt);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

RELEASE:

  mysql_stmt_close(stmt);  

  return res;
} 

int
gim_model_select_conversation_member(void*        conn_inst,
                                     char*        errmsg,
                                     gfc_list_p   list,
                                     const char*  conversation,
                                     const char*  member_id,
                                     const char*  member_type,
                                     const char*  alias)
{
  int           res  = ERROR_SUCCESS;
  MYSQL*        conn = (MYSQL*) conn_inst;
  MYSQL_STMT*   stmt;
  MYSQL_BIND*   params;
  MYSQL_BIND    binds[13];
  MYSQL_FIELD*  field;
  MYSQL_ROW     row;
  MYSQL_RES*    result;
  ulong*        lengths;
  ulong         bindlens[13];
  bool          is_nulls[13];
  int           param_count = 0;
  int           param_index = 0;
  int           i = 0;
  stmt = mysql_stmt_init(conn);

  gfc_string_p sql = gfc_string_new(SQL_SELECT_TV_GIM_CONVOMBR);
  if (conversation != NULL) 
  {
    gfc_string_concat(sql, "and convombr.convoid = ? ");
    param_count++;
  }
  if (member_id != NULL) 
  {
    gfc_string_concat(sql, "and convombr.mbrid = ? ");
    param_count++;
  }
  if (member_type != NULL) 
  {
    gfc_string_concat(sql, "and convombr.mbrtyp = ? ");
    param_count++;
  }
  if (alias != NULL) 
  {
    gfc_string_concat(sql, "and convombr.als = ? ");
    param_count++;
  }

  params  = (MYSQL_BIND*) malloc(sizeof(MYSQL_BIND) * param_count);
  lengths = (ulong*) malloc(sizeof(ulong) * param_count);
  
  res = mysql_stmt_prepare(stmt, 
                           sql->buffer, 
                           gfc_string_length(sql));
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }                             
  memset(params, 0, sizeof(MYSQL_BIND) * param_count); 
  memset(binds, 0, sizeof(binds));  

  if (conversation != NULL) 
  {
    lengths[param_index] = strlen(conversation);
    params[param_index].buffer_type = MYSQL_TYPE_STRING;
    params[param_index].buffer = (char *) conversation;
    params[param_index].length = &lengths[param_index];
    params[param_index].is_null = 0;
    param_index++;
  }
  if (member_id != NULL) 
  {
    lengths[param_index] = strlen(member_id);
    params[param_index].buffer_type = MYSQL_TYPE_STRING;
    params[param_index].buffer = (char *) member_id;
    params[param_index].length = &lengths[param_index];
    params[param_index].is_null = 0;
    param_index++;
  }
  if (member_type != NULL) 
  {
    lengths[param_index] = strlen(member_type);
    params[param_index].buffer_type = MYSQL_TYPE_STRING;
    params[param_index].buffer = (char *) member_type;
    params[param_index].length = &lengths[param_index];
    params[param_index].is_null = 0;
    param_index++;
  }
  if (alias != NULL) 
  {
    lengths[param_index] = strlen(alias);
    params[param_index].buffer_type = MYSQL_TYPE_STRING;
    params[param_index].buffer = (char *) alias;
    params[param_index].length = &lengths[param_index];
    params[param_index].is_null = 0;
    param_index++;
  }

  res = mysql_stmt_bind_param(stmt, params);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  res = mysql_stmt_execute(stmt);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  char buff_conversation[2048];  
  char buff_member_id[2048];  
  char buff_member_type[2048];  
  char buff_alias[2048];  
  int buff_unread_count;  
  char buff_last_conversation_time[2048];  
  char buff_joined_time[2048];  
  char buff_leave_time[2048];  
  char buff_status[2048];  
  char buff_conversation_name[2048];  
  char buff_conversation_type[2048];  
  char buff_conversation_status[2048];  
  int buff_reserved;
  binds[0].buffer_type = MYSQL_TYPE_STRING;
  binds[0].buffer = (char *) buff_conversation;
  binds[0].buffer_length = 2048;
  binds[0].length = &bindlens[0];  
  binds[0].is_null = &is_nulls[0];  
  binds[1].buffer_type = MYSQL_TYPE_STRING;
  binds[1].buffer = (char *) buff_member_id;
  binds[1].buffer_length = 2048;
  binds[1].length = &bindlens[1];  
  binds[1].is_null = &is_nulls[1];  
  binds[2].buffer_type = MYSQL_TYPE_STRING;
  binds[2].buffer = (char *) buff_member_type;
  binds[2].buffer_length = 2048;
  binds[2].length = &bindlens[2];  
  binds[2].is_null = &is_nulls[2];  
  binds[3].buffer_type = MYSQL_TYPE_STRING;
  binds[3].buffer = (char *) buff_alias;
  binds[3].buffer_length = 2048;
  binds[3].length = &bindlens[3];  
  binds[3].is_null = &is_nulls[3];  
  binds[4].buffer_type = MYSQL_TYPE_LONG;
  binds[4].buffer = (int *) &buff_unread_count;
  binds[4].length = &bindlens[4];  
  binds[4].is_null = &is_nulls[4];  
  binds[5].buffer_type = MYSQL_TYPE_STRING;
  binds[5].buffer = (char *) buff_last_conversation_time;
  binds[5].buffer_length = 2048;
  binds[5].length = &bindlens[5];  
  binds[5].is_null = &is_nulls[5];  
  binds[6].buffer_type = MYSQL_TYPE_STRING;
  binds[6].buffer = (char *) buff_joined_time;
  binds[6].buffer_length = 2048;
  binds[6].length = &bindlens[6];  
  binds[6].is_null = &is_nulls[6];  
  binds[7].buffer_type = MYSQL_TYPE_STRING;
  binds[7].buffer = (char *) buff_leave_time;
  binds[7].buffer_length = 2048;
  binds[7].length = &bindlens[7];  
  binds[7].is_null = &is_nulls[7];  
  binds[8].buffer_type = MYSQL_TYPE_STRING;
  binds[8].buffer = (char *) buff_status;
  binds[8].buffer_length = 2048;
  binds[8].length = &bindlens[8];  
  binds[8].is_null = &is_nulls[8];  
  binds[9].buffer_type = MYSQL_TYPE_STRING;
  binds[9].buffer = (char *) buff_conversation_name;
  binds[9].buffer_length = 2048;
  binds[9].length = &bindlens[9];  
  binds[9].is_null = &is_nulls[9];  
  binds[10].buffer_type = MYSQL_TYPE_STRING;
  binds[10].buffer = (char *) buff_conversation_type;
  binds[10].buffer_length = 2048;
  binds[10].length = &bindlens[10];  
  binds[10].is_null = &is_nulls[10];  
  binds[11].buffer_type = MYSQL_TYPE_STRING;
  binds[11].buffer = (char *) buff_conversation_status;
  binds[11].buffer_length = 2048;
  binds[11].length = &bindlens[11];  
  binds[11].is_null = &is_nulls[11];  
  binds[12].buffer_type = MYSQL_TYPE_LONG;
  binds[12].buffer = (int *) &buff_reserved;
  binds[12].length = &bindlens[12];  

  mysql_stmt_bind_result(stmt, binds);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }
  while (!mysql_stmt_fetch(stmt))
  {
    gfc_map_p obj = gfc_map_new();
    if (!is_nulls[0])
    {
      gfc_map_put(obj, "conversationId", (void*) strdup(buff_conversation));
    }
    if (!is_nulls[1])
    {
      gfc_map_put(obj, "memberId", (void*) strdup(buff_member_id));
    }
    if (!is_nulls[2])
    {
      gfc_map_put(obj, "memberType", (void*) strdup(buff_member_type));
    }
    if (!is_nulls[3])
    {
      gfc_map_put(obj, "alias", (void*) strdup(buff_alias));
    }
    if (!is_nulls[4])
    {
      int* val = malloc(sizeof(int));
      *val = buff_unread_count;
      gfc_map_put(obj, "unreadCount", (void*) val);
    }
    if (!is_nulls[5])
    {
      gfc_map_put(obj, "lastConversationTime", (void*) strdup(buff_last_conversation_time));
    }
    if (!is_nulls[6])
    {
      gfc_map_put(obj, "joinedTime", (void*) strdup(buff_joined_time));
    }
    if (!is_nulls[7])
    {
      gfc_map_put(obj, "leaveTime", (void*) strdup(buff_leave_time));
    }
    if (!is_nulls[8])
    {
      gfc_map_put(obj, "status", (void*) strdup(buff_status));
    }
    if (!is_nulls[9])
    {
      gfc_map_put(obj, "conversationName", (void*) strdup(buff_conversation_name));
    }
    if (!is_nulls[10])
    {
      gfc_map_put(obj, "conversationType", (void*) strdup(buff_conversation_type));
    }
    if (!is_nulls[11])
    {
      gfc_map_put(obj, "conversationStatus", (void*) strdup(buff_conversation_status));
    }
    gfc_list_append(list, obj);
  }

RELEASE: 

  mysql_stmt_free_result(stmt);
  mysql_stmt_close(stmt);
  gfc_string_free(sql);
  if (params != NULL)
    free(params);
  if (lengths != NULL)
    free(lengths);

  return res;
}

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
                                      const char*  status)
{
  sqlite3*        conn    = (sqlite3*) conn_inst;
  sqlite3_stmt*   stmt    = NULL;
  int             res     = ERROR_SUCCESS;  

  res = sqlite3_prepare_v3(db, 
                           SQL_INSERT_TN_GIM_CONVOMSG, 
                           -1, 
                           0, 
                           &stmt, 
                           NULL);
  if (res)
  {
    sprintf(errmsg, "%s", sqlite3_errmsg(conn));
    goto RELEASE;
  }

  // 【会话】
  sqlite3_bind_text(stmt, 1, conversation_messageId, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【会话】
  sqlite3_bind_text(stmt, 2, conversationId, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【发送者】
  sqlite3_bind_text(stmt, 3, sender_id, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【发送者类型】
  sqlite3_bind_text(stmt, 4, sender_type, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【接收者】
  sqlite3_bind_text(stmt, 5, receiver_id, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【接收者类型】
  sqlite3_bind_text(stmt, 6, receiver_type, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【消息时间】
  sqlite3_bind_text(stmt, 7, message_time, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【消息内容】
  sqlite3_bind_text(stmt, 8, message_type, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【消息内容】
  sqlite3_bind_text(stmt, 9, message_content, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【创建时间】
  sqlite3_bind_text(stmt, 10, create_time, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  
  // 【附加选项】
  sqlite3_bind_text(stmt, 11, status, -1, NULL);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }  

  res = sqlite3_step(stmt);
  if (res)
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

RELEASE:

  if (stmt != NULL)
    sqlite3_finalize(stmt);

  return res;
}
      
/*!
** 更新【会话消息信息】中【附加选项】数据。
*/
int
gim_model_update_conversation_message_status(void*        conn_inst,
                                       char*        errmsg,
                                             const char*  id,
                                             const char*  status)
{
  MYSQL*        conn = (MYSQL*) conn_inst;
  MYSQL_STMT*   stmt;
  MYSQL_BIND    params[2];
  ulong         lengths[2];    
  int           param_index = 0;
  int           res         = ERROR_SUCCESS;
  
  stmt    = mysql_stmt_init(conn);
  
  res = mysql_stmt_prepare(stmt, 
                           SQL_UPDATE_TN_GIM_CONVOMSG_STS, 
                           strlen(SQL_UPDATE_TN_GIM_CONVOMSG_STS));
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  memset(params, 0, sizeof(params)); 
  lengths[param_index] = strlen(status);
  params[param_index].buffer_type = MYSQL_TYPE_STRING;
  params[param_index].buffer = (char *) status;   
  params[param_index].length = &lengths[param_index];
  params[param_index].is_null = 0;   
  param_index++;     
  lengths[param_index] = strlen(id);
  params[param_index].buffer_type = MYSQL_TYPE_STRING;
  params[param_index].buffer = (char *) id;
  params[param_index].length = &lengths[param_index];
  params[param_index].is_null = 0;   
  param_index++;       
  
  res = mysql_stmt_bind_param(stmt, params);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  res = mysql_stmt_execute(stmt);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

RELEASE:

  mysql_stmt_close(stmt);  

  return res;
} 

int
gim_model_select_conversation_message(void*        conn_inst,
                                      char*        errmsg,
                                      gfc_list_p   list,
                                      const char*  conversation,
                                      const char*  message_time0,
                                      const char*  message_time1)
{
  int           res  = ERROR_SUCCESS;
  MYSQL*        conn = (MYSQL*) conn_inst;
  MYSQL_STMT*   stmt;
  MYSQL_BIND*   params;
  MYSQL_BIND    binds[15];
  MYSQL_FIELD*  field;
  MYSQL_ROW     row;
  MYSQL_RES*    result;
  ulong*        lengths;
  ulong         bindlens[15];
  bool          is_nulls[15];
  int           param_count = 0;
  int           param_index = 0;
  int           i = 0;
  stmt = mysql_stmt_init(conn);

  gfc_string_p sql = gfc_string_new(SQL_SELECT_TN_GIM_CONVOMSG);
  if (conversation != NULL) 
  {
    gfc_string_concat(sql, "and convomsg.convoid = ? ");
    param_count++;
  }
  if (message_time0 != NULL) 
  {
    gfc_string_concat(sql, "and convomsg.msgtm >= ? ");
    param_count++;
  }
  if (message_time1 != NULL) 
  {
    gfc_string_concat(sql, "and convomsg.msgtm <= ? ");
    param_count++;
  }  

  params  = (MYSQL_BIND*) malloc(sizeof(MYSQL_BIND) * param_count);
  lengths = (ulong*) malloc(sizeof(ulong) * param_count);
  
  res = mysql_stmt_prepare(stmt, 
                           sql->buffer, 
                           gfc_string_length(sql));
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }                             
  memset(params, 0, sizeof(MYSQL_BIND) * param_count); 
  memset(binds, 0, sizeof(binds));  

  if (conversation != NULL) 
  {
    lengths[param_index] = strlen(conversation);
    params[param_index].buffer_type = MYSQL_TYPE_STRING;
    params[param_index].buffer = (char *) conversation;
    params[param_index].length = &lengths[param_index];
    params[param_index].is_null = 0;
    param_index++;
  }
  if (message_time0 != NULL) 
  {
    lengths[param_index] = strlen(message_time0);
    params[param_index].buffer_type = MYSQL_TYPE_STRING;
    params[param_index].buffer = (char *) message_time0;
    params[param_index].length = &lengths[param_index];
    params[param_index].is_null = 0;
    param_index++;
  }
  if (message_time1 != NULL) 
  {
    lengths[param_index] = strlen(message_time1);
    params[param_index].buffer_type = MYSQL_TYPE_STRING;
    params[param_index].buffer = (char *) message_time1;
    params[param_index].length = &lengths[param_index];
    params[param_index].is_null = 0;
    param_index++;
  }  

  res = mysql_stmt_bind_param(stmt, params);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  res = mysql_stmt_execute(stmt);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }

  char buff_id[2048];  
  char buff_conversation[2048];  
  char buff_sender_id[2048];  
  char buff_sender_type[2048];  
  char buff_receiver_id[2048];  
  char buff_receiver_type[2048];  
  char buff_message_time[2048];  
  char buff_message_type[2048];  
  char buff_message_content[2048];  
  char buff_create_time[2048];  
  char buff_status[2048];  
  char buff_conversation_name[2048];  
  char buff_conversation_type[2048];  
  char buff_conversation_status[2048];  
  int buff_reserved;
  binds[0].buffer_type = MYSQL_TYPE_STRING;
  binds[0].buffer = (char *) buff_id;
  binds[0].buffer_length = 2048;
  binds[0].length = &bindlens[0];  
  binds[0].is_null = &is_nulls[0];  
  binds[1].buffer_type = MYSQL_TYPE_STRING;
  binds[1].buffer = (char *) buff_conversation;
  binds[1].buffer_length = 2048;
  binds[1].length = &bindlens[1];  
  binds[1].is_null = &is_nulls[1];  
  binds[2].buffer_type = MYSQL_TYPE_STRING;
  binds[2].buffer = (char *) buff_sender_id;
  binds[2].buffer_length = 2048;
  binds[2].length = &bindlens[2];  
  binds[2].is_null = &is_nulls[2];  
  binds[3].buffer_type = MYSQL_TYPE_STRING;
  binds[3].buffer = (char *) buff_sender_type;
  binds[3].buffer_length = 2048;
  binds[3].length = &bindlens[3];  
  binds[3].is_null = &is_nulls[3];  
  binds[4].buffer_type = MYSQL_TYPE_STRING;
  binds[4].buffer = (char *) buff_receiver_id;
  binds[4].buffer_length = 2048;
  binds[4].length = &bindlens[4];  
  binds[4].is_null = &is_nulls[4];  
  binds[5].buffer_type = MYSQL_TYPE_STRING;
  binds[5].buffer = (char *) buff_receiver_type;
  binds[5].buffer_length = 2048;
  binds[5].length = &bindlens[5];  
  binds[5].is_null = &is_nulls[5];  
  binds[6].buffer_type = MYSQL_TYPE_STRING;
  binds[6].buffer = (char *) buff_message_time;
  binds[6].buffer_length = 2048;
  binds[6].length = &bindlens[6];  
  binds[6].is_null = &is_nulls[6];  
  binds[7].buffer_type = MYSQL_TYPE_STRING;
  binds[7].buffer = (char *) buff_message_type;
  binds[7].buffer_length = 2048;
  binds[7].length = &bindlens[7];  
  binds[7].is_null = &is_nulls[7];  
  binds[8].buffer_type = MYSQL_TYPE_STRING;
  binds[8].buffer = (char *) buff_message_content;
  binds[8].buffer_length = 2048;
  binds[8].length = &bindlens[8];  
  binds[8].is_null = &is_nulls[8];  
  binds[9].buffer_type = MYSQL_TYPE_STRING;
  binds[9].buffer = (char *) buff_create_time;
  binds[9].buffer_length = 2048;
  binds[9].length = &bindlens[9];  
  binds[9].is_null = &is_nulls[9];  
  binds[10].buffer_type = MYSQL_TYPE_STRING;
  binds[10].buffer = (char *) buff_status;
  binds[10].buffer_length = 2048;
  binds[10].length = &bindlens[10];  
  binds[10].is_null = &is_nulls[10];  
  binds[11].buffer_type = MYSQL_TYPE_STRING;
  binds[11].buffer = (char *) buff_conversation_name;
  binds[11].buffer_length = 2048;
  binds[11].length = &bindlens[11];  
  binds[11].is_null = &is_nulls[11];  
  binds[12].buffer_type = MYSQL_TYPE_STRING;
  binds[12].buffer = (char *) buff_conversation_type;
  binds[12].buffer_length = 2048;
  binds[12].length = &bindlens[12];  
  binds[12].is_null = &is_nulls[12];  
  binds[13].buffer_type = MYSQL_TYPE_STRING;
  binds[13].buffer = (char *) buff_conversation_status;
  binds[13].buffer_length = 2048;
  binds[13].length = &bindlens[13];  
  binds[13].is_null = &is_nulls[13];  
  binds[14].buffer_type = MYSQL_TYPE_LONG;
  binds[14].buffer = (int *) &buff_reserved;
  binds[14].length = &bindlens[14];  

  mysql_stmt_bind_result(stmt, binds);
  if (res) 
  {
    sprintf(errmsg, "%s", mysql_stmt_error(stmt));
    goto RELEASE;
  }
  while (!mysql_stmt_fetch(stmt))
  {
    gfc_map_p obj = gfc_map_new();
    if (!is_nulls[0])
    {
      gfc_map_put(obj, "conversationMessageId", (void*) strdup(buff_id));
    }
    if (!is_nulls[1])
    {
      gfc_map_put(obj, "conversationId", (void*) strdup(buff_conversation));
    }
    if (!is_nulls[2])
    {
      gfc_map_put(obj, "senderId", (void*) strdup(buff_sender_id));
    }
    if (!is_nulls[3])
    {
      gfc_map_put(obj, "senderType", (void*) strdup(buff_sender_type));
    }
    if (!is_nulls[4])
    {
      gfc_map_put(obj, "receiverId", (void*) strdup(buff_receiver_id));
    }
    if (!is_nulls[5])
    {
      gfc_map_put(obj, "receiverType", (void*) strdup(buff_receiver_type));
    }
    if (!is_nulls[6])
    {
      gfc_map_put(obj, "messageTime", (void*) strdup(buff_message_time));
    }
    if (!is_nulls[7])
    {
      gfc_map_put(obj, "messageType", (void*) strdup(buff_message_type));
    }
    if (!is_nulls[8])
    {
      gfc_map_put(obj, "messageContent", (void*) strdup(buff_message_content));
    }
    if (!is_nulls[9])
    {
      gfc_map_put(obj, "createTime", (void*) strdup(buff_create_time));
    }
    if (!is_nulls[10])
    {
      gfc_map_put(obj, "status", (void*) strdup(buff_status));
    }
    if (!is_nulls[11])
    {
      gfc_map_put(obj, "conversationName", (void*) strdup(buff_conversation_name));
    }
    if (!is_nulls[12])
    {
      gfc_map_put(obj, "conversationType", (void*) strdup(buff_conversation_type));
    }
    if (!is_nulls[13])
    {
      gfc_map_put(obj, "conversationStatus", (void*) strdup(buff_conversation_status));
    }
    gfc_list_append(list, obj);
  }

RELEASE: 

  mysql_stmt_free_result(stmt);
  mysql_stmt_close(stmt);
  gfc_string_free(sql);
  if (params != NULL)
    free(params);
  if (lengths != NULL)
    free(lengths);

  return res;
}
