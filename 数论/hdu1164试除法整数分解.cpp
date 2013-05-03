#include <iostream>
using namespace std;
#include <cstdio>
#define N 10002
void divide(int n)
{
	int i,ct=0,factor[N];
	for(i=2;i<=sqrt(n+0.0)+1;i++)
	{
		while(n%i==0)
		{
			ct++;
			factor[ct]=i;
			if(ct!=1)
				printf("*");
			printf("%d",i);
			n/=i;
		}
	}
	if(n!=1)
	{
		ct++;
		factor[ct]=n;
		if(ct!=1)
			printf("*");
		printf("%d",n);
	}
}
int main()
{
	int n;
	while(cin>>n)
	{
		divide(n);
		printf("\n");
	}
}