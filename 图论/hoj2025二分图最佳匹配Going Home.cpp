#include <stdio.h>
#include <string.h>
#define M 310
#define inf 0x3f3f3f3f
struct point
{
    int x, y;
} xx[M], yy[M];
int n,m,nx,ny;
int link[M],lx[M],ly[M],slack[M];    //lx,ly为顶标，nx,ny分别为x点集y点集的个数
int visx[M],visy[M],w[M][M];

int DFS(int x)
{
    visx[x] = 1;
    for (int y = 1;y <= ny;y ++)
    {
        if (visy[y])
            continue;
        int t = lx[x] + ly[y] - w[x][y];
        if (t == 0)       //
        {
            visy[y] = 1;
            if (link[y] == -1||DFS(link[y]))
            {
                link[y] = x;
                return 1;
            }
        }
        else if (slack[y] > t)  //不在相等子图中slack 取最小的
            slack[y] = t;
    }
    return 0;
}
int max(int a,int b)
{
    return a>b?a:b;

}
int KM()
{
    int i,j;
    memset (link,-1,sizeof(link));
    memset (ly,0,sizeof(ly));
    for (i = 1;i <= nx;i ++)            //lx初始化为与它关联边中最大的
        for (j = 1,lx[i] = -inf;j <= ny;j ++)
            if (w[i][j] > lx[i])
                lx[i] = w[i][j];

    for (int x = 1;x <= nx;x ++)
    {
        for (i = 1;i <= ny;i ++)
            slack[i] = inf;
        while (1)
        {
            memset (visx,0,sizeof(visx));
            memset (visy,0,sizeof(visy));
            if (DFS(x))     //若成功（找到了增广轨），则该点增广完成，进入下一个点的增广
                break;  //若失败（没有找到增广轨），则需要改变一些点的标号，使得图中可行边的数量增加。
                        //方法为：将所有在增广轨中（就是在增广过程中遍历到）的X方点的标号全部减去一个常数d，
                        //所有在增广轨中的Y方点的标号全部加上一个常数d
            int d = inf;
            for (i = 1;i <= ny;i ++)
                if (!visy[i]&&d > slack[i])
                    d = slack[i];
            for (i = 1;i <= nx;i ++)
                if (visx[i])
                    lx[i] -= d;
            for (i = 1;i <= ny;i ++)  //修改顶标后，要把所有不在交错树中的Y顶点的slack值都减去d
                if (visy[i])
                    ly[i] += d;
                else
                    slack[i] -= d;
        }
    }
    int res = 0;
    for (i = 1;i <= ny;i ++)
        if (link[i] > -1)
            res += w[link[i]][i];
    return res;
}
int ab(int a)
{
    if(a>=0)return a;
    else return -a;
}
int dist(point a,point b)
{
    return ab(a.x-b.x)+ab(a.y-b.y);
}
int main()
{
//    freopen("in.txt","r",stdin);
    char str[M];
    int a, b,dis;
    while (scanf("%d%d", &n, &m) != EOF,n+m)
    {
        a = b = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%s", str);
            for (int j = 0; j < m; j++)
            {
                if (str[j] == 'H')
                {
                    xx[++a].x = i;
                    xx[a].y = j;
                }
                if (str[j] == 'm')
                {
                    yy[++b].x = i;
                    yy[b].y = j;
                }
            }
        }
        nx=ny= max(a, b);
        memset(w,0,sizeof(w));
        for (int i = 1; i <= a; ++i)
            for (int j = 0; j <= b; ++j)
            {
                dis=dist(yy[j],xx[i]);
                w[j][i]=(300-dis);
            }
        int ans=KM();
        printf("%d\n",300*nx-ans);
    }
}
