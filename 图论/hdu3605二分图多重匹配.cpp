//题目描述:世界末日即将到来，地球上有n个人想转移到m个外星球，但是不同的人适应于不同的星球(1个人可适应多个星球)，每个外星球都有人数的限制，现在给你星球人数的上限。还有每个人不同的适应情况。问，能否安排所有的人都成功地转移到外星球上。
#include<iostream>
#include<vector>
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
    int i, j;
    while (cin >> n >> m)
    {
        fill(&map[0][0], &map[n][m] + 1, 0);
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                scanf("%d", &map[i][j]);
            }
        }
        for (i = 0; i < m; i++) scanf("%d", &cap[i]);
        if (hungary()) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}