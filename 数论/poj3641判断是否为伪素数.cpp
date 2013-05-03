#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;

bool isprime(long long n)
{
	long long i;
	int flag=0;
	if(n==2||n==1)
	{
		return 1;
	}
	else
	{
		long long b=sqrt(n+0.0)+1;
		for(i=2;i<=b;i++)
		{
			if(n%i==0)
			{
				flag=1;return 0;
			}
			if(i==b)return 1;
		}
	}
}
long long Pow(long long a,long long b,long long n)//速度最快
{
     long long t=1;
     for(;b;b>>=1,a=a*a%n)
     if(b&1) t=t*a%n;
     return t;
}
int main()
{
	long long a,b,p,n;
	while(cin>>p>>a&&(p+a))
	{
		if(isprime(p))
			cout<<"no"<<endl;
		else
		{
			if(Pow(a,p,p)==a)
				cout<<"yes"<<endl;
			else
				cout<<"no"<<endl;
		}
	}
}