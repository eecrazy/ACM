// 欧拉回路：前向星存图，无向图存2次。基于深度优先搜索
int ans[maxm];
int ansi=0;
bool visit[2*maxm];
void dfs(int now)
{
	int k;
	for (int k =head[now] ; k !=1; k=edge[k].next)
	{
		if(!visit[k])
		{
			visit[k]=1;
			visit[k^1]=true;
			dfs(edge[k].to);
			ans[ansi++]=k;
		}
	}
}