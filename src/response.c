#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/response.h"
#include "../inc/parse_request.h"

size_t process_request(fields_t fields, char * response_headers, char * response_data){
    resp_fields_t respFields;
    if (strcmp(fields.method, "GET\n")){
        respFields = genGETResponse(fields, NULL);
    }
    generateRawHeaders(&respFields, response_headers);
    return (size_t)atoi(respFields.content_length);
}

resp_fields_t genGETResponse(fields_t reqFields, char * response_data){
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
            fillResponse(&reqFields, &respFields,  "text/html", "200 OK", resource);
            fclose(resource);
        }
        else {
            FILE * notfound = fopen("default_pages/404_notfound.html", "rb");
            if (notfound != NULL){
                fillResponse(&reqFields, &respFields,  "text/html", "404 Not Found", notfound);
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
    size_t length = fillResponseData(resource);
    snprintf(response->content_length,MAX_CONTENTLENGTH_LEN, "%ld", length);
    return retval;
}

size_t fillResponseData(FILE * resource){
    size_t length = 0;
    if (resource != NULL){
        size_t file_size;
        fseek(resource, 0, SEEK_END);
        file_size = ftell(resource);
        fseek(resource, 0, SEEK_SET);
        response.response_data = (char *)malloc(file_size);
        if (response.response_data != NULL){
            length = fread(response.response_data, 1, file_size, resource);
        }
    }
    return length;
}

status_t generateRawHeaders(resp_fields_t *responseFields, char *response){
    status_t retval;
    if (strlen(responseFields->version) != 0 && strlen(responseFields->code) != 0){
        sprintf(response, "%s %s\r\n", responseFields->version, responseFields->code);
        addToHeader(response, "Server", responseFields->server);
        addToHeader(response, "Content-Type", responseFields->content_type);
        addToHeader(response, "Content-Length", responseFields->content_length);
        sprintf(response + strlen(response), "\r\n");
        retval = SUCCESS;
    }
    else {
        retval = FAIL;
    }
    return retval;
}

status_t addToHeader(char *response, char * key, char * value){
    status_t retval;
    if (response != NULL && key != NULL && value != NULL){
        if (strlen(key) != 0 && strlen(value) != 0){
            snprintf(response + strlen(response), MAX_BUFFER_SIZE, "%s: %s\r\n", key, value);
            retval = SUCCESS;
        }
        else {
            retval = FAIL;
        }
    }
    else {
        retval = FAIL;
    }
    return retval;
}