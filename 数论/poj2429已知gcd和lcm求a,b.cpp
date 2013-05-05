#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define LL unsigned long long
#define nmax 2005
LL factor[nmax], num[nmax], minx, ans;
int flen, nnum;
LL modular_multi(LL a, LL b, LL c)
{
    LL ret;
    ret = 0, a %= c;
    while (b)
    {
        if (b & 1)
        {
            ret += a;
            if (ret >= c)
            {
                ret -= c;
            }
        }
        a <<= 1;
        if (a >= c)
        {
            a -= c;
        }
        b >>= 1;
    }
    return ret;
}
LL modular_exp(LL a, LL b, LL c)
{
    LL ret;
    ret = 1, a %= c;
    while (b)
    {
        if (b & 1)
        {
            ret = modular_multi(ret, a, c);
        }
        a = modular_multi(a, a, c);
        b >>= 1;
    }
    return ret;
}
int miller_rabin(LL n, int times)
{
    if (n == 2)
    {
        return 1;
    }
    if ((n < 2) || (!(n & 1)))
    {
        return 0;
    }
    LL temp, a, x, y;
    int te, i, j;
    temp = n - 1;
    te = 0;
    while (!(temp & 1))
    {
        temp >>= 1;
        te++;
    }
    srand(time(0));
    for (i = 0; i < times; i++)
    {
        a = rand() % (n - 1) + 1;
        x = modular_exp(a, temp, n);
        for (j = 0; j < te; j++)
        {
            y = modular_multi(x, x, n);
            if ((y == 1) && (x != 1) && (x != (n - 1)))
            {
                return 0;
            }
            x = y;
        }
        if (x != 1)
        {
            return 0;
        }
    }
    return 1;
}
LL gcd(LL a, LL b)
{
    LL te;
    if (a < b)
    {
        te = a, a = b, b = te;
    }
    if (b == 0)
    {
        return a;
    }
    while (b)
    {
        te = a % b, a = b, b = te;
    }
    return a;
}
LL pollard_rho(LL n, int c)
{
    LL x, y, d, i, k;
    srand(time(0));
    x = rand() % (n - 1) + 1;
    y = x;
    i = 1;
    k = 2;
    while (1)
    {
        i++;
        x = (modular_multi(x, x, n) + c) % n;
        d = gcd(y - x, n);
        if ((d > 1) && (d < n))
        {
            return d;
        }
        if (y == x)
        {
            return n;
        }
        if (i == k)
        {
            y = x;
            k <<= 1;
        }
    }
    return -1;
}
void findFactor(LL n, int c)
{
    if (n == 1)
    {
        return;
    }
    if (miller_rabin(n, 6))
    {
        factor[++flen] = n;
        return;
    }
    LL p = n;
    while (p >= n)
    {
        p = pollard_rho(p, c--);
    }
    findFactor(p, c);
    findFactor(n / p, c);

}
int cmp(const void *a, const void *b)
{
    LL te = (*(LL *) a - *(LL *) b);
    if (te > 0)
    {
        return 1;
    }
    else if (te < 0)
    {
        return -1;
    }
    return 0;
}
void solve()
{
    qsort(factor, flen + 1, sizeof(factor[0]), cmp);
    num[0] = factor[0];
    nnum = 0;
    int i;
    for (i = 0; i < flen; i++)
    {
        if (factor[i] == factor[i + 1])
        {
            num[nnum] *= factor[i + 1];
        }
        else
        {
            num[++nnum] = factor[i + 1];
        }
    }
}
void dfs(int s, LL sn, LL n)
{
    if (s == nnum + 1)
    {
        if (minx == -1 || (sn + n / sn < minx))
        {
            if (gcd(sn, n / sn) == 1)
            {
                minx = sn + n / sn;
                ans = sn;
            }
        }
        return;
    }
    dfs(s + 1, sn * num[s], n);
    dfs(s + 1, sn, n);
}
int main()
{
    //NB啊，还能这么写，提交oj不会判错。
    #ifndef ONLINE_JUDGE
        freopen("t.txt", "r", stdin);
    #endif
    LL a, b, n, x, y;
    while (scanf("%lld %lld", &a, &b) != EOF)
    {
        if (a == b)
        {
            printf("%lld %lld\n", a, b);
            continue;
        }
        n = b / a;
        if (miller_rabin(n, 10))
        {
            printf("%lld %lld\n", a, b);
            continue;
        }
        flen = -1;
        findFactor(n, 207);
        solve();
        minx = -1LL;
        dfs(0, 1LL, n);
        x = ans;
        y = n / ans;
        if (x > y)
        {
            n = x, x = y, y = n;
        }
        printf("%lld %lld\n", x * a, y * a);
    }
    return 0;
}
