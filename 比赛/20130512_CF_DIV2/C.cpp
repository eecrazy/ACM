可以做c，n奇数
0 1 2 3 4 5 6
1 2 3 4 5 6 0
1 3 5 0 2 4 6
n偶数，-1
#include <cstdio>
int main()
{
    int n;
	while(scanf("%d",&n)!=EOF)
	{
		if(n%2==0)
		{
			printf("-1\n");
		}
		else
		{
			for(int i=0;i<n;i++)
			{
				printf("%d",i);
				if(i!=n-1)
					printf(" ");
			}
			printf("\n");
			for(int i=1;i<n;i++)
			{
				printf("%d",i);
					printf(" ");
			}
			printf("0\n");
			for(int i=1;i+2<=n;i+=2)
			{
				printf("%d ",i);
			}
			printf("0 ");
			for(int i=2;i+1<=n;i+=2)
			{
				printf("%d",i);
				if(i+1!=n)
					printf(" ");
			}
			printf("\n");

		}

	}
}
