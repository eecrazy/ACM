struct LogVar
{
	int index;
	bool pre;
	LogVar(int _index=0,bool _pre=false ):index(_index),pre(_pre){}
};

struct BinExp
{
	LogVar p,q;
	BinExp(LogVar _p=LogVar(),LogVar _q=LogVar()):p(_p),q(_q){}
};

inline int get_value(int sol[maxn],int n,int x)
{
	int r=x>n?x-n:x;
	if(sol[r]==-1)
	{
		return -1;
	}
	return x>n?!sol[r]:sol[r]:
}

void dfs(int x)
{
	low[x]=dfn[x]=++id_cnt;
	s[++top]=x;
	vis[x]=true;
	for(int i=head[x],k;i;i=h[i].next)
	{
		if(!vis[k=h[i].to])
		{
			dfs(k);
			low[x]=min(low[x],low[k]);
		}
		else
		{
			low[x]=min(low[x],dfn[k]);
		}
	}
	if(dfn[x]==low[x])
	{
		s[top+1]=-1;
		for(++cnt;s[top+1]!=x;--top)
		{
			c[cnt].push_back(s[top]);
			belong[s[top]]=cnt;
		}
	}
}

inline bool two_SAT(int n,int m,BinExp a[maxn],int sol[maxn])
{
	edge_tot=0,id_cnt=0,cnt=0,top=0;
	for(int i=1;i<=2;i++)
	{
		head[i]=0;
		vid[i]=false;
		c[i].clear();
	}
	for(int i=1;i<=n;++i)
	{
		sol[i]=-1;

	}
	for(int i=0;i<m;++i)
	{
		add_edge(a[i].p.index+a[i].p.pre*n,a[i].q.index+!a[i].q.pre*n);
		add_edge(a[i].q.index+a[i].q.pre*n,a[i].p.index+!a[i].p.pre*n);

	}
	for(int i=1;i<=2*n;i++)
	{
		if(!vis[i])
		{
			dfs(i);
		}
	}
	for(int i=1;i<n;++i)
	{
		if(belong[i]==belong[i+n])
		{
			return false;
		}
	}

	for(int i=1;i<=cnt;++i)
	{
		int val=1;
		for(int j=0;j<int(c[i].size());++j)
		{
			int cur=c[i][j];
			if(get_value(sol,n,cur)==0)
			{
				val=0;
			}
			for(int k=head[cur];k;k=h[k].next)
			{
				if(get_value(sol,n,h[k].to)==0)
				{
					val=0;
				}
			}
			if(val==0)
				break;
		}
		for(int j=0;j<int(c[i].size());++j)
		{
			if(c[i][j]>n)
			{
				sol[c[i][j]-n]!=val;
			}
			else
			{
				sol[c[i][j]]=val;
			}
		}
	}
	return true;
}