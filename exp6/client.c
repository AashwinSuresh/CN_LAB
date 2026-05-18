#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>

void main(){
    struct sockaddr_in serveraddr;
    char buffer[1024];
    strcpy(buffer,"hello from udp client");

    int client_socket = socket(AF_INET,SOCK_DGRAM,0);
    
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(4444);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int addrsize = sizeof(serveraddr);
    strcpy(buffer,"i need time");
    sendto(client_socket,buffer,strlen(buffer),0,(struct sockaddr*)&serveraddr,addrsize);
    bzero(buffer,1024);
    recvfrom(client_socket,buffer,1024,0,(struct sockaddr*)&serveraddr,&addrsize);
    printf("\n the time received from the server is : %s \n",buffer);

    
    
}