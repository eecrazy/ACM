#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
vector<char>end;
struct point
{
    int x;
    int y;
};
char v[31][31], v1[27], v2[27][27];
int h, w, flag[27], sum;
void dfs(int    flag[])
{
    int i, j, k;
    if (end.size() == sum)
    {
        for (j = 0; j < end.size(); j++)
            cout << end[j];
        cout << endl;
        return ;
    }
    for (i = 1; i <= 26; i++)
    {
        if (flag[i] == 0)
        {
            int flag1[27], l;
            end.push_back(v1[i]);
            for (l = 1; l <= 26; l++) flag1[l] = flag[l];
            flag1[i] = -1;
            for (k = 1; k <= 26; k++)
            {
                if (v2[i][k] != '0') flag1[k]--;
            }
            dfs(flag1);
            end.pop_back();
        }//if
    }//for
    return ;
}
int main()
{
    //freopen("input.txt","r",stdin);
    int i, j, k, i1, temp;
    point a, b;
    while (scanf("%d%d", &h, &w) != EOF)
    {
        sum = 0;
        memset(v2, '0', sizeof(v2));
        memset(flag, -1, sizeof(flag));
        end.clear();
        for (i = 0; i < h; i++)
            scanf("%s", &v[i]);
        v1[1] = 'A';
        for (i = 2; i <= 26; i++)
            v1[i] = v1[i - 1] + 1;
        for (k = 1; k <= 26; k++)
        {
            a.x = 10000; a.y = 10000; b.x = -1; b.y = -1;
            for (i = 0; i < h; i++)
                for (j = 0; j < w; j++)
                {
                    if (v[i][j] == v1[k])
                    {
                        if (i < a.x) a.x = i;
                        if (j < a.y) a.y = j;
                        if (i > b.x) b.x = i;
                        if (j > b.y) b.y = j;
                    }
                }//for

            if (a.x == 10000 && a.y == 10000 && b.x == -1 && b.y == -1) continue;
            else
            {
                flag[k] = 0; sum++;
                for (i1 = a.y; i1 <= b.y; i1++)
                {
                    if (v[a.x][i1] != v1[k])
                    {
                        temp = v[a.x][i1] - 'A' + 1;
                        if (v2[k][temp] == '0')
                            v2[k][temp] = v[a.x][i1];
                    }
                    if (v[b.x][i1] != v1[k])
                    {
                        temp = v[b.x][i1] - 'A' + 1;
                        if (v2[k][temp] == '0')
                            v2[k][temp] = v[b.x][i1];

                    }
                }//for
                for (i1 = a.x; i1 <= b.x; i1++)
                {
                    if (v[i1][a.y] != v1[k])
                    {
                        temp = v[i1][a.y] - 'A' + 1;
                        if (v2[k][temp] == '0')
                            v2[k][temp] = v[i1][a.y];
                    }
                    if (v[i1][b.y] != v1[k])
                    {
                        temp = v[i1][b.y] - 'A' + 1;
                        if (v2[k][temp] == '0')
                            v2[k][temp] = v[i1][b.y];
                    }
                }//for
            }//else

        }
        for (i = 1; i <= 26; i++)
            for (j = 1; j <= 26; j++)
                if (v2[j][i] != '0') flag[i]++;
        dfs(flag);
    }
    return 0;
}
// 上东方饭店