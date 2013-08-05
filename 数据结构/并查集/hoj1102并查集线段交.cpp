#include <cstdio>
using namespace srd;
int n;
int len[maxn][2];

struct point
{
	int x,y;
}p1[10005],p2[10005];
int mult(point a,point b,point c)
{
	return (a.x-c.x)*(b.y-c.y)-(b.x-c.x)*(a.y-c.y);
}
bool inter(point a,point b,point c,point d)
{
	return max(a.x,b.x)>=min(c.x,d.x)
	&&max(a.y,b.y)>=min(c.y,d.y)
	&&max(c.x,d.x)>=min(a.x,bf.x)
	&&max(c.y,d.y)>=min(a.y,b.y)
	&&mult(c,b,a)*mult(b,d,a)>=0
	&&mult(a,d,c)*mult(d,b,c)>=0;
}
void init()
{
	for(int i=0;i<=n;i++)
		parent[i]=i;
}
void uni(int a,int b)
{
	int x=find(a);
	int y=find(b);
	if(x<y)
		parent[y]=x;
	if(x>y)
		parent[x]=y;
}
void find(int x)
{
	if(x==parent[x])
		return x;
	else return parent[x]=find(parent[x]);

}
int main()
{
	int a,b;
	while(scanf("%d",&n)!=EOF,n)
	{
		init();
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d%d%d",&p1[i].x,&p1[i].y,&p2[i].x,&p2[i].y);
		}
		for(int i=1;i<n;i++)
			for(int j=i+1;j<=n;j++)
			{
				if(inter(p1[i],p2[i],p1[j],p2[j]))
					uni(i,j);
			}
		while(scanf("%d%d",&a,&b),a+b)
		{
			if(find(a)==find(b))
				puts("CONNECTED");
			else
				puts("NOT CONNECTED");
		}
	}
}