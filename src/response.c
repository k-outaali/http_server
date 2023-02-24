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
    if (strcmp(reqFields.uri, "/")==0){
        FILE * index = fopen("website/index.html", "rb");
        if (index != NULL){
            long file_size;
            fseek(index, 0, SEEK_END);
            file_size = ftell(index);
            fseek(index, 0, SEEK_SET);
            fread(respFields.data, 1, file_size, index);
            respFields.data[file_size] = '\0'; // null-terminate the string
            //fgets(respFields.data, MAX_DATA_LEN, index);
            strcpy(respFields.code, "200 OK");
        }
        else {
            strcpy(respFields.code, "404 Not Found");
            strcpy(respFields.data, "<h1>Error 404 :</h1><h2>File index.html Not Found</h2>");
        }
        fclose(index);
    }
    else {
        char path[8+MAX_URI_LEN] = "website";
        strncat(path, reqFields.uri, MAX_URI_LEN);
        printf("%s\n", path);
        FILE * resource = fopen(path, "rb");
        if (resource != NULL){
            long file_size;
            fseek(resource, 0, SEEK_END);
            file_size = ftell(resource);
            fseek(resource, 0, SEEK_SET);
            fread(respFields.data, 1, file_size, resource);
            respFields.data[file_size] = '\0'; // null-terminate the string
            //fgets(respFields.data, MAX_DATA_LEN, index);
            strcpy(respFields.code, "200 OK");
            fclose(resource);
        }
        else {
            strcpy(respFields.code, "404 Not Found");
            strcpy(respFields.data, "<h1>Error 404 : </h1><h2>File Not Found</h2>");
        }
    }
    strcpy(respFields.version, reqFields.version);
    strcpy(respFields.server, "SOK");
    strcpy(respFields.content_type, "text/html");
    return respFields;

}