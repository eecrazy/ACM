#include <iostream>
#include <cstdio>
#include <string.h>
using namespace std;
#include <cmath>
#define maxn 20005
int p[maxn],dis[maxn];
int find(int x)
{
	if(x==p[x])return x;
	int ss=p[x];
	p[x]=find(p[x]);
	dis[x]+=dis[ss];
	return p[x];
}
void init(int n)
{
	for(int i=0;i<=n;i++)
		p[i]=i;
}
int bs(int x)
{
    if(x>=0)return x;
    else return -x;
}
int main()
{
	int t,n;
	scanf("%d",&t);
	while(t--)
	{
		memset(dis,0,sizeof(dis));
		scanf("%d",&n);
		init(n);
		char op;
		while(scanf(" %c",&op)&&op!='O')
		{
			if(op=='E')
			{
				int x;
				scanf("%d",&x);
				find(x);
				printf("%d\n",dis[x]);
			}
			else
			{
				int u,v;
				scanf("%d%d",&u,&v);
				dis[u]=bs(u-v)%1000;
				p[u]=v;
			}
		}
	}
	return 0;
}
