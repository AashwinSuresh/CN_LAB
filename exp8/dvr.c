#include<stdio.h>
#define MAX 10
#define inf 999

void distanceVectorRouting(int n , int cost[MAX][MAX]){
    int dist[MAX][MAX];
    int next[MAX][MAX];
    int updated=1;

    for(int i =1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i==j){
                dist[i][j]=0;                                                    
                next[i][j]=i;
            }
            else if(cost[i][j]!=-1){
                dist[i][j]=cost[i][j];
                next[i][j]=j;
            }
            else{
                dist[i][j]=inf;
                next[i][j]=-1;
            }
        }
    }


    while(updated==1){
        updated=0;
        for(int i =1;i<=n;i++){
            for(int j=1;j<=n;j++){
                for(int k =1;k<=n;k++){
                    // if(dist[i][k]!=inf && dist[k][j]!=inf){
                        if(dist[i][j]>(dist[i][k]+dist[k][j])){
                            dist[i][j]=(dist[i][k]+dist[k][j]);
                            next[i][j]=next[i][k];
                            updated=1;
                        }
                    // }
                }
            }
        }   
    }





    for (int i = 1; i <= n; i++) {
        printf("\nRouter %d:\n", i);
        printf("Dest\tCost\tNext Hop\n");

        for (int j = 1; j <= n; j++) {
            if (dist[i][j] >= inf) {
                printf("%d\t-\t-\n", j);
            } else {
                printf("%d\t%d\t%d\n", j, dist[i][j], next[i][j]);
            }
        }
    }
}






int main() {
    int n,cost[MAX][MAX];

    printf("Enter number of routers: ");
    scanf("%d", &n);

    printf("Enter cost matrix (Use -1 for no direct connection):\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d",&cost[i][j]);
        }
    }

    distanceVectorRouting(n, cost);

    return 0;
}