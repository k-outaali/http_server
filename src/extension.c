#include "../inc/extensions.h"
#include <stdio.h>
#include <string.h>

extension_t get_extension(char * filename){
    char * cur = filename;
    char * prevCur;
    if (filename == NULL || (cur = strstr(filename, ".")) == NULL){
        return UNKNOWN;
    }
    prevCur = cur;
    while ((cur = strstr(++cur, ".")) != NULL){
        if (cur != NULL){
            prevCur = cur;
        }
    };
    prevCur++;
    
    if (!strcmp(prevCur,"html")){
        return HTML;
    }
    else if (!strcmp(prevCur,"css")){
        return CSS;
    }
    else if (!strcmp(prevCur,"js")){
        return JS;
    }
    else if (!strcmp(prevCur,"json")){
        return JSON;
    }
    else if (!strcmp(prevCur,"php")){
        return PHP;
    }
    else if (!strcmp(prevCur,"xml")){
        return XML;
    }
    else if (!strcmp(prevCur,"xhtml")){
        return XHTML;
    }
    else {
        return UNKNOWN;
    }
}