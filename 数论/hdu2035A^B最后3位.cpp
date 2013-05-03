#include <iostream>
using namespace std;
//同余基本性质：ab=(a%m)(b%m)(mod m);
int main()
{
	int i,a,b,ans;
	while(cin>>a>>b&&a+b)
	{
		ans=1;
		for(i=1;i<=b;i++)
		{
			ans=ans*a%1000;
		}
		cout<<ans<<endl;
	}
}