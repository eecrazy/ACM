#include <iostream>
#include <cstdio>
#include <limits.h>
using namespace std;
#define maxn 5000
#define maxm 20000
struct node 
{
	int to,w,next;
}edge[maxm];
int head[maxn],ansi;
int dist[maxn];
int indegree[maxn];
int que[maxn];
int iq;
void init()
{
	memset(head,-1;sizeof(head));
	memset(dist,INT_MAX;sizeof(dist));
	memset(indegree,0;sizeof(indegree));
	ansi=0;
}
void add(int a,int b,int w)
{
	edge[ansi].to=b;
	edge[ansi].next=head[a];
	head[a]=ansi++;
}
void topsort()
{
	int i,k;
	iq=0;
	for(i=1;i<=n;i++)
	{
		if(indegree[i]==0)
		{
			que[iq++]=i;
		}
	}
	for(int i=0;i<iq;i++)
	{
		for(k=head[que[i]];k!=-1;k=edge[k].next)
		{
			indegree[edge[k].to]--;
			if(indegree[edge[k].to]==0)
				que[iq++]=edge[k].to;
		}
	}
	// for(i=0;i<iq;i++)
	// {
	// 	cout<<que[i]<<" ";
	// }cout<<endl;
}
void  solve()
{
	dist[1]=0;
	for(int i=0;i<iq;i++)
	{
		for(k=head[que[i]];k!=-1;k=edge[k].next)
		{
			if(dist[edge[k].to]>dist[que[i]]+edge[k].w)
				dist[edge[k].to]>dist[que[i]]+edge[k].w;
		}
	}
}
int main()
{
	
}