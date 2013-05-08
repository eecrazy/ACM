//姜慧文的没有AC的代码！
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>

int len, l;
char num[5000], f[5000];
int as[500];

long long mod(long long a,long long b)
{
	long long ans=1;
	while(b)
	{
		if(b&1)
		{
			ans=(ans*a);
			b--;
		}
		b/=2;
		a=a*a;
	}
	return ans;
}
int main()
{
    bool tag = 0;
    while (gets(f))
    {
        l = strlen(f);
        //printf("%s\n", f);
        if (l == 0)
        {
            scanf(" %s", num);
            for (int i=len-1; i>=0; i--)
                if (num[i] <= ' ') len--;
                else break;
            gets(f);
            len = strlen(num);
            for (int i=0; i<len; i++)
                as[num[i]] = i;
            if (tag) printf("\n");
            tag = 1;
        }
        else
        {
            int x = 1, max = 0;
            long long ans = 0;
            for (int i=l-1; i>=0; i--)
                if (f[i] <= ' ') l--;
                else break;
            for (int j=l-1; j>=0; j--)
            {
                if (as[f[j]] > max) max = as[f[j]];
            }
                //printf("%d\n", max);
            for (int j=l-1; j>=0; j--)
            {
                for (int k=max+1; k<=len; k++)
                {
                    ans += as[f[j]]*mod(k, l-j-1);
                    //printf("%d^%d = %d\n", k, l-j-1, mod(k, l-j-1));
                }
            }
            printf("%lld\n", ans);
            tag = 1;
        }
    }
    return 0;
}