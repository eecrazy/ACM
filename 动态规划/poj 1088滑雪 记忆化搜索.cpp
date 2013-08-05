#include <cstdio>
#include <cstring>
#define MAXN 105
int dp[MAXN][MAXN], h[MAXN][MAXN];
int op[4][2] =
{
    {1, 0},
    { -1, 0},
    {0, 1},
    {0, -1}
};
int r, c;

int DP(int x, int y)
{
    if (dp[x][y] != -1) return dp[x][y];//已经计算过了
    int res = 0;
    //状态转移
    for (int i = 0; i < 4; i++)
        if (h[x + op[i][0]][y + op[i][1]] < h[x][y] && res < DP(x + op[i][0], y + op[i][1]))
            res = DP(x + op[i][0], y + op[i][1]);
    dp[x][y] = res + 1;
    return dp[x][y];
}

int main()
{
    while (scanf("%d%d", &r, &c) == 2)
    {
        memset(h, 0x3f, sizeof (h));//将所有格子高度赋值成较大的值(比题目中最大值大)，这样保证不会走出边界
        memset(dp, -1, sizeof (dp));
        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                scanf("%d", &h[i][j]);
        int ans = 0;
        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                if (ans < DP(i, j)) ans = DP(i, j);
        printf("%d\n", ans);
    }
    return 0;
}
