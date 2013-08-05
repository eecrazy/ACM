//扫描线啊！！！终于看明白了！！
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define maxn 2222
int cnt[maxn << 2];//记录该线段被覆盖的次数
double sum[maxn << 2];
double x[maxn];
struct Seg
{
    double h, l, r;
    int s;
    Seg() {}
    Seg(double a, double b, double c, double d): l(a), r(b), h(c), s(d) {}
    bool operator <(const Seg &cmp)const
    {
        return h < cmp.h;//按照高度h排序
    }
} ss[maxn];
void pushup(int rt, int l, int r)
{
    if (cnt[rt])sum[rt] = x[r + 1] - x[l]; //如果线段被覆盖,求和
    else if (l == r)sum[rt] = 0;//线段没有被覆盖且是叶子节点(即是相邻的2个x坐标)，sun值为零
    else sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];//不是叶子节点，长度为左右儿子之和
}
void update(int L, int R, int c, int l, int r, int rt )
{
    if (L <= l && r <= R)
    {
        cnt[rt] += c;
        pushup(rt, l, r);
        return ;
    }
    int m = (l + r) >> 1;
    if (L <= m)update(L, R, c, lson);
    if (R > m)update(L, R, c, rson);
    pushup(rt, l, r);
}
int Bin(double key, int n, double x[])
{
    int l = 0, r = n - 1;
    while (l <= r)
    {
        int m = (l + r) >> 1;
        if (x[m] == key)return m;
        if (x[m] < key)l = m + 1;//先改变左端点值，在改变右端点值
        else r = m - 1;
    }
    return -1;
}

int main()
{
    int n, cas = 1;
    while (scanf("%d", &n) && n)
    {
        int m = 0;
        while (n--)
        {
            double a, b, c, d;
            scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
            x[m] = a;//x数组保存所有x值
            ss[m++] = Seg(a, c, b, 1);//ss数组保存所有线段
            x[m] = c;
            ss[m++] = Seg(a, c, d, -1);
        }
        sort(x, x + m); //按x坐标排序
        sort(ss, ss + m); //线段按y坐标排序
        //去重函数,高级啊
        int k = 1;
        for (int i = 1; i < m; i++)
        {
            if (x[i] != x[i - 1])x[k++] = x[i];
        }

        memset(cnt, 0, sizeof(cnt));
        memset(sum, 0, sizeof(sum));
        double ret = 0;
        for (int i = 0; i < m - 1; i++)
        {
            int l = Bin(ss[i].l, k, x);
            int r = Bin(ss[i].r, k, x) - 1;
            if (l <= r)update(l, r, ss[i].s, 0, k - 1, 1);
            ret += sum[1] * (ss[i + 1].h - ss[i].h);
        }
        printf("Test case #%d\nTotal explored area: %.2lf\n\n", cas++, ret);

    }
    return 0;
}
