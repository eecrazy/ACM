//完全背包问题
#include <cstdio>
#define maxn 10050
#include <iostream>
using namespace std;
#define INF 99999999
int f[maxn];//记录硬币面值
int w[maxn];//记录硬币重量
int k[maxn];//记录最小取值
int main()
{
	int t,num,e,count,n;
	scanf("%d",&num);
	while(num--)
	{
		scanf("%d%d%d",&e,&t,&n);
		count=t-e;
		for(int i=0;i<n;i++)
			scanf("%d%d",&f[i],&w[i]);
		k[0]=0;
		for(int i=1;i<=count;i++)
			k[i]=INF;
		for(int i=0;i<n;i++)
			for(int j=w[i];j<=count;j++)
			    k[j]=min(k[j],k[j-w[i]]+f[i]);
		if(k[count]==INF)
			printf("This is impossible.\n");
		else
			printf("The minimum amount of money in the piggy-bank is %d.\n",k[count]);
	}
}
