//指数型母函数
/*HDOJ  1521 排列组合
有n种物品，并且知道每种物品的数量。要求从中选出m件物品的排列数。<=m,n<=10
数量较少时，直接用除法*/
#include <cstdio>
#include <string>
#define MAX 100
double cal[2][MAX];
double *pre,*now,*pt;
int n,m;
int a[11];
double fac[100];
int main()
{
    int i,j,k,sum;
    fac[0]  = fac[1] =  1;
    for (i=2; i<=20; i++)
    {
        fac[i] = fac[i-1] * i;
    }
    while (scanf("%d  %d",&n,&m)==2)
    {
        memset(cal,0,sizeof(cal));
        for (i=0; i<n; i++)
        {
            scanf("%d",&a[i]);
        }
        pre = cal[0];
        now = cal[1];
        pre[0] =  1;
        for (i=1; i<=a[0]; i++)
        {
            pre[i]  =  1.0 / fac[i];
        }
        for (i=1; i<n; i++)
        {
            for (j=0; j<MAX; j++)
            {
                if (pre[j] >  0)
                {
                    for (k=0; k<=a[i]; k++)
                    {
                        now[k+j]  += pre[j] / fac[k];
                    }
                }
            }
            pt = now;
            now = pre;
            pre = pt;
            memset(now,0,sizeof(cal[0]));
            pre[0]  = 1;
        }
        printf("%.0lf\n",fac[m]  * pre[m]);
    }
}


//指数型母函数（大数据）
#include<iostream>
using namespace std;
int mm[1000][100];
__int64  a[1000], b[1000];
inline __int64 gcd(__int64 x, __int64 y) //求公约数
{
    __int64 temp;
    while (x % y)
    {
        temp = x % y;
        x = y;
        y = temp;
    }
    return y;
}
int main()
{
    int n, m, i, j, k;
    __int64 tmp, tmp1;
    while (scanf("%d  %d",  &n, &m)  != EOF)
    {
        for (i =  0; i < n; i ++)
        {
            scanf("%d",  &mm[i][0]);
            for (j = 1; j <= mm[i][0]; j ++)scanf("%d",  &mm[i][j]);
        }
        memset(a,  0, sizeof(__int64)*(m  +  1));
        for (i =  1; i <= mm[0][0];  i ++)a[mm[0][i]]  =  1;
        for (i = 1; i < n; i ++)
        {
            memset(b,  0, sizeof(__int64)*(m  +  1));
            for (j = 0; j <= m; j ++)
                for (k = 1; j + mm[i][k]  <= m && k <= mm[i][0]; k ++)
                {
                    if (mm[i][k]  !=  0)
                    {
                        tmp = 1;
                        tmp1 =  1;
                        int w = j + mm[i][k];
                        int x = mm[i][k]  < j ? mm[i][k]  : j; //x是较小的数
                        int y = w - x;
                        __int64 z;
                        while (w > y)
                        {
                            tmp *= w;
                            tmp1 *= x;
                            z = gcd(tmp, tmp1);
                            if (z > 1)
                            {
                                tmp /= z;
                                tmp1 /= z;
                            }
                            w--;
                            x--;
                        }
                        b[j + mm[i][k]]  += tmp * a[j];
                    }
                }
            for (j = 0; j <= m; j ++)a[j]  += b[j];
        }
        printf("%I64d\n",  a[m]);
    }
    return 0;
}
