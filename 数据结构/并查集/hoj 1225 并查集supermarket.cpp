#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cmath>
#include <vector>
#include <cstdlib>

using namespace std;
struct node
{
    int pi,di;
}pro[10005];
int fa[10005];
bool cmp(node a,node b)
{
   return a.pi>b.pi;
}
void init()
{
    for(int i=1;i<=10005;i++)
    fa[i]=i;
}
int Find_set(int x)
{
    if(x==fa[x]) return x;
    fa[x]=Find_set(fa[x]);
    return fa[x];
}
int main()
{
   int n;
   while(scanf("%d",&n)==1)
   {
       for(int i=0;i<n;i++)
       scanf("%d%d",&pro[i].pi,&pro[i].di);
       sort(pro,pro+n,cmp);
       init();
       int sum=0;
       for(int i=0;i<n;i++)
       {
           int rt=Find_set(pro[i].di);
           if(rt>0)
           {
               sum+=pro[i].pi;
               fa[rt]=rt-1;
           }
       }
       printf("%d\n",sum);
   }
   return 0;
}
