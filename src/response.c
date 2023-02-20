#include <stdio.h>
#include <string.h>
#include "../inc/response.h"
#include "../inc/parse_request.h"

int process_request(fields_t fields, char * response){
    resp_fields_t respFields;
    if (strcmp(fields.method, "GET\n")){
        respFields = genGETResponse(fields);
    }
    sprintf(response, "%s %s\r\nServer: %s\r\nContent-Type: %s\r\n\r\n%s\r\n",respFields.version, respFields.code, respFields.server, respFields.content_type, respFields.data);
}

resp_fields_t genGETResponse(fields_t reqFields){
    resp_fields_t respFields;
    strcpy(respFields.code, "200 OK");
    strcpy(respFields.version, reqFields.version);
    strcpy(respFields.server, "SOK");
    strcpy(respFields.content_type, "text/html");
    strcpy(respFields.data,"<h1>Hello World!<h2>");
    return respFields;

}