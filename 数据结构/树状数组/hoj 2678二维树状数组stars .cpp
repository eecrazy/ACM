#include <cstdio>
using namespace std;
#define maxn 1005
int ans[maxn];
int c[maxn][maxn];
int lowbit(int x)
{
	return x&-x;
}
struct point
{
	int x,y,z;
}p[maxn];
bool cmp(point i,point j)
{
	if(i.z!=j.z)return i.z<j.z;
	else if(i.y!=j.y)return i.y<j.y;
	else return i.x<=j.x;
}
int sum(int x,int y)
{
	int ans=0;
	for(int i=x;i>0;i-=lowbit(i))
	{
		for(int j=y;j>0;j-=lowbit(j))
		{
			ans+=c[i][j];
		}
	}
	return ans;
}
void modify(int x,int y,int t)
{
	for(int i=x;i<maxn;i+=lowbit(i))
	{
		for(int j=t;j<maxn;j+=lowbit(j))
		{
			c[i][j]+=t;
		}
	}
}
}
int n;
int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		for(int i=0;i<n;i++)
		{
			scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].z);
			ans[i]=0;
		}
		sort(p,p+n,cmp);
		for(int i=0;i<n;i++)
		{
			ans[sum(p[i].x+1,p[i].y+1)]++;
			modify(p[i].x+1,p[i].y+1,1);
		}
		for(int i=0;i<n-1;i++)
			printf("%d ",ans[i]);
		printf("%d\n",ans[n-1]);
	}

}