/*
 *最小费用最大流模板
 * 连续最短路法（SPFA)
 * O(Maxflow(G)*kV)
 * HIT_ACM 2012 Summer Camp
 * by xiaodai
 */
#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>

#define SETZR(a) memset(a,0,sizeof(a))

using namespace std;

const int maxn = 10000;
const int maxm = 1000000;
const int INF = 1000000000;

struct record {
    int v, f, c, next;
} edge[maxm];

int cas, ans, cl, n, m, s, t, aug, k, p;
int dist[maxn], pre[maxn], pointer[maxn];
bool vis[maxn];
queue<int> q;

void connect(int a, int b, int f, int c) {
    cl++;
    edge[cl].next = pointer[a];
    edge[cl].v = b;
    edge[cl].f = f;
    edge[cl].c = c;
    pointer[a] = cl;
    cl++;
    edge[cl].next = pointer[b];
    edge[cl].v = a;
    edge[cl].f = 0;
    edge[cl].c = -c;
    pointer[b] = cl;
}

bool spfa() {
    memset(vis, 0, sizeof (vis));
    for (int i = 0; i < n; i++) dist[i] = INF;
    q.push(s);
    dist[s] = 0;
    pre[s] = 0;
    while (!q.empty()) {
        k = q.front();
        q.pop();
        vis[k] = 0;
        p = pointer[k];
        while (p != 0) {
            if ((edge[p].f > 0) && (edge[p].c + dist[k] < dist[edge[p].v])) {
                dist[edge[p].v] = edge[p].c + dist[k];
                pre[edge[p].v] = p;
                if (!vis[edge[p].v]) {
                    q.push(edge[p].v);
                    vis[edge[p].v] = 1;
                }
            }
            p = edge[p].next;
        }
    }
    if (dist[t] == INF) return false;
    p = pre[t];
    aug = INF;
    while (p != 0) {
        aug = min(aug, edge[p].f);
        p = pre[edge[p^1].v];
    }
    p = pre[t];
    while (p != 0) {
        edge[p].f -= aug;
        edge[p^1].f += aug;
        p = pre[edge[p^1].v];
    }
    ans += dist[t] * aug;
    return true;
}

int main() {
    scanf("%d", &cas);
    while (cas--) {
        cl = 1;
        scanf("%d%d%d%d", &n, &m, &s, &t);
        SETZR(pointer);
        for (int i = 0; i < m; i++) {
            int p, k, f, c;
            scanf("%d%d%d%d", &p, &k, &f, &c);
            connect(p, k, f, c);
        }
        ans = 0;
        while (spfa()) {
        };
        printf("%d\n", ans);
    }
    return 0;
}

