/*题目：
哈工大推出新的宿舍分配方案，当两人对A B题有相同答案的人可以分在A类宿舍，
对C D题有相同答案的人可以分在B类宿舍，每一间的宿舍人数没有限制的话，问可
以最少要分配多少间宿舍才能分好所有学生
分析：
每一个学生都可以分配在A类宿舍i，或者B类宿舍j，因此，g[i][j] = true，由此可以
构造一个二分图，用hungry算法做由于输入的数据比较大，若用两层循环判断的话，会超时，
所以可以先排序，然后再判断与前面的一不一样，若一样则置g[i][j] = true, i 和 j的值
需要先处理好，具体看代码 */
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
                using namespace std;
#define X 102
int ym[X], na, nb;
bool g[X][X], use[X];
struct node
{
    int a, b, c, d;
    int na, nb;                   //所在的宿舍A B的房间号
} p[X *X];
bool cmp1(node a, node b) //对前两个关键字排序
{
    if (a.a == b.a)
        return a.b < b.b;
    else
        return a.a < b.a;
}
bool cmp2(node a, node b) //对后两个关键字进行排序
{
    if (a.c == b.c)
        return a.d < b.d;
    else
        return a.c < b.c;
}
bool dfs(int u)//寻找一条增广路
{
    int t;
    for (int v = 1; v <= nb; v++)
        if (g[u][v] && !use[v])
        {
            use[v] = true;
            t = ym[v];
            ym[v] = u;    //路径取反操作
            if (t == -1 || dfs(t)) //寻找是否为增广轨
                return true;
            ym[v] = t;
        }
    return false;
}
int hungry()  //
{
    memset(ym, -1, sizeof(ym));
    int ret = 0;                  //初始时增广轨为空
    for (int u = 1; u <= na; u++) //从二分图的左部的每个顶点开始寻找增广轨
    {
        memset(use, false, sizeof(use));
        if (dfs(u))                   //若找到，把它取反，总匹配加一
            ret++;
    }
    return ret;                          //返回最大匹配数
}
int main()
{
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);
    int n, t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d%d%d%d", &p[i].a, &p[i].b, &p[i].c, &p[i].d);
        sort(p, p + n, cmp1);
        na = nb = 1;
        p[0].na = p[0].nb = 1;
        int ta = p[0].a, tb = p[0].b;
        for (int i = 1; i < n; i++)     //对A型宿舍进行标号
        {
            if (p[i].a == ta && p[i].b == tb) //如果与前面的一样的话，在A型宿舍的位置与当前的B型宿舍总数一样
                p[i].na = na;
            else                                    //否则，B型宿舍总数加一
            {
                p[i].na = ++na;
                ta = p[i].a;                   //更新
                tb = p[i].b;
            }
        }
        memset(g, false, sizeof(g));
        sort(p, p + n, cmp2);   //对后两个关键字进行排序
        int tc = p[0].c, td = p[0].d;
        for (int i = 0; i < n; i++)
        {
            if (p[i].c == tc && p[i].d == td) //如果与前面的一样的话，在B型宿舍的位置与当前的B型宿舍总数一样
                p[i].nb = nb;
            else                                    //否则，B型宿舍总数加一
            {
                p[i].nb = ++nb;
                tc = p[i].c;                   //更新
                td = p[i].d;
            }
            g[p[i].na][p[i].nb] = true;//相当于A型宿舍i与B型宿舍j相连
        }
        printf("%d\n", hungry());
    }
    return 0;
}

