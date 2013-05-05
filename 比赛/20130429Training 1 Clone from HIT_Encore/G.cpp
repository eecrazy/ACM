#include <stdio.h>
const int maxn = 501;
struct edge
{
    int l, r;
} e[maxn];
bool used[maxn];
int n;
inline int min(int a, int b)
{
    return (a < b) ? a : b;
}
inline int abs(int a)
{
    if (a < 0)
        return -a;
    return a;
}
bool in(int i, int j, int k)
{
    if ((e[j].l - k <= i && e[j].r >= i) || (e[j].r + k >= i && e[j].l <= i))
        return true;
    return false;
}
bool f(int k)
{
    int i, j, sel;
    for (i = 1; i <= n; i++)
        used[i] = false;
    for (i = 1; i <= n; i++)
    {
        sel = 0;
        for (j = 1; j <= n; j++)
            if (!used[j])
            {
                if (in(i, j, k) && e[j].r < e[sel].r)
                    sel = j;
            }
        if (sel == 0)
            return false;

        used[sel] = true;
    }
    return true;
}
int main()
{
    int test, tt, l, r, m, i;
    scanf("%d", &test);
    e[0].r = 501;
    for (tt = 1; tt <= test; tt++)
    {
        scanf("%d", &n);
        for (i = 1; i <= n; i++)
            scanf("%d%d", &e[i].l, &e[i].r);
        printf("Case #%d: ", tt);
        l = 0, r = n;
        while (r > l + 1)
        {
            m = (l + r) / 2;
            if (f(m))
                r = m;
            else
                l = m;
        }
        if (f(l))
            printf("%d\n", l);
        else
            printf("%d\n", r);
    }
}