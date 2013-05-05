#include <stdio.h>
#include <algorithm>
using namespace std;
const int maxn=510;
const int inf=-1000000000;
int n,m;
int dp[maxn][maxn],a[maxn][maxn];
int wrong(int x)//一旦小于零，就不能用了
{
    if(x>0) return x;
    return inf;
}
int get(int x)
{
    dp[1][1]=x;
    for(int j=2; j<=m; j++)
        dp[1][j]=wrong(a[1][j]+dp[1][j-1]);
    for(int i=2; i<=n; i++)
        dp[i][1]=wrong(dp[i-1][1]+a[i][1]);
    for(int i=2; i<=n; i++)
        for(int j=2; j<=m; j++)
            dp[i][j]=wrong(max(dp[i-1][j],dp[i][j-1])+a[i][j]);
    return dp[n][m];
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                scanf("%d",&a[i][j]);
        int l=1,r=1000005,mid;
        while(l<=r)
        {
            mid=(l+r)>>1;
            if(get(mid)<0) l=mid+1;
            else r=mid-1;
        }
        printf("%d\n",l);
    }
    return 0;
}
