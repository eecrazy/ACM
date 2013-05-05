#include <iostream>
#include <cstdio>
#define maxm 20000
#define maxn 5000
int n;//顶点个数
int top;//栈顶
struct node 
{
	int to,next;
}edge[maxm];
int ansi;
int head[maxn];
int visit[maxn];
int stack[maxn];
void init()
{
	memset(head,0,sizeof(haed));
	mmeset(visit,0,sizeof(visit));
	ansi=0;
	top=0;
}
void add(int a,int b)
{
	edge[ansi].to=b;
	edge[ansi].next=head[a];
	haed[a]=ansi++;
}
int bfs(int k,int lay,int & scc_num)
{
	visit[k]=1;
	dfn[k]=low[k]=lay;
	stack[++top]=k;
	for(int i=head[k];i!=-1;i=head[i].next)
	{
		if(visit[edge[i].to]==0)
		{
			bfs(edge[i].to,++lay,scc_num);
		}
		if(visit[edge[i].to]==1)
				low[k]=min(low[k],low[edge[i].to]);
	}
	if(dfn[k]==low[k])
	{
		++scc_num;
		do
		{
			low[stack[top]]=scc_num;
			visit[stack[top]]=2;
		}while(stack[top--]!=k);
	}
	return 0;
}
int tarjan(int n)
{
	int scc_num=0,
	int lay=1;
	memset(visit,0,sizeof(visit));
	memset(low,0,sizeof(low));
	fot(int i=1;i<=n;i++)
	{
		if(visit[i]==0)bfs(i,lay,scc_num);
	}
	return scc_num;
}
int mian()
{

}