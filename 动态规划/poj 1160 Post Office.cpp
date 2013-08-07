//这道题和hoj1005是一样的题目.
#include <stdio.h>
#include <math.h>
int w[301][301], m[31][301], d[305] ;
int main()
{
    int n, p, Case = 1 ;
    while ( scanf("%d%d", &n, &p) == 2 )
    {
        int i, j, k, t ;
        for ( i = 1; i <= n; i++ )
            scanf("%d", &d[i]) ;

        for ( i = 1; i <= n; i++ )
        {
            w[i][i] = 0 ;//边界问题
            for ( j = i + 1; j <= n; j++ )
            {
                //奇数个建立在最中间那个,偶数个建立在中间2个都可以
                w[i][j] = w[i][j - 1] + d[j] - d[(i + j) / 2] ;
            }
        }
        for ( j = 1; j <= n; j++ ) m[1][j] = w[1][j] ;//边界问题

        for ( i = 2; i <= p; i++ )
        {
            m[i][i] = 0 ;
            for ( j = i + 1; j <= n; j++ )
            {
                m[i][j] = 100000000 ;
                for ( k = i - 1; k < j; k++ )
                {
                    //循环求解最小值
                    t = m[i - 1][k] + w[k + 1][j] ;
                    if ( t < m[i][j] ) m[i][j] = t ;
                }
            }
        }
        printf("%d\n", m[p][n]) ;
    }
    return 0 ;
}
//////////////////上面没有使用四边形优化47ms，下面是使用了四边形优化的版本，32ms
//就是加了一个s数组来优化k的取值范围
#include <iostream>
#include <cstdio>
using namespace std;
#define inf 0x7ffffff
#define MIN(a,b) ((a)<(b)?(a):(b))
int dp[31][301];
int val[301];
int w[301][301];
int s[31][301];//表示前i-1个邮局的城市数
int main()
{
    int n, m;
    while (~scanf("%d%d", &n, &m))
    {
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &val[i]);
        }
        for (int i = 1; i <= n; ++i)
        {
            w[i][i] = 0;
            for (int j = i + 1; j <= n; ++j)
            {
                w[i][j] = w[i][j - 1] + val[j] - val[(i + j) / 2];
            }

        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                dp[j][i] = inf;
            }
        }
        for (int i = 1; i <= n; ++i)
        {
            dp[1][i] = w[1][i];
            s[1][i] = 0;
        }
        for (int i = 2; i <= m; ++i)
        {
            s[i][n + 1] = n;
            for (int j = n; j > i; --j)
            {
                for (int k = s[i - 1][j]; k <= s[i][j + 1]; ++k)
                {
                    if (dp[i - 1][k] + w[k + 1][j] < dp[i][j])
                    {
                        s[i][j] = k;
                    }
                    dp[i][j] = MIN(dp[i][j], dp[i - 1][k] + w[k + 1][j]);
                }
            }
        }
        printf("%d\n", dp[m][n]);
    }
    return 0;
}
