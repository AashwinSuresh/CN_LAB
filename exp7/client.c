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
    char buffer[1024];

    int client_socket = socket(AF_INET,SOCK_DGRAM,0);
    
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(4444);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int addr_size = sizeof(serveraddr);
    if(fork()==0){             //CHILD PROCESS HANDLES THE SENDING PART 
        bzero(buffer,1024);
        strcpy(buffer,"initialize");
        sendto(client_socket,buffer,1024,0,(struct sockaddr*)&serveraddr,addr_size);

        while(1){
            bzero(buffer,1024);
            fgets(buffer,1024,stdin);
            sendto(client_socket,buffer,1024,0,(struct sockaddr*)&serveraddr,addr_size);
        }
    }
    else{                      //PARENT PROCESS HANDLES THE RECIEVING PART 
        while(1){
            bzero(buffer,1024);
            recvfrom(client_socket,buffer,1024,0,(struct sockaddr*)&serveraddr,&addr_size);
            printf("\n%s\n",buffer);
        }
    }
}