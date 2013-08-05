#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;
#define maxn 10005
int c[maxn];
int n,m;
int lowbit(int x)
{
	return x&-x;
}

int sum(int x)
{
	int ret=0;
	while(x>0)
	{
		ret+=c[x];
		x-=lowbit(x);
	}
	return ret;
}
void modify(int i,int x)
{
	while(i<maxn)
	{
		c[i]+=x;
		i+=lowbit(i);
	}
}
int main()
{
	int a,b,d;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		memset(c,0,sizeof(c));
		for(int i=-0;i<m;i++)
		{
			scanf("%d%d%d",&a,&b,&d);
			if(d==1)
			{
				fill(c+a-1,c+b,1);
			}

            if(d==0)
			{
				fill(c+a-1,c+b,0);
			}

		}
		int ans=0;
		for(int i=0;i<n;i++)
			if(c[i]==0)ans++;
		printf("%d\n",ans);
	}

}
