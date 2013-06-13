#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
long long x[12];
long long gcd(long long a,long long b)
{
    return b==0?a:gcd(b,a%b);
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in","r",stdin);
#endif
    int t;
    scanf(" %d",&t);
    while(t--)
    {
        int n,m;
        long long sum = 0;
        scanf(" %d%d",&n,&m);

        for(long long i=0; i<n; i++)
        {
            scanf("%lld",&x[i]);
        }
        for(long long i = 1; i<(1<<n); i++)
        {
            long long s = 1;
            long long bits = 0;
            for(long long j=0; j<n; j++)
            {
                if(i &(1<<j))
                {
                    bits++;
                    s *= x[j]/gcd(s,x[j]);
                }
            }
            long long temp = m/s;
            //bits是奇数时
            if(bits&1)
            {
                sum +=temp*bits;
            }
            else
            {
                sum -=temp*bits;
            }
        }
        printf("%lld\n",sum);

    }
}
