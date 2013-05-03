#include <iostream>	
using namespace std;

long long mod(long long a,long long b,long long m)//快速幂取模
{
	long long ans=1;
	while(b)
	{
		if(b&1)
		{
			ans=(ans*a)%m;
			b--;
		}
		b/=2;
		a=a*a%m;
	}
	return ans;
}
int main()
{
	int c,m,n;
	int i,ans,a,b;
	cin>>c;
	while(c--)
	{
		cin>>m>>n;
		ans=0;
		for(i=1;i<=n;i++)
		{
			cin>>a>>b;
			ans=(ans+mod(a,b,m))%m;
		}
		cout<<ans<<endl;
	}

}
