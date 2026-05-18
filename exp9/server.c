#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>


void handle_client(int newsocket){
    int pid = getpid();
    char buffer[1024],filename[100];
    recv(newsocket,filename,100,0);
    FILE *fp = fopen(filename,"r");
    if(fp==NULL){
        printf("\nerror opening file\n");
        sprintf(buffer," file not found and the pid is : %d\n",pid);
        write(newsocket,buffer,1024);
    }
    else{
        printf("\n file found sending it to the client .. \n");
        sprintf(buffer," file  found and the pid is : %d\n",pid);
        printf("\nthis is the file content : \n");
        while(fgets(buffer,1024,fp)!=NULL){
            printf("%s",buffer);
            write(newsocket,buffer,1024);
        }
    }
    fclose(fp);
    // close(newsocket);
    exit(0);
}


void main(){
    struct sockaddr_in serveraddr,clientaddr;
    int server_socket = socket(AF_INET,SOCK_STREAM,0);

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(4444);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int addrlen = sizeof(serveraddr);
    bind(server_socket,(struct sockaddr*)&serveraddr,addrlen);
    listen(server_socket,7);
    

    
    while(1){
        int newsocket = accept(server_socket,(struct sockaddr*)&clientaddr,&addrlen);
        if (fork()==0){
            close(server_socket);
            handle_client(newsocket);
        }
        close(newsocket);
    }
    exit(0);
}
    