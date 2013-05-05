// 分析：由于要把 N 个点都访问一遍，因而最优解必然要经过 N-1 条（种）边，且每
// 条（种）边至少经过一次。最优解也最多经过 N-1 条（种）边，因为经过 N-1 条
// （种）边时，已经把 N 个点都访问至少一遍。因而可以枚举哪条边不走，之后
// 终点必然是这条边的两个端点之一。 假如起点到两个端点的距离分别是 S1， S2，
// 则 这 种 方 案 的 最 优 解 是 S1+S2+min(S1,S2). 以 这 个 起 点 的 最 优 解 是
// min{S1+S2+min(S1,S2)}.总的复杂度为 N^2。 
#include <cstdio>
#define inf 100000000
int map[1050][1050];
int min(int a,int b)
{
    return a<b?a:b;
}
int main()
{
    int i,j,k;
    int e[10000];
    int n;
    int t;
    scanf("%d",&t);
    int num=0;
    while (t--)
    {
        num++;
        scanf("%d",&n);
        int total=0;
        for (i=0;i<n;i++)
        {
            scanf("%d",e+i);
            map[i][i]=0;
            total+=e[i];
        }
        for (j=0;j<n;j++)
        {
            for (i=j+1;i<n;i++)
            {
                map[j][i]=map[j][i-1]+e[i-1];
                map[i][j]=total-map[j][i];
            }
        }
        printf("Case #%d:",num);
         for (i=0;i<n;i++)
         {
             int ans=inf;
             for (j=0;j<n;j++)
             {
                 ans=min(ans,map[i][j]+map[(j+1)%n][i]+min(map[i][j],map[(j+1)%n][i]));
             }
             printf(" %d",ans);
         }
         printf("\n");
    }
}
