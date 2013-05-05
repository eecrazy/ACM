#include <iostream>
#include <vector>
#include <cstdio>
#include <string.h>
using namespace std;
const int N = 100010;
int n, m;
int cap[11], map[N][11];
int val[11], mat[11][N];
bool mark[11];
bool find(int x)
{
    int i, j;
    for (i = 0; i < m; i++)
    {
        if (!mark[i] && map[x][i])
        {
            mark[i] = true;
            if (val[i] < cap[i])
            {
                mat[i][val[i]++] = x;
                return true;
            }
            for (j = 0; j < val[i]; j++)
            {
                if (find(mat[i][j]))
                {
                    mat[i][j] = x;
                    return true;
                }
            }
        }
    }
    return false;
}
bool hungary()
{
    int i;
    memset(val, 0, sizeof(val));
    for (i = 0; i < n; i++)
    {
        memset(mark, false, sizeof(mark));
        if (!find(i)) return false;
    }
    return true;
}

int main()
{
    freopen("in.txt","r",stdin);
    int i, j,num;
    char str[15], ch[25][2];
    while (scanf("%s", str))
    {
        if (str[0] == 'E')break;
        scanf("%d", &n);
        m=5;
        fill(&map[0][0], &map[n][m] + 1, 0);
        for (i = 0; i < n; i++)
        {
            scanf("%s", ch[i]);
            if (ch[i][0] == 'S')
            {
                j = 0;
            } if (ch[i][0] == 'M')
            {
                j = 1;
            } if (ch[i][0] == 'L')
            {
                j = 2;
            } if (ch[i][0] == 'X')
            {
                j = 3;
            } if (ch[i][0] == 'T')
            {
                j = 4;
            } if (ch[i][1] == 'S')
            {
                num = 0;
            } if (ch[i][1] == 'M')
            {
                num = 1;
            } if (ch[i][1] == 'L')
            {
                num = 2;
            } if (ch[i][1] == 'X')
            {
                num = 3;
            } if (ch[i][1] == 'T')
            {
                num = 4;
            }
            for (j; j <= num; j++)
            {
                map[i][j] = 1;
            }
        }
        for (i = 0; i < m; i++)
            scanf("%d", &cap[i]);
        scanf("%s",str);
        if (hungary())
            printf("T-shirts rock!\n");
        else printf("I'd rather not wear a shirt anyway...\n");
    }
    return 0;
}
