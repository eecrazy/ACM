// floyd最小环.cpp
int min=INT_MAX;
for(k=1;k<=n;k++)
{
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;++j)
		if(dist[i][j]!=INF&&map[j][k]!=INF&&map[k][i]!=INF&&dist[i][j]+dist[j][k]+map[k][i]<mindis)
			mindis=min(mindis,dist[i][j]+map[j][k]+map[k][i]);
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if(dist[i][k]!=INF&&dist[k][j]!=INF&&dist[i][k]+dist[k][j]<dist[i][j])
			{
				dist[i][j]=dist[i][k]+dist[k][j];
				pre[i][j]=pre[k][j];
			}
		}
	}
}
