#include <cstdio>
#include <cstring>
int c, n;
int map[5000][5000];
int f[5000];
int main()
{
    while (scanf("%d %d", &c, &n) == 2)
    {
        memset(f, 0, sizeof(f));
        for (int i=0; i<n; i++)
            for (int j=i+1; j<=n; j++)
                scanf("%d", &map[i][j]);
        for (int i=1; i<=n; i++)
        {
            f[i] = map[0][i] + c;
            for (int j=1; j<i; j++)
            {
                if (f[i] > f[j]+map[j][i]+c)
                    f[i] = f[j]+map[j][i]+c;
            }
        }
        printf("%d\n", f[n]);
    }
    return 0;
}