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

#include <mysql.h>

#include "gim-db.h"
#include "gim-model.h"

static int
gim_free_map(const char* key, user_data* data)
{
  if (data != NULL) free(data);
  return 0;
}

int main(void)
{
  int i = 0;
  char errmsg[1024] = {'\0'};
  gim_db_p db;
  gim_db_create(&db, "localhost", 3306, "root", "ganguo", "jim", 5);

  MYSQL* conn = (MYSQL*) gim_db_connect(db);

  const char* conversation_id = "123";

  gim_model_create_conversation(conn,
                                errmsg,
                                conversation_id,
                                "中文会话",
                                NULL,
                                NULL,
                                "00");

  gim_model_create_conversation_member(conn,
                                       errmsg,
                                       conversation_id,
                                       "M1",
                                       "MEMBER",
                                       NULL,
                                       0,
                                       "2022-10-01 12:00:00",
                                       "2022-10-01 12:00:00",
                                       NULL,
                                       "01");

  gim_model_create_conversation_member(conn,
                                       errmsg,
                                       conversation_id,
                                       "M2",
                                       "MEMBER",
                                       NULL,
                                       0,
                                       "2022-10-01 12:00:00",
                                       "2022-10-01 12:00:00",
                                       NULL,
                                       "01");

  gim_model_update_conversation_member_unread_count(conn,
                                                    errmsg,
                                                    conversation_id,
                                                    "M1",
                                                    "MEMBER",
                                                    1);

  gim_model_update_conversation_member_last_conversation_time(conn,
                                                              errmsg,
                                                              conversation_id,
                                                              "M1",
                                                              "MEMBER",
                                                              NULL);

  gfc_list_p list = gfc_list_new();
  gim_model_select_conversation_member(conn,
                                       errmsg,
                                       list,
                                       conversation_id,
                                       NULL,
                                       NULL,
                                       NULL,
                                       NULL);
  printf("list size:  %d\n", gfc_list_size(list));
  gfc_map_p first = gfc_list_get(list, 0);

  user_data data;
  gfc_map_get(first, "lastConversationTime", &data);
  printf("last conversation time: %s\n", (char*)data);
  gfc_map_get(first, "leaveTime", &data);
  printf("leave time: %s\n", (char*)data);
  gfc_map_get(first, "conversationName", &data);
  printf("conversationName: %s\n", (char*)data);
  gfc_map_get(first, "unreadCount", &data);
  int* val = (int*) data;
  printf("unread count: %d\n", *val);


  gim_model_delete_conversation_member(conn,
                                       errmsg,
                                       conversation_id,
                                       NULL,
                                       NULL);

  gim_model_delete_conversation(conn,
                                errmsg,
                                conversation_id);



  gim_db_release(db, conn);

  for (i = 0; i < gfc_list_size(list); i++)
  {
    gfc_map_p obj = gfc_list_get(list, i);
    gfc_map_deep_free(obj);
  }
  gfc_list_free(list);
  return 0;
}