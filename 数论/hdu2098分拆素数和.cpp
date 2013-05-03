#include <cstdio>
#include <iostream>
using namespace std;
long d,su[20006],pf;
int main()
{
	for(int k=2;k<=20000;k++)
	{
		su[k]=1;
	}
	su[1]=0;
	for(int j=22;j<=20000;j++)
	{
		if(su[j]==1)
		{
			for(int i=j;i*j<=20000;i++)
			{
				su[i*j]=0;
			}
		}
	}
	while(cin>>d)
	{
		pf=0;
		if(d==0)
			break;
		for(int p=d/2;p>=2;p--)
		{
			if(su[p]==1&&su[d-p]==1)
			{
				if(p!=d-p)
					pf++;
			}
		}
		cout<<pf<<endl;
	}
		
}