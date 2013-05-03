const int maxn=100005;
vector<int> g[maxn];
int du[maxn],n,m,L[maxn];

bool topsort()
{
	memset(du,0,sizeof(du));
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<g[i].size();j++)
		{
			du[g[i][ij]]++;
		}
	}
	int tot=0;
	queue<int> Q;
	for(int i=0;i<n;i++)
	{
		if(!du[i])Q.push(i);
	}
	while(!Q.empty())
	{
		int x=Q.front();Q.pop();
		L[tot++]=x;
		for(int j=0;j<g[x].size();j++)
		{
			int t=g[x][j];
			du[t]--;
			if(!du[t])Q.push(t);
		}
	}
	if(tot==n)
	{
		return 1;
	}
	return 0;
}