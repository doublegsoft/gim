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
#include "gim-util.h"
#include "gim_test.h"

typedef struct gim_client_s
{
  struct tws_ctx        tws;

  char                  user_id[1024];
  char                  convo_id[1024];
}
gim_client_t;

static void signal_handler(int signum)
{
  exit(0);
}

static void on_receive_message(void* data)
{

}

static void on_send_message(void* data)
{

}

static void
login(gim_client_t* client)
{
  char ts[1024];
  char* buff = NULL;
  size_t buff_size;
  int frm_type;
  char msg[4096];

  sprintf(msg,
          "{"
          "\"operation\":\"login\","
          "\"userId\":\"%s\","
          "\"userType\":\"TEST\","
          "\"payload\":{"
          "  }"
          "}",
         client->user_id);
  if (tws_connect(&client->tws, TEST_ADDRESS, TEST_PORT) < 0)
  {
    fprintf(stderr, "Unable to connect!\n");
    return;
  }
  tws_sendframe(&client->tws, (uint8_t *) msg, strlen(msg), FRM_TXT);
  tws_receiveframe(&client->tws, &buff, &buff_size, &frm_type);

  gim_util_now(ts);
  fprintf(stdout, "LOGIN [%s]: %s\n", ts, buff);
}

static void
logout(gim_client_t* client)
{
  char ts[1024];
  char* buff;
  size_t buff_size;
  int frm_type;
  char msg[4096];

  sprintf(msg,
          "{"
          "\"operation\":\"logout\","
          "\"userId\":\"%s\","
          "\"userType\":\"TEST\","
          "\"payload\":{"
          "  }"
          "}",
          client->user_id);
  tws_sendframe(&client->tws, (uint8_t *)msg, strlen(msg), FRM_TXT);
  tws_receiveframe(&client->tws, &buff, &buff_size, &frm_type);

  gim_util_now(ts);
  fprintf(stdout, "LOGOUT [%s]: %s\n", ts, buff);
  tws_close(&client->tws);
}

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    fprintf(stdout,
        "usage:\n"
        "\tgim_client <userId> <convoId>\n\n");
    return 0;
  }
  gim_client_t client;
  strcpy(client.user_id, "1");

  signal(SIGINT, signal_handler);

  int i = 0;
  login(&client);

  logout(&client);
  return (0);
}
