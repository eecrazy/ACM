const int maxn=1000;
int dis[maxn],g[maxn][maxn],N;
bool v[maxn];

void dijkstra()
{
	for(int i=1;i<=N;++i)
	{
		dis[i]=INF;
	}
	dis[1]=0;
	memset(v,0,sizeof(v));
	for(int i=1;i<=N;++i)
	{
		int mark=-1,mindis=INF;
		for(int j=1;j<=N;j++)
		{
			if(!v[j]&&dos[j]<mindis)
			{
				mindis=dis[j];
				mark=j;
			}
		}
		v[mark]=1;
		for(int j=1;j<=N;++j)
		{
			if(!v[j])
			{
				dis[j]=min(dis[j],dis[mark]+g[mark][j]);
			}
		}

	}
}