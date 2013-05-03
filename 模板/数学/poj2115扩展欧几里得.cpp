/*数论；
题意：给你一个循环 for (i = A; i != b; i = (i + C) % (2 ^ k)) ;求其循环次数，
若无解，则输出“FOREVER” ；
算法：即求出一个x，使得 (A + x * C) % (2 ^ k) = B, 
变换一下：x * C + y * (2 ^ k) = b - a， 显然这个可以用拓展欧几里得算法求出；
有一点需要注意：1左移32位会溢出，所以我们要做类型转换，转换的时候不能这么写： 
(__int64)(1 << k), 因为在过程中可能会溢出，而应该这么写：
 ((__int64)1) << k ， 这样1就会转换为__int64了，也就不用担心溢出了；*/
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
    while (scanf ("%lld%lld%lld%lld", &a, &b, &c, &k), a | b | c | k)
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
