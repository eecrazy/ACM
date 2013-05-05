const int maxn=1010;
int n,m,src;
vector<pair<int ,int>> g[maxn];
int dist[maxn];
bool inQue[maxn];
queue<int> que;

void spfa()
{
	memset(dist,63,sizeof(dist));
	dist[src]=0;
	while(!que.empty())que.pop();
	que.push(src);
	inQue[src]=true;
	while(!que.empty())
	{
		int u=que.front();
		que.pop();
		for(int i=0;i<g[u].size();i++)
		{
			if(dist[u]+g[u][i].second<dist[g[u][i].first])
			{
				dist[g[u][i].first]=dist[u]+g[u][i].second;
				if(!inQue[g[u][i].first])
				{
					inQue[g[u][i].first]=true;
					que.push(g[u][i].first);
				}
			}
		}
		inQue[u]=false;
	}
}