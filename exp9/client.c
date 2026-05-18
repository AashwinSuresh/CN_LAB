#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

void main(){
    struct sockaddr_in serveraddr;
    int client_socket = socket(AF_INET,SOCK_STREAM,0);
    char buffer[1024],filename[100];
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(4444);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int addrlen = sizeof(serveraddr);
    connect(client_socket,(struct sockaddr*)&serveraddr,addrlen);

    printf("\n enter the file name : ");
    scanf("%s",filename);
    send(client_socket,filename,strlen(filename),0);

    int bytes=100;
    while(bytes>0){
        bytes = read(client_socket,buffer,1024);
        printf("%s : .... [bytes : %d]",buffer,bytes);
    }
    printf("\nexited the loop .. ");
    close(client_socket);
    exit(0);
}