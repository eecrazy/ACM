// HOJ1068 POJ1364内存开大点啊！runtime error!
#include <iostream>
#include <cstdio>
#include <string.h>
using namespace std;
#define MAX 99999999
const int maxn = 2010;
const int maxm = 8000;
int head[maxn];
int dist[maxn];
bool visit[maxn];
int s, n, m, cnt;
struct node
{
    int to; int w; int next;
};
node edge[maxm];
bool spfa()
{
    s = n;
    int i, k, iq = 0, top;
    int queue[maxn];
    int outque[maxn];
    for (i = 0; i <= n; i++)
    {
        outque[i] = 0;
    }
    queue[iq++] = s;
    visit[s] = true;
    i = 0;
    while (i != iq)
    {
        top = queue[i];
        visit[top] = false;
        outque[top]++;
        if (outque[top] > n + 1)return false;
        k = head[top];
        while (k >= 0)
        {
            if (dist[edge[k].to] > edge[k].w + dist[top])
            {
                dist[edge[k].to] = dist[top] + edge[k].w;
                if (!visit[edge[k].to])
                {
                    visit[edge[k].to] = true;
                    queue[iq] = edge[k].to;
                    iq++;
                }
            }
            k = edge[k].next;
        }
        i++;
    }
    return true;
}
void init()
{
    memset(visit, 0, sizeof(visit));
    memset(dist, 10000, sizeof(dist));
    dist[n] = 0;
    memset(head, -1, sizeof(head));
}
void add(int a, int b, int w)
{
    edge[cnt].to = b;
    edge[cnt].w = w;
    edge[cnt].next = head[a];
    head[a] = cnt++;
}
void read()
{
    int a, b, w;
    char ch[5];
    init();
    cnt = 1;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> ch >> w;
        if (ch[0] == 'g')
            add(a + b, a - 1, -w - 1);
        else
            add(a - 1, a + b, w - 1);
    }
    for (int i = 1; i <= n; i++)
    {
        add(n, i, 0);
    }
}
int main()
{
    while (scanf("%d", &n) != EOF && n != 0)
    {
        n++;
        scanf("%d", &m);
        read();
        if (spfa())
            cout << "lamentable kingdom\n";
        else
            cout << "successful conspiracy\n";

    }
}
