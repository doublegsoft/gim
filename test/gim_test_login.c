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
#include <time.h>
#include <unistd.h>

#include "toyws.h"
#include "gim_test.h"

void signal_handler(int signum){
  exit(0);
}

int main(void)
{
  char *buff;
  int frm_type;
  size_t buff_size;

  buff      = NULL;
  buff_size = 0;
  frm_type  = 0;

  signal(SIGINT, signal_handler);

  int i = 0;
  for (i = 0; i < 1000; i++)
  {
    struct tws_ctx ctx;
    if (tws_connect(&ctx, TEST_ADDRESS, TEST_PORT) < 0)
      fprintf(stderr, "Unable to connect!\n");
    char *msg = "{"
                "\"operation\":\"login\","
                "\"payload\":{"
                "    \"userId\":\"发送者%d\""
                "  }"
                "}";
    char msgbuff[1024] = {'\0'};
    sprintf(msgbuff, msg, i);
    tws_sendframe(&ctx, (uint8_t *) msgbuff, strlen(msgbuff), FRM_TXT);
    tws_receiveframe(&ctx, &buff, &buff_size, &frm_type);
    msg = "{"
          "\"operation\":\"logout\","
          "\"payload\":{"
          "    \"userId\":\"发送者%d\""
          "  }"
          "}";
    msgbuff[0] = '\0';
    sprintf(msgbuff, msg, i);
    tws_sendframe(&ctx, (uint8_t *) msgbuff, strlen(msgbuff), FRM_TXT);
    tws_close(&ctx);
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 100 * 1000000;
    nanosleep(&ts, &ts);
  }
  free(buff);
  return (0);
}
