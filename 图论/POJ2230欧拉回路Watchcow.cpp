//由这道题，一定要会使用vector存图，因为可以动态删除边。
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define N 10001
vector<int> v[N];
int n,m;
void dfs(int k)
{
	int i,j;

	while (v[k].size())
	{
		j=v[k][v[k].size()-1];
		v[k].pop_back();//删除掉已访问的边
		dfs(j);
	}printf("%d\n",k);   //输出一定要放在后面不然会WA,因为少输出了一个1。
}

int main()
{
	int i,j,k;
	scanf("%d%d",&n,&m);
	for (i=1;i<=n;i++)
		v[i].clear();
	while (m--)
	{
		scanf("%d%d",&i,&j);
		v[i].push_back(j);
		v[j].push_back(i);

	}
	dfs(1);
	return 0;
}
