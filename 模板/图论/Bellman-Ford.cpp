const int maxn=1010;
const int maxm=2000;
#define INF 1<<31
int head[maxn];//-1
int dist[maxn];//INF
int s,n;
struct node
{
	int to;int w;int next;
};
node edge[maxm];

bool bellmanford(int s,int n)
{
	int i,j,k;
	for(i=0;i<n;i++)
		dist[i]=INF;
	dist[s]=0;
	for(i=0;i<n-1;i++)
	{
		for(j=0;i<n;j++)
		{
			if(dist[j]==INF)continue;
			for(k=head[j];k!=-1;k=edge[k].next)
			{
				if(edge[k].w!=INF&&dist[edge[k].to]>dist[j]+edge[k].w)
					dist[edge[k].to]=dist[j]+edge[k].w;
			}
		}
	}
	for(j=0;j<n;j++)
	{
		if(dist[j]=INF)continue;
		for(k=head[j];k!=-1;k=edge[k].next)
		{
			if(edge[k].w!=INF&&dist[edge[k].to]>dist[j]+edge[k].w)
				return false;
		}
	}
	return true;

}