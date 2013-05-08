#include <iostream>
#include <queue>
#include <algorithm>
#include  <cstdio>
#include <string.h>
using namespace std;
int gg[30][30], mm[30][30];
int a[30], n, ggpre[30], mmpre[30];
queue<int>my;
void stable_marriage()
{
    int i;
    memset(ggpre, 0, sizeof(ggpre)); //gg优先选择.
    memset(mmpre, -1, sizeof(mmpre)); //mm优先选择.
    int pm, pf;
    while (!my.empty())
    {
        pm = my.front();
        my.pop();
        pf = gg[pm][ggpre[pm]];
        ggpre[pm]++;
        if (mmpre[pf] < 0) mmpre[pf] = pm; //pf是自由的（pm，pf）变成约会状态
        else if (mm[pf][mmpre[pf]] < mm[pf][pm]) //pf更喜欢pm1,pm保持自由.
        {
            my.push(pm);
        }
        else                           //pf更喜欢pm,而不是pm1,(pm,pf)变成约会状态.
        {
            my.push(mmpre[pf]);
            mmpre[pf] = pm;
        }
    }
    for (i = 0; i < 26; i++)
        if (mmpre[i] > -1) ggpre[mmpre[i]] = i;
    for (i = 0; i < n; i++)
        printf("%c %c\n", a[i] + 'a', ggpre[a[i]] + 'A');
    puts("");
}
int main()
{
    int i, j, t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        char temp, str[30];
        while (!my.empty())
            my.pop();
        for (i = 0; i < n; i++)
        {
            scanf(" %c", &temp);
            a[i] = temp - 'a';
            my.push(temp - 'a');
        }
        sort(a, a + n);
        for (i = 0; i < n; i++)
            scanf(" %c", &temp);
        for (i = 0; i < n; i++)
        {
            scanf("%s", str);
            for (j = 0; j < n; j++)
                gg[str[0] - 'a'][j] = str[j + 2] - 'A';
        }
        for (i = 0; i < n; i++)
        {
            scanf("%s", str);
            for (j = 0; j < n; j++)
                mm[str[0] - 'A'][str[j + 2] - 'a'] = j;
        }
        stable_marriage();
    }
    return 0;
}
