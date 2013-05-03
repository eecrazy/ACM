#include <queue>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
#define MAXN 1011
#define MAXM 500000
#define inf 999999999   //表示无穷大
int n, m, S, T, K;
int dist[MAXN];
struct Edge
{
    int to;
    int w;
    int next;
    Edge(int to, int w, int next):to(to),w(w),next(next) {}
    Edge() {}
    inline bool operator < (const Edge &b) const
    {
        return w + dist[to] > b.w + dist[b.to]; //这里是对估价函数的使用，使得路径最短的先出队
    }
};
Edge e[MAXM], ee[MAXM];
int pn1[MAXM], pn2[MAXM];
int cnt1, cnt2;
int getint()                 //这个getchar的输入对大数据量输入非常有用，甚至可以挽救效率不高的算法
{
    int ret=0;
    char tmp;
    while(!isdigit(tmp=getchar()));
    do
    {
        ret=(ret<<3)+(ret<<1)+tmp-'0';
    }
    while(isdigit(tmp=getchar()));
    return ret;
}
void addedge(Edge *e, int *pn, int &cnt, int from, int to, int w)
{
    e[cnt].to = to;
    e[cnt].w = w;
    e[cnt].next = pn[from];
    pn[from] = cnt++;
}
void Dijkstra(int v)
{
    int i, u, x;
    bool s[MAXN];    //最短路径顶点集
    memset(s,false,sizeof(s));
    for (i = 1; i <= n; i++)        //初始化
        dist[i] = inf;
    priority_queue<Edge> heap;
    dist[v] = 0;        //把顶点v加入最短路径顶点集

    heap.push(Edge(v,0,-1));
    while (!heap.empty())
    {
        u = heap.top().to;
        heap.pop();
        if (s[u])
            continue;
        s[u] = 1;
        for (i = pn2[u]; i != -1; i = ee[i].next)
        {
            x = ee[i].to;
            if (!s[x] && dist[u] + ee[i].w < dist[x])
            {
                dist[x] =  dist[u] + ee[i].w;
                heap.push(Edge(x,dist[x],-1));
            }
        }
    }
}
int Astar()          //A*搜索
{
    int u, i, len, c[MAXN], temp;
    if(dist[S] == inf)
        return -1;
    priority_queue<Edge> heap;  //用优先级队列实现Open表
    memset(c,0,sizeof(c));
    heap.push(Edge(S,0,-1));
    while(!heap.empty())
    {
        u = heap.top().to;  //从Open表中取得一个节点X
        len = heap.top().w;
        heap.pop();   //并从Open表中删除。
        c[u]++;
        if(c[T] == K)  //第K次到达目标节点
            return len;
        if(c[u] > K)
            continue;
        for (i = pn1[u]; i != -1; i = e[i].next)  //每个X的子节点Y
        {
            temp = e[i].to;
            heap.push(Edge(temp,len + e[i].w,-1));   //更新Open表
        }
    }
    return -1;
}
int main()
{
    int u, v, w;
//   freopen("in.txt","r",stdin);

    n = getint();
    m = getint();
//scanf("%d %d",&n,&m);
    memset(pn1,0xff,sizeof(pn1));
    memset(pn2,0xff,sizeof(pn2));
    cnt1 = cnt2 = 1;
    while (m--)
    {
        u=getint();
        v=getint();
        w=getint();
//  scanf("%d %d %d",&u,&v,&w);
        addedge(e,pn1,cnt1,u,v,w);   //构造正向图
        addedge(ee,pn2,cnt2,v,u,w);  //构造反向图
    }
// scanf("%d %d %d",&S,&T,&K);
    S=getint();
    T=getint();
    K=getint();
    if (S == T)
        K++;
    Dijkstra(T);
    printf("%d\n",Astar());

    system("pause");
//   fclose(stdin);//关闭文件
    return 0;
}
