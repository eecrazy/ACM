// 题目大意：输入n个单词，每个单词都形成一条从该单词首字母到尾字母的
// 边，单词尾字母要与下一个单词首字母相同，若可以组成这样的路，即可
// 以组成这样一条连着的单词串，输出路径（单词串），若有多条，则要按
// 字典顺序输出，找不到路则输出***。 此题搞了很长的时间啊，主要是建
// 边那一部分，看了很久，不能用邻接矩阵，后来就用了链表，还有输出路
// 径这个难搞啊，后来参考了一下别人的代码，发现那个dfs路径竟然如此巧
// 妙！实在很巧妙！
//邻接表实现#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <algorithm>
#include <math.h>
using namespace std;

bool app[30];
char res[1005][26];
int in[30], out[30], deg[30], father[30], adj[30];
int n, ant, odd, begin, end;

struct edge
{
    bool vis;
    char sh[25];
    int y, next;
} a[1005];

bool cmp(edge a, edge b)
{
    return strcmp(a.sh, b.sh) > 0;
}

void init()
{
    int i;
    ant = odd = 0;
    memset(app, false, sizeof(app));
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    memset(deg, 0, sizeof(deg));
    memset(adj, -1, sizeof(adj));
    for (i = 0; i < 1005; i++) a[i].vis = false;
    for (i = 0; i < 26; i++) father[i] = i;
}

int find(int x)
{
    if (x != father[x])
    {
        father[x] = find(father[x]);
    }
    return father[x];
}

void Union(int x, int y)
{
    father[x] = y;
}

int judge()     //判断是否满足欧拉。0不满足，1欧拉回路，2欧拉路
{
    int i, k;
    for (i = 0; i < 26; i++)    //判断有向图欧拉
    {
        if (!app[i]) continue;
        deg[i] = in[i] - out[i];
        if (abs(deg[i]) > 1) return 0;
        if (deg[i] < 0) begin = i;  //起点
        if (deg[i] > 0) end = i;    //终点
        if (deg[i] % 2) odd++;
        if (odd > 2) return 0;
    }
    for (i = 0; i < 26; i++) if (app[i]) break;
    k = find(i);
    for (i = k + 1; i < 26; i++) //判断连通性
    {
        if (!app[i]) continue;
        if (k != find(i)) return 0;
    }
    if (odd == 0)   //有欧拉回路
    {
        for (i = 0; i < 26; i++)
            if (app[i]) break;
        begin = i;
        return 1;
    }
    return 2;
}

void dfs(int x, int id) //深搜寻找欧拉路径，很巧妙！！！
{
    int i;
    for (i = adj[x]; i != -1; i = a[i].next)
    {
        if (!a[i].vis)
        {
            a[i].vis = true;
            dfs(a[i].y, i);
        }
    }
    if (id != -1) strcpy(res[ant++], a[id].sh); //最先进去的肯定是终点
}

int main()
{
    int i, x, y, fx, fy, t, len, tar;
    scanf("%d", &t);
    while (t--)
    {
        init();
        scanf("%d", &n);
        for (i = 0; i < n; i++)
        {
            scanf("%s", a[i].sh);
        }
        //题目要求是字典顺序，但是我是用前插链表，这时的顺序恰好会相反
        sort(a, a + n, cmp); //所以排序时从大到小，这样刚刚会是字典顺序
        for (i = 0; i < n; i++)
        {
            len = strlen(a[i].sh);
            x = a[i].sh[0] - 'a';
            y = a[i].sh[len - 1] - 'a';
            in[y]++;
            out[x]++;
            app[x] = true;
            app[y] = true;
            /// *****建边*****
            a[i].y = y;
            a[i].next = adj[x];
            adj[x] = i;
            /// ***************
            fx = find(x);
            fy = find(y);
            if (fx != fy) Union(fx, fy);
        }
        tar = judge();
        if (tar == 0)
        {
            printf("***\n");
            continue;
        }
        dfs(begin, -1);
        printf("%s", res[ant - 1]);
        for (i = ant - 2; i >= 0; i--)
        {
            printf(".%s", res[i]);
        }
        printf("\n");
    }

    return 0;
}