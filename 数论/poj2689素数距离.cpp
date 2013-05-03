//筛素数，此题很好。
#include <stdio.h>

long long l,u;
int prime[47000];
int prime1[1000100];
int is[47000],is1[1000100];
int cou=0,cou1;
int min,max;
int a,b;

void getPrime()
{
    for(int i=2;i<46400;i++) is[i]=1;
    for(int i=2;i<46400;i++)
        {
            if(is[i])  prime[cou++]=i;
            for(int j=0;j<cou&&i*prime[j]<46400;j++)
            {
                is[i*prime[j]]=0;
                if(i%prime[j]==0)  break;
            }
       }
}

void solve(long long l,long long u)
{
    long long p,s;
    if(u<46400)
    {
      for(int i=l;i<=u;i++)
       if(is[i])
       prime1[cou1++]=i-l;
    }
    else
    {
      for(int i=0;i<=u-l;i++)   is1[i]=1;
      for(int i=0;i<cou&&prime[i]*prime[i]<=u;i++)
         {
             s=l/prime[i];
             if(s*prime[i]<l)  s++;
             if(s<=1) s++;
             for(long long j=s;j*prime[i]<=u;j++)
              {
                  p=(int)j*prime[i]-l;
                  is1[p]=0;
              }
         }
      for(int i=0;i<=u-l;i++)
       if(is1[i])
       prime1[cou1++]=i;
    }
}
int main()
{
    getPrime();
    while(scanf("%lld %lld",&l,&u)!=EOF)
    {
       cou1=0;
       solve(l,u);
       min=2147483647;
       max=-1;
       if(cou1<2)
       {
           printf("There are no adjacent primes.\n");
           continue;
       }
       for(int i=0;i<cou1-1;i++)
       {
           if(prime1[i+1]-prime1[i]<min)
           {
               min=prime1[i+1]-prime1[i];
               a=i;
           }
           if(prime1[i+1]-prime1[i]>max)
           {
               max=prime1[i+1]-prime1[i];
               b=i;
           }
       }
       printf("%I64d,%I64d are closest, %I64d,%I64d are most distant.\n",prime1[a]+l,prime1[a+1]+l,prime1[b]+l,prime1[b+1]+l);
    }
}



下面代码WA:?????
#include <cstdio>
#include <iostream>
using namespace std;

#define N 50001
#define INF 99999999
int prime[N],nprime;
bool isprime[N*20];

void make_prime1()
{
	long long i,j;
	nprime=0;
	memset(isprime,1,sizeof(isprime));
	for( i=2;i<N;i++)
	{
		if(isprime[i])
		{
			nprime++;
			prime[nprime]=i;
			for(j=i*i;j<N;j+=i)
			{
				isprime[j]=0;
			}
		}
	}
}

long long l,u;
long long prime2[1000001];

int nprime2;
void make_prime2()
{
	long long i,j,b;
	memset(isprime,1,sizeof(isprime));
	for(i=1;i<=nprime;i++)
	{
		b=l/prime[i];
		while(b*prime[i]<l||b<=1)
			b++;
		for(j=b*prime[i];j<=u;j+=prime[i])
		{
			if(j>=l)
			{
				isprime[j-l]=0;
			}
		}
	}
	if(l==1)
	{
		isprime[0]=0;
	}
}

void solve()
{
	int i;
	long long min=INF,max=-INF;
	long long min1,max1,maxr,minr;
	make_prime2();
	nprime2=0;
	for(i=0;i<=u-l;i++)
	{
		if(isprime[i])
		{
			nprime2++;
			prime2[nprime2]=i+l;
		}
	}
	if(nprime2<=1)
	{
		printf("There are no adjacent primes.\n");
	}
	else
	{
		for(i=1;i<nprime2;i++)
		{
			if(prime2[i+1]-prime2[i]<min)
			{
				min=prime2[i+1]-prime2[i];
				min1=prime2[i],minr=prime2[i+1];
			}
			if(prime2[i+1]-prime2[i]>max)
			{
				max=prime2[i+1]-prime2[i];
				max1=prime[i],maxr=prime2[i+1];
			}
		}
		printf("%lld,%lld are closest, %lld,%lld are most distant.\n",min1,minr,max1,maxr);
	}
}
int main()
{
	make_prime1();
	while(scanf("%lld%lld",&l,&u)!=EOF)
	{
		solve();
	}
	return 0;
}
