#include <iostream>
#include <cstdio>
using namespace std;
#include<cstring>
int s[35],e[35],a[35][35],n;
int gauss()//高斯消元
{
    int i,j;
    for (i=1,j=1; i<=n&&j<=n; j++)
    {
        int k=i;
        for(; k<=n; k++)
            if(a[k][j])break;
        if(a[k][j])
        {
            for(int r=1; r<=n+1; r++)
                swap(a[i][r],a[k][r]);
            for(int r=1; r<=n; r++)
                if(r!=i&&a[r][j])
                    for(k=1; k<=n+1; k++)
                        a[r][k]^=a[i][k];
            i++;
        }
    }
    for(j=i; j<=n; j++)
        if(a[j][n+1])
            return -1;
    return 1<<(n-i+1);//n-i+1为自由元个数
}
int main()
{
    int t,i,j;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        memset(a,0,sizeof(a));
        for( i=1; i<=n; i++)
            scanf("%d",&s[i]);
        for( i=1; i<=n; i++)
        {
            scanf("%d",&e[i]);
            if(s[i]!=e[i])a[i][n+1]=1;
            a[i][i]=1;
        }
        while(scanf("%d%d",&i,&j)&&i+j)
        {
            a[j][i]=1;
        }
        int ans=gauss();
        if(ans==-1)
            printf("Oh,it's impossible~!!\n");
        else
            printf("%d\n",ans);
    }
}
