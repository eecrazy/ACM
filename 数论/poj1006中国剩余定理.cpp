//要好好理解中国剩余定理
#include<cstdio>

int main()
{
    int p, e, i, d, ans;
    int icase = 1;
    while(icase)
    {
        scanf("%d%d%d%d",&p,&e,&i,&d);
        if(p == -1 && e == -1 && e == -1 && d == -1)
            break;
        ans = (5544 * p + 14421 * e + 1288 * i ) % (23 * 28 * 33) - d;
        while (ans <= 0)
            ans += 21252;
        printf("Case %d: the next triple peak occurs in %d days.\n",icase++,ans);
    }
    return 0;
}
