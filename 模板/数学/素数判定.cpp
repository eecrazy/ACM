#include<stdio.h>
#include<stdlib.h>
long long Pow(long long a,long long b,long long n)//速度最快
{
    long long t=1;
    for(; b; b>>=1,a=a*a%n)
        if(b&1) t=t*a%n;
    return t;
}
long long Witness(const long long a, const long long b, const long long c)
{
    if (b == 0) return 1;
    long long x = Witness(a, b / 2, c);
    if (x == 0) return 0;
    long long y = Pow(x, x, c);
    if (y == 1 && x != 1 && x != c - 1) return 0;
    if (b & 1) y = Pow(y, a, c);
    return y;
}
bool MillerRabin(const long long &n) //二次探测
{
    if (n < 2) return false;
    if (n == 2) return true;
    if (!(n & 1)) return false;
    for (int i = 0; i < 10; ++i)
        if (Witness(rand() % (n - 2) + 2, n - 1, n) != 1)
            return false;
    return true;
}
int main()
{
    int sel;
    long long n;
    while(scanf("%lld",&n)!=EOF)
    {
        sel=1;
        if(n<=1)sel=0;
        else if(n==2||n==3)sel=1;
        else if((n&1)==0)sel=0;
        else
        {
            if(!MillerRabin(n))
                sel=0;
        }
        if(sel)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
