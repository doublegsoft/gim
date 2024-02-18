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

void signal_handler(int signum){
  exit(0);
}

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
              "\"userType\":\"STDBIZ.SMS.PERSON\","
              "\"payload\":{"
              "  }"
              "}";
  tws_sendframe(&ctx, (uint8_t *) msg, strlen(msg), FRM_TXT);
  tws_receiveframe(&ctx, &buff, &buff_size, &frm_type);
  printf("login: %s\n", buff);

  sleep(3);

  msg = "{"
        "\"operation\":\"sendMessage\","
        "\"userId\":\"1\","
        "\"userType\":\"STDBIZ.SMS.PERSON\","
        "\"payload\":{"
        "    \"receiverId\":\"2\","
        "    \"receiverType\":\"STDBIZ.SMS.PERSON\","
        "    \"receiverAlias\":\"2号选手\","
        "    \"messageType\": \"TEXT\","
        "    \"messageContent\": \"你好\""
        "  }"
        "}";
  tws_sendframe(&ctx, (uint8_t *) msg, strlen(msg), FRM_TXT);
  tws_receiveframe(&ctx, &buff, &buff_size, &frm_type);
  printf("send: %s\n", buff);
  sleep(1);

//  msg = "{"
//        "\"operation\":\"sendMessage\","
//        "\"userId\":\"123\","
//        "\"userType\":\"STDBIZ.SMS.PERSON@RM\","
//        "\"payload\":{"
//        "    \"senderId\":\"123\","
//        "    \"senderType\":\"STDBIZ.SMS.PERSON@RM\","
//        "    \"conversationId\":\"8315595A-EEDB-411A-A172-D177AA4E3148\","
//        "    \"messageType\": \"TEXT\","
//        "    \"messageContent\": \"在不在\""
//        "  }"
//        "}";
//  tws_sendframe(&ctx, (uint8_t *) msg, strlen(msg), FRM_TXT);
//  tws_receiveframe(&ctx, &buff, &buff_size, &frm_type);
//  printf("send: %s\n", buff);
//  sleep(1);
//
//  msg = "{"
//        "\"operation\":\"sendMessage\","
//        "\"userId\":\"123\","
//        "\"userType\":\"STDBIZ.SMS.PERSON@RM\","
//        "\"payload\":{"
//        "    \"senderId\":\"123\","
//        "    \"senderType\":\"STDBIZ.SMS.PERSON@RM\","
//        "    \"conversationId\":\"8315595A-EEDB-411A-A172-D177AA4E3148\","
//        "    \"messageType\": \"TEXT\","
//        "    \"messageContent\": \"说一句\""
//        "  }"
//        "}";
//  tws_sendframe(&ctx, (uint8_t *) msg, strlen(msg), FRM_TXT);
//  tws_receiveframe(&ctx, &buff, &buff_size, &frm_type);
//  printf("send: %s\n", buff);
//  sleep(1);
//
//  msg = "{"
//        "\"operation\":\"logout\","
//        "\"userId\":\"123\","
//        "\"userType\":\"STDBIZ.SMS.PERSON@RM\","
//        "\"payload\":{"
//        "    \"userId\":\"123\""
//        "  }"
//        "}";
//  tws_sendframe(&ctx, (uint8_t *) msg, strlen(msg), FRM_TXT);
//  tws_receiveframe(&ctx, &buff, &buff_size, &frm_type);
//  printf("logout: %s\n", buff);

  tws_close(&ctx);
  free(buff);
  return (0);
}
