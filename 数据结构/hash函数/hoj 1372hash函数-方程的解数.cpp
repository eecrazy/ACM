#include <cstdio>
#include<string.h>
#include<cmath>
using namespace std;
#define max 4000037
int k[7],p[7];
int n,m,mid,total;
long answer[max],amount[max],use[max];
long locate(long s)
{
    long h=s;
    while(h<0)h+=max;
    while(h>=max)h-=max;
    while(use[h]&&answer[h]!=s)
    {
        h++;
        if(h>=max)h-=max;
    }
    return h;
}
void insert(long s)
{
    long pos=locate(s);
    if(!use[pos])
    {
        use[pos]=1;
        answer[pos]=s;
    }
    amount[pos]++;
}
void firsthalf(long d,long s)
{
    if(d==mid)
    {
        insert(s);
        return ;
    }
    long t=0;
    for(int i=1; i<=m; i++)
    {
        t=k[d];
        if(t!=0&&i!=1)
         t=t*pow((double)i,(double)p[d]);
        firsthalf(d+1,t+s);
    }
}
void find(long d,long s)
{
    if(d==n)
    {
        long pos;
        s=-s;
        pos=locate(s);
        if(answer[pos]==s)
            total+=amount[pos];
        return ;
    }
    long t=0;
    for(int i=1; i<=m; i++)
    {
        t=k[d];
        if(t!=0&&i!=1)
        t=t*pow((double)i,(double)p[d]);
        find(d+1,t+s);
    }
}
int main()
{

    while(scanf("%d%d",&n,&m)!=EOF)
    {
        total=0;
        memset(use,0,sizeof(use));
        memset(amount,0,sizeof(amount));
        memset(answer,0,sizeof(answer));
        for(int i=0; i<n; i++)
        {
            scanf("%d%d",&k[i],&p[i]);
        }
        mid=n/2;
        firsthalf(0,0);
        find(mid,0);
        printf("%d\n",total);
    }
    return 0;
}