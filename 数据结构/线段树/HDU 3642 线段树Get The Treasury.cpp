//求长方体交3次以上部分体积
//离散化Z轴然后线段树算面积
#include <cstdio>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define ls rt<<1
#define rs rt<<1|1
#define lson l,m,ls
#define rson m,r,rs
#define maxn 2222
struct tran
{
    int x1, x2, y1, y2, z1, z2;
} s[maxn];
struct seg
{
    int x, y1, y2, c;
} g[maxn];
int y[maxn], z[maxn];
int t[maxn << 2], once[maxn << 2], twice[maxn << 2], more[maxn << 2];

bool cmp(seg a, seg b)
{
    return a.x < b.x;
}
void build(int n)
{
    while (n--)
        t[n] = once[n] = twice[n] = more[n];
}
int L, R, val;
void updata(int l, int r, int rt)
{
    if (L <= y[l] && R >= y[r])t[rt] += val;
    else
    {
        int m = (l + r) >> 1;
        if (L < y[m])updata(lson);
        if (R > y[m])updata(rson);
    }
    if (t[rt] > 2)
    {
        more[rt] = y[r] - y[l];
        twice[rt] = once[rt] = 0;
    }
    else if (t[rt] > 1)
    {
        more[rt] = more[ls] + more[rs] + twice[ls] + twice[rs] + once[ls] + once[rs];
        twice[rt] = y[r] - y[l] - more[rt];
        once[rt] = 0;
    }
    else if (t[rt])
    {
        more[rt] = more[ls] + more[rs] + twice[ls] + twice[rs];
        twice[rt] = once[ls] + once[rs];
        once[rt] = y[r] - y[l] - twice[rt] - more[rt];
    }
    else if (l >= r)once[rt] = twice[rt] = more[rt] = 0;
    else
    {
        once[rt] = once[ls] + once[rs];
        twice[rt] = twice[ls] + twice[rs];
        more[rt] = more[ls] + more[rs];
    }
}
int main()
{
    int k, ca = 1, n, m, i, w, t;
    __int64 ans;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d%d%d%d%d", &s[i].x1, &s[i].y1, &s[i].z1, &s[i].x2, &s[i].y2, &s[i].z2);
            z[i] = s[i].z1;
            z[i + n] = s[i].z2;
        }
        //排序加离散化z坐标
        sort(z, z + 2 * n);
        for (m = i = 0; i < n + n; i++)
        {
            if (z[m] < z[i])z[++m] = z[i];
        }
        ans = 0;
        for (int j = 1; j <= m; j++)
        {
            for ( k = i = 0; i < n; i++)
            {
                if (s[i].z1 <= z[j - 1] && s[i].z2 >= z[j])
                {
                    g[k].x = s[i].x1;
                    g[k].y1 = s[i].y1;
                    g[k].y2 = s[i].y2;
                    g[k].c = 1;
                    y[k] = s[i].y1;
                    k++;
                    g[k].x = s[i].x2;
                    g[k].y1 = s[i].y1;
                    g[k].y2 = s[i].y2;
                    g[k].c = -1;
                    y[k] = s[i].y2;
                    k++;
                }
            }
            sort(y, y + k);
            sort(g, g + k, cmp);
            for (w = i = 0; i < k; i++)
                if (y[w] < y[i])y[++w] = y[i];
            build(w << 2);
            for (int i = 0; i < k; i++)
            {
                L = g[i].y1;
                R = g[i].y2;
                val = g[i].c;
                updata(0, w, 1);
                if (g[i].x < g[i + 1].x)
                    ans += (__int64)(g[i + 1].x - g[i].x) * (__int64)more[1] * (z[j] - z[j - 1]);
            }
        }
        printf("Case %d: %I64d\n", ca++, ans);
    }
}



//////////////////////////////////////还是很难得这类题目！！这个比较好理解一点啊
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>
#define N 2003
#define lson l,m,k<<1
#define rson m,r,k<<1|1
using namespace std;
struct node
{
    int x, y1, y2, z1, z2;
    int flag;
    bool operator<(const node &a)const
    {
        return x < a.x;
    }
};
struct tree
{
    int cover, one, two, more; //代表的是当前区间被覆盖1,2,2次以上线段长度
};
int rcy[N], rcz[N];
node In[N];
tree st[N << 2];
void build(int l, int r, int k)
{
    st[k].cover = st[k].one = st[k].two = st[k].more = 0;
    if (l + 1 == r)
        return;
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
}
void up(int &k, int &l, int &r) //这个是这类题目的关键
{
    int ls = k << 1, rs = k << 1 | 1;
    if (st[k].cover > 2)
    {
        st[k].more = rcy[r] - rcy[l];
        st[k].one = st[k].two = 0;
        return;
    }
    if (st[k].cover == 2)
    {
        if (l + 1 == r)
        {
            st[k].two = rcy[r] - rcy[l];
            st[k].one = st[k].more = 0;
            return ;
        }
        st[k].more = st[ls].one + st[rs].one + st[ls].two + st[rs].two;
        st[k].more += st[ls].more + st[rs].more;
        st[k].two = rcy[r] - rcy[l] - st[k].more;
        st[k].one = 0;
        return ;
    }
    if (st[k].cover == 1)
    {
        if (l + 1 == r)
        {
            st[k].one = rcy[r] - rcy[l];
            st[k].two = st[k].more = 0;
            return ;
        }
        st[k].two = st[ls].one + st[rs].one;
        st[k].more = st[ls].two + st[rs].two + st[ls].more + st[rs].more;
        st[k].one = rcy[r] - rcy[l] - st[k].more - st[k].two;
        return ;
    }
    if (l + 1 == r)
    {
        st[k].one = st[k].two = st[k].more = 0;
        return;
    }

    st[k].one = st[ls].one + st[rs].one;
    st[k].two = st[ls].two + st[rs].two;
    st[k].more = st[ls].more + st[rs].more;
}
int flag;
void update(int &y1, int &y2, int l, int r, int k)
{
    if (y1 <= rcy[l] && y2 >= rcy[r])
    {
        st[k].cover += flag;
        up(k, l, r);
        return;
    }
    int m = (l + r) >> 1;
    if (y1 < rcy[m]) update(y1, y2, lson);
    if (y2 > rcy[m]) update(y1, y2, rson);
    up(k, l, r);
}
int main()
{
    int x1, y1, z1, x2, y2, z2;
    int n, t = 1, T;
    int i, j, k, l, ry, rz;
    double v, s;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        for (j = i = 0; i < n; i++)
        {
            scanf("%d%d%d%d%d%d", &x1, &y1, &z1, &x2, &y2, &z2);
            In[j].x = x1; In[j].y1 = y1; In[j].y2 = y2;
            In[j].z1 = z1; In[j].z2 = z2;
            rcy[j] = y1; rcz[j] = z1; In[j++].flag = 1;

            In[j].x = x2; In[j].y1 = y1; In[j].y2 = y2;
            In[j].z1 = z1; In[j].z2 = z2;
            rcy[j] = y2; rcz[j] = z2; In[j++].flag = -1;
        }

        sort(In, In + j);
        sort(rcy, rcy + j);
        sort(rcz, rcz + j);

        for (ry = 0, i = 1; i < j; i++)
            if (rcy[i] != rcy[ry])
                rcy[++ry] = rcy[i];

        for (rz = 0, i = 1; i < j; i++)
            if (rcz[i] != rcz[rz])
                rcz[++rz] = rcz[i];
        v = 0; j--;
        for (i = 0; i < rz; i++)
        {
            build(0, ry, 1);
            s = 0;
            for (k = 0; k < j; k++)
            {
                if (In[k].z1 <= rcz[i] && In[k].z2 > rcz[i])
                {
                    flag = In[k].flag;
                    update(In[k].y1, In[k].y2, 0, ry, 1);
                    for (l = k + 1; l < j + 1; l++) //开始没发现这个问题，Wa的我好郁闷
                        if (In[l].z1 <= rcz[i] && In[l].z2 > rcz[i])
                            break;
                    s += 1.0 * st[1].more * (In[l].x - In[k].x);
                }
            }
            v += s * (rcz[i + 1] - rcz[i]);
        }
        printf("Case %d: %.0lf\n", t++, v);
    }
    return 0;
}