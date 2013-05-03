struct node
{
	int to;
	int g,f;//f=g+h
	bool operator <(const node& r)const
	{
		if(r.f==f)return r.g<g;
		return r.f<f;
	}
};

bool spfa(int s,int n,int head[maxn],node edge[maxn],int dist[maxn]);

int astar(int start,int end,int n,int k,int head[maxn],node edge[maxn],int dist[maxn])
{
	node e,ne;
	int cnt=0;
	priority_queue<node> que;
	if(start==end)k++;
	if(dist[start]==INF)return -1;
	e.to=start;
	e.g=0;
	e.f=e.g+dist[e.to];
	que.push(e);
	while(!que.empty())
	{
		e=que.top();
		que.pop();
		if(e.to==end)cnt++;
		if(cnt==k)return e.g;
		for(int i=head[e.to];i!=-1;i=edge[i].next)
		{
		ne.to=edge[i].to;
		ne.g=e.g+edge[i].w;
		ne.f=ne.g+dist[ne.to];
		que.push(ne);
		}
	}	
	return -1;
}

int main()
{
	//读取图信息，存在head和edge中，并且生成所有边反向的图存在head1和edge1中，///进行下面的操作
	spfa(t,n,head1,edge1,dist);
	int ans=astar(s,t,n,k,head,edge,dist)
}