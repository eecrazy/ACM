
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
	while(scanf("%d %d %d", &n, &m,&q)==3 && n!=0)
	{
		makeSet(n);
		int a, b;
		for(i = 0; i < m; i++)
		{
			scanf("%d %d",&a, &b);
			Union(a,b);
		}
		for(i = 0; i < q; i++)
		{
			scanf("%d %d",&a, &b);
			if(findSet(a)==findSet(b))
			printf("yes\n");
			else
			printf("no\n");
		}

	}
	return 0;
}
