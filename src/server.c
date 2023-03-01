#include<sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<stdlib.h>
#include"../inc/debug.h"
#include"../inc/parse_request.h"
#include "../inc/response.h"
#include "../inc/server.h"
#include<unistd.h>


char storage_buffer[MAX_BUFFER_SIZE];
response_t response;

size_t data_size;
int main(int argc,char **argv){
    if (argc!=2){
        printf("Usage : ./server <port>\n");
        return -1;
    }
    int socket_descriptor,status,length_address,client_socket;
    ssize_t read_status;
    socket_descriptor=socket(AF_INET,SOCK_STREAM,0); 
    check(socket_descriptor<0,"Socket creation failed");
    // server and client address structures
    struct sockaddr_in server_address;
    struct sockaddr_in connection_address;
    //  initializing structure elements for address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(atoi(argv[1]));
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_zero[8]='\0';
    
    // bind the socket with the values address and port from the sockaddr_in structure
    status=bind(socket_descriptor, (struct sockaddr*)&server_address, sizeof(struct sockaddr));
    check(status<0,"Couldn't bind socket");
    //listen on a specified port with a max of 5 requests
    status=listen(socket_descriptor,5);
    check(status<0,"anable to listen to connections");
    length_address=sizeof(connection_address);
    while (1)
    {
        client_socket=accept(socket_descriptor,(struct sockaddr *)&connection_address,&length_address);
        check(client_socket<0,"Couldn't establish connection with client");
        read_status= read(client_socket,storage_buffer,MAX_BUFFER_SIZE);
        check(read_status==-1,"Error Reading");
        storage_buffer[read_status] = '\0';
        if (read_status){
            printf("Message from client: %s \n",storage_buffer);
            fields_t fields = parse_request(storage_buffer,read_status);
            data_size = process_request(fields, &response);
            printf("%s", response.response_headers);
            write(client_socket, response.response_headers, strlen(response.response_headers));
            if (response.response_data != NULL){
                write(client_socket, response.response_data, data_size);
                free(response.response_data);
            }
            else {
                printf("no print\n");
            }
        }
        close(client_socket);
    }
    
    close(socket_descriptor);
    
    

}
