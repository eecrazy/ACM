#include <iostream>
#include <cstdio>
#include <math.h>
#include <algorithm>
using namespace std;


double a[10000][2];
int n,s,t;
double com(int i,int j)
{
    return sqrt((a[i][0]-a[j][0])*(a[i][0]-a[j][0])+(a[i][1]-a[j][1])*(a[i][1]-a[j][1]));
}
int v[1001];
void make(int x)
{
    v[x]=x;
}
int find(int x)
{
    if(v[x]!=x)v[x]=find(v[x]);
    return v[x];
}
void uni(int x,int y)
{
    if(x<y)v[y]=x;
    else v[x]=y;
}
struct edge
{
    int x,y;
    double  w;
}e[10000];
bool cmp(edge e1,edge e2)
{
    return  (e1.w<e2.w);
}
int main()
{
    freopen("in.c","r",stdin);
    while(scanf("%d",&n)!=EOF,n)
    {
        scanf("%d%d",&s,&t);
        for(int i=1;i<=n;i++)
        {
            scanf("%lf%lf",&a[i][0],&a[i][1]);
        }
        int num=0;
         double ans=0;
        for(int i=1;i<=n-1;i++)
        for(int j=i+1;j<=n;j++)
        {
            e[num].x=i;
            e[num].y=j;
            e[num].w=com(i,j);
            if((i==s&&j==t)||(i==t&&j==s)){ans=e[num].w;e[num].w=0;}
            num++;
        }
        sort(e,e+num,cmp);
        for(int i=1;i<=n;i++)
        make(i);
        int s1,s2;
        int cnt=0;
        for(int i=0;i<num;i++)
        {
            s1=find(e[i].x);
            s2=find(e[i].y);
            if(s1!=s2)
            {
                ans+=e[i].w;
                uni(s1,s2);
                cnt++;
            }
            if(cnt==n-1)break;
        }
        printf("%.2lf\n",ans);
    }
}
