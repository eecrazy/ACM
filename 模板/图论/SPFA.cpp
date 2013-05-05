
#define INF　1<<28
const int maxn=1010;
const int maxm=2000;
int head[maxn];
int dist[maxn];
bool visit[maxn];
int s,n;
struct node
{
	int to;int w;int next;
};
node edge[maxm];
bool spfa(int s,int n)
{
	int i,k,iq=0,top;
	int queue[maxn];
	int outque[maxn];
	for(i=0;i<=n;i++)
	{
		dist[i]=INF;
		visit[i]=false;
		outque[i]=0;
	}
	queue[iq++]=s;
	visit[s]=true;
	dist[s]=0;
	i=0;
	while(i!=iq)
	{
		top=queue[i];
		visit[top]=false;
		outque[top]++;
		if(outque[top]>n)return false;
		k=head[top];
		while(k>=0)
		{
			if(dist[edge[k].to]>edge[k].w+dist[top])
			{
				dist[edge[k].to]=dist[top]+dist[k].w;
				if(!visit[edge[k].to])
				{
					visit[edge[k].to]=true;
					queue[iq]=edge[k].to;
					iq++;
				}
			}
			k=edge[k].next;
		}
		i++;
	}
	return true;
}