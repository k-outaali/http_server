#include<sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<stdlib.h>
#include<debug.h>
#include<unistd.h>

#define CONNECTION_PORT 3500
int main(){
    int socket_descriptor,status,length_address,client_socket;
    char storage_buffer[80];
    ssize_t read_status;
    socket_descriptor=socket(AF_INET,SOCK_STREAM,0); 
    check(socket_descriptor>0,"Socket creation failed");
    // server and client address structures
    struct sockaddr_in server_address;
    struct sockaddr_in connection_address;
    //  initializing structure elements for address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(CONNECTION_PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_zero[8]='\0';
    
    // bind the socket with the values address and port from the sockaddr_in structure
    status=bind(socket_descriptor, (struct sockaddr*)&server_address, sizeof(struct sockaddr));
    check(status<0,"Couldn't bind socket");
    //listen on a specified port with a max of 5 requests
    status=listen(socket_descriptor,5);
    check(status<0,"anable to listen to connections");
    length_address=sizeof(connection_address);
    client_socket=accept(socket_descriptor,(struct sockaddr *)&connection_address,&length_address);
    check(client_socket<0,"Couldn't establish connection with client");
    read_status= read(client_socket,storage_buffer,80);
    check(read_status==-1,"Error Reading");
    
}