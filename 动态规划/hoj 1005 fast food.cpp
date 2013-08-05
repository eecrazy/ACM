#include <stdio.h>
#include <math.h>
//m[i,j]表示在前 j 个村庄建立 i 个邮局的最小距离和
//w[i,j]表示在 d[i..j]之间建立一个邮局的最小距离和
int w[201][201], m[31][201], d[201] ;
int main()
{
    int n, p, Case = 1 ;
    while ( scanf("%d%d", &n, &p) , n )
    {
        int i, j, k, t ;
        for ( i = 1; i <= n; i++ ) scanf("%d", &d[i]) ;
        for ( i = 1; i <= n; i++ )
        {
            w[i][i] = 0 ;
            for ( j = i + 1; j <= n; j++ )
            {
                w[i][j] = w[i][j - 1] + d[j] - d[(i + j) / 2] ;
            }
        }

        for ( j = 1; j <= n; j++ ) m[1][j] = w[1][j] ;

        for ( i = 2; i <= p; i++ )
        {
            m[i][i] = 0 ;
            for ( j = i + 1; j <= n; j++ )
            {
                m[i][j] = 100000000 ;
                for ( k = i - 1; k < j; k++ )
                {
                    t = m[i - 1][k] + w[k + 1][j] ;
                    if ( t < m[i][j] ) m[i][j] = t ;
                }
            }
        }
        printf("Chain %d\nTotal distance sum = %d\n\n", Case++, m[p][n]) ;
    }
    return 0 ;
}