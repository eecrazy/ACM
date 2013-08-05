// a sequence contains n characters which are all '0's or '1's.
// we have 5 Change operations:
// 0 a b  [a , b]区间覆盖为0
// 1 a b  [a , b]区间覆盖为1
// 2 a b  [a , b]区间执行异或操作
// Output operations:
// 3 a b  输出[a, b]区间中1的个数
// 4 a b  输出[a, b]区间中连续最长的1的个数
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#define lson l,m,k<<1
#define rson m+1,r,k<<1|1
#define N 100003
using namespace std;
struct node
{
    int lm, rm, m; //lm代表从区间左端开始以1开始的最长连续序列，rm类同，m代表区间最长的连续1了
    int len, cover, sum; //sum就是成段更新的附带水货了
};
node st[N << 2];
void up(int &k)
{
    int ls = k << 1, rs = k << 1 | 1;
    st[k].sum = st[ls].sum + st[rs].sum;
    st[k].lm = st[ls].lm == st[ls].len ? st[ls].len + st[rs].lm : st[ls].lm;
    st[k].rm = st[rs].rm == st[rs].len ? st[rs].len + st[ls].rm : st[rs].rm;

    st[k].m = max(max(st[ls].m, st[rs].m), st[ls].rm + st[rs].lm);
    //st[k].m = max(max(st[k].lm, st[k].rm), st[k].m); //经研究、发现这句可以不用
}
void qup(node &rt, node &ls, node &rs)
{
    rt.lm = ls.lm == ls.len ? ls.len + rs.lm : ls.lm;
    rt.rm = rs.rm == rs.len ? rs.len + ls.rm : rs.rm;

    rt.m = max(max(ls.m, rs.m), ls.rm + rs.lm);
    //rt.m = max(max(rt.lm, rt.rm), rt.m); //这里就类同了，可以不要这句、是多余的比较了
}
void down(int &k)
{
    st[k << 1].cover = st[k << 1 | 1].cover = st[k].cover;
    st[k << 1].lm = st[k << 1].rm = st[k << 1].m = st[k << 1].sum = st[k].cover ? st[k << 1].len : 0;
    st[k << 1 | 1].lm = st[k << 1 | 1].rm = st[k << 1 | 1].m = st[k << 1 | 1].sum = st[k].cover ? st[k << 1 | 1].len : 0;
    st[k].cover = -1;
}
void build(int l, int r, int k)
{
    st[k].len = r - l + 1;
    if (l == r)
    {
        scanf("%d", &st[k].cover);
        st[k].lm = st[k].rm = st[k].m = st[k].sum = st[k].cover ? 1 : 0;
        return ;
    }
    st[k].cover = -1;
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
    up(k);
}
bool flag;
void update(int &L, int &R, int l, int r, int k)
{
    //printf("%d ",flag);
    if (L <= l && R >= r)
    {
        st[k].lm = st[k].rm = st[k].m = st[k].sum = flag ? st[k].len : 0;
        st[k].cover = flag;
        return ;
    }
    if (st[k].cover != -1)
        down(k);
    int m = (l + r) >> 1;
    if (L <= m) update(L, R, lson);
    if (R > m)  update(L, R, rson);
    up(k);
}
void Xor(int &L, int &R, int l, int r, int k)
{
    if (L <= l && R >= r && st[k].cover != -1)
    {
        // printf("k=%d %d %d\n",l,r,st[k].cover);
        st[k].cover ^= 1;
        st[k].lm = st[k].rm = st[k].m = st[k].sum = st[k].cover ? st[k].len : 0;
        return ;
    }
    if (st[k].cover != -1)
        down(k);
    int m = (l + r) >> 1;
    if (L <= m) Xor(L, R, lson);
    if (R > m)  Xor(L, R, rson);
    up(k);
}
int Qsum(int L, int R, int l, int r, int k)
{
    if (L <= l && R >= r)
    {
        return st[k].sum;
    }
    if (st[k].cover != -1)
        down(k);
    int m = (l + r) >> 1;
    int t1 = 0, t2 = 0;
    if (L <= m) t1 = Qsum(L, R, lson);
    if (R > m)  t2 = Qsum(L, R, rson);
    return t1 + t2;
}
node Qconti(int &L, int &R, int l, int r, int k)
{
    if (L <= l && R >= r)
    {
        return st[k];
    }
    if (st[k].cover != -1)
        down(k);
    int m = (l + r) >> 1;
    node t1, t2;
    t1.len = t2.len = 0;
    if (L <= m) t1 = Qconti(L, R, lson);
    if (R > m)  t2 = Qconti(L, R, rson);
    if (t1.len && t2.len)
    {
        node te;
        qup(te, t1, t2);
        te.len = t1.len + t2.len;
        return te;
    }
    if (t1.len)
        return t1;
    return t2;
}
int main()
{
    int T;
    scanf("%d", &T);
    int n, m;
    int op, a, b;
    node t;
    while (T--)
    {
        scanf("%d%d", &n, &m);
        n--;
        build(0, n, 1);
        while (m--)
        {
            scanf("%d%d%d", &op, &a, &b);
            switch (op)
            {
            case 0: flag = 0; update(a, b, 0, n, 1); break;
            case 1: flag = 1; update(a, b, 0, n, 1); break;
            case 2: Xor(a, b, 0, n, 1); break;
            case 3: printf("%d\n", Qsum(a, b, 0, n, 1)); break;
            case 4: t = Qconti(a, b, 0, n, 1); printf("%d\n", t.m); break;
            }
        }
    }
    return 0;
}
