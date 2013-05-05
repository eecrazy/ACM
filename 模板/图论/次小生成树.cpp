// 次小生成树.cpp
#include <iostream>
#include <cstdio>
using namespace std;

#define maxn 1010
#define maxe 100010
int tree[maxn];
int find(int x)
{
	if(tree[x]!=x) tree[x]=find(tree[x]);
	else return tree[x];
}
void merge(int x,int y)
{
	int xx=find(x);
	int yy=find(y);
	if(xx<yy)tree[yy]=xx;
	if(xx>yy)tree[xx]=yy;
}
//kruskal
struct node
{
	int a,b;
	int w;
	bool select;
}edge[maxe];
bool cmp(node a,node b)
{
	if(a.w!=b.w)return a.w<b.w;
	if(a.a!=b.a)return a.a<b.a;
	return a.b<b.b;
}


struct node1
{
	int to;int next;
};
node1 link[maxn];
int i1;
int head[maxn];
int end[maxn];
int length[maxn][maxn];
void kruskal(node *edge,int n,int m)
{
	int k=0;
	int i,x,y;
	int w,v;
	for(i1=0;i1<n;i1++)
	{
		link[i1].to=i1+1;
		link[i1].next=head[i1]+1;
		end[i1+1]=i1;
		head[i1+1]=i1;
	}
	sort(edge+1,edge+1+m,cmp);
	for(i=1;i<=m;i++)
	{
		if(k==n-1)break;
		if(edge[i].w<0)continue;
		x=find(edge[i].a);
		y=find(edge[i].b);
		if(x!=y)
		{
			for(w=head[x];w!=-1;w=link[w].next)
			{
				for(v=head[y];v!=-1;v=link[v].next)
				{
					length[link[w].to][link[v].to]=length[link[v].to][link[w].to]=edge[i].w;
				}
			}
			link[end[y]].next=head[x];
			end[y]=end[x];
			merge(x,y);
			k++;
			edge[i].select=true;
		}
	}
}
int main()
{
	// 初始化建图
	int mst,secmst;
	kruskal(edge,n,m);
	mst=0;
	for(i=1;i<=m;i++)
	{
		if(edge[i].select)mst+=edge[i].w;
	}
	secmst=INF;
	for(i=1;i<=m;i++)
	{
		if(!edge[i].select)secmst=min(secmst,mst+edge[i].w-length[edge[i].a][edge[i].b]);
	}
}