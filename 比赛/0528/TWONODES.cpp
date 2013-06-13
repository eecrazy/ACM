/*题意：给出一个无向图，求去处两个点之后使得剩余的连通分支最多。输出最多数量
 *解法：先枚举删除一个点：然后对对于删除一个点后的图 求割点，看与割点相连的
 *      双联通分量最多。
 *   求割点的方法：用tarjan算法。建图时建立双向边。当从一个点u出发
 *   发现其儿子节点v，low[v]=dfn[u]，则u点为割点。判断割点删除
 *   后会形成多少个连通分量，则看dfs的过程low[v]=dfn[u]出现过多少次。
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
using namespace std;
#define eN 10005
#define vN 5005
#define LL long long
int n,m;
struct edge
{
        int u,v,next;
}e[eN];
int head[vN],used[vN],en=0;
void addedge(int x,int y)
{
    e[en].u=x;
    e[en].v=y;
    e[en].next=head[x];
    head[x]=en++;
}
int dfn[vN],low[vN],res[vN],temp;
int ex,num;
int tarjan(int u)
{
    used[u]=1;
    low[u]=dfn[u]=num++;
    for(int i=head[u];i!=-1;i=e[i].next)
    {
        int v=e[i].v;
        if(v==ex)continue;
        if(!used[v])
        {
            tarjan(v);
            if(low[v]==dfn[u])
            {
                res[u]++;
            }
            low[u]=min(low[u],low[v]);
        }
        else
        {
            low[u]=min(low[u],dfn[v]);
        }

    }
    if(temp<res[u])temp=res[u];
}
int main()
{
    //freopen("data.in","r",stdin);
    while(scanf("%d%d",&n,&m)==2)
    {
        fill(head,head+n,-1);
        en=0;
        for(int i=0;i<m;i++)
        {
            int x,y;
            scanf("%d%d",&x,&y);
            addedge(x,y);
            addedge(y,x);
        }
        int ans=0,last=0;
        for(int i=0;i<n;i++)
        {
            int cnt=0;
            fill(used,used+n,0);
            ans=0;
            for(int i=0;i<n;i++)res[i]=1;
            for(int j=0;j<n;j++)
            {
                ex=i;
                num=1;
                if(j==i||used[j])continue;
                //if(head[j]!=-1)
                    res[j]=0;
                cnt++;
                temp=0;
                tarjan(j);
                if(ans<temp)
                    ans=temp;
            }
            if(last<ans+cnt-1)last=ans+cnt-1;
        }
        printf("%d\n",last);
    }
}
