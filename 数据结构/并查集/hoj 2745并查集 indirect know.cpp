
#include <cstdio>
#include<iostream>
using namespace std;

int n, m, i;
int father[50005], num[50005];

void makeSet(int n)
{
	for(int j = 1; j <= n; j++)
	{
		father[j] = j;
		num[j] = 1;
	}
}
int findSet(int x)
{
	if(father[x] != x)
	{
		father[x] = findSet(father[x]);
	}
	return father[x];
}

void Union(int a, int b)
{
	int x = findSet(a);
	int y = findSet(b);
	if(x == y)
	{
		return;
	}
	if(num[x] <= num[y])
	{
		father[x] = y;
		num[y] += num[x];

	}
	else
	{
		father[y] = x;
		num[x] += num[y];

	}
}

int main()
{
	int Case = 1,q;
	while(scanf("%d ", &n)==1)
	{
		makeSet(n);
		int a, b;
		for(int i=0;i<n;i++)
		{
			scanf("%d",&m);
			while(m--)
			{
				scanf("%d",&q);
				Union(i,q);
			}
		}
		int ans=0;
		for(i = 0; i < n-1; i++)
		{
			for(int j=i+1;i<n;j++)
			{
				if(findSet(i)=findSet(j))
				{
					ans++;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
