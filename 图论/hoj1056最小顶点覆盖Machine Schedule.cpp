//DFS找增广路，速度慢。O(nm)二分图最大匹配。等于最小顶点覆盖
#include <iostream>
#include<cstdio>
#include <string.h>
using namespace std;
#define maxn 102//顶点个数
bool map[maxn][maxn];//存图
bool mark[maxn];//寻找增广路时的标志数组
int nx,ny,k;//A,B集合中的点数
int cx[maxn],cy[maxn];//匹配到的顶点序号

int findpath(int u)
{
    int i,j;
    for (int i = 0; i < ny; ++i)
    {
        if (map[u][i]&&!mark[i])
        {
            mark[i]=1;
            if (cy[i]==-1||findpath(cy[i]))
            {
                    cy[i]=u;
                    cx[u]=i;
                    return 1;
            }
        }
    }
    return 0;
}

int maxmatch()
{
    int ans=0,i,j;
    for (int i = 0; i < nx; ++i)
        cx[i]=-1;
    for (int i = 0; i < ny; ++i)
        cy[i]=-1;

    for (int i = 0; i < nx; ++i)
    {
        if (cx[i]==-1)
        {
            for (int j = 0; j < ny; ++j)
                mark[j]=0;
            ans+=findpath(i);
        }
    }
    return ans;
}
int main()
{
    int a,b,c;
    while(scanf("%d",&nx)!=EOF,nx)
    {
        memset(map,0,sizeof(map));
        scanf("%d%d",&ny,&k);
        for(int i=0;i<k;i++)
        {
            scanf("%d%d%d",&c,&a,&b);
            if(a>0&&b>0)
                map[a][b]=1;
        }
        printf("%d\n", maxmatch());
    }
}
