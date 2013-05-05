#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
vector<char>end;
char v1[27], v2[27][27];
int  flag[27], sum;
void dfs(int flag[])//这个dfs的作用是按字母表的顺序输出所有拓扑序列！！！！
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
    char ch1[500], ch2[5000];
    v1[1] = 'a';
    for (i = 2; i <= 26; i++)
        v1[i] = v1[i - 1] + 1;
        int aa=0;
    while (gets(ch1))
    {
        if(aa==1)
        puts("");
        aa=1;
        gets(ch2);
        sum = 0;
        memset(v2, '0', sizeof(v2));
        memset(flag, -1, sizeof(flag));
        end.clear();

        for (int i = 0; i < strlen(ch1); i++)
        {
            if (ch1[i] == ' ')continue;
            else
            {
                k = ch1[i] - 'a' + 1;
                flag[k] = 0;
                sum++;
            }
        }
        int a, b;
        for (int i = 0; i < strlen(ch2); i += 4)
        {
            a = ch2[i] - 'a' + 1;
            b = ch2[i + 2] - 'a' + 1;
            if (v2[a][b] == '0')
                v2[a][b] = ch2[i+2];
        }
        for (i = 1; i <= 26; i++)
            for (j = 1; j <= 26; j++)
                if (v2[j][i] != '0')
                    flag[i]++;//字母i的最少层数。0是最底层
        dfs(flag);

    }
    return 0;
}
