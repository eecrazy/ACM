//别人的代码
//http://codeforces.com/contest/304/problem/E
#include<cstdio>
#include<cstring>
#define MaxN 1000010
#define MaxNode 14000010
using namespace std;
struct state
{
    int u, v;
} sta[MaxNode];
int N, K, Total;
int aa[MaxN], prep[MaxNode], head[MaxN], f[MaxN], nowpoi[MaxN], nowTotal, ret, maxi;
int cntt[MaxN];
bool UsedPoi[MaxN], iss[MaxN];
int Abs(int a)
{
    return a > 0 ? a : -a;
}
int find(int x)
{
    return f[x] == x ? f[x] : f[x] = find(f[x]);
}
int main()
{
    int i, j, k;
    scanf("%d%d", &N, &K);
    for (i = 1; i <= N; ++i)
    {
        scanf("%d", &aa[i]);
        if (aa[i] > maxi)
            maxi = aa[i];
    }
    ++maxi;
    for (i = 1; i <= N; ++i)
    {
        for (j = 1; j <= N; ++j)
        {
            int dd = Abs(aa[i] - aa[j]);
            if (!iss[dd])
            {
                ++cntt[dd];
                iss[dd] = 1;
            }
        }
        for (j = 1; j <= N; ++j)
        {
            int dd = Abs(aa[i] - aa[j]);
            iss[dd] = 0;
        }
    }
    for (i = 1; i <= N; ++i)
    {
        for (j = i + 1; j <= N; ++j)
        {
            int dd = Abs(aa[i] - aa[j]);
            sta[++Total].u = i; sta[Total].v = j;
            prep[Total] = head[dd];
            head[dd] = Total;
        }
    }
    for (i = 1; i <= N; ++i)
        f[i] = i;
    int nowflag = 0;
    for (i = 1; i <= maxi; ++i)
    {
        nowTotal = 0;
        ret = 0;
        nowflag = 0;
        for (j = 1; j * i <= maxi; ++j)
        {
            if (cntt[j * i] > 2 * K)
            {
                nowflag = 1;
                break;
            }
            for (k = head[j * i]; k; k = prep[k])
            {
                if (find(sta[k].u) != find(sta[k].v))
                {
                    f[find(sta[k].u)] = find(sta[k].v);
                    --ret;
                }
                if (!UsedPoi[sta[k].u])
                {
                    ++ret;
                    UsedPoi[sta[k].u] = 1;
                    nowpoi[++nowTotal] = sta[k].u;
                }
                if (!UsedPoi[sta[k].v])
                {
                    ++ret;
                    UsedPoi[sta[k].v] = 1;
                    nowpoi[++nowTotal] = sta[k].v;
                }
                if (nowTotal > 2 * K)
                {
                    nowflag = 1;
                    break;
                }
            }
        }
        for (j = 1; j <= nowTotal; ++j)
        {
            f[nowpoi[j]] = nowpoi[j];
            UsedPoi[nowpoi[j]] = 0;
        }
        if (nowTotal - ret <= K && (!nowflag))
        {
            printf("%d\n", i);
            return 0;
        }
    }
    return 0;
}