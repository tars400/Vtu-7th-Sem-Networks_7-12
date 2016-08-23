#include<iostream> 
#include<stdio.h>
using namespace std;
struct node
{
    int dist[20];
    int from[20];
 }rt[10];
int main()
{
    int dm[20][20]; 
    int i,j,k,n,src,dest,count=0;
    cout<<"enter no of nodes:"<<endl;
    cin>>n;
    cout<<"Enter distance matrix:"<<endl;
    for(i=0;i<n;i++) 
        for(j=0;j<n;j++)
        {
            cin>>dm[i][j];
            dm[i][i]=0;
            rt[i].dist[j]=dm[i][j]; 
            rt[i].from[j]=j;
        }
    do
    {
        count=0;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                for(k=0;k<n;k++)
                     if((rt[i].dist[j])>(dm[i][k]+rt[k].dist[j])) 
                    {
                        rt[i].dist[j]=rt[i].dist[k]+rt[k].dist[j];
                        rt[i].from[j]=k;
                        count++;
                    }
    }while(count!=0);
    
    for(i=0;i<n;i++) 
    {
        cout<<"Router info for router "<<i+1<<endl;
        printf("Dest\tNext Hop\tDist\n");
        for(j=0;j<n;j++)
            printf("%d\t%d\t\t%d\n",j+1,rt[i].from[j]+1,rt[i].dist[j]);
    }
    cout<<"\n enter source and destination:";
    cin>>src>>dest;
    src--;dest--;
    printf("shortest path:\n via router:%d\n shortest distance:%d\n",rt[src].from[dest]+1,rt[src].dist[dest]);
return 0;
}
