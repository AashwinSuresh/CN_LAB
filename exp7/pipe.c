// THIS IS AN EXAMPLE TO UNDERSTAND PIPE 
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void main(){
    int num = 1;  
    num2 =100;
    int fd[2]; // HERE fd[1] ---> write , fd[0] ---> read
    pipe(fd);
    if (fork()==0){  // CHILD PROCESS
        close(fd[1]); // here child only does read operation
        int curr_value;
        for(int i=0;i<4;i++){
            read(fd[0],&curr_value,sizeof(curr_value));
            printf("\nthe value updated by the parent process(num) : %d\n",curr_value);
        }
    }
    else{ // PARENT PROCESS
        close(fd[0]); // here child only does write operation
        for(){
            num++;
            write(fd[1],&num,sizeof(num));
            printf("\n parent process : %d\n",num);
        }
    }
}