#ifndef RESPONSE_H
#define RESPONSE_H
#include "parse_request.h"

#define MAX_CONTENTTYPE_LEN 30
#define MAX_CODE_LEN    50
#define MAX_SERVER_LEN  10
#define MAX_DATA_LEN    100

typedef struct {
    char data[MAX_DATA_LEN];
    char content_type[MAX_CONTENTTYPE_LEN];
    char version[MAX_VERSION_LEN];
    char server[MAX_SERVER_LEN];
    char code[MAX_CODE_LEN];
    
} resp_fields_t;


int process_request(fields_t, char *);
resp_fields_t genGETResponse(fields_t);


#endif