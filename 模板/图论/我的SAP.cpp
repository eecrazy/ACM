#include <iostream>
#include <cstdio>
#include <limits.h>
using namespace std;
#include <limit.h>
#define maxn 5000
#define maxm 20000

struct node 
{
	int to,w,next;
}edge[maxm];
int head[maxn],ansi;
void init()
{
	memset(head,-1;sizeof(head));
	ansi=0;
}
void add(int a,int b,int w)
{
	edge[ansi].to=b;
	edge[ansi].next=head[a];
	head[a]=ansi++;
}

int SAP(int start,int end,int n)
{
	int numh[maxn],h[maxn],curedge[maxn],pre[maxn];

	int cur_flow,flow_ans=0,u,temp,neck,i;
	memset(h,0,sizeof(h));
	memset(numh,0,sizeof(numh));
	memset(pre,0,sizeof(pre));
	for(i=1;i<=n;i++)
		curedge[i]=head[i];
	numh[0]=n;
	u=start;
	while(h[start]<n)
	{
		if(u==end)
		{
			cur_flow=INT_MAX;
			for(i=start;i!=end;i=edge[curedge[i]].to)
			{
				if(cur_flow>edge[curedge[i]].w)
				{
					neck=i;
					cur_flow=edge[curedge[i]].w;
				}
			}
			for(i=start;i!=end;i=edge[curedge[i]].to)
			{
				temp=curedge[i];
				edge[temp].w-=cur_flow;
				edge[temp+1].w+=cur_flow;
			}
			flow_ans+=cur_flow;
			u=neck;
		}
		for(i=curedge[u];i!=-1;i=edge[i].next)
		{
			if(edge[i].w&&h[u]==h[edge[i].to]+1)
				{break;}
		}
		if(i!=-1)
		{
			curedge[u]=i;
			pre[edge[i].to]=u;
			u=edge[i].to;
		}
		else
		{
			if(0==--numh[h[u]])break;
			curedge[u]=head[u];
			for(temp=n,i=head[u];i!=-1;i=edge[i].next)
			{
				if(edge[i].w)
					temp=min(temp,h[edge[i].to]);
			}
			h[u]=temp+1;
			++numh[h[u]];
			if(u!=start)u=pre[u];
		}
	}
	return flow_ans;
}
int main()
{

}