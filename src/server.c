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
#include<unistd.h>
#define MAX_BUFFER_SIZE 1024
#define CONNECTION_PORT 3600
int main(int argc,char **argv){
    if (argc!=2){
        printf("Usage : ./server <port>\n");
        return -1;
    }
    int socket_descriptor,status,length_address,client_socket;
    char storage_buffer[MAX_BUFFER_SIZE];
    char response_buffer[MAX_BUFFER_SIZE];
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
        printf("Message from client: %s \n",storage_buffer);
        //printf("%d\n",read_status);
        fields_t fields = parse_request(storage_buffer,read_status);
        //printf("%s %s %s %s %s\n",fields.method,fields.version,fields.uri, fields.user_agent, fields.host);
        process_request(fields, response_buffer);
        printf("%s", response_buffer);
        write(client_socket, response_buffer, strlen(response_buffer));

    }
    close(socket_descriptor);
    
    
    

}
