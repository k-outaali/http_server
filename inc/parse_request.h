#ifndef PARSE_H
#define PARSE_H

#define MAX_URI_LEN 128
#define MAX_HOST_LEN    128
#define MAX_VERSION_LEN 10
#define MAX_METHOD_LEN  10
#define MAX_USERAGENT_LEN   256
#define MAX_ACCEPTLANG_LEN  20

typedef struct {
    char user_agent[MAX_USERAGENT_LEN];
    char uri[MAX_URI_LEN];
    char host[MAX_HOST_LEN];
    char accept_language[MAX_ACCEPTLANG_LEN];
    char method[MAX_METHOD_LEN];
    char version[MAX_VERSION_LEN];
} fields_t;

fields_t parse_request(char * frame, int length);
#endif