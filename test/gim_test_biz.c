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

#include <json.h>
#include <gfc.h>

#include "gim-err.h"
#include "gim-db.h"
#include "gim-biz.h"

gim_db_p    g_db;
gfc_lru_p   g_sessions;

struct gim_db_s
{
  int max_connections;

  int active_connections;

  void**  connections;

  pthread_mutex_t   mutex;

  pthread_cond_t    cond;
};

int main(void)
{
  FILE *file = fopen("/proc/self/status", "r");
  char line[128];

  while (fgets(line, 128, file) != NULL) {
    printf("%s\n", line);
  }
  fclose(file);
  return ERROR_SUCCESS;
}