// 这道题是第一道欧拉回路(混合图求欧拉回路)的题，还算比较顺利地过掉了。

// 1 定义

// 欧拉通路 (Euler tour)——通过图中每条边一次且仅一次，并且过每一顶点的通路。
// 欧拉回路 (Euler circuit)——通过图中每条边一次且仅一次，并且过每一顶点的回路。
// 欧拉图——存在欧拉回路的图。

// 2 无向图是否具有欧拉通路或回路的判定

// G有欧拉通路的充分必要条件为：G 连通，G中只有两个奇度顶点(它们分别是欧拉通路的两个端点)。
// G有欧拉回路(G为欧拉图)：G连通，G中均为偶度顶点。

// 3 有向图是否具有欧拉通路或回路的判定

// D有欧拉通路：D连通，除两个顶点外，其余顶点的入度均等于出度，这两个特殊的顶点中，一个顶点的入度比出度大1，另一个顶点的入度比出度小1。
// D有欧拉回路(D为欧拉图)：D连通，D中所有顶点的入度等于出度。

// 4 混合图。混合图也就是无向图与有向图的混合，即图中的边既有有向边也有无向边。

// 5 混合图欧拉回路

// 混合图欧拉回路用的是网络流。
// 把该图的无向边随便定向，计算每个点的入度和出度。如果有某个点出入度之差为奇数，那么肯定不存在欧拉回路。因为欧拉回路要求每点入度 = 出度，也就是总度数为偶数，存在奇数度点必不能有欧拉回路。
// 现在每个点入度和出度之差均为偶数。将这个偶数除以2，得x。即是说，对于每一个点，只要将x条边反向（入>出就是变入，出>入就是变出），就能保证出 = 入。如果每个点都是出 = 入，那么很明显，该图就存在欧拉回路。
// 现在的问题就变成了：该改变哪些边，可以让每个点出 = 入？构造网络流模型。有向边不能改变方向，直接删掉。开始已定向的无向边，定的是什么向，就把网络构建成什么样，边长容量上限1。另新建s和t。对于入 > 出的点u，连接边(u, t)、容量为x，对于出 > 入的点v，连接边(s, v)，容量为x（注意对不同的点x不同。当初由于不小心，在这里错了好几次）。之后，察看是否有满流的分配。有就是能有欧拉回路，没有就是没有。查看流值分配，将所有流量非 0（上限是1，流值不是0就是1）的边反向，就能得到每点入度 = 出度的欧拉图。
// 由于是满流，所以每个入 > 出的点，都有x条边进来，将这些进来的边反向，OK，入 = 出了。对于出 > 入的点亦然。那么，没和s、t连接的点怎么办？和s连接的条件是出 > 入，和t连接的条件是入 > 出，那么这个既没和s也没和t连接的点，自然早在开始就已经满足入 = 出了。那么在网络流过程中，这些点属于“中间点”。我们知道中间点流量不允许有累积的，这样，进去多少就出来多少，反向之后，自然仍保持平衡。
// 所以，就这样，混合图欧拉回路问题，解了。

#include <stdio.h>
#include <string.h>
#include <algorithm>
#define M(x, n) memset(x, n, sizeof(x))
#define rep(i, n) for(int i = 0; i < n; ++i)

using namespace std;

const int inf = 0x7fffffff;
const int MaxN = 2000;

struct Edge
{
    int u, v, w;
    struct Edge *next, *neg;
    Edge() {}
    Edge(const int &U, const int &V, const int &W)
        :u(U), v(V), w(W) {}
} mem[1<<19];

Edge *adj[MaxN<<1], *pre[MaxN<<1];
int src, dst, mtp;
int q[MaxN<<1], qs, qe;
int f[MaxN<<1], mark[MaxN<<1], cut[MaxN<<1];
int m, s, indeg[MaxN], outdeg[MaxN];

inline void addedge(const int &u, const int &v, const int &w)
{
    mem[mtp] = Edge(u, v, w);
    mem[mtp].next = adj[u];
    adj[u] = mem + mtp++;
    mem[mtp] = Edge(v, u, 0);
    mem[mtp].next = adj[v];
    adj[v] = mem + mtp++;
    adj[u]->neg = adj[v];
    adj[v]->neg = adj[u];
}

bool spfa(int src, int dst)
{
    int u, v;
    M(f, 0);
    M(mark, 0);
    M(pre, 0);
    f[src] = inf;
    mark[src] = true;
    pre[src] = NULL;
    q[0] = src;
    qs = 0;
    qe = 1;
    while(qs != qe)
    {
        u = q[qs++];
        if(qs == MaxN) qs = 0;
        for(Edge *p = adj[u]; p; p = p->next)
        {
            v = p->v;
            if(!mark[v] && p->w > 0)      //<<<<<<<<<<<<<<<<<<<<<<<
            {
                f[v] = min(f[u], p->w);
                pre[v] = p;
                mark[v] = true;
                q[qe++] = v;
                if(qe == MaxN) qe = 0;
            }
        }
    }
    if(f[dst] > 0)
        return true;
    return false;
}

int MaxFlow()
{
    int flow = 0;
    while(spfa(src, dst))
    {
        flow += f[dst];
        Edge *p = pre[dst];
        for(int u; p; u = p->u, p = pre[u])
            p->w -= f[dst], p->neg->w += f[dst];
    }
    return flow;
}

inline void add(int i, int &flow)
{
    if(outdeg[i] > indeg[i])
    {
        addedge(src, i, (outdeg[i]-indeg[i])/2);
        flow += (outdeg[i]-indeg[i])/2;
    }
    else if(outdeg[i] < indeg[i])
        addedge(i, dst, (indeg[i]-outdeg[i])/2);
}

int main()
{
    int t;
    int bufu[MaxN], bufv[MaxN], bufm[MaxN];
    for(scanf("%d", &t); t--;)
    {
        scanf("%d%d", &m, &s);
        M(indeg, 0);
        M(outdeg, 0);
        for(int i = 0; i < s; ++i)
        {
            scanf("%d%d%d", bufu+i, bufv+i, bufm+i);
            outdeg[bufu[i]]++;
            indeg[bufv[i]]++;
        }
        int i;
        for(i = 1; i <= m; ++i)
        {
            if((outdeg[i] - indeg[i] + 1000)&1)
                break;
        }
        if(i <= m)
        {
            printf("impossible\n");
            continue;
        }
        src = 0;
        dst = m + 1;
        int Flow = 0;
        M(adj, 0);
        mtp = 0;
        for(int i = 0; i < s; ++i)
        {
            if(!bufm[i] && bufu[i] != bufv[i])
                addedge(bufu[i], bufv[i], 1);
        }
        for(int i = 1; i <= m; ++i)
            add(i, Flow);
        if(MaxFlow() == Flow)
            printf("possible\n");
        else
            printf("impossible\n");
    }
    return 0;
}
