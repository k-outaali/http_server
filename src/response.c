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
            fillResponse(&reqFields, &respFields, "text/html", "200 OK", index);
            fclose(index);
        }
        else {
            FILE * notfound = fopen("default_pages/404_notfound.html", "rb");
            if (notfound != NULL){
                fillResponse(&reqFields, &respFields, "text/html", "404 Not Found", notfound);
                fclose(notfound);
            }
            else {
                printf("please create notfound page\n");
            }
        }
    }
    else if (strcmp(reqFields.uri,"/favicon.ico")==0){
        char path[8+MAX_URI_LEN] = "website";
        strncat(path, reqFields.uri, MAX_URI_LEN);
        printf("%s\n", path);
        FILE * resource = fopen(path, "rb");
        if (resource != NULL){
            fillResponse(&reqFields, &respFields, "image/x-icon", "200 OK", resource);
            fclose(resource);
        }
        else {
            fillResponse(&reqFields, &respFields, NULL, "404 Not Found", NULL);
        }
    }
    else {
        char path[8+MAX_URI_LEN] = "website";
        strncat(path, reqFields.uri, MAX_URI_LEN);
        printf("%s\n", path);
        FILE * resource = fopen(path, "rb");
        if (resource != NULL){
            fillResponse(&reqFields, &respFields, "text/html", "200 OK", resource);
            fclose(resource);
        }
        else {
            FILE * notfound = fopen("default_pages/404_notfound.html", "rb");
            if (notfound != NULL){
                fillResponse(&reqFields, &respFields, "text/html", "404 Not Found", notfound);
                fclose(notfound);
            }
            else {
                printf("please create notfound page\n");
            }
        }
    }
    return respFields;

}

status_t fillResponse(fields_t * request,resp_fields_t * response, char * content_type, char * code, FILE * resource){
    status_t retval;
    strncpy(response->code, code, MAX_CODE_LEN);
    if (content_type != NULL){
        strncpy(response->content_type, content_type, MAX_CONTENTTYPE_LEN);
    }
    strcpy(response->server, "SOK");
    strncpy(response->version, request->version, MAX_VERSION_LEN);
    if (resource != NULL){
        long file_size;
        fseek(resource, 0, SEEK_END);
        file_size = ftell(resource);
        if (file_size<=MAX_DATA_LEN){
            fseek(resource, 0, SEEK_SET);
            fread(response->data, 1, file_size, resource);
            response->data[file_size] = '\0'; // null-terminate the string
            retval = SUCCESS;
        }
        else {
            retval = FAIL;
        }
    }
    else {
        retval = SUCCESS;
    }
    return retval;
}