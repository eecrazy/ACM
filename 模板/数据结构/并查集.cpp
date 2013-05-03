struct DisjointSet
{
	std::vector<int> father,rank;
	DisjointSet(int n):father(n),rank(n)
	{
		for (int i = 0; i < n; ++i)
		{
			father[i]=i;
		}
	}
	int find(int v)
	{
		return father[v]=father[v]==v?v:find(father[v]);
	}
	void merge(int x,int y)
	{
		int a=find(x),b=find(y);
		if(rank[a]<rank[b])
		{
			father[a]=b;
		}
		else
		{
			father[b]=a;
			if(rank[b]==rank[a])++rank[a];
		}
	}
};