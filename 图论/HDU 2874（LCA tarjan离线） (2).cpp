/*HDU 2874（LCA tarjan离线）
完全自学算法真是挺艰苦的，唯一找到的所谓的捷径就是：手工模拟算法！
不明白就手工模拟把~
*/
/*题意：给定有N个结点的森林和Q次询问，求任意给定的两个结点之间的距离。 
N<=100000 , Q<=1000000
算法：LCA离线算法。所不同的是，这题并不是给你一颗树，而是一个森林，
因此还需要用并查集将一颗树上的结点放到同一个集合中去，然后对每棵树
用Tarjin算法求一次LCA，就可以得出结果了。*/
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#define N 10010
#define M 1000010
using namespace std;
bool vis[N],first[N],judge[N];
int n,m,q,cnt;
int head[N],next[M<<1],to[M<<1],len[M<<1],dis[M<<1],hd[N],nt[M<<1],tu[M<<1],ln[M<<1],ans[M<<1],fa[N],pa[N];
void initial()//初始化
{
    memset(head,0,sizeof head);
    memset(vis,0,sizeof vis);
    memset(hd,0,sizeof hd);
    memset(first,0,sizeof first);
    memset(ans,-1,sizeof ans);
    memset(judge,0,sizeof judge);
}
void add(int u,int v,int w)//添加边
{
    to[cnt]=v;
    len[cnt]=w;
    next[cnt]=head[u];
    head[u]=cnt++;
}
void ask(int u,int v,int order)//添加询问
{
    tu[cnt]=v;
    ln[cnt]=order;
    nt[cnt]=hd[u];
    hd[u]=cnt++;
}
int findfa(int x)//为tarjan服务
{
    if(fa[x]==x) return x;
    else return fa[x]=findfa(fa[x]);
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
void read()//读入
{
    for(int i=1; i<=n; i++) fa[i]=pa[i]=i; //并查集初始化
    int a,b,c;
    cnt=1;
    for(int i=1; i<=m; i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        un(a,b);
        add(a,b,c);
        add(b,a,c);
    }
    cnt=1;
    for(int i=1; i<=q; i++)
    {
        scanf("%d%d",&a,&b);
        ask(a,b,i);
        ask(b,a,i);
    }

}
void dfs(int u)//深搜，找出森林，并拓展dis，dis[i]表示i点到i所在森林里的根的距离
{
    judge[u]=true;//区分于vis数组，此数组不清零
    for(int i=head[u]; i>0; i=next[i])
    {
        int v=to[i],dist=len[i];
        if(!judge[v])
        {
            dis[v]=dis[u]+dist;
            dfs(v);
        }
    }
}
void tarjan(int u)//LCA
{
    vis[u]=true;
    for(int i=hd[u]; i>0; i=nt[i])
    {
        int v=tu[i],num=ln[i];
        if(vis[v])//v已经被处理过
        {
            int root=findfa(v);
            ans[num]=dis[u]+dis[v]-2*dis[root];
        }
    }
    for(int i=head[u]; i>0; i=next[i])
    {
        int v=to[i];
        if(!vis[v])//v未被处理过
        {
            tarjan(v);
            fa[v]=u;//注意这两句的顺序性
        }
    }
}
void solve()
{
    for(int i=1; i<=n; i++) first[findpa(i)]=1; //找各片森林的根
    for(int i=1; i<=n; i++)
    {
        if(first[i])//如果i为某片森林的根
        {
            dis[i]=0;
            dfs(i);//深搜一下这片森林
            memset(vis,0,sizeof vis);
            tarjan(i);//LCA
        }
    }
}
void print()//输出答案
{
    for(int i=1; i<=q; i++)
    {
        if(ans[i]==-1) printf("Not connected\n");
        else printf("%d\n",ans[i]);
    }
}
int main()
{
    while(scanf("%d%d%d",&n,&m,&q)!=EOF)
    {
        initial();
        read();
        solve();
        print();
    }
}
