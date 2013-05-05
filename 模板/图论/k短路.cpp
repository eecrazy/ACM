const int maxn=1010;
const int maxm=2000;
struct node
{
	int to;
	int w;
	int next;
	int g,f;//f=g+h
	bool operator <(const node& r)const
	{
		if(r.f==f)return r.g<g;
		return r.f<f;
	}
};
node edge1[maxm];
int head1[maxn];
node edge[maxm];
int head[maxn];
int dist[maxn];//公共的dist数组
int s,t,n;
bool spfa()
{
	int i,k,iq=0,top;
	bool visit[maxn];
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
		k=head1[top];
		while(k>=0)
		{
			if(dist[edge1[k].to]>edge1[k].w+dist[top])
			{
				dist[edge1[k].to]=dist[top]+dist[k].w;
				if(!visit[edge1[k].to])
				{
					visit[edge1[k].to]=true;
					queue[iq]=edge1[k].to;
					iq++;
				}
			}
			k=edge1[k].next;
		}
		i++;
	}
	return true;
}

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