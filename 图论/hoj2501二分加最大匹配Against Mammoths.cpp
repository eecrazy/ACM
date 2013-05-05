//有难度，二分不太会写。
#include <iostream>
using namespace std;
#include <string.h>
#include <cstdio>
const int INF = 2000000000;
const int xMax = 255;
const int yMax = 255;
int n, m, vis[yMax], yM[yMax], xM[xMax];
bool map[xMax][yMax]; //map[i][j]:xi与yj相邻

bool SearchPath(int u)
{
    for (int i = 1; i <= m; i++)
        if (map[u][i] && !vis[i])
        {
            vis[i] = true; //记录已找
            //dfs，形成一条交错路径，到yM[i]==-1(最后一条边是非匹配边，可增广）
            //或者，都不满足if(map[u][i] && !vis[i])，即非匹配边与匹配边相等，不可增广
            if (yM[i] == -1 || SearchPath(yM[i]))
            {
                yM[i] = u; //记录yi的匹配是u，相当于在交错路径中交换匹配边和非匹配边
                xM[u] = i;
                return true;
            }
        }
    return false;
}

int MaxMatch()
{
    int u, ret = 0;
    memset(xM, -1, sizeof(xM));
    memset(yM, -1, sizeof(yM));
    for (u = 1; u <= n; u++) //开始匹配
        if (xM[u] == -1) //这里可有可无
        {
            memset(vis, false, sizeof(vis)); //第一次都要初始
            if (SearchPath(u)) //能拓展路径
                ret++;
        }
    return ret;
}

long long sh1[xMax], rate1[xMax]; //会溢出,要用long long,如果预处理,就不用long long
long long sh2[yMax], rate2[yMax];
long long Time[xMax][yMax];

void build_Graph(long long mid)
{
    int i, j;
    for (i = 1; i <= n; i++)
        for (j = 1; j <= m; j++)
        {
            if (sh1[i] + (mid - Time[i][j])*rate1[i] >= sh2[j] + mid * rate2[j])
                map[i][j] = 1;
            else
                map[i][j] = 0;
        }
}

int solve() //二分答案求解
{
    long long low = 0, high = INF, mid;
    while (low < high)
    {
        mid = (low + high) / 2;
        build_Graph(mid);
        if (MaxMatch() == m)
            high = mid;
        else
            low = mid + 1;
    }
    return low;
}

int main()
{
    int i, j;
    while (scanf("%d%d", &n, &m) && !(n == 0 && m == 0))
    {
        for (i = 1; i <= n; i++)
            scanf("%d%d", &sh1[i], &rate1[i]);
        for (j = 1; j <= m; j++)
            scanf("%d%d", &sh2[j], &rate2[j]);
        for (i = 1; i <= n; i++)
        {
            for (j = 1; j <= m; j++)
                scanf("%d", &Time[i][j]);
        }
        //先判断有无解
        build_Graph(INF);
        if (MaxMatch() != m)
            cout << "IMPOSSIBLE" << endl;
        else //二分答案
            cout << solve() << endl;
    }
    return 0;
}
