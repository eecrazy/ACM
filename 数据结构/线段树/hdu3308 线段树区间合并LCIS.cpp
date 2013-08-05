#include <iostream>
using namespace std;
#include <cstdio>
const int maxn = 200000;
struct Node
{
    int l, r, lt, rt, lx, rx, mx;
} tree[maxn * 2];
int tnum;
int a[maxn];
void maketree(int k)
{
    int mid;
    tree[k].lx = tree[k].rx = tree[k].mx = 1;
    if (tree[k].l == tree[k].r)
    {
        tree[k].lt = tree[k].rt = -1;
        return ;
    }
    mid = (tree[k].l + tree[k].r) / 2;
    tree[tnum].l = tree[k].l;
    tree[tnum].r = mid;
    tree[k].lt = tnum;
    tnum++;
    tree[tnum].l = mid + 1;
    tree[tnum].r = tree[k].r;
    tree[k].rt = tnum++;
}
void pushup(int k)
{
    if (tree[k].lt == tree[k].rt) return ;//叶子节点就返回

    int lt = tree[k].lt, rt = tree[k].rt;
    tree[k].mx = max(tree[lt].mx, tree[rt].mx);
    tree[k].lx = tree[lt].lx;
    tree[k].rx = tree[rt].rx;
    if (a[tree[lt].r] < a[tree[rt].l])
    {
        tree[k].mx = max(tree[k].mx, tree[lt].rx + tree[rt].lx);
        if (tree[lt].lx == tree[lt].r - tree[lt].l + 1)
            tree[k].lx += tree[rt].lx;
        if (tree[rt].rx == tree[rt].r - tree[rt].l + 1)
            tree[k].rx += tree[lt].rx;
    }
}
void update(int k, int c, int val)
{
    if (tree[k].l == tree[k].r)//叶子节点
    {
        a[c] = val;//替换
        return ;
    }
    int mid = (tree[k].l + tree[k].r) / 2;
    if (c <= mid)
        update(tree[k].lt, c, val);
    else update(tree[k].rt, c, val);
    pushup(k);
}
int query(int k, int l , int r)
{
    if (tree[k].l == l && tree[k].r == r)
        return tree[k].mx;
    int mid = (tree[k].l + tree[k].r) / 2;
    if (r <= mid)
        return query(tree[k].lt, l, r);
    if (l > mid)
     return query(tree[k].rt, l, r);
    int mmax = max(query(tree[k].lt, l, mid), query(tree[k].rt, mid + 1, r));
    if (a[mid] < a[mid + 1])
        mmax = max(mmax, min(mid - l + 1, tree[tree[k].lt].rx) + min(r - mid, tree[tree[k].rt].lx));
    return mmax;
}
int n, m;
int main()
{
   // freopen("in.in", "r", stdin);
    int cass;
    for (scanf("%d", &cass); cass--;)
    {
        int i, j, k;
        scanf("%d%d", &n, &m);
        tnum = 1;

        tree[0].l = 0; tree[0].r = n - 1;
        for (i = 0; i < n; i++)
            scanf("%d", &a[i]);

        for (i = 0; i < tnum; i++) maketree(i);
        for (i = tnum - 1; i >= 0; i--) pushup(i);
        char s[10];
        while (m--)
        {
            scanf("%s%d%d", s, &i, &j);
            if (s[0] == 'Q')
                printf("%d\n", query(0, i, j));
            else
                update(0, i, j);
        }
    }
    return 0;
}

//////////////////////////////////////
//学弟的代码，好强悍！
#include <cstdio>
#include <cstring>
#include <map>
#include <cmath>
#include <queue>
#include <string>
#include <stack>
#include <cstdlib>
#include <iostream>
#include <set>
#include <ctime>
#include <vector>
#include <algorithm>
#define abs(x) ((x)>0?(x):-(x))
#define __max(a,b) ((a)>(b)?(a):(b))
#define __min(a,b) ((a)<(b)?(a):(b))
#define rep(i,a,b) for(int i=a;i<b;i++)
#define erep(i,a,b) for(int i=a;i<=b;i++)
#define inf 0x7f//2147483647
#define iinf 0x7fffffff
#define PI acos(-1.0)
#define NOBUG puts("No_Bug_Hear");
#define STOP system("pause");
#define FOUT freopen("out","w",stdout);
#define FIN freopen("in","r",stdin);
#define OUTCLOSE fclose(stdout);
#define INCLOSE fclose(stdin);
#define rd2(a,b) scanf("%d%d",&a,&b)
#define rd(a) scanf("%d",&a)
#define rd3(a,b,c) scanf("%d%d%d",&a,&b,&c)
#define rd4(a,b,c,d) scanf("%d%d%d%d",&a,&b,&c,&d)
#define INIT(a,b) memset(a,b,sizeof(a))
#define pb push_back
#define lson sl,mid,rt<<1
#define rson mid+1,ed,rt<<1|1
#define maxn 100008
typedef long long ll;
using namespace std;


int L, Q, u, v;
char op;
struct node
{
    int lfm, rtm, lfv, rtv, opt;
} t[maxn << 2];
void pushup(int rt, int len)
{
    t[rt].opt = __max(t[rt << 1].opt, t[rt << 1 | 1].opt);
    if (t[rt << 1].rtv < t[rt << 1 | 1].lfv)
    {
        t[rt].opt = __max(t[rt].opt, t[rt << 1].rtm + t[rt << 1 | 1].lfm);
    }
    if (len - len / 2 == t[rt << 1].lfm && t[rt << 1].rtv < t[rt << 1 | 1].lfv)
        t[rt].lfm = t[rt << 1].lfm + t[rt << 1 | 1].lfm;
    else
    {
        t[rt].lfm = t[rt << 1].lfm;
    }
    if (len / 2 == t[rt << 1 | 1].rtm && t[rt << 1].rtv < t[rt << 1 | 1].lfv)
        t[rt].rtm = t[rt << 1].rtm + t[rt << 1 | 1].rtm;
    else
    {
        t[rt].rtm = t[rt << 1 | 1].rtm;
    }
    t[rt].lfv = t[rt << 1].lfv;
    t[rt].rtv = t[rt << 1 | 1].rtv;
}
void build(int st, int ed, int rt)
{
    if (st == ed)
    {
        rd(t[rt].lfv);
        t[rt].rtv = t[rt].lfv;
        t[rt].opt = t[rt].lfm = t[rt].rtm = 1;
        return ;
    }
    int mid = (st + ed) >> 1;
    build(lson);
    build(rson);
    pushup(rt, ed - st + 1);
}

void update(int pos, int x, int st, int ed, int rt)
{
    if (st == ed)
    {
        t[rt].rtv = t[rt].lfv = x;
        return ;
    }
    int mid = (st + ed) >> 1;
    if (pos <= mid)
        update(pos, x, lson);
    else
        update(pos, x, rson);
    pushup(rt, ed - st + 1);
}
int query(int l, int r, int st, int ed, int rt)
{
    if (l <= st && ed <= r)
    {
        return t[rt].opt;
    }
    int mid = (st + ed) >> 1, ret = -1;
    if (l <= mid)ret = max(ret, query(l, r, lson));
    if (r > mid)ret = max(ret, query(l, r, rson));
    if ((l <= mid && r > mid) && (t[rt << 1].rtv < t[rt << 1 | 1].lfv))
    {
        int rrtm = min(t[rt << 1].rtm, mid - l + 1), llfm = min(t[rt << 1 | 1].lfm, r - mid);
        ret = max(ret, rrtm + llfm);
    }
    return ret;
}
int main()
{
    //FIN
    //FOUT
    int T;
    rd(T);
    while (T-- && rd2(L, Q))
    {
        build(1, L, 1);
        while (Q-- && scanf(" %c", &op))
        {
            rd2(u, v);
            if (op == 'Q')
            {
                printf("%d\n", query(u + 1, v + 1, 1, L, 1));
            }
            else
            {
                update(u + 1, v, 1, L, 1);
            }
        }
    }
    //STOP
    //INCLOSE
    //OUTCLOSE
    return 0;
}