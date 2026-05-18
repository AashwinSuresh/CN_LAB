#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


void main(){
    struct sockaddr_in serveraddr;
    char buffer[1024];

    int clientsocket = socket(AF_INET,SOCK_STREAM,0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(4444);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientsocket,(struct sockaddr *)&serveraddr, sizeof(serveraddr));
    printf("connected to server succesfully");

    strcpy(buffer,"hello from client");
    send(clientsocket,buffer,strlen(buffer),0);

    bzero(buffer,sizeof(buffer));
    recv(clientsocket,buffer,1024,0);
    printf("data recieved : %s\n",buffer);

    close(clientsocket);
}