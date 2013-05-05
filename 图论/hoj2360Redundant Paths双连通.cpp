 // POJ3177，POJ3352
 //把这两个题写到一起，是因为这两题完全一样，用下面的代码两个题都可以AC。
 // 题目大意是给一个无向连通图，求添加最少边数使原图变成双连通图。由于是第一次
 // 写双连通图的缩点，所以WA了5次，在WA到AC的过程中，发现的错误如下：1、深度优
 // 先数没有初始化；2、深度优先数初始化错误；3、桥的判断有误；4、输入数据有重边，
 // 使用邻接表存储没有跳过重边。下面写一下这题的主要思路，用数组dfn保存各个结点
 // 的访问顺序（深度优先数），数组low[k]保存结点k及其子结点通过回边能到达的所有
 // 结点的最小深度优先数（下面简称最小深度优先数）。若子节点的最小深度优先数大于
 // 父结点的最小深度优先数，则连接父子结点的边为桥，否则该边不是桥。程序中使用了
 // 并查集来合并属于同一个双连通分量的所有结点（简称缩点），下面将简单证明这样做
 // 的正确性。要证明能够使用并查集来合并，只需证明点与点之间的双连通关系是等价关系
 // 即可。已知点a与点b双连通（a到b至少有两条不同路径），点b与点c双连通，求证点a与
 // 点c双连通。分两种情况讨论：1、点c在a到b的路径上，则结论显然成立；2、点c不在a到
 // b的路径上，则路径ab与路径bc连接即可得到路径ac，同理可得路径ca。以上就证明了点与
 // 点双连通是等价关系。用并查集缩点后，得到的是一棵树，将一棵树通过加边的到双连通图
 // 需加最少边数为(叶子结点数目+1)/2。
#include <cstdio>
#include <string.h>
const int maxn = 10001;
struct node
{
    int to;
    int next;
} e[maxn];
int head[maxn];
int ansi;
int top;//栈中的元素个数
int cnt;//记录边连通分量编号
int Index;//记录遍历的步数
int dfn[maxn];//记录节点u第一次被访问时的步数
int low[maxn];//记录与节点u和u的子树节点中最早的步数
bool instack[maxn];//记录节点u是否在栈中
int stack[maxn];//栈
int Belong[maxn];//记录每个节点属于的强连通分量编号
int N;//节点个数
int ans[maxn];//顶点出度记录
//bool Flag[5002][5002];
int min(int a, int b){ return a < b ? a : b;}
void add(int a, int b)
{
    e[ansi].to = b;
    e[ansi].next = head[a];
    head[a] = ansi++;
}
void tarjan(int i, int from)
{
    int j;
    dfn[i] = low[i] = ++Index;
    instack[i] = true;
    stack[++top] = i;
    bool flag = false;
    for (int k = head[i]; k != -1; k = e[k].next)
    {
        j = e[k].to;
        if (j == from && !flag) //这个flag是为了处理重边，正常情况下只要判断j==from就行了
            flag = true;
        else
        {
            if (!dfn[j])
            {
                tarjan(j, i);
                low[i] = min(low[i], low[j]);
            }
            else if (instack[j] && low[j] < low[i])
                low[i] = low[j];
        }
    }
    //节点i是强连通分量的根
    if (dfn[i] == low[i])
    {
        //退栈，直至找到根为止
        do
        {
            j = stack[top--];
            instack[j] = false;
            Belong[j] = cnt;
        }
        while (j != i);
        cnt++;
    }
}
void solve()
{
    top = cnt = Index = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(ans, 0, sizeof(ans));
    memset(instack, 0, sizeof(instack));
    int re = 0;
    int i, j;
    for (i = 1; i <= N; i++)
        if (!dfn[i]) //有可能不是连通图
            tarjan(i, -1);

    for (i = 1; i <= N; i++)
        for (j = head[i]; j != -1; j = e[j].next)
            if (Belong[i] != Belong[e[j].to])
                ans[Belong[i]]++;//出度加1
    for (i = 0; i < cnt; i++)
        if (ans[i] == 1)
            re++;
    printf("%d\n", (re + 1) / 2);
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int M,a,b;
    while (scanf("%d %d", &N, &M) != EOF)
    {
        ansi = 0;
        memset(head, -1, sizeof(head));
        memset(Flag, 0, sizeof(Flag));
        for (int i = 0; i < M; i++)
        {
            scanf("%d%d", &a, &b);
//            if(Flag[a][b]||Flag[b][a])continue;//在输入的时候处理重边
//            Flag[a][b]=Flag[b][a]=1;
            add(a, b);
            add(b, a);
        }
        solve();
    }
    return 0;
}


//附一神代码,写的太简洁了！
#include <stdio.h>
#include <vector>
using namespace std;
int f,r,low[5005],visit[5005],degree[5005],count;
bool connect[5005][5005];
vector< vector<int> >adj;
int min(int x, int y)
{
    return x<y?x:y;
}
void dfs(int x, int p)
{
    visit[x]=true;
    low[x]=count++;
    int len=adj[x].size();
    for(int i=0;i<len;i++)
    {
        if(adj[x][i]==p) continue;
        if(!visit[adj[x][i]]) 
          dfs(adj[x][i],x);
        low[x]=min(low[x],low[adj[x][i]]);
    }
}
int main()
{
    int a,b;
    scanf("%d%d",&f,&r);
    adj.assign(f+1,vector<int>());
    while(r--)
    {
        scanf("%d%d",&a,&b);
        if(!connect[a][b])
        {
            connect[a][b]=true;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }
    count=0;
    dfs(1,1);
    for(int i=1;i<=f;i++)
    {
        int len=adj[i].size();
        for(int j=0;j<len;j++)
        {
            if(low[i]!=low[adj[i][j]])
            {
                degree[low[i]]++;
            }
        }
    }
    int ans=0;
    for(int i=0;i<=f;i++)
    {
        if(degree[i]==1)
        {
            ans++;
        }
    }
    printf("%d/n",(ans+1)>>1);
    return 0;
}
