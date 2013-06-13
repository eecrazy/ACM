#include <iostream>
#include  <cstdio>
using namespace std;
#define maxn 30005
int a[maxn];
int n,m;
void init(int n)
{
	for(int i=0;i<=n;i++)
	{
		a[i]=i;
	}
}
int find(int x)
{
	if(a[x]==x)
		return a[x];
	else return a[x]=find(a[x]);
}
void uni(int x,int y)
{
	int xx=find(x);
	int yy=find(y);
	if(xx<yy)
		a[yy]=xx;
	if(xx>yy)
		a[xx]=yy;
}
int main()
{
    //freopen("in","r",stdin);
	while(scanf("%d%d",&n,&m),n+m)
	{
	    init(n);
		for(int i=0;i<m;i++)
		{
			int s,e,b;
			scanf("%d",&s);
			for(int j=0;j<s;j++)
			{
				scanf("%d",&e);
				if(j!=0)uni(b,e);
				b=e;
			}
		}
		int sum=1;
		int ff=find(0);
//		for(int i=0;i<n;i++)
//		{
//		    printf("%d ",find(i));}
		for(int i=1;i<n;i++)
		{
		    if(ff==find(i))
				sum++;
		}

		printf("%d\n",sum);
	}
}
