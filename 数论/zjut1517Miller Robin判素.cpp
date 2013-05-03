#include <iostream>
using namespace std;
#include <cstdio>
long long Pow(long long a,long long b,long long n)//速度最快
{
     long long t=1;
     for(;b;b>>=1,a=a*a%n)
     if(b&1) t=t*a%n;
     return t;
}

// bool witness(long long a,long long n)
// {
// 	long long m=n-1;
// 	int j=0;
// 	while(!(m&1))
// 	{
// 		j++;
// 		m>>1;
// 	}
// 	long long x=Pow(a,m,n);
// 	if(x==1||x==n-1)
// 		return false;
// 	while(j--)
// 	{
// 		x=x*x%n;
// 		if(x==n-1)return false;
// 	}
// 	return true;
// }
// bool miller_robin(long long n)
// {
// 	if(n<2)return false;
// 	if(n==2||n==3)return true;
// 	if(!(n&1))return false;
// 	for(int i=0;i<times;i++)
// 	{
// 		long long a=randome(n-2)+1;
// 		if(witness(a,n))return false;
// 	}
// 	return true;
// }
bool test(long long n,long long a,long long d)
{
	if(n==2)return true;
	if(n==a)return true;
	if((n&1)==0)return false;
	while(!(d&1))d=d>>1;
	long long t=Pow(a,d,n);
	while((d!=n-1)&&(t!=1)&&(t!=n-1))
	{
		t=(long long)t*t%n;
		d=d<<1;
	}
	return (t==n-1||(d&1)==1);
}
bool isPrime(long long n)
{
	if(n<2)return false;
	long long a;
	for(long long i=0;i<=2;i++)
	{
		a=rand()%(n-1)+1;
		if(!test(n,a[i],n-1))return false;
		return true;
	}
}
int main()
{
	long long n;
	while(scanf("%lld",&n)==1)
	{
		if(isPrime(n))
			cout<<"Yes"<<endl;
		else
			cout<<"No"<<endl;
	}
}