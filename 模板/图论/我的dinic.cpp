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
int level[maxn];
int que[maxn];
void init()
{
	memset(head,-1,sizeof(head));
	memset(level,0,sizeof(level));
	ansi=0;
}
void add(int a,int b,int w)
{
	edge[ansi].to=b;
	edge[ansi].next=haed[a];
	head[a]=ansi++;
}
bool makelevel(int s,int t)
{
	memset(level,0,sizeof(level));
	level[s]=1;
	int iq=0;
	que[iq++]=s;
	int i,k;
	int top;
	for(i=0;i<iq;i++)
	{
		top=que[i];
		if(top==1)return true;
		for(k=head[top];k!=-1;k=edge[k].next)
		{
			if(!level[edge[k].to]&&edge[k].w)
			{
				que[iq++]=edge[k].to;
				level[edge[k].to]=level[top]+1;
			}
		}
	}
	return false;
}
int DFS(int now,int maxf,int t)
{
	if(now==t) return maxf;
	int ret=0,f,k;
	for(k=head[now];k!=-1;k=edge[k].next)
	{
		if(edge[k].w&&level[edge[k].to]==level[now]+1)
		{
			f=DFS(edge[k].to,min(maxf-ret,edge[k].w),t);
			edge[k].w-=f;
			edge[k+1].w+=f;
			ret+=f;
			if(ret==maxf)return ret;
		}
	}
	return ret;
}
int dinic(int s,int t)
{
	int ans=0;
	while(makelevel(s,t))ans+=DFS(s,INT_MAX,t);
	return ans;
}
int main()
{
	
}