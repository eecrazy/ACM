#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
using namespace std;
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1

const int maxn = 55555;
int lsum[maxn << 2] , rsum[maxn << 2] , msum[maxn << 2];
int cover[maxn << 2];

void PushDown(int rt, int m)
{
    if (cover[rt] != -1)
    {
        cover[rt << 1] = cover[rt << 1 | 1] = cover[rt];
        msum[rt << 1] = lsum[rt << 1] = rsum[rt << 1] = cover[rt] ? 0 : m - (m >> 1);
        msum[rt << 1 | 1] = lsum[rt << 1 | 1] = rsum[rt << 1 | 1] = cover[rt] ? 0 : (m >> 1);
        cover[rt] = -1;
    }
}
void PushUp(int rt, int m) //要对左右区间进行合并
{
    lsum[rt] = lsum[rt << 1];
    rsum[rt] = rsum[rt << 1 | 1];
    if (lsum[rt] == m - (m >> 1)) lsum[rt] += lsum[rt << 1 | 1];
    if (rsum[rt] == (m >> 1)) rsum[rt] += rsum[rt << 1];

    msum[rt] = max(lsum[rt << 1 | 1] + rsum[rt << 1] , max(msum[rt << 1] , msum[rt << 1 | 1]));
}
void build(int l, int r, int rt)
{
    msum[rt] = lsum[rt] = rsum[rt] = r - l + 1;//每个区间最长空位都是区间长度
    cover[rt] = -1;//都没有被覆盖
    if (l == r) return ;
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
}
void update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && r <= R)
    {
        msum[rt] = lsum[rt] = rsum[rt] = c ? 0 : r - l + 1;
        cover[rt] = c;
        return ;
    }
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (L <= m) update(L , R , c , lson);
    if (m < R) update(L , R , c , rson);
    PushUp(rt , r - l + 1);
}
int query(int w, int l, int r, int rt)
{
    if (l == r) return l;
    PushDown(rt , r - l + 1);
    int m = (l + r) >> 1;
    if (msum[rt << 1] >= w) return query(w , lson);
    else if (rsum[rt << 1] + lsum[rt << 1 | 1] >= w) return m - rsum[rt << 1] + 1;
    return query(w , rson);
}
int main()
{
    int n , m;
    scanf("%d%d", &n, &m);
    build(1 , n , 1);
    while (m --)
    {
        int op , a , b;
        scanf("%d", &op);
        if (op == 1)
        {
            scanf("%d", &a);
            if (msum[1] < a) puts("0");
            else
            {
                int p = query(a , 1 , n , 1);
                printf("%d\n", p);
                update(p , p + a - 1 , 1 , 1 , n , 1);
            }
        }
        else
        {
            scanf("%d%d", &a, &b);
            update(a , a + b - 1 , 0 , 1 , n , 1);
        }
    }
    return 0;
}
