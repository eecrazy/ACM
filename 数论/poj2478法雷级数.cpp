#include<iostream>
#include <cstdio>
#define maxn 1000000
using namespace std;
long long a[maxn+1];
int main()
{
	int i,j;
	for(i=1;i<=maxn;i++)
	a[i]=i;
	for(i=2;i<=maxn;i+=2)
	a[i]/=2;
	for(i=3;i<=maxn;i+=2)
	if(a[i]==i)
	{
		for(j=i;j<=maxn;j+=i)
		a[j]=a[j]/i*(i-1);
	}
	for(int i=3;i<=maxn;i++)
	a[i]+=a[i-1];
	int n;
	while(scanf("%d",&n)!=EOF && n)
	{
		printf("%I64d\n",a[n]);
	}
}