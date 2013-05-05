#include <iostream>
using namespace std;
long long a[4];
#include <cstdio>
#include <algorithm>
int ca=1;
int main()
{
	while(cin>>a[0]>>a[1]>>a[2]>>a[3])
	{
		sort(a,a+4);
		printf("Case %d: ",ca++);
		cout<<a[2]+a[3]<<endl;
	}
}
