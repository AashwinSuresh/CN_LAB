#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void main(){
    struct sockaddr_in serveraddr,clientaddr;
    char buffer[1024];
    int server_socket = socket(AF_INET,SOCK_DGRAM,0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(4444);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(server_socket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    bzero(buffer,1024);
    
    int addr_size = sizeof(clientaddr);
    recvfrom(server_socket,buffer,1024,0,(struct sockaddr*)&clientaddr,&addr_size);
    char rev[1024];
    for(int i = 0;i<strlen(buffer);i++){
        rev[i]=buffer[strlen(buffer)-i-1];
    }
    rev[strlen(buffer)]='\0';
    sendto(server_socket,rev,strlen(rev),0,(struct sockaddr*)&clientaddr,addr_size);
}