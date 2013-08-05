// 题意:求Inversion后的最小逆序数
// 思路:用O(nlogn)复杂度求出最初逆序数后,就可以用O(1)的复杂度分别递推出其他解
// 线段树功能:update:单点增减 query:区间求和
#include <iostream>
#include <cstring>
using namespace std;
long long a[500005];
long long t;
int b[500005];
int main()
{
    int n;
    while (cin >> n)
    {
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        t = 0;
        memset(b, 0, sizeof(b));
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
                if (a[i] > a[j])
                    b[i]++;
            t += b[i];
        }
        long long min = t;
        for ( int i = 0; i < n - 1; i++) //
        {
            //
            t = t - a[i] + (n - 1) - a[i]; //移动第一个到最后一个后新的逆序数求法
            if (min > t)
                min = t;
        }
        cout << min << endl;
    }
    return 0;
}

//+++++++++++++++++++++++++++++++++++++++
//线段树版本
#include <cstdio>
#include <algorithm>
using namespace std;

#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1
const int maxn = 5555;
int sum[maxn << 2];
void PushUP(int rt)
{
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}
void build(int l, int r, int rt)
{
    sum[rt] = 0;
    if (l == r) return ;
    int m = (l + r) >> 1;
    build(lson);
    build(rson);
}
void update(int p, int l, int r, int rt)
{
    if (l == r)
    {
        sum[rt] ++;
        return ;
    }
    int m = (l + r) >> 1;
    if (p <= m) update(p , lson);
    else update(p , rson);
    PushUP(rt);
}
int query(int L, int R, int l, int r, int rt)
{
    if (L <= l && r <= R)
    {
        return sum[rt];
    }
    int m = (l + r) >> 1;
    int ret = 0;
    if (L <= m) ret += query(L , R , lson);
    if (R > m) ret += query(L , R , rson);
    return ret;
}
int x[maxn];
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        build(0 , n - 1 , 1);
        int sum = 0;
        for (int i = 0 ; i < n ; i ++)
        {
            scanf("%d", &x[i]);
            sum += query(x[i] , n - 1 , 0 , n - 1 , 1);
            update(x[i] , 0 , n - 1 , 1);
        }
        int ret = sum;
        for (int i = 0 ; i < n ; i ++)
        {
            sum += n - x[i] - x[i] - 1;
            ret = min(ret , sum);
        }
        printf("%d\n", ret);
    }
    return 0;
}
