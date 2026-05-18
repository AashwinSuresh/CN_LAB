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
    struct sockaddr_in serveraddr,clientaddr;
    char buffer[1024];
    int server_socket = socket(AF_INET,SOCK_DGRAM,0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(4444);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(server_socket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    
    int addr_size = sizeof(clientaddr);
    while(1){
        bzero(buffer,1024);
        recvfrom(server_socket,buffer,1024,0,(struct sockaddr*)&clientaddr,&addr_size);

        printf("\nmessage recieved from client : %s",buffer);

        if(fork()==0){
            time_t current_time = time(NULL);
            char *timestring = ctime(&current_time);

            printf("\nsending current time to client (from the child process) : %s\n",timestring);

            sendto(server_socket,timestring,strlen(timestring)+1,0,(struct sockaddr*)&clientaddr,addr_size);

            exit(0);

        }
    }
    close(server_socket);
}