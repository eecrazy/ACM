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
		for(int i=0;i<m;i++)
		{
			scanf("%d%d",&a,&b);
				modify(a,1);
				modify(b+1,-1);
		}
		int ans=0;
		for(int i=i;i<=n;i++)
		{
			m=sum(i);
			if(!(m&1))ans++;
		}
		printf("%d\n",ans);
		
	}

}
