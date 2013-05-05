#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const int M = 505;
struct point
{
    double x;double y;
}s[M],e[M];
int n,m;
double ss,v;
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
double dis(point a,point b)
{
      return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
int main()
{
    int i,j;
    while(scanf("%d%d%lf%lf",&n,&m,&ss,&v)!=EOF)
    {
        un=vn=max(n,m);
        double dd=ss*v;
        dd=dd*dd;
        for (i = 0; i < n; i++)
        {
            scanf("%lf%lf",&s[i].x,&s[i].y);
        }
        for (i = 0; i < m; i++)
        {
            scanf("%lf%lf",&e[i].x,&e[i].y);
        }
        memset(g, false, sizeof(g));
        for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
        {
            if(dis(s[i],e[j])<=dd)
            g[i][j]=1;
        }
        cout << n-match() << endl;
    }
    return 0;
}
