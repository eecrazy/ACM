//求割点HOJ1007
#include <cstdio>
#define min(a,b)  a>b?b:a;
#define max(a,b)  a>b?a:b;
const int V=1001;
struct Edge
{
    int next,adj;
} edge[V*V];
int cnt,idx;
int cut[V],n,head[V];
int low[V],dfn[V];
void init()
{
    cnt=0;
    idx=0;
    for(int i=1; i<=V; i++)
    {
        head[i]=-1;
        low[i]=0;
        dfn[i]=0;
        cut[i]=0;
    }
}
void addedge(int u,int v)
{
    edge[cnt].adj=v;
    edge[cnt].next=head[u];
    head[u]=cnt++;
}
void tarjan(int u,int fa)
{
    low[u]=dfn[u]=(++idx);
    //printf("u=%d/n",u);
    for(int p=head[u]; p!=-1; p=edge[p].next)
    {
        int v=edge[p].adj;
        if(v==fa)  continue;
        if(dfn[v]!=0)
        {
            low[u]=min(dfn[v],low[u]);
            continue;
        }
        tarjan(v,u);
        low[u]=min(low[u],low[v]);
        if(low[v]>=dfn[u])  cut[u]++;//访问不到比U小的节点
    }
    if(fa!=0) cut[u]++;
}
int main()
{
    //freopen("a.txt","r",stdin);
    int a,b;
    int num=0;
    while(scanf("%d",&a)!=EOF)
    {
        if(a==0)  break;
        init();
        n=0;
        scanf("%d",&b);
        n=max(a,n);
        n=max(b,n);
        addedge(a,b);
        addedge(b,a);
        if(num>0)  printf("\n");
        printf("Network #%d\n",++num);
        while(1)
        {
            scanf("%d",&a);
            if(a==0) break;
            scanf("%d",&b);
            n=max(a,n);
            n=max(b,n);
            addedge(a,b);
            addedge(b,a);
        }
        tarjan(1,0);
        bool flag=false;
        for(int i=1; i<=n; i++)
            if(cut[i]>1)
            {
                printf("  SPF node %d leaves %d subnets\n",i,cut[i]);
                flag=true;
            }
        if(!flag)  printf("  No SPF nodes\n");
    }
    return 0;
}