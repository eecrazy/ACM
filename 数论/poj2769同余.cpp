//用到了哈希的思想，找到最小的i使得对i均不同余.
#include <cstdio>
#include <iostream>
using namespace std;
bool p[100001];
int d[100001];
int main()
{
	int c,i,j,num;
	cin>>c;
	while(c--)
	{
		cin>>num;
		for(int i=1;i<=num;i++)
		{
			cin>>d[i];
		}
		bool find;
		for( i=1;;i++)
		{
			find=1;
			memset(p,0,sizeof(p));
			for( j=1;j<=num;j++)
			{
				if(p[d[j]%i])
				{
					find=0;break;
				}
				p[d[j]%i]=1;
			}
			if(find)break;
		}
		cout<<i<<endl;
	}

}
