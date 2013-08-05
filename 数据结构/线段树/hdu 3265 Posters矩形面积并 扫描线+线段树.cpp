//还是矩形面积并，只是在矩形内部出现了洞。只需要把矩形分成几个矩形就好.
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define maxn 50500
int cnt[maxn << 3];//记录该线段被覆盖的次数
__int64  sum[maxn << 3];
int x[maxn<<3];
struct Seg
{
    int h, l, r;
    int s;
    Seg() {}
    Seg(int a, int b, int c, int d): l(a), r(b), h(c), s(d) {}
    bool operator <(const Seg &cmp)const
    {
        return h < cmp.h;//按照高度h排序
    }
} ss[maxn<<3];
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
int Bin(int key, int n, int x[])
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
            int x1, y1, x2, y2, x3, y3, x4, y4;
            scanf("%d%d%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
            x[m] = x1;//x数组保存所有x值
            ss[m++] = Seg(x1, x2, y1, 1);//ss数组保存所有线段
            x[m] = x1;
            ss[m++] = Seg(x1, x2, y3, -1);
            x[m] = x1;
            ss[m++] = Seg(x1,x3,y3,1);
            x[m] = x2;
            ss[m++] = Seg(x1,x3,y4,-1);
            x[m] = x2;
            ss[m++] = Seg(x4,x2,y3,1);
            x[m] = x2;
            ss[m++] = Seg(x4,x2,y4,-1);
            x[m] = x3;
            ss[m++] = Seg(x1,x2,y4,1);
            x[m] = x4;
            ss[m++] = Seg(x1,x2,y2,-1);
        }
        sort(x, x + m); //按x坐标排序
        sort(ss, ss + m); //线段按y坐标排序
        //去重函数,高级啊
        int k = 1;
        for (int i = 1; i < m; i++)
        {
            if (x[i] != x[i - 1])x[k++] = x[i];
        }
        __int64 ret=0;
        memset(cnt, 0, sizeof(cnt));
        memset(sum, 0, sizeof(sum));
        for (int i = 0; i < m - 1; i++)
        {
            int l = Bin(ss[i].l, k, x);
            int r = Bin(ss[i].r, k, x) - 1;
            if (l <= r)update(l, r, ss[i].s, 0, k - 1, 1);
            ret += sum[1] * (ss[i + 1].h - ss[i].h);
        }
        printf("%I64d\n",ret);

    }
    return 0;
}
