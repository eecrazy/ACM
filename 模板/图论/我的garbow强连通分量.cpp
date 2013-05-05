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
int sta[maxn],top1;
int stack[maxn],top2;
int belg[maxn];
int low[maxn];
void init()
{
	memset(head,0,sizeof(haed));
	memset(belg,0,sizeof(belg));
	memset(low,0,sizeof(low));
	ansi=0;
	top1=0;
	top2=0;
}
void add(int a,int b)
{
	edge[ansi].to=b;
	edge[ansi].next=head[a];
	haed[a]=ansi++;
}
int bfs(int cur,int lay,int &scc_num)
{
	sta[++top1]=cur;
	stack[++top2]=cur;
	for(int i=head[cur];i!=-1;i=edge[i].next)
	{
		if(!low[edge[i].to])
		{
			bfs(edge[i].to,lay,scc_num);
		}
		else if(belg[edge[i].to]==0)
		{
			while(low[stack[top2]]>low[edge[i].to])
				--top2;
		}
	}
	if(stack[top2]==cur)
	{
		top2--;
		scc_num++;
		do
		{
			belg[sta[top1]]==scc_num;
		}while(sta[top1--]!=cur);
	}
	return 0;
}
int garbow(int n)
{
	int scc_num=0;
	int lay=0;
	for(int i=0;i<n;i++)
	{
		if(low[i]==0)
			bfs(i,lay,scc_num);
	}
	return scc_num;
}
int main()
{

}