const int V=1000;
int edge[V][V];
int bridge[V][V],cur[V];
int low[V],dfn[V],vis[V];

void cut_bridge(int cur,int father,int dep,int n)
{
	vis[cur]=1;dfn[cur]=low[cur]=dep;
	int children=0;
	for(int i=0;i<n;i++)
	{
		if(edge[cur][i])
		{
			if(i!=father&&1==vis[i])
			{
				if(dfn[i]<low[cur])
				{
					low[cur]=dfn[i];
				}
			}
			if(0==vis[i])
			{
				cut_bridge(i,cur,dep+1,n);
				children++;
				if(low[i]<low[cut])low[cur]=low[i];
				if((father==-1&&children>1)||(father!=-1&&low[i]>=dfn[cur]))
					cut[cur]=true;
				if(low[i]>dfn[cur])
				{
					bridge[cur][i]=bridge[i][cur]=true;
				}
			}
		}
	}
	vis[cur]=2;
}