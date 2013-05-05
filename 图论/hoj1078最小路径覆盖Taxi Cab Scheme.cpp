#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int M = 505;
struct point
{
    int x, y;
} s[M], e[M];//起点和终点
int st[M], et[M];
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
int ab(int x, int y)
{
    if (x > y)
        return x - y;
    return y - x;
}
int main()
{
    int t, m, i, h, mi, j, dis;
    cin >> t;
    while (t--)
    {
        cin >> m;
        for (i = 0; i < m; i++)
        {
            scanf("%d:%d", &h, &mi);
            scanf("%d%d%d%d", &s[i].x, &s[i].y, &e[i].x, &e[i].y);
            st[i] = h * 60 + mi;
            et[i] = ab(s[i].x, e[i].x) + ab(s[i].y, e[i].y) + st[i];
        }
        memset(g, false, sizeof(g));
        vn = un = m;
        for (i = 0; i < m; i++)
        {
            for (j = i + 1; j < m; j++)
            {
                dis = ab(e[i].x, s[j].x) + ab(e[i].y, s[j].y);
                if (et[i] + dis + 1 <= st[j]) g[i][j] = true;
            }
        }
        cout << m - match() << endl;
    }
    return 0;
}