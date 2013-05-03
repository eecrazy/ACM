#include <iostream>
using namespace std;
#include <cstdio>
int d,su[2006];
int main()
{
	for(int k=2;k<=2000;k++)
	{
		su[k]=1;
	}
	su[1]=0;
	for(int j=2;j<=2000;j++)
	{
		if(su[j]==1)
		{
			for(int i=j;i*j<=2000;i++)
			{
				su[i*j]=0;
			}
		}
	}
	while(scanf("%d",&d)!=EOF)
	{
		if(su[d]==1)
			cout<<"YES"<<endl;
		else
		cout<<"NO"<<endl;
	}
}
