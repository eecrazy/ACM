// 题意:h*w的木板,放进一些1*L的物品,求每次放空间能容纳且最上边的位子
// 思路:每次找到最大值的位子,然后减去L
// 线段树功能:query:区间求最大值的位子(直接把update的操作在query里做了)
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define MAXM 200005
#define MAXN 1000005
using namespace std;
const int INF = 0x3f3f3f3f;
int n, H, W, val;
int Tree[MAXN];
int GetTree(int l, int r, int k)
{
    if (l == r)
    {
        Tree[k] += val;
        return l;
    }
    int mid = (l + r) >> 1, num;
    if (Tree[k << 1] + val <= W)
        num = GetTree(l, mid, k << 1);
    else if (Tree[k << 1 | 1] + val <= W)
        num = GetTree(mid + 1, r, k << 1 | 1);
    Tree[k] = min(Tree[k << 1], Tree[k << 1 | 1]);
    return num;
}

int main()
{
    int i;
    //  freopen("input.txt","r",stdin);
    while (scanf("%d%d%d", &H, &W, &n) != EOF)
    {
        memset(Tree, 0, sizeof(Tree));
        for (H = min(H, n), i = 1; i <= n; i++)
        {
            scanf("%d", &val);
            if (Tree[1] + val <= W) printf("%d\n", GetTree(1, H, 1));
            else printf("-1\n");
        }
    }
    return 0;
}


//另一个版本
#include <cstdio>
#include <iostream>
using namespace std;
#define maxn 200005
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1

int most[maxn << 2];

void pushup(int rt)
{
    most[rt] = max(most[rt << 1], most[rt << 1 | 1]);
}
void build(int W, int l, int r, int rt)
{
    most[rt] = W;
    if (l == r)return ;
    int m = (l + r) >> 1;
    build(W, lson);
    build(W, rson);
    pushup(rt);
}

int query(int p, int l, int r, int rt)
{
    if (l == r)
    {
        most[rt] -= p;
        return l;
    }
    int m = (l + r) >> 1;
    int ans;
    if (p <= most[rt << 1])
        ans = query(p, lson);
    else ans = query(p, rson);
    pushup(rt);
    return ans;
}
int main()
{
    int h, w, n;
    while (scanf("%d%d%d", &h, &w, &n) != EOF)
    {
        int m=n;
        n = min(h, n);
        build(w, 1, n, 1);
        for (int i = 0; i < m; i++)
        {
            scanf("%d", &w);
            if (most[1] < w)
                printf("-1\n");
            else
                printf("%d\n", query(w, 1, n, 1));

        }
    }
}
