// 题目大意是，给出了很多条平行于y轴的线段，然后定义，两条线段能互相‘看见’的条件是，两条线段能由一条水平线连接，
// 且这条水平线不能跟其他的所有线段有交点。
// 而题目要求的是，3个线段能互相看见，这个条件下有多少组不同的。
// 然后就能明显的感觉到是区间覆盖问题了。但是有一个细节问题，就是中间的水平线不一定经过整点，所以即使这个区间的所有点
// 都被覆盖，也不能说其就不能穿过一条线，于是，可以将所有线段的长度扩大至2倍，这样就解决了这个问题。
// 然后对读入的数据，先按x坐标进行排序，然后从左到右，一次对每条线段，先进行查询，看左边能看见多少条线段，然后进行覆盖，
// 因为很明显，如果一条线段能看见另一条线段，那么这个关系必然是相互的，所以对每条线段，只需要往左看就行了，将能看见的
// 线段编号都存入vector中，开一个used数组进行判重.
// 最后就是一个超级暴力的n4枚举了，貌似很不可行，实际上可以观察到平均每个线段能观察到得线段是很少的。

// 思路：

// 线段树的区间染色查询：

// 1. 对区间的x坐标从小到大排序

// 2. 一边更新线段树一边做好统计工作

// 3. Query的时候注意要执行PushDown操作
//下面这点很重要啊！！
// 4. 对于题目给定的区间要 * 2，比如[1, 3] [4, 5]这样的区间中间是有[3, 4]是空着的但是表示不出来。
#include <cstdio>
#include <string.h>
#include <algorithm>
#define maxn 8500<<1
#include <vector>
using namespace std;
struct node
{
    int left, right, mid;
    int cover;
} tree[maxn << 2];
struct seg
{
    int s, t, x;
} p[maxn];
vector<int> g[maxn];
int used[maxn];
bool cmp( seg x, seg y)
{
    return x.x < y.x;
}
void maketree(int s, int e, int rt)
{
    tree[rt].left = s;
    tree[rt].right = e;
    tree[rt].mid = (s + e) >> 1;
    tree[rt].cover = -1;
    if (s == e)return ;
    maketree(s, tree[rt].mid, rt << 1);
    maketree(tree[rt].mid + 1, e, rt << 1 | 1);
}
void pushdown(int rt)
{
    if (tree[rt].cover != -1)
    {
        tree[rt << 1].cover = tree[rt << 1 | 1].cover = tree[rt].cover;
        tree[rt].cover = -1;
    }
}
void update(int s, int e, int p, int rt)
{
    if (tree[rt].left >= s && tree[rt].right <= e)
    {
        tree[rt].cover = p;
        return;
    }
    pushdown(rt);
    if (tree[rt].mid >= s)update(s, e, p, rt << 1);
    if (tree[rt].mid < e)update(s, e, p, rt << 1 | 1);
}
void query(int s, int e, int p, int rt)
{
    if (tree[rt].cover != -1)
    {
        if (used[tree[rt].cover] != p)
        {
            g[tree[rt].cover].push_back(p);
            used[tree[rt].cover] = p;
        }
        return ;
    }
    if (tree[rt].left == tree[rt].right)return ;
    pushdown(rt);
    if (tree[rt].mid >= s)query(s, e, p, rt << 1);
    if (tree[rt].mid < e)query(s, e, p, rt << 1 | 1);
}
int main()
{
    int t, n;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 0; i <= n; i++)
        {
            g[i].clear();
            used[i] = -1;
        }
        for (int i = 0; i < n; i++)
        {
            scanf("%d%d%d", &p[i].s, &p[i].t, &p[i].x);
            p[i].s *= 2;
            p[i].t *= 2;
        }
        sort(p, p + n, cmp);
        maketree(1, maxn, 1);
        for (int i = 0; i < n; i++)
        {
            query(p[i].s, p[i].t, i, 1);
            update(p[i].s, p[i].t, i, 1);
        }
        //下面这段很暴力呀！！
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            int t = g[i].size();
            for (int j = 0; j < t; j++)
            {
                int tx = g[i][j];
                for (int k = j + 1; k < t; k++)
                {
                    int tt = g[tx].size();
                    for (int l = 0; l < tt; l++)
                    {
                        if (g[i][k] == g[tx][l])ans++;
                    }
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
////////////////////////////////////////
// 第一次在poj的效率榜上排第一的题目~~
// 做这题最重要的是看懂题目。。题目中的visible就是指在这两条线之间任意连一条线，存在那么一条它只交于这两条线，问题是找出有多少组，一组3条线中每2条线都存在这个关系。
// 解法就是线段树，先按x排序，然后逐渐插入并查询可以看到的线并记录，记录可以用vector，最后4个for 暴力寻找满足条件的3条线~OK
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#define N 8010
#define lson l,mid,ID<<1
#define rson mid+1,r,ID<<1|1
using namespace std;
vector<int>vis[N];
int color[N << 3], hash[N];
struct node
{
    int l, r, x;
    bool operator<(const node &b)const
    {
        return x < b.x;
    }
} seg[N];
void Pushdown(int ID)
{
    if (color[ID] != -1)
    {
        color[ID << 1] = color[ID << 1 | 1] = color[ID];
        color[ID] = -1;
    }
}
void Update(int L, int R, int x, int l, int r, int ID)
{
    int mid;
    if (L <= l && r <= R)
    {
        color[ID] = x;
        return ;
    }
    Pushdown(ID);
    mid = (l + r) >> 1;
    if (L <= mid)
        Update(L, R, x, lson);
    if (R > mid)
        Update(L, R, x, rson);
}
void query(int L, int R, int x, int l, int r, int ID)
{
    int mid;
    if (color[ID] != -1)
    {
        if (hash[color[ID]] != x)
        {
            vis[color[ID]].push_back(x);
            hash[color[ID]] = x;
        }
        return;
    }
    if (l == r)
        return;
    Pushdown(ID);
    mid = (l + r) >> 1;
    if (R <= mid)
        query(L, R, x, lson);
    else if (L > mid)
        query(L, R, x, rson);
    else
    {
        query(L, R, x, lson);
        query(L, R, x, rson);
    }
}
int main()
{
    int t, n, cnt, i, j, k, l, flag, l1, l2;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        memset(color, -1, sizeof(color));
        for (i = 0; i < n; i++)
        {
            scanf("%d%d%d", &seg[i].l, &seg[i].r, &seg[i].x);
            seg[i].l *= 2;
            seg[i].r *= 2;
            vis[i].clear();
        }
        sort(seg, seg + n);
        memset(hash, -1, sizeof(hash));
        for (i = 0; i < n; i++)
        {
            query(seg[i].l, seg[i].r, i, 0, 16000, 1);
            Update(seg[i].l, seg[i].r, i, 0, 16000, 1);
        }
        cnt = 0;
        for (i = 0; i < n; i++)
        {
            l1 = vis[i].size();
            for (j = 0; j < l1; j++)
            {
                for (k = j + 1; k < l1; k++)
                {
                    flag = 0;
                    l2 = vis[vis[i][j]].size();
                    for (l = 0; l < l2; l++)
                    {
                        if (vis[vis[i][j]][l] == vis[i][k])
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if (flag)
                        cnt++;
                }
            }
        }
        printf("%d\n", cnt);
    }
    return 0;
}