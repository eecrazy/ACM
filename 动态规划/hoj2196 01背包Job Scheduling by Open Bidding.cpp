#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;
int f[2700];
int w[600];
int val[600];

int main()
{
    freopen("in","r",stdin);
    int t,tt,n,a,b;

    scanf("%d", &t);
    int ca=1;
    while (t--)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
        {
            scanf("%d %d.%d", &w[i], &a,&b);
            val[i]=a*100+b;

        }
        scanf("%d", &tt);
        memset(f, 0, sizeof(f));
        int best=0,ct=0,bt=0;
        for (int j = 1; j <= n; j++)
        {
            for (int v = tt; v >= w[j]; v--)
            {
                    f[v] = max(f[v], f[v-w[j]]+val[j]);
                    if(f[v] >= best) best = f[v], bt = v;
            }
        }

        printf("Problem %d: %d seconds scheduled for $%d.%02d\n", ca++, bt, best/100, best%100);
    }
    return 0;
}
