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
#include <time.h>
#include <errno.h>

#include "toyws.h"
#include "gim_test.h"

void signal_handler(int signum){
  exit(0);
}

void test_send(void)
{
  struct tws_ctx ctx;

  char *buff;
  int frm_type;
  size_t buff_size;

  buff      = NULL;
  buff_size = 0;
  frm_type  = 0;

  if (tws_connect(&ctx, TEST_ADDRESS, TEST_PORT) < 0)
  {
    fprintf(stderr, "Unable to connect!\n");
    return;
  }


  char* msg = "{"
              "\"operation\":\"login\","
              "\"userId\":\"123\","
              "\"userType\":\"STDBIZ.SMS.PERSON@RM\","
              "\"payload\":{"
              "    \"userId\":\"123\""
              "  }"
              "}";
  tws_sendframe(&ctx, (uint8_t *) msg, strlen(msg), FRM_TXT);
  tws_receiveframe(&ctx, &buff, &buff_size, &frm_type);
  printf("login: %s\n", buff);

  msg = "{"
        "\"operation\":\"logout\","
        "\"userId\":\"123\","
        "\"userType\":\"STDBIZ.SMS.PERSON@RM\","
        "\"payload\":{"
        "    \"userId\":\"123\""
        "  }"
        "}";
  tws_sendframe(&ctx, (uint8_t *) msg, strlen(msg), FRM_TXT);
  tws_receiveframe(&ctx, &buff, &buff_size, &frm_type);
  printf("logout: %s\n", buff);

  tws_close(&ctx);
  free(buff);
}

int main(void)
{
  signal(SIGINT, signal_handler);

  int i = 0;
  int res;

  struct timespec ts;

  ts.tv_sec = 0;
  ts.tv_nsec = (100 % 1000) * 1000000;

  for (i = 0; i < 10000; i++)
  {
    printf("第%04d次请求\n", i);
    test_send();
    do {
      res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);
  }

  return (0);
}
