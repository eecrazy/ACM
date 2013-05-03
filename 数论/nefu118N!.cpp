//N！末尾0的个数;
#include <iostream>
using namespace std;

int main()
{
	int n,m,t,sum,five;
	cin>>n;
	while (n--)
	{
		cin>>m;
		t=m;
		five=5;
		sum=0;
		while(five<=t)
		{
			sum+=t/five;
			five*=5;
		}
		cout<<sum<<endl;
	}
}