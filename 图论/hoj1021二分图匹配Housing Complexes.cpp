#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;
const int MAX = 64;
const int N_MAX = 32;
const int INF = 1 << 30;
int r, c, w, h;
int match[N_MAX];
bool check[N_MAX], build[N_MAX][N_MAX];

bool construct(char land[][MAX], char buy)//能否用字母buy买下
{
    int i, j, x, y;
    for (i = 0; i <= r - h; i++)
    {
        for (j = 0; j <= c - w; j++)
        {
            bool can = true;
            for (x = 0; x < h && can; x++)
            {
                for (y = 0; y < w; y++)
                {
                    if (land[i + x][j + y] != '0' && land[i + x][j + y] != buy)
                    {
                        can = false;
                        break;
                    }
                }
            }
            if (can)
                return true;
        }
    }
    return false;
}
bool DFS(int p, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (!check[i] && build[p][i])
        {
            check[i] = true;
            int t = match[i];
            match[i] = p;
            if (t == -1 || DFS(t, n))
                return true;
            match[i] = t;
        }
    }
    return false;
}
int main()
{
    char land[N_MAX][MAX][MAX];
    bool app[N_MAX];
    int m, t, T, i, j, k;
    scanf("%d", &T);
    for (t = 0; t < T; t++)
    {
        scanf("%d %d %d %d %d\n", &m, &r, &c, &h, &w);
        memset(build, false, sizeof(build));
        int n = m, total = 0;

        for (i = 0; i < m; i++)
        {
            memset(app, false, sizeof(app));
            for (j = 0; j < r; j++)
            {
                gets(land[i][j]);
                for (k = 0; k < c; k++)
                {
                    if (isalpha(land[i][j][k]))
                        app[land[i][j][k] - 'A'] = true;
                }
            }
            if (!construct(land[i], ' '))//不可以用空格建造？
            {
                for (j = 0; j < 26; j++)
                {
                    if (app[j] && construct(land[i], j + 'A'))
                    {
                        build[i][j] = true;
                        n = max(n, j + 1);
                    }
                }
            }
            else//可以用空格建造
                total++;
        }
        memset(match, -1, sizeof(match));
        for (i = 0; i < n; i++)
        {
            memset(check, false, sizeof(check));
            if (DFS(i, n))
                total++;
        }
        printf("%d\n", total);
    }
    return 0;
}