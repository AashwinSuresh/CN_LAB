#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

struct sockaddr_in client_list[1000];
int client_count=0;

int client_find(struct sockaddr_in clientaddr){
    for(int i=1;i<=client_count;i++){
        if(client_list[i].sin_addr.s_addr == clientaddr.sin_addr.s_addr){
            if(client_list[i].sin_port == clientaddr.sin_port){
                return i;
            }
        }
    }
    return -1;
}
void main(){
    struct sockaddr_in serveraddr,clientaddr;
    char buffer[1024];
    int server_socket = socket(AF_INET,SOCK_DGRAM,0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(4444);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(server_socket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    while(1){
        int addr_size = sizeof(clientaddr);
        bzero(buffer,1024);
        recvfrom(server_socket,buffer,1024,0,(struct sockaddr*)&clientaddr,&addr_size);
        int flag1=client_find(clientaddr);
        int client_id;
        if(flag1==-1){
            client_count+=1;
            client_list[client_count]=clientaddr;
            client_id=client_count;
            printf("\nNEW CLIENT CREATED WITH CLIENT ID : %d\n",client_id);
            continue;
        }
        else{
            client_id = flag1;
        }
        char mssg[1300];
        sprintf(mssg,"CLIENT %d : %s ",client_id,buffer);
        printf("\n%s\n",mssg);
        if (fork()==0){
            for(int i=1;i<=client_count;i++){

                if(client_list[i].sin_addr.s_addr != clientaddr.sin_addr.s_addr || 
                    client_list[i].sin_port != clientaddr.sin_port) {

                    int addr = sizeof(client_list[i]);
                    sendto(server_socket,mssg,1024,0,(struct sockaddr*)&client_list[i],addr);   
                }
            }
            exit(0);
        }
    }
}