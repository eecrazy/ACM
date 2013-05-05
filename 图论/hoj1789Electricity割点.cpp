// 分析：题目要求去掉一个点，使得剩下最多不连通的块，我们可以先计算出原来有
// 几个不连通的快，然后选一个连通快，去掉其割点，看一下去掉哪个割点后分出来
// 的块最多，加上原来的块就是答案了，当没有边的时候应该是答案n-1.
#include <cstdio>
#define min(a,b) (a<b?a:b)
const int maxm = 202222;
const int maxn = 11111;
int cut[maxn], dfn[maxn], low[maxn];
int i, j, ansi, num, n, m, Index, cnt, sum, ans;
struct node
{
    int to,next;
}edge[maxm];
int head[maxn];
void dfs(int u, int fa)//这个算法还要好好理解，用dfs求割点
{
    int i, v, cnt = 0;
    dfn[u] = low[u] = ++Index;
    for (i = head[u]; i >= 0; i = edge[i].next)
    {
        v = edge[i].to;
        if (!dfn[v])
        {
            dfs(v, u);
            ++cnt;
            low[u] = min(low[u], low[v]);
            if ((u == num && cnt > 1) || (u != num && dfn[u] <= low[v]))++cut[u];
        }
        else if (v != fa)low[u] = min(low[u], dfn[v]);
    }
}
void tarjan()
{
    Index = cnt = sum = ans = 0;
    for ( i = 0; i < n; ++i)
        dfn[i] = cut[i] = 0;
    for (num = 0; num < n; ++num)
    {
        if (!dfn[num])
        {
            dfs(num, 0);
            ++sum;
        }
        if (cut[num] > ans)
            ans = cut[num];
    }
    ans += sum;
}
int main()
{
    while (scanf("%d%d", &n, &m), n + m)
    {
        if (m == 0)
        {
            printf("%d\n", n - 1);
            continue;
        }
        for (ansi = i = 0; i < n; ++i)
            head[i] = -1;
        while (m--)
        {
            scanf("%d%d", &i, &j);
            edge[ansi].to = j, edge[ansi].next = head[i], head[i] = ansi++;
            edge[ansi].to = i, edge[ansi].next = head[j], head[j] = ansi++;
        }
        tarjan();
        printf("%d\n", ans);
    }
    return 0;
}
