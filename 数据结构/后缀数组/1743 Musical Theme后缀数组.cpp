// 1743 Musical Theme不可重叠最长重复子串
#include <cstdio>
#include <algorithm>
#define INF 0x7FFFFFFF
#define MAXN 20010
using namespace std;
int a[MAXN];
int wa[MAXN], wb[MAXN], sa[MAXN], wv[MAXN], ws[MAXN];
int height[MAXN], Rank[MAXN];
inline bool cmp(int *r, int a, int b, int len)
{
    return r[a] == r[b] && r[a + len] == r[b + len];
}
void SA(int n, int m)
{
    int i, j, p, *x = wa, *y = wb, *t;
    for (i = 0; i < m; i++)
        ws[i] = 0;
    for (i = 0; i < n; i++)
        ws[x[i] = a[i]]++;
    for (i = 1; i < m; i++)
        ws[i] += ws[i - 1];
    for (i = n - 1; i >= 0; i--)
        sa[--ws[x[i]]] = i;
    for (j = p = 1; p < n; j <<= 1, m = p)
    {
        for (p = 0, i = n - j; i < n; i++)
            y[p++] = i;
        for (i = 0; i < n; i++)
        {
            if (sa[i] >= j)
                y[p++] = sa[i] - j;
        }
        for (i = 0; i < m; i++)
            ws[i] = 0;
        for (i = 0; i < n; i++)
            ws[wv[i] = x[y[i]]]++;
        for (i = 1; i < m; i++)
            ws[i] += ws[i - 1];
        for (i = n - 1; i >= 0; i--)
            sa[--ws[wv[i]]] = y[i];
        for (t = x, x = y, y = t, x[sa[0]] = 0, p = i = 1; i < n; i++)
            x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
    }
}
void Height(int n)
{
    int i, j, k;
    for (i = 1; i <= n; i++)
        Rank[sa[i]] = i;
    for (i = k = 0; i < n; height[Rank[i++]] = k)
        for (k ? k-- : 0, j = sa[Rank[i] - 1]; a[i + k] == a[j + k]; k++);
}
//以上代码均为后缀数组模板
bool OK(int n, int len)//二分判断代码
{
    int i, up, down;
    up = down = sa[1];
    for (i = 2; i <= n; i++)
    {
        if (height[i] < len)
            up = down = sa[i];
        else
        {
            up = max(up, sa[i]);
            down = min(down, sa[i]);
            if (up - down >= len)
            {
                return true;

            }
        }
    }
    return false;
}
int main()
{
    int n, i, low, high, mid;
    while (scanf("%d", &n), n)
    {
        for (i = 0; i < n; i++)
            scanf("%d", &a[i]);

        for (i = 0; i < n - 1; i++)
            a[i] = a[i + 1] - a[i] + 88;//全部变成差来处理
        a[n - 1] = 0;
        
        SA(n, 177);
        Height(n - 1);
        for (low = 4, high = n >> 1 | 1; low < high;)
        {
            mid = (low + high) >> 1;
            if (OK(n, mid))
                low = mid + 1;
            else
                high = mid;
        }
        if (low < 5)
            low = 0;
        printf("%d\n", low);
    }
    return 0;
}
