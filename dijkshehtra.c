#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int src=0;
int dist[6],path[6],visited[6],max=999,min;

void dijkstra(int a[6][6])
{
   int i,j;
   for(i=0;i<6;i++)
   {

       dist[i]=a[src][i];
       path[i]=src;
       visited[i]=0;
   }
   dist[src]=0;
   visited[src]=1;
   for(i=0;i<6;i++)
   {
       for(j=0;j<6;j++)
       {
           if(visited[j]==0)
           {
              if(dist[j]<max)
               {
                   max=dist[j];
                   min=j;
               }
           }
       }

       for(j=0;j<6;j++)
       {
           if(a[min][j]+dist[min]<dist[j]&& visited[j]==0 && a[min][j]!=0)
           {
               dist[j]=a[min][j]+dist[min];
               path[j]=min;
           }
       }
       visited[min]=1;
       max=999;
   }

   for(j=0;j<6;j++)
   {
       printf("%d\n",dist[j]);
   }

}

int main()
{
    int a[6][6]={{0,4,6,7,max,10},{4,0,5,max,max,1},{6,5,0,2,3,max},{7,max,2,0,6,8},{max,max,3,6,0,2},{10,1,max,8,2,0}};

    dijkstra(a);
} 