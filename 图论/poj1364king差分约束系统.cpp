#include <iostream>
#include <cstdio>
#include <string.h>
#include <string>
using namespace std;
#define INF 1<<28
const int maxn=5010;
const int maxm=20000;
int head[maxn];
int dist[maxn];
bool visit[maxn];
int s,n,m,cnt;
struct node
{
	int to;int w;int next;
};
node edge[maxm];
bool spfa()
{
	s=n;
	int i,k,iq=0,top;
	int queue[maxn];
	int outque[maxn];
	for(i=0;i<=n;i++)
	{
		outque[i]=0;
	}
	queue[iq++]=s;
	visit[s]=true;
	dist[s]=0;
	i=0;
	while(i!=iq)
	{
		top=queue[i];
		visit[top]=false;
		outque[top]++;
		if(outque[top]>n)return false;
		k=head[top];
		while(k>=0)
		{
			if(dist[edge[k].to]>edge[k].w+dist[top])
			{
				dist[edge[k].to]=dist[top]+edge[k].w;
				if(!visit[edge[k].to])
				{
					visit[edge[k].to]=true;
					queue[iq]=edge[k].to;
					iq++;
				}
			}
			k=edge[k].next;
		}
		i++;
	}
	return true;
}
void init()
{
	memset(visit,0,sizeof(visit));
	memset(dist,10000,sizeof(dist));
	dist[n]=0;
	memset(head,-1,sizeof(head));
}
void add(int a,int b,int w)
{
	edge[cnt].to=b;
    edge[cnt].w=w;
    edge[cnt].next=head[a];
    head[a]=cnt++;
}
void read()
{
	int a,b,w;
	string ch;
	init();
	cnt=1;
	for(int i=0;i<m;i++)
	{
		cin>>a>>b>>ch>>w;
		if(ch=="gt")
			add(b+a,a-1,-w-1);
		else
			add(a-1,b+a,w-1);
	}
	for(int i=0;i<=n;i++)
	{
		add(n,i,0);
	}
}
int main()
{
	while(scanf("%d",&n)!=EOF&&n!=0)
	{
	    n++;
		scanf("%d",&m);
		read();
		if(spfa())
			cout<<"lamentable kingdom\n";
		else
			cout<<"successful conspiracy\n";

	}
}
