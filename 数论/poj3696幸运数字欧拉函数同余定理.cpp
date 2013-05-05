//P165有题解，用到了欧拉函数，同于定理。没过呢！！！！
#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

long long gcd(long long a,long long b)
{
	return b==0?a:gcd(b,a%b);
}

long long mo;
long long mul(long long a,long long b)
{
	long long n=0;
	while(b)
	{
		if(b&1)n=(n+a)%mo;
		a=a*2%mo;
		b>>=1;
	}
	return n;
}


long long mul(long long x)
{
	long long n=1,m=10;
	while(x>0)
	{
		if(x&1)n=mul(n,m);
		m=mul(m,m);
		x>>=1;
	}
	return n;
}

int main()
{
	int ca=0;
	while(scanf("%lld",&mo)&&mo)
	{
		printf("Case %d:",++ca);
		mo=mo*9/gcd(mo,8);
		if(gcd(mo,10)!=1)
		{
			printf(" 0\n");continue;
		}
		long long rear=mo,n=mo;
		long long p[50][2];int k=0;
		for(long long i=2;i*i<=n;i++)
		{
			if(n%i==0)
			{
				rear=rear-rear/i;
				do
				{
					n/=i;
				}while(n%i==0);
			}
		}
		if(n>1)
				{rear=rear-rear/n;}
			n=rear;
			for(long long i=2;i*i<=n;i++)
			{
				if(n%i==0)
				{
					p[k][0]=i;
					p[k][1]=0;
					do
					{
						n/=i;
						p[k][1]++;
					}while(n%i==0);
					k++;
				}
			}
			if(n>1)
				{p[k][0]=n;p[k][1]=1;k++;}
			for(int i=0;i<k;i++)
			{
				for(int  j=1;j<=p[i][1];j++)
				{
					if(mul(rear/p[i][0])==1)
					{
						rear/=p[i][0];
					}
				}
			}
			printf(" %lld\n",rear);
	}
	return 0;
}
