#include<cstdio>
#include<cstring>
#define X 1200
int ym[X], c[X][X], r[X][X], n, m, g[X][X], use[X];
bool dfs(int u)//在g[][]中寻找增广路径算法
{
    int t;
    for (int v = 1; v <= m; v++)
    {
        if (g[u][v] && !use[v])
        {
            use[v] = 1;
            t = ym[v];
            ym[v] = u;
            if (t == -1 || dfs(t))
                return true;
            ym[v] = t;
        }
    }
    return 0;
}
int hungry()//匈牙利算法
{
    int ret = 0;
    memset(ym, -1, sizeof(ym));
    for (int u = 1; u <= n; u++)
    {
        memset(use, 0, sizeof(use));
        if (dfs(u))
            ret++;
    }
    return ret;
}
int main()
{
    //freopen("in.txt","r",stdin);
    int t,tt;
    char ch[X][X];
    while (scanf("%d%d", &t,&tt)!=EOF)
    {
        for (int i = 0; i < t; i++)
        {
            scanf("%s", ch[i]);
        }
        memset(g, 0, sizeof(g));
        n = m = 0;
        bool flag;
        for (int i = 0; i < t; i++)
        {
            flag = 1;
            for (int j = 0; j < tt; j++)
            {
                if (ch[i][j] == '*')
                {
                    if (flag)
                        n++;
                    r[i][j] = n;
                    flag = 0;
                }
                else
                {
                    flag = 1;
                    r[i][j] = -1;
                }
            }
        }
        for (int i = 0; i < tt; i++)
        {
            flag = 1;
            for (int j = 0; j < t; j++)
            {
                if (ch[j][i] == '*')
                {
                    if (flag)
                        m++;
                    flag = 0;
                    c[j][i] = m;
                }
                else
                {
                    flag = 1;
                    c[j][i] = -1;
                }
            }
        }
        for (int i = 0; i < t; i++)
            for (int j = 0; j < tt; j++)
            {
                if (c[i][j] != -1 && r[i][j] != -1)
                    g[r[i][j]][c[i][j]] = 1;
            }
        printf("%d\n", hungry());
    }
    return 0;
}