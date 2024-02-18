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

#include "toyws.h"
#include "gim_test.h"

int main(void)
{
	struct tws_ctx ctx;

	/* Buffer params. */
	char *buff;
	int frm_type;
	size_t buff_size;

	buff      = NULL;
	buff_size = 0;
	frm_type  = 0;

	int i = 0;
  if (tws_connect(&ctx, TEST_ADDRESS, TEST_PORT) < 0)
    fprintf(stderr, "Unable to connect!\n");

  char* msg = "hello";
  tws_sendframe(&ctx, (uint8_t *) msg, strlen(msg), FRM_TXT);
  tws_receiveframe(&ctx, &buff, &buff_size, &frm_type);
  printf("%s\n", buff);

  msg = "{}";
  tws_sendframe(&ctx, (uint8_t *) msg, strlen(msg), FRM_TXT);
  tws_receiveframe(&ctx, &buff, &buff_size, &frm_type);
  printf("%s\n", buff);

  msg = "{\"operation\":\"login\"}";
  tws_sendframe(&ctx, (uint8_t *) msg, strlen(msg), FRM_TXT);
  tws_receiveframe(&ctx, &buff, &buff_size, &frm_type);
  printf("%s\n", buff);

  tws_close(&ctx);

	free(buff);
	return (0);
}
