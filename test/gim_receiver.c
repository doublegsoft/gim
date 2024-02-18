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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#include "toyws.h"
#include "gim_test.h"

void signal_handler(int signum)
{
  exit(0);
}

int
main(int argc, char* argv[])
{
  struct tws_ctx ctx;

  char *buff;
  int frm_type;
  size_t buff_size;

  buff      = NULL;
  buff_size = 0;
  frm_type  = 0;

  signal(SIGINT, signal_handler);
  signal(SIGPIPE, SIG_IGN);

  int i = 0;
  if (tws_connect(&ctx, TEST_ADDRESS, TEST_PORT) < 0)
    fprintf(stderr, "Unable to connect!\n");

  char* msg = "{"
              "\"operation\":\"login\","
              "\"userId\":\"2\","
              "\"userType\":\"TEST\","
              "\"payload\":{"
              "  }"
              "}";
  tws_sendframe(&ctx, (uint8_t *) msg, strlen(msg), FRM_TXT);
  tws_receiveframe(&ctx, &buff, &buff_size, &frm_type);
  printf("login: %s\n", buff);
  while (1)
  {
    if (ctx.status == TWS_ST_DISCONNECTED)
    {
      printf("socket closed by server side.");
      exit(0);
    }
    tws_receiveframe(&ctx, &buff, &buff_size, &frm_type);
    printf("received: %s\n", buff);
    sleep(1);
  }

  tws_close(&ctx);

  free(buff);
  return (0);
}
