#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

const int MAX = 50;
const int inf = 0x0fffffff;
int W[MAX][MAX], pre[MAX], best[MAX], dist[MAX], fa[MAX];
bool vis[MAX], mark[MAX], edge[MAX][MAX];
char str[50][50];
int ans, cnt, K, S;

void init()//初始化
{
    for (int i = 0; i < MAX; ++ i)
        for (int j = 0; j < MAX; ++ j)
            W[i][j] = inf;
    memset(vis, false, sizeof(vis));
    memset(edge, false, sizeof(edge));
    ans = 0, cnt = 0;
}
int GetD(char *ss)//得到地点的标号
{
    for (int i = 0; i < MAX; ++ i)
        if (0 == strcmp(ss, str[i]))
            return i;
    for (int i = 0; i < MAX; ++ i)
        dist[i] = inf;
    strcpy(str[cnt ++], ss);
    return cnt - 1;
}
void dfs(int root)//深搜求父节点
{
    mark[root] = false;
    for (int i = 0; i < cnt; ++ i)
        if (mark[i] && W[root][i] < inf && edge[i][root])
        {
            pre[i] = root;
            dfs(i);
        }
}
void prim(int s)//求最小生成树
{
    memset(mark, false, sizeof(mark));
    vis[s] = mark[s] = true;
    for (int i = 0; i < cnt; ++ i)
        if (W[s][i] != inf && !vis[i] && !mark[i])
            dist[i] = W[s][i], fa[i] = s;
    while (true)
    {
        int minn = inf, k = -1;
        for (int i = 0; i < cnt; ++ i)
            if (minn > dist[i] && !vis[i] && !mark[i])
                minn = dist[i], k = i;
        if (-1 == k)break;
        ans += minn;
        mark[k] = vis[k] = true;
        edge[k][fa[k]] = edge[fa[k]][k] = true;
        for (int i = 0; i < cnt; ++ i)
            if (dist[i] > W[k][i] && !vis[i] && !mark[i])
                dist[i] = W[k][i], fa[i] = k;
    }
    int minn = inf, root;
    for (int i = 0; i < cnt; ++ i) //找到mst里点与S项连的最小边
        if (minn > W[S][i] && mark[i])
            minn = W[S][i], root = i;
    ans += minn;
    dfs(root);
    pre[root] = S;
}
int Best(int u)//更新u点到S点最小生成树路径上的最大权值
{
    if (pre[u] == S)
        return -1;
    if (best[u] != -1)
        return best[u];
    int temp = Best(pre[u]);
    if (temp != -1 && W[temp][pre[temp]] > W[u][pre[u]])
        best[u] = temp;
    else
        best[u] = u;
    return best[u];
}
void solve()
{
    int mst = 0;
    for (int i = 0; i < cnt; ++ i) //求出森林中最小生成树
        if (!vis[i])
        {
            prim(i);
            mst ++;
        }
    for (int c = mst + 1; c <= K && c < cnt; ++ c)
    {
        memset(best, -1, sizeof(best));
        for (int i = 0; i < cnt; ++ i)
            if (best[i] == -1 && pre[i] != S && i != S)
                Best(i);//更新最大值
        int minn = inf, u, v, k;
        for (int i = 0; i < cnt; ++ i) //i到S在mst树路径最大值与iS边权值之差最大
            if (W[S][i] < inf && pre[i] != S)
            {
                v = best[i]; u = pre[v];
                if (minn > W[S][i] - W[u][v])
                    minn = W[S][i] - W[u][v], k = i;
            }
        if (minn > 0)break;
        v = best[k]; u = pre[v];
        ans += minn;
        W[u][v] = W[v][u] = inf;
        pre[k] = S;
        W[k][S] = W[S][k] = inf;
    }
}
int main()
{
    freopen("in.txt", "r", stdin);
    int M, u, v, w, t,flag=0;
    scanf("%d", &t);
    while (t--)
    {
        if(flag==1)
            printf("\n");
        flag=1;
        scanf("%d", &M);
        init();
        char str1[50], str2[50];
        while (M --)
        {
            scanf("%s%s%d", str1, str2, &w);
            u = GetD(str1), v = GetD(str2);
            W[u][v] = W[v][u] = w;
        }
        scanf("%d",&K);
        S = GetD("Park");
        vis[S] = true;
        solve();
        printf("Total miles driven: %d\n", ans);
    }
}
