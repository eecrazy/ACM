//素数定理：PI(x)=x/ln(x);小于x的素数有多少个
//位数公式：ln(x)+1就是x的位数；
#include <iostream>
using namespace std;
#include<cmath>

int main()
{
	double n,m,e=2.71828;
	while (cin>>n)
	{
		m=double(n-log10(n)-log10(log(10)));
		cout<<int(m)+1<<endl;
	}
}
