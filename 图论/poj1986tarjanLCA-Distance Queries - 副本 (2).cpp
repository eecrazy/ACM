//#include <iostream>
#include <cstdio>
//using namespace std;
#define maxn 40011
#define maxm 80011
int p[maxn];
int pa[maxn];
int first[maxn];
int head[maxn];
int qhead[maxn];
int ans[maxm];
struct node
{
    int to;
    int w;
    int next;
    int lca;
};
node edge[maxm];
node qedge[maxm];
bool visit[maxn];
bool judge[maxn];
int dist[maxm];
int dis=0;//树根到子节点的距离
int n,m,q,num,cnt;
void init()
{
    for(int i=1; i<=n; i++)
    {
        head[i]=qhead[i]=-1;
        p[i]=pa[i]=i;
        first[i]=0;
        ans[i]=-1;
        judge[i]=false;
    }
}
void add(int a,int b,int w)
{
    edge[cnt].to=b;
    edge[cnt].w=w;
    edge[cnt].next=head[a];
    head[a]=cnt++;
}
void ask(int a,int b,int order)
{
    qedge[cnt].to=b;
    qedge[cnt].w=order;
    qedge[cnt].next=qhead[a];
    qhead[a]=cnt++;
}
int find(int x)
{
    if(p[x]==x) return x;
    else return p[x]=find(p[x]);
}
int findpa(int x)//为一开始划分集合服务
{
    if(pa[x]==x) return x;
    else return pa[x]=findpa(pa[x]);
}
void un(int x,int y)//必须讲究顺序性：大的并到小的上
{
    int fx=findpa(x),fy=findpa(y);
    if(fx<fy) pa[fy]=fx;
    else if(fx>fy) pa[fx]=fy;
}
void read()
{
    init();
    int a,b,w,k;
    char ch[5];
    cnt=1;
    for(int i=1; i<=m; i++)
    {
        scanf("%d%d%d%s",&a,&b,&w,ch);
        un(a,b);
        add(a,b,w);
        add(b,a,w);
    }
    scanf("%d",&q);
    cnt=1;
    for(int i=1; i<=q; i++)
    {
        scanf("%d%d",&a,&b);
        ask(a,b,i);
        ask(b,a,i);
    }
}
void dfs(int u)
{
    judge[u]=true;
    for(int k=head[u]; k!=-1; k=edge[k].next)
    {
        if(!judge[edge[k].to])
        {
            dis+=edge[k].w;
            dist[edge[k].to]=dis;
            dfs(edge[k].to);
            dis-=edge[k].w;
        }
    }
}
void lca(int u)
{
    visit[u]=true;
    for(int k=head[u]; k!=-1; k=edge[k].next)
    {
        int v=edge[k].to;
        if(!visit[v])
        {
            lca(v);
            p[v]=u;
        }
    }
    for(int k=qhead[u]; k!=-1; k=qedge[k].next)
    {
        int v=qedge[k].to;
        if(visit[v])
        {
            int root=find(qedge[k].to);
            num=qedge[k].w;
            ans[num]=dist[u]+dist[v]-2*dist[root];
        }
    }
}
void solve()
{
    read();
    for(int i=1; i<=n; i++) first[findpa(i)]=1; //找各片森林的根
    for(int i=1; i<=n; i++)
    {
        if(first[i])//如果i为某片森林的根
        {
            dist[i]=0;
            dfs(i);//深搜一下这片森林
            for(int i=1; i<=n; i++)visit[i]=false;
            lca(i);//LCA
        }
    }
}
int main()
{
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        solve();
        for(int i=1; i<=q; i++)
        printf("%d\n",ans[i]);
    }
}
