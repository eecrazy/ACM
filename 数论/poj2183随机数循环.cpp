#include <iostream>
#include <cstdio>
using namespace std;
int use[1000001];
int main()
{
	int x,y,i;
	cin>>x;
	memset(use,-1,sizeof(use));
	use[x]=0;
	for(int i=1;;i++)
	{
		x=x/10%10000;
		x*=x;
		x%1000000;
		if(use[x]>=0)break;
		use[x]=i;
	}
	printf("%d %d %d\n",x,i-use[x],i);
}