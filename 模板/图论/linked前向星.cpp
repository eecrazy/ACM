//structure
#define maxn 100
#define maxm 300

int head[maxn];
struct node
{
	int to;int w;int next;
};
node edge[maxm];

//input
memset(head,-1,sizeof(head));
int i,j,k=0,w;
cin>>i>>j>>w;
edge[k].to=j;
edge[k].w=w;
edge[k].next=head[i];
head[i]=k;
k++;

//traverse
for(i=1;i<=n;i++)
{
	for(k=head[i];k!=-1;k=edge[k].next)
	{
		cout<<i<<" "<<edge[k].to<<" "<<edge[k].w<<endl;
	}
}
