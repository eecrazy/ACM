// 本题大意：有一条点，第i点与第i+1点之间有路i，第k次走过路i获得的愉悦值是ai-(k-1)*bi，
// 保证愉悦值为正，求如何走可以使得愉悦值最大
// 分析：考虑起点i和重点j，可以假设i<=j，那么i左边的路必定走过偶数次，j右边的路必定走过
// 偶数次，i与j之间的路必定走过奇数次，然后DP即可。
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 110;

int v[MAXN][MAXN];
int f[MAXN][MAXN][3];

int main()
{
    int n, m;
    //freopen("input.txt","r",stdin);
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            for (int j = 0; j <= m; ++j) v[i][j] = a * j - j * (j - 1) * b / 2;
        }
        int ans = 0;
        memset(f, 0, sizeof(f));
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
                for (int k = 1; k <= j; ++k)
                {
                    if (k & 1)
                    {
                        f[i][j][1] = max(f[i][j][1], f[i - 1][j - k][2] + v[i][k]);
                        f[i][j][1] = max(f[i][j][1], f[i - 1][j - k][1] + v[i][k]);
                    }
                    else
                    {
                        f[i][j][2] = max(f[i][j][2], f[i - 1][j - k][2] + v[i][k]);
                        f[i][j][0] = max(f[i][j][0], f[i - 1][j - k][1] + v[i][k]);
                        f[i][j][0] = max(f[i][j][0], f[i - 1][j - k][0] + v[i][k]);
                    }
                }
            ans = max(ans, max(f[i][m][0], max(f[i][m][1], f[i][m][2])));
        }
        printf("Case #%d: %d\n", t, ans);
    }
    return 0;
}