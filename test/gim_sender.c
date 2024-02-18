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

static void signal_handler(int signum)
{
  exit(0);
}

//static int msleep(long msec)
//{
//  struct timespec ts;
//  int res;
//
//  if (msec < 0)
//  {
//    errno = EINVAL;
//    return -1;
//  }
//
//  ts.tv_sec = msec / 1000;
//  ts.tv_nsec = (msec % 1000) * 1000000;
//
//  do
//  {
//    res = nanosleep(&ts, &ts);
//  }
//  while (res && errno == EINTR);
//
//  return res;
//}

int main(void)
{
  struct tws_ctx ctx;

  char *buff;
  int frm_type;
  size_t buff_size;

  buff      = NULL;
  buff_size = 0;
  frm_type  = 0;

  signal(SIGINT, signal_handler);

  int i = 0;
  if (tws_connect(&ctx, TEST_ADDRESS, TEST_PORT) < 0)
  {
    fprintf(stderr, "Unable to connect!\n");
    return 0;
  }

  char* msg = "{"
              "\"operation\":\"login\","
              "\"userId\":\"1\","
              "\"userType\":\"TEST\","
              "\"payload\":{"
              "  }"
              "}";
  tws_sendframe(&ctx, (uint8_t *) msg, strlen(msg), FRM_TXT);
  tws_receiveframe(&ctx, &buff, &buff_size, &frm_type);
  printf("login: %s\n", buff);
  while (1)
  {
    msg = "{"
          "\"operation\":\"sendMessage\","
          "\"userId\":\"1\","
          "\"userType\":\"TEST\","
          "\"payload\":{"
          "    \"receiverId\":\"2\","
          "    \"receiverType\":\"TEST\","
          "    \"receiverAlias\":\"2号选手\","
          "    \"messageType\": \"TEXT\","
          "    \"messageContent\": \"你好\""
          "  }"
          "}";
    tws_sendframe(&ctx, (uint8_t *) msg, strlen(msg), FRM_TXT);
    tws_receiveframe(&ctx, &buff, &buff_size, &frm_type);
    printf("%s\n", buff);
    sleep(3);
  }

  tws_close(&ctx);
  free(buff);
  return (0);
}
