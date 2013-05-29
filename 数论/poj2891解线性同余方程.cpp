#include <cstdio>
void exgcd(long long a,long long b,long long &d,long long &x,long long &y)
{
	if(!b)
	{
		x=1;y=0;d=a;
	}
	else
	{
		exgcd(b,a%b,d,y,x);
		y-=x*(a/b);
	}
}

int main()
{
	long long i,n,a1,r1,a2,r2,ans,a,b,c,d,x0,y0;
	while(scanf("%lld",&n)!=EOF)
	{
		bool flag=1;
		scanf("%lld%lld",&a1,&r1);
		for(i=1;i<n;i++)
		{
			scanf("%lld%lld",&a2,&r2);
			a=a1,b=a2,c=r2-r1;
			exgcd(a,b,d,x0,y0);
			if(c%d)
			{
				flag=0;
			}
			int t=b/d;
			x0=(x0*(c/d)%t+t)%t;
			r1=a1*x0+r1;
			a1=a1*(a2/d);
		}
		if(!flag)
		{
			printf("-1\n");
			continue;
		}
		else
		{
			printf("%lld\n",r1);
		}
	}
}