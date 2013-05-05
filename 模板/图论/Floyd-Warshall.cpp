1:const int maxn=111;
const int INF=1000000000;
int N,g[maxn][maxn];

void floyd()
{
	for(int k=1;k<=N;k++)
	{
		for(int i=1;i<=N;++i)
		{
			for(int j=1;j<=N;++j)
			{
				g[i][j]=min(g[i][j],g[i][k]+g[k][j];
			}
		}
	}
}

2:
const int maxn=101;
void floyd()
{
	int i,j,k;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=nlj++)
		{
			dist[i][j]=map[i][j];
			pre[i][j]=i;
		}
	}
	for(k=1;k<=n;k++)
	{
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
}