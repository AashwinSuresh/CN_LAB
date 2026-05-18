#include<stdio.h>
void main(){
    int in,bsize,bucket=0,n,out;
    printf("\n enter the no of inputs : ");
    scanf("%d",&n);
    printf("\n enter the max bucket size : ");
    scanf("%d",&bsize);
    printf("\n enter the outgoing rate : ");
    scanf("%d",&out);

    while(n>0){
        printf("\n\n\nIncoming packets : ");
        scanf("%d",&in);
        if(in<=(bsize-bucket)){
            bucket+=in;
            printf("\nbucket size %d out of %d",bucket,bsize);
        }
        else{
            printf("\n INCOMING PACKET CANNOT BE ACCOMADATED INTO THE BUCKET");
            printf("\n DROPPED PACKETS : %d",(in-(bsize-bucket)));
            bucket=bsize;
            printf("\nbucket size %d out of %d",bucket,bsize);        
        }
        bucket=bucket-out;
        printf("\nAFTER OUTGOING , BUCKET STATUS: %d ",bucket);
        n--;
    }
}