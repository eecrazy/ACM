//这道题什么意思？？
#include <cstdio>
#include <iostream>
using namespace std;

#define N 64

int bo[N],t;
void divide(int m)
{
	int i;
	t=0;
	for(int i=2;i*i<=m;i++)
	{
		if(m%i==0)
		{
			t++;
			bo[t]=i;
			while(m%i==0)
				m/=i;
		}
	}
	if(m!=1)
	{
		t++;
		bo[t]=m;
	}
}
long long quick_multi(long long a,long long b)
{
	long long ans=1;
	while(b)
	{
		ans*=a;
		b--;
	}
	return ans;
}
long long ans,temp;
int a[N],m,n;
void dfs(int b,int ct,int c)
{
	int i,x;
	if(ct==c)
	{
		x=m;
		for(i=1;i<=c;i++)
		{
			x/=a[i];
		}
		temp+=quick_multi(x,n);
		return;
	}
	for(i=b+1;i<=t;i++)
	{
		a[ct+1]=bo[i];
		dfs(i,ct+1,c);
	}
}
int main()
{
	int i;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		ans=t=0;
		divide(m);
		for(i=1;i<=t;i++)
		{
			temp=0;
			dfs(0,0,i);
			if(i&1)
				ans+=temp;
			else
				ans-=temp;
		}
		ans=quick_multi(m,n)-ans;
		printf("%lld\n",ans);
	}
	return 0;
}
