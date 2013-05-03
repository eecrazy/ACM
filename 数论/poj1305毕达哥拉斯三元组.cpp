/*本原毕达哥拉斯三元组满足：
x=m^2-n^2;
y=2mn;
i*z=m^2+n^2;
其中m>n;且m为奇数n为偶数或者m为偶数n为奇数；
*/

// n以内本原毕达哥拉斯三元组的个数以及毕达哥拉斯三元组不涉及的数的个数；
#include <cstdio>
#include <iostream>
using namespace std;
#include <cmath>
#define N 1000001
bool flag[N];
int gcd(int a,int b)
{
	return b==0?a:gcd(b,a%b);
}
void solve(int t)
{
	int temp,m,n,i,ans1,ans2,x,y,z;
	ans1=ans2=0;
	memset(flag,0,sizeof(flag));
	temp=sqrt(t+0.0);
	for(n=1;n<=temp;n++)
	{
		for(m=n+1;m<=temp;m++)
		{
			if(m*m+n*n>t)
				break;
			if(n%2!=m%2)
			{
				if(gcd(m,n)==1)
				{
					x=m*m-n*n;
					y=2*m*n;
					z=m*m+n*n;
					ans1++;
					for(i=1;;i++)
					{
						if(i*z>t)
						{
							break;
						}
						flag[i*x]=1;
						flag[i*y]=1;
						flag[i*z]=1;
					}
				}
			}
		}
	}
	for(i=1;i<=t;i++)
	{
		if(!flag[i])ans2++;
	}
	cout<<ans1<<" "<<ans2<<endl;
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
