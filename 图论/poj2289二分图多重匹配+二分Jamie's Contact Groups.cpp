// 多重匹配:对于二部图，y集合的元素可以匹配x集合中的一个或者多个。
// 解决思路：根据匈牙利算法的思想，这时的link[u]要变成link[u][i],表示与y[u]匹配好了的第i个点，
// 用vlink[u]记录已经于u点匹配了的点的个数，对于x中的x[k],找到一个与他相连的y[i]后，同样判断
// 匈牙利算法中的两个条件是否成立，若满足第一个条件，直接将x[k]，y[i]匹配，否则，如果与y[i]缩
// 匹配的点已经达到了饱和，那么在所有与y[i]配合的点中选一个点，检查能否找到增光路，如果能，就
// 让出位置让x[k]与y[i]匹配。
// 推荐两个典型的“二分图多重匹配 +　二分答案”解决的题目:poj 2112 , poj 2289.
// poj2112 二分的是cow所走的距离，以此重新构图，poj2289二分的分组中的元素个数的最大值，以此作
// 为匹配的上限。

#include <iostream>
using namespace std;
const int N = 1001;
const int M = 501;
const int inf = 100000000;
int link[N][M], vlink[N], g[N][M];
int in[N], n, m, lim;
char str[160000];
bool vst[N];
bool dfs(int u)
{
    for (int v = 0; v < m; v++)
    {
        if (g[u][v] && !vst[v])
        {
            vst[v] = 1;
            if (vlink[v] < lim)
            {
                link[v][vlink[v]++] = u; return true;
            }
            for (int i = 0; i < vlink[v]; i++)
            {
                if (dfs(link[v][i]))
                {
                    link[v][i] = u; return true;
                }
            }
        }
    }
    return false;
}
bool match()
{
    memset(vlink, 0, sizeof(vlink));
    for (int i = 0; i < n; i++)
    {
        memset(vst, 0, sizeof(vst));
        if (!dfs(i)) return false;
    }
    return true;
}
void cal()
{
    int l = 0 , r = inf;
    while (l < r)
    {
        lim = (l + r) / 2;
        if (match()) r = lim;
        else l = lim + 1;
    }
    printf("%d\n", r);
}
int main()
{
    int x;
    while (scanf("%d%d", &n, &m) != EOF && (m || n))
    {
        getchar();
        memset(g, 0, sizeof(g));
        for (int i = 0; i < n; i++)
        {
            gets(str);
            for (int j = 0; str[j];)
            {
                while (str[j] > '9' || str[j] < '0')
                    j++;
                int tmp = 0;
                while (str[j] >= '0' && str[j] <= '9')
                {
                    tmp = tmp * 10 + str[j++] - '0';
                }
                g[i][tmp] = 1;
            }
        }
        cal();
    }
    return 0;
}