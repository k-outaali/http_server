#include "../inc/parse_request.h"
#include "../inc/debug.h"
#include <string.h>
#include <stdio.h>
/*
char req[1000] = "GET /hello.txt HTTP/1.1\nUser-Agent: curl/7.64.1\nHost: www.example.com\nAccept-Language: en, mi";

int main(){
    fields_t result = parse_request(req, 20);
    printf("%s %s %s\n%s %s %s\n", result.method, result.uri, result.version, result.user_agent, result.host, result.accept_language); 
    return 0;
}
*/
fields_t parse_request(char * frame, int length){
    fields_t usefulData;
    char * httpElement = strtok(frame, " ");
    check(httpElement==NULL, "No method\n");
    strncpy(usefulData.method, httpElement, MAX_METHOD_LEN);
    httpElement = strtok(NULL, " ");
    check(httpElement==NULL, "No uri\n");
    strncpy(usefulData.uri, httpElement, MAX_URI_LEN);
    httpElement = strtok(NULL, "\n");
    check(httpElement==NULL, "No version\n");
    strncpy(usefulData.version, httpElement, MAX_VERSION_LEN);
    while ((httpElement = strtok(NULL, " "))!=NULL){
        //httpElement = strtok(NULL, " ");
        check(httpElement==NULL, "Frame error");
        if (strcmp(httpElement, "Host:")==0){
            httpElement = strtok(NULL, "\n");
            strncpy(usefulData.host, httpElement, MAX_HOST_LEN);
        }
        else if (strcmp(httpElement, "User-Agent:")==0){
            httpElement = strtok(NULL, "\n");
            strncpy(usefulData.user_agent, httpElement, MAX_USERAGENT_LEN);
        }
        else if (strcmp(httpElement, "Accept-Language:")==0){
            httpElement = strtok(NULL, "\n");
            strncpy(usefulData.accept_language, httpElement, MAX_ACCEPTLANG_LEN);
        }
        else {
            httpElement = strtok(NULL, "\n");
        }
    }
    
    return usefulData;
}