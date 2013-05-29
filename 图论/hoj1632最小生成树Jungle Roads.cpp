#include <cstdio>
#include <iostream>
#include <limits.h>
#include <string.h>
using namespace std;
const int maxn=27;
int map[maxn][maxn];
#define inf 100000000
int visit[maxn],dis[maxn];
int sum;
int n;
void  prim()
{
    for(int i=2;i<=n;i++)
    {
        visit[i]=false;
        dis[i]=map[1][i];
    }
//    for(int i=2;i<=n;i++)
//    {
//        printf("%d ",dis[i]);
//    }
//    printf("\n ");
	dis[1]=0;
	sum=0;
	visit[1]=1;
	int k=0;
	int min;
	for(int i=1;i<n;i++)
	{
		k=0;
		min=inf;
		for(int j=1;j<=n;j++)
		{
			if(!visit[j]&&dis[j]<min)
			{
				min=dis[j];
				k=j;
			}
		}
		visit[k]=1;
		sum+=min;
//		printf("%d %d\n",min,sum);
		for(int j=1;j<=n;j++)
		{
			if(!visit[j]&&map[k][j]!=inf&&dis[j]>map[k][j])
			{
				dis[j]=map[k][j];
			}
		}
	}
}
int main()
{
	char ch[20];
	int a,b;
	//freopen("int.txt","r",stdin);
	while(scanf("%d",&n)&&n)
	{

		for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		map[i][j]=inf;
		for(int i=1;i<n;i++)
		{
			scanf("%s",ch);
			scanf("%d",&a);
			while(a--)
			{
				scanf("%s",ch);
				scanf("%d",&b);
				int s=ch[0]-'A'+1;
				map[i][s]=map[s][i]=b;
			}
		}
//		printf("ddd\n");
		prim();
		printf("%d\n",sum);
	}
}
