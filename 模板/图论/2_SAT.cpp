/*
2-sat
题意：一个环上有n个点，有m对点之间有连接，连接可以在环内，也可以在环外，问这些连接是否相交
重点还是在建图，每个连接作为一个对象，他有两个状态，在环内，在环外
若两连接相交，则必是一个在环内，一个在环外，
如a、b相交，包含同在环内相交，同在环外相交，则
同在内相交：
a在内(a*2),那么b必在外(b*2+1)
b在内(b*2),那么a必在外(a*2+1)
同在外相交：
a在外(a*2+1),那么b必在内(b*2)
b在外(b*2+1),那么a必在内(a*2)
如此建边即可
*/
#include <stdio.h>
#include <string.h>
#include <queue>
#include <stack>
using namespace std;
struct edge
{
    int ansi;
    int v[1000000];
    int next[1000000];
    int head[1000000];
    edge()
    {
        clear();
    }
    void clear()
    {
        ansi = 1;
        memset(head, 0, sizeof(head));
    }
    void add(int u, int w)
    {
        v[ansi] = w;
        next[ansi] = head[u];
        head[u] = ansi;
        ansi++;
    }
} e1;
int dfn[5000], low[5000];
int n, m, index, scc;
stack<int>ss;
int instack[5000], belong[5000];
struct link
{
    int x, y;
} l[1200];
void tarjan(int u)//tarjan求强连通分量
{
    int i, v;
    dfn[u] = low[u] = index++;
    instack[u] = 1;
    ss.push(u);//之前误写成队列
    for (i = e1.head[u]; i; i = e1.next[i])
    {
        v = e1.v[i];
        if (dfn[v] == 0)
        {
            tarjan(v);
            if (low[v] < low[u])
                low[u] = low[v];
        }
        else if (instack[v] && dfn[v] < low[u])
            low[u] = dfn[v];
    }
    if (low[u] == dfn[u])
    {
        do
        {
            v = ss.top();
            ss.pop();
            instack[v] = 0;
            belong[v] = scc; //标记所属强连通分量的标号
        }
        while (v != u);
        scc++;
    }
}
int jiao(int j, int i)
{
    if (l[j].x < l[i].x && l[i].x < l[j].y && l[j].y < l[i].y)
        return 1;
    if (l[i].x < l[j].x && l[j].x < l[i].y && l[i].y < l[j].y)
        return 1;
    return 0;
}
int main()
{
    e1.clear();
    int i, j;
    scanf("%d%d", &n, &m);
    for (i = 0; i < m; i++)
    {
        scanf("%d%d", &l[i].x, &l[i].y);
        if (l[i].x > l[i].y)
        {
            int tmp = l[i].x;
            l[i].x = l[i].y;
            l[i].y = tmp;
        }
        for (j = 0; j < i; j++)
        {
            if (jiao(j, i))
            {
                e1.add(i * 2, j * 2 + 1);
                e1.add(j * 2, i * 2 + 1);
                e1.add(i * 2 + 1, j * 2);
                e1.add(j * 2 + 1, i * 2);
            }
        }
    }
    index = 1; //dfn[]标记
    scc = 0; //强连通分量个数，从0开始计数
    memset(dfn, 0, sizeof(dfn));
    memset(instack, 0, sizeof(instack));
    for (i = 0; i < 2 * m; i++) //有n组钥匙,2*n个钥匙，4*n个钥匙状态
    {
        if (!dfn[i])
            tarjan(i);
    }
    for (i = 0; i < m; i++)
    {
        if (belong[2 * i] == belong[2 * i + 1])
            break;
    }
    if (i == m)
        printf("panda is telling the truth...\n");
    else printf("the evil panda is lying again\n");
    return 0;
}
