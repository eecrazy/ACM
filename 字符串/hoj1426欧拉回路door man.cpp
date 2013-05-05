//注意是无向图
#include <cstdio>
#include <cstring>
const int MAX = 32;
int door[MAX][MAX];
bool DFS(const int n)
{
    int stack[MAX], top = 0;
    bool visit[MAX] = {false};
    int i, j;
    stack[top++] = 0;
    visit[0] = true;
    while (top > 0)
    {
        int p = stack[--top];
        for (i = 0; i < n; i++)
        {
            if (door[p][i] != 0 && !visit[i])
            {
                stack[top++] = i;
                visit[i] = true;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n && !visit[j]; j++)
        {
            if (door[i][j] != 0)
            {
                return false;
            }
        }
    }
    return true;
}
int main()
{
    int i, j, src, n, m, dn;
    int id[MAX], odd;
    char info[MAX], ch;
    bool euler;
    while (scanf("%s", info) != EOF && strcmp(info, "ENDOFINPUT"))
    {
        scanf("%d %d", &src, &n);
        dn = 0;
        getchar();
        memset(door, 0, sizeof(door));
        for (i = 0; i < n; i++)
        {
            while (true)
            {
                if ((ch = getchar()) == '\n')
                {
                    break;
                }
                else if (ch != ' ')
                {
                    ungetc(ch, stdin);//把ch重新写回输入流
                    scanf("%d", &m);
                    door[i][m]++;
                    door[m][i]++;
                    dn++;
                }
            }
        }
        euler = true;
        odd = 0;
        //if (!DFS(n))//判断是否存在欧拉回路
        // {
            // euler = false;
        // }
        // else
        // {
            memset(id, 0, sizeof(id));
            for (i = 0; i < n; i++)
            {
                for (j = 0; j < n; j++)
                {
                    id[i] += door[i][j];
                }
                if (id[i] % 2 != 0)
                {
                    odd++;
                }
            }
            if (src == 0)//从0出发回到0
            {
                if (odd != 0)
                {
                    euler = false;
                }
            }
            else//不是从0出发，也要回到零
            {
                if (odd != 2 || id[src] % 2 == 0 || id[0] % 2 == 0)
                {
                    euler = false;
                }
            }
        // }
        scanf("%s", info);
        if (euler)
        {
            printf("YES %d\n", dn);
        }
        else
        {
            printf("NO\n");
        }
    }

    return 0;
}

