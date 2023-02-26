#ifndef RESPONSE_H
#define RESPONSE_H
#include "parse_request.h"
#include "server.h"

#define MAX_CONTENTTYPE_LEN 30
#define MAX_CODE_LEN    50
#define MAX_SERVER_LEN  10
#define MAX_DATA_LEN    4096
#define MAX_CONTENTLENGTH_LEN 10

extern response_t response;

typedef enum {
    SUCCESS,
    FAIL
}status_t;

typedef struct {
    char content_type[MAX_CONTENTTYPE_LEN];
    char version[MAX_VERSION_LEN];
    char server[MAX_SERVER_LEN];
    char code[MAX_CODE_LEN];
    char content_length[MAX_CONTENTLENGTH_LEN];
} resp_fields_t;



size_t process_request(fields_t fields, response_t *response);
resp_fields_t genGETResponse(fields_t reqFields, char * response_data);
status_t fillResponse(fields_t * request,resp_fields_t * response, char * content_type, char * code, FILE * resource);
size_t fillResponseData(FILE * resource);
status_t generateRawHeaders(resp_fields_t *responseFields, char *response);
status_t addToHeader(char *response, char * key, char * value);


#endif