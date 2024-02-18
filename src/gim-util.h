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

#ifndef __GIM_UTIL_H__
#define __GIM_UTIL_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <json.h>

int
gim_util_now(char* holder);

int
gim_util_id(char* holder);

int
gim_util_get_string(json_object* jobj,
                    const char* name,
                    char* holder);

int
gim_util_get_int(json_object* jobj,
                 const char* name,
                 int* holder);

int
gim_util_get_array(json_object* jobj,
                   const char* name,
                   json_object** holder);

#ifdef __cplusplus
};
#endif

#endif // __GIM_UTIL_H__
