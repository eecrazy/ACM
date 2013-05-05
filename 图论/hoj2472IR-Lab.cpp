// 最小路径覆盖，以任务为顶点建图。
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int M = 50;
int s[M],e[M];
bool g[M][M];
int un, vn;
int xm[M], ym[M];
bool check[M];
bool search(int u)
{
    int v;
    for (v = 0; v < vn; v++)
        if (g[u][v] && !check[v])
        {
            check[v] = true;
            if (ym[v] == -1 || search(ym[v]))
            {
                ym[v] = u; xm[u] = v;
                return true;
            }
        }
    return false;
}
int match()
{
    int u, ret = 0;
    memset(xm, -1, sizeof(xm));
    memset(ym, -1, sizeof(ym));
    for (u = 0; u < un; u++)
        if (xm[u] == -1)
        {
            memset(check, false, sizeof(check));
            if (search(u)) ret++;
        }
    return ret;
}

int main()
{
    //freopen("in.txt","r",stdin);
    int t, m, i,j,a,b,v,k,p;
    char ss[3];
    while (scanf("%d%d",&k,&p)!=EOF,k+p)
    {
        memset(g,0,sizeof(g));
        un=p;
        vn=k;
        for(i=0;i<p;i++)
        {
            scanf("%d",&m);
            for(j=0;j<m;j++)
            {
                scanf("%d",&a);
                g[i][a]=1;
            }
        }
        if(match()==k)
        printf("yes\n");
        else
        printf("no\n");
    }
    return 0;
}
