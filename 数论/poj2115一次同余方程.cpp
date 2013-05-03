#include <stdio.h>
long long a, b, c, k ,x, y ;
long long gcd(long long aa, long long bb)
{
    long long t, d ;
    if (!bb)
    {
        x = 1, y = 0 ;
        return aa ;
    }
    d = gcd (bb, aa % bb) ;
    t = x, x = y, y = t - aa / bb * y ;
    return d ;
}
int main ()
{
    long long d, t, r ;
    while (scanf ("%I64d%I64d%I64d%I64d", &a, &b, &c, &k), a | b | c | k)
    {
        t = b - a ;
        d = gcd (c, ((long long)1) << k) ;
        if (t % d)
        {
            printf ("FOREVER\n") ;
            continue ;
        }
        x *= t / d ;
        r = (((long long)1) << k) / d ;
        x = (x % r + r) % r ;
        printf ("%lld\n", x) ;
    }
    return 0 ;
}