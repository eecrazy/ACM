#include <iostream>
using namespace std;
#define N 1<<24
bool is[N];
int main()
{
	int m,n;
	memset(is,1,sizeof(is));
	is[0]=is[1]=0;
	for(int i=4;i<=N;i+=2)
		is[i]=0;
	for(int i=3;i<=e;i++)
	{
		if(is[i])
		{
			for(int j=i+i;j<=N;j+=i)
				is[j]=0;
		}
	}
	while(cin>>n)
	{
		int t=0;
		for(int i=2;i<n/2+1;i++)
		{
			if(is[i]&&is[n-i])
			{
				t++;
			}
			cout<<t<<endl;
		}
	}
}