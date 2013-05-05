/*
强连通分量+缩点+传递闭包。有n种物品，现给出m种关系，每种关系a,b对应着物品b能够用物品a来换，
然后有q个询问(a,b)，问物品a能不能换到物品b。刚开始是判断两个点是否在一个连通分量里，后来想下
题目有问单向可达即可，判连通分量范围太小，是错的。这题直接搜索也能过。但是如果求传递闭包的话，
直接用floyed超时。可以先缩点，再对新图求传递闭包。这是一类关系问题中的单向连通。是一类有代表性的题目。
*/

#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;
vector<int> e[5001];//旧图
vector<int> ne[5001];//新图
int dfn[5001];
int low[5001];
int stack[5001];
bool instack[5001];
int belong[5001];
bool map[1001][1001];//新图
int n, m, ansi, top;
int cnt;//强连通分量编号

void tarjan(int u)
{
    int j;
    stack[top++] = u;
    low[u] = dfn[u] = ++ansi;
    instack[u] = true;
    int len = e[u].size();
    for (int i = 0; i < len; i++)
    {
        int v = e[u][i];
        if (!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[v], low[u]);
        }
        else if (instack[v])
            low[u] = min(dfn[v], low[u]);
    }
    if (low[u] == dfn[u])
    {
        cnt++;
        do
        {
            j = stack[--top];
            instack[j] = false;
            belong[j] = cnt;
        }
        while (j != u);
    }
}
void dfs(int u, int v)
{
    int len = ne[v].size();
    for (int i = 0; i < len; i++)
        dfs(u, ne[v][i]);
    map[u][v] = true;
}
void init()(
{
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    memset(instack, false, sizeof(instack));
    memset(belong, 0, sizeof(belong));
    memset(map, false, sizeof(map));
    for (int i = 1; i <= n; i++)
        e[i].clear(), ne[i].clear();
    top = 0;
    ansi = 0;
    cnt = 0;
}
void read()
{
    int a, b;
    while (m--)
    {
        scanf("%d%d", &a, &b);
        e[a].push_back(b);
    }
}
void solve()
{
    init();
    read();
    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i])
            tarjan(i);
    }
    for (int i = 1; i <= n; i++)
    {
        int len = e[i].size();
        for (int j = 0; j < len; j++)
        {
            int u = e[i][j];
            if (belong[i] != belong[u])
                ne[belong[i]].push_back(belong[u]);
        }
    }
    for (int i = 1; i <= cnt; i++)
        dfs(i, i);
}
int main()
{
    while (scanf("%d%d", &n, &m) == 2)
    {
        int t, a, b;
        scanf("%d", &t);
        while (t--)
        {
            scanf("%d%d", &a, &b);
            if (belong[a] == belong[b])
            {
                printf("Yes\n");
                continue;
            }
            if (map[belong[a]][belong[b]]) printf("Yes\n");
            else printf("No\n");
        }
    }
    return 0;
}
