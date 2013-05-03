//计算C(2n,n)能被素数p整除几次,有公式可套用
#include <iostream>
using namespace std;

int main()
{
	int t,n;
	cin>>t;
	while(t--)
	{
		cin>>n>>p;
		int sum=0;
		double s=log10(2.0*n)/log10(p);
		int q=int(s);
		int tag=1;
		for(int i=1;i<=q;i++)
		{
			tag=tag*p;
			sum+=(int)(2*n/tag)-2*(int)(n/tag);
		}
		cout<<sum<<endl;
	}
}