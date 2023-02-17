#ifndef DEBUG_H
#define DEBUG_H

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define check(COND, MSG,...)    if(COND){\
                                    fprintf(stderr, "[ERROR] file: %s line: %d errno: %s msg:" MSG "\n", __FILE__, __LINE__, strerror(errno), ##__VA_ARGS__);\
                                    exit(EXIT_FAILURE);\
                                }

#endif