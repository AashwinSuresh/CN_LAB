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
    int buffer[1024];
    int row,col,copy[100][100];
    int server_socket = socket(AF_INET,SOCK_DGRAM,0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(4444);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(server_socket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    
    int addr_size = sizeof(clientaddr);

    recvfrom(server_socket,&row,sizeof(int),0,(struct sockaddr*)&clientaddr,&addr_size);
    recvfrom(server_socket,&col,sizeof(int),0,(struct sockaddr*)&clientaddr,&addr_size);
    recvfrom(server_socket,buffer,row*col*sizeof(int),0,(struct sockaddr*)&clientaddr,&addr_size);

    int idx=0;
    for(int i =0;i<row;i++){
        for(int j=0;j<col;j++){
            copy[i][j] = buffer[idx++];
        }
    }

    for(int i =0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("  %d  ",copy[i][j]);
        }
        printf("\n");
    }
}