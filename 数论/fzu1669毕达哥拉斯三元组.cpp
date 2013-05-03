//判断a+b+c<=L的三角形数有几个。a^2+b^2=c^2
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

#define N 1000001
bool flag[N];
int gcd(int a,int b)
{
	return b==0?a:gcd(b,a%b);
}
void solve(int t)
{
	int temp,m,n,i,ans,x,y,z;
	ans=0;
	memset(flag,0,sizeof(flag));
	temp=sqrt(t+0.0);
	for(n=1;n<=temp;n++)
	{
		for(m=n+1;m<=temp;m++)
		{
			if(2*m*n+2*m*n>t)
				break;
			if(n%2!=m%2)
			{
				if(gcd(m,n)==1)
				{
					x=m*m-n*n;
					y=2*m*n;
					z=m*m+n*n;
					for(i=1;;i++)
					{
						if(i*(x+y+z)>t)
						{
							break;
						}
						ans++;
					}
				}
			}
		}
	}
	cout<<ans<<endl;
}
int main()
{
	int n;
	while(cin>>n)
	{
		solve(n);
	}
	return 0;
}
