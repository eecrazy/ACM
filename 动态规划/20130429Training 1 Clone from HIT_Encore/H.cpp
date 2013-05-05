// High-level ancients(UESTC_1653)
// 题目大意：
// 给一棵多叉树。初始所有结点的权值为0
// 有两种操作 
// 1.add
// ADD u val
// 以u为根的子树 
// u的权值+val 
// u的下一层儿子权值+val+1
// 下下一层儿子权值+val+2
// 类推...
// 2.Query
// Q x
// 询问以x为根的子树（包含x）的权值和
// 结点个数N<=50000 询问个数 P<=100000 0<=val<=1000
// 题解：
// dfs一遍整棵树  记录进结点和出结点的时间戳 得到dfs序 A
// idx[u] idy[u] u进出的时间戳
// tot[u] 以u为根的结点个数
// tot_h[u] 以u为根的所有子结点（包括u)高度和
// val[]       每在u添加一个x,val[idx[u]]+=x-h[u]
//                            val[idy[u]]-=x-h[u];
// time_u[u]   每在u添加一个x, time_u[idx[u]]+=1
//                              time_u[idy[u]]-=1
// sum_u[idx[u]] 每在u添加一个x,sum_u+=(x-h[u])*tot[u]+tot_h[u];
// ANS=tot_h[u]*Sigma_time(1,idx[fa[u]])+Sigma_val(1,idx[fa[u]])*tot[u]+Sigma_sum(idx[u],idy[u]-1);
// 询问u的答案就是 ANS
// 因为只涉及修改和求和操作。维护3个树状数组即可。
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define maxn 50050

using namespace std;

int id;
long long fa[maxn], q[maxn * 2], tot[maxn], h[maxn], idx[maxn], idy[maxn], tot_h[maxn];
long long  val[maxn * 2], time_u[maxn * 2], sum_u[maxn * 2];
vector <int> graph[maxn];

void dfs(int u, int deep)
{
    tot_h[u] = h[u] = deep;
    q[++id] = u;
    idx[u] = id;
    tot[u] = 1;

    for (int i = 0; i < graph[u].size(); i++)
    {
        dfs(graph[u][i], deep + 1);
        tot_h[u] += tot_h[graph[u][i]];
        tot[u] += tot[graph[u][i]];
    }

    q[++id] = u;
    idy[u] = id;
}

int lowbit(int x)
{
    return x & (-x);
}

void add(int x, int pos, long long a[])
{
    while (x <= id)
    {
        a[x] += pos;
        x += lowbit(x);
    }
}

long long sum(int x, long long a[])
{
    long long tot = 0;
    while (x > 0)
    {
        tot += a[x];
        x -= lowbit(x);
    }
    return tot;
}


int main()
{
    int tt, cal = 0;
    scanf("%d", &tt);
    while (tt--)
    {
        cal++;
        printf("Case #%d:\n", cal);
        int n, m;
        scanf("%d%d", &n, &m);

        for (int i = 1; i <= n; i++)
            graph[i].clear();

        for (int i = 2; i <= n; i++)
        {
            scanf("%lld", &fa[i]);
            graph[fa[i]].push_back(i);
        }

        id = 0;
        dfs(1, 1);
        memset(val, 0, sizeof(val));
        memset(sum_u, 0, sizeof(sum_u));
        memset(time_u, 0, sizeof(time_u));
        fa[1] = 0; idx[0] = idy[0] = 0;

        while (m--)
        {
            char str[2];
            scanf("%s", str);
            if (str[0] == 'Q')
            {
                int u;
                scanf("%d", &u);
                long long ans;

                ans = tot_h[u] * sum(idx[fa[u]], time_u) + sum(idx[fa[u]], val) * tot[u] + sum(idy[u] - 1, sum_u) - sum(idx[u] - 1, sum_u);
                printf("%lld\n", ans);
            }
            else
            {
                int u, x;
                scanf("%d%d", &u, &x);
                add(idx[u], x - h[u], val);
                add(idy[u], -x + h[u], val);
                add(idx[u], 1, time_u);
                add(idy[u], -1, time_u);
                add(idx[u], (x - h[u])*tot[u] + tot_h[u], sum_u);
            }
        }

    }
    return 0;
}
