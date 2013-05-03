#include <cstdio>
#include <iostreaam>
using namespace std;

int main()
{
	int a,b,sum;
	while(cin>>a>>b)
	{
		if(a==0&&b==0)
			break;
		a*=100;
		sum=0;
		for(int i=0;i<=99;i++)
		{
			if((a+i)%b==0)
			{
				sum++;
				if(sum>1)printf(" %02d",i);
				else
					printf("%02d",i);
			}

		}cout>>endl;
	}
}