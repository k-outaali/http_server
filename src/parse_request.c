#include "../inc/parse_request.h"
#include "../inc/debug.h"
#include <string.h>
#include <stdio.h>
/*
char req[1000] = "GET /hello.txt HTTP/1.1\r\nUser-Agent: curl/7.64.1\r\nHost: www.example.com\r\nAccept-Language: en, min\r\n\r\n";

int main(){
    fields_t result = parse_request(req, 20);
    printf("%s %s %s\n%s %s %s\n", result.method, result.uri, result.version, result.host, result.user_agent, result.accept_language); 
    return 0;
}
*/
fields_t parse_request(char * frame, int length){
    fields_t usefulData;
    char * httpElement = strtok(frame, " ");
    check(httpElement==NULL, "No method\n");
    //printf("%s\n", httpElement);
    strncpy(usefulData.method, httpElement, MAX_METHOD_LEN);
    httpElement = strtok(NULL, " ");
    //printf("%s\n",httpElement);
    check(httpElement==NULL, "No uri\n");
    strncpy(usefulData.uri, httpElement, MAX_URI_LEN);
    httpElement = strtok(NULL, "\r");
    //printf("%s\n",httpElement);
    check(httpElement==NULL, "No version\n");
    strncpy(usefulData.version, httpElement, MAX_VERSION_LEN);
    while ((httpElement = strtok(NULL, " "))!=NULL){
        //printf("%s",httpElement);
        //httpElement = strtok(NULL, " ");
        check(httpElement==NULL, "Error format");
       // int i = 0;
       // printf("%d %x\n", strlen(httpElement), httpElement[0]);  
       // printf("\n");
        if (strcmp(httpElement, "\nHost:")==0){
          //  printf("in host\n", httpElement);
            httpElement = strtok(NULL, "\r");
            strncpy(usefulData.host, httpElement, MAX_HOST_LEN);
        }
        else if (strcmp(httpElement, "\nUser-Agent:")==0){
            httpElement = strtok(NULL, "\r");
            strncpy(usefulData.user_agent, httpElement, MAX_USERAGENT_LEN);
        }
        else if (strcmp(httpElement, "\nAccept-Language:")==0){
            httpElement = strtok(NULL, "\r");
            strncpy(usefulData.accept_language, httpElement, MAX_ACCEPTLANG_LEN);
        }
        else {
            //printf("%s\n", httpElement);
            httpElement = strtok(NULL, "\r");
        }
    }
    
    return usefulData;
}