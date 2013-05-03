//hoj1802&&poj2142
#include <cstdio>
using namespace std;
#include <iostream>
#define INF 999999999
long long ABS(long long x)
{
	return x<0?(-x):x;
}
void exgcd(long long a,long long b,long long &x,long long &y,long long &d)
{
	if(!b)
		{d=a;x=1;y=0;}
	else
		{exgcd(b,a%b,y,x,d);y-=x*(a/b);}
}
int main()
{
	long long a,b,c,sub,d;
	while(scanf("%lld%lld%lld",&a,&b,&c)!=EOF&&a+b+c)
	{
		bool ifsub=0;
		if(a<b)
		{
			ifsub=1;
			sub=a;
			a=b;
			b=sub;
		}
		long long x0,y0;
		exgcd(a,b,x0,y0,d);
		x0=x0*(c/d);
		y0=y0*(c/d);
		long long t=y0*(d/a);
		long long ans,anst;
        long long min=INF;
		for(long long i=t-50002;i<=t+50002;i++)
		{
			if(ABS(x0+b/d*i)+ABS(y0-a/d*i)<min)
			{
				ans=a*ABS(x0+b/d*i)+b*ABS(y0-a/d*i);
				anst=i;
				min=ABS(x0+b/d*i)+ABS(y0-a/d*i);
			}
			else if(ABS(x0+b/d*i)+ABS(y0-a/d*i)==min)
			{
				if(a*ABS(x0+b/d*i)+b*ABS(y0-a/d*i)<ans)
				{
					ans=a*ABS(x0+b/d*i)+b*ABS(y0-a/d*i);
					anst=i;
					min=ABS(x0+b/d*i)+ABS(y0-a/d*i);
				}
			}
		}
		if(!ifsub)
		{
			printf("%lld %lld\n",ABS(x0+b/d*anst),ABS(y0-a/d*anst));
		}
		else
			printf("%lld %lld\n",ABS(y0-a/d*anst),ABS(x0+b/d*anst));

	}
}
