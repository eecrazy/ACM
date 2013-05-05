//不会啊？怎么建立模型？？？
#include <cstdio>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 40960;
const int BN = 256;
const int INF = 1 << 28;
const int DIR[][2] = { { 1, 2 }, { 1, -2 }, { -1, 2 }, { -1, -2 }, { 2, 1 }, { 2, -1 }, { -2, 1 }, { -2, -1 } };

class Graph
{
private:
    vector<int> g[N];
    int ns, nt, xmate[N], ymate[N], ds[N], dt[N], dis;
    bool vst[N];
    int sn, m;
    bool search();
    bool dfs(int);
    bool legal(int x, int y) const
    {
        return x >= 0 && x < sn && y >= 0 && y < sn;
    }
public:
    int getTotalNode() const
    {
        return ns + nt - m;
    }
    bool build();
    int match();
};
bool Graph::build()
{
    if (scanf("%d %d", &sn, &m) == EOF) return false;
    int board[BN][BN], wn = 0, bn = 0;
    for (int i = 0; i < sn; i++)
        for (int j = 0; j < sn; j++)
            if (!((i + j) & 1)) board[i][j] = bn++;
            else board[i][j] = wn++;
    ns = bn; nt = wn;
    for (int i = 0; i < ns; i++) g[i].clear();
    for (int i = 0; i < m; i++)
    {
        int x, y; scanf("%d %d", &x, &y);
        board[x - 1][y - 1] = -1;
    }
    for (int i = 0; i < sn; i++)
        for (int j = 0; j < sn; j++)
        {
            if (board[i][j] == -1 || ((i + j) & 1)) continue;
            for (int k = 0; k < 8; k++)
            {
                int x = i + DIR[k][0], y = j + DIR[k][1];
                if (!legal(x, y) || board[x][y] == -1) continue;
                g[board[i][j]].push_back(board[x][y]);
            }
        }
    return true;
}
bool Graph::search()
{
    memset(ds, -1, sizeof(ds)); memset(dt, -1, sizeof(dt));
    queue<int> Q; dis = INF;
    for (int i = 0; i < ns; i++)
        if (xmate[i] == -1)
        {
            Q.push(i);
            ds[i] = 0;
        }
    while (!Q.empty())
    {
        int u = Q.front(); Q.pop();
        if (ds[u] > dis) break;
        for (int i = g[u].size() - 1; i >= 0; i--)
        {
            int v = g[u][i];
            if (dt[v] != -1) continue;
            dt[v] = ds[u] + 1;
            if (ymate[v] == -1) dis = dt[v];
            else
            {
                ds[ymate[v]] = dt[v] + 1;
                Q.push(ymate[v]);
            }
        }
    }
    return (dis != INF);
}
bool Graph::dfs(int u)
{
    for (int i = g[u].size() - 1; i >= 0; i--)
    {
        int v = g[u][i];
        if (vst[v] || dt[v] != ds[u] + 1) continue;
        int ut = ymate[v], vs = xmate[u];
        vst[v] = true;
        if (ut != -1 && dt[v] == dis) continue;
        ymate[v] = u; xmate[u] = v;
        if (ut == -1 || dfs(ut)) return true;
        ymate[v] = ut;  xmate[u] = vs;
    }
    return false;
}
int Graph::match()
{
    int mth = 0;
    memset(xmate, -1, sizeof(xmate)); memset(ymate, -1, sizeof(ymate));
    while (search())
    {
        memset(vst, false, sizeof(vst));
        for (int i = 0; i < ns; i++)
            if (ds[i] == 0 && dfs(i)) mth++;
    }
    return mth;
}

Graph g;

int main()
{
   // freopen("in.txt", "r", stdin);
    while (g.build()) printf("%d\n", g.getTotalNode() - g.match());

    return 0;
}
