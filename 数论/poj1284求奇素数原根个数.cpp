//有一个结论，p是素数，则p有phi(p-1)个原根。
#include <iostream>
using namespace std;
int phi(int n)
{
	int rea=n;
	for(int i=2;i*i<=n;i++)
	{
		if(n%i==0)
		{
			rea=rea-rea/i;
			do
			{
				n/=i;
			}while(n%i==0);
		}
	}
	if(n>1)
		rea=rea-rea/n;
	return rea;
}
int main()
{
	int n;
	while(cin>>n)
	{
		n--;
		cout<<phi(n)<<endl;
	}
}
