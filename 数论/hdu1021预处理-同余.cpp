#include <cstdio>
#include <iostream>
using namespace std;

#define N 1000011
int d[N];
void pre_solve()
{
	int i;
	d[0]=7%3;
	d[1]=11%3;
	for(i=2;i<N;i++)
	{
		d[i]=(d[i-1]%3+d[i-2]%3)%3;
	}
}
int main()
{
	pre_solve();
	int n;
	while(cin>>n)
	{
		if(!d[n])
			cout<<"yes"<<endl;
		else
			cout<<"no"<<endl;
	}
}