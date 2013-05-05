#include <cstdio>
#include <string.h>
#define maxn 1005
#define maxm 1000005
#define min(a,b) (a<b?a:b);
struct node
{
    int to;
    int next;
} edge[maxm];
int map[maxn][maxn];//原图
int head[maxn];//头结点
int Belong[maxn];//i属于第几个强连通分量
int color[maxn];//染色序列
int n, m, cnt, ansi, Index, top, scc; //scc是强连通分量标号
int low[maxn], dfn[maxn], stack[maxn];
int temp[maxn];//临时的栈,存储双连通分支
bool instack[maxn];//是否在栈内
bool expell[maxn];// expell[i]==true表示i需要被驱逐
void init()
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j)map[i][j] = 1;
            else map[i][j] = 0;
    for (int i = 1; i <= n; i++)
    {
        expell[i] = true;
        instack[i] = false;
        dfn[i] = low[i] = Belong[i] = 0;
        head[i] = -1;
    }
    Index = cnt = ansi = top = scc = 0;
}
void add(int a, int b)
{
    edge[ansi].to = b;
    edge[ansi].next = head[a];
    head[a] = ansi++;
}
bool odd_cycle(int u, int clr) //判断奇圈
{
    color[u] = clr;
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].to;
        if (Belong[v] == scc)
        {
            if (color[v] && color[v] == color[u])
                return true;
            if (!color[v] && odd_cycle(v, -clr))
                return true;
        }
    }
    return false;
}
void tarjan(int u, int father) //求点强连通分量
{
    int v, t;
    stack[++top] = u;
    instack[u] = true;
    dfn[u] = low[u] = ++Index;
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        v = edge[i].to;
        if (v == father)continue;
        if (!dfn[v])
        {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) //点强连通分量满足的条件,u是割点
            {
                scc++;
                do
                {
                    t = stack[top--];
                    instack[t] = false;
                    Belong[t] = scc;
                    temp[++cnt] = t; //出栈的同时把所有的点记录在temp中，即用temp来储存双连通分支内所有的点
                }
                while (t != v); //注意不要把u出栈，因为一个割点可能属于不同的双联通分支
                temp[++cnt] = u; // 割点u属于不同的双联通分支，所以它必然也属于temp
                memset(color, 0, sizeof(color)); //所有颜色置为0
                if (cnt >= 3 && odd_cycle(u, 1)) //// 当temp中存在奇圈，那么temp中的所有人都可以留下
                {
                    while (cnt != 0)
                        expell[temp[cnt--]] = false;
                }
                else cnt = 0;
            }
        }
        else if (instack[v])
            low[u] = min(low[u], low[v]);
    }
}
int main()
{
    while (scanf("%d%d", &n, &m) != EOF && n + m)
    {
        init();
        int a, b;
        for (int i = 0; i < m; ++i)
        {
            scanf("%d%d", &a, &b);
            map[a][b] = map[b][a] = 0;
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (map[i][j])
                {
                    add(i, j);
                    add(j, i);
                }
            }
        }
        for (int i = 1; i <= n; i++)
        {
            if (!dfn[i])
                tarjan(i, -1);
        }
        int res = 0;
        for (int i = 1; i <= n; i++)
            if (expell[i])res++;
        printf("%d\n", res);
    }
}
