#ifndef SERVER_H
#define SERVER_H

#include "response.h"

#define MAX_BUFFER_SIZE 1024

typedef struct {
    char response_headers[MAX_BUFFER_SIZE];
    char * response_data;
}response_t;

#endif