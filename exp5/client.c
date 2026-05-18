#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

void main(){
    struct sockaddr_in serveraddr;
    int buffer[1024];
    int idx=0;
    int row,col,copy[100][100];
    int client_socket = socket(AF_INET,SOCK_DGRAM,0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(4444);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("\nenter the no of rows and coloumn of the matrix : ");
    scanf("%d%d",&row,&col);

    printf("\n enter the matrix elements : ");
    for(int i =0;i<row;i++){
        for(int j=0;j<col;j++){
            scanf("%d",&copy[i][j]);
            buffer[idx++]=copy[i][j];
        }
    }
    int addr_size = sizeof(serveraddr);
    sendto(client_socket,&row,sizeof(int),0,(struct sockaddr*)&serveraddr,addr_size);
    sendto(client_socket,&col,sizeof(int),0,(struct sockaddr*)&serveraddr,addr_size);
    sendto(client_socket,&buffer,row*col*sizeof(int),0,(struct sockaddr*)&serveraddr,addr_size);
}
