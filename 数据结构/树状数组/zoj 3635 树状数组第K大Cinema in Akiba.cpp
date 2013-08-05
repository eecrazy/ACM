#include <cstdio>
#define maxn 50005
int c[maxn];
int ans[maxn];
int n,m;
int lowbit(int x)
{
	return x&-x;
}
void fillone()
{
	for(int i=i;i<=n;i++)
		c[i]=lowbit(i);
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
int sumseek (int k)
{
    int ans = 0, sum = 0, i;
    for (i = 18; i >= 0; i--)
    {
        ans += (1 << i);
        if (ans >= n || sum + c[ans] >= k) ans -= (1 << i);
        else sum += c[ans];
    }
    return ans + 1;
}
int add(int i)
{
	while(i<maxn)
	{
		c[i]--;
		i+=lowbit(i);
	}
}
int main()
{
	int a;
	while(scanf("%d",&n)!=EOF)
	{
	    fillone();
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&a);
			int p=sumseek(a);
			ans[i]=p;
			add(p);
		}
		scanf("%d",&m);
		int flag=1;
		while(m--)
		{
			if(flag==0)
				printf(" ");
			flag=0;
			scanf("%d",&a);
			printf("%d",ans[a]);
		}
		printf("\n");
	}
}
