#include <iostream>
#include <cstdio>
using namespace std;
using namespace std; 
const int nMax = 105000; 
const int mMax = 10000500; 
const int inf = 1 << 28; 
struct node
{ 
    int v, next; 
    int  w; 
} edge[mMax];//下标从1开始 
int n, k, head[nMax]; 
int dis[nMax];//dis[i]表示在[1,i]这个区间所要选择的元素的最少个数 
int stack[nMax], m, sum[nMax]; 
bool vis[nMax]; 
 
void addedge(int a, int b, int w) 
{ 
    edge[k].w = w; 
    edge[k].v = b; 
    edge[k].next = head[a]; 
    head[a] = k; 
    k++; 
} 
//dis[t] -dist[s-1] >= c,也就是dist[t] >= dist[s-1] + c,这是求最长路的形式,所以要求最长路 
bool spfa(int s) 
{ 
    int i, top = 0; 
    memset(vis, 0, sizeof(vis)); 
    for(i = 0; i <= n; i++)dis[i] = -inf;//求最长路,所以要置为负无穷 
    dis[s] = 0; 
    stack[++top] = s; 
    vis[s] = true; 
    while(top) 
    { 
        int u = stack[top--]; 
        for(i = head[u]; i != 0; i = edge[i].next) 
        { 
            int v = edge[i].v; 
            if(dis[v] < dis[u] + edge[i].w)//求最长路 
            { 
                dis[v] = dis[u] + edge[i].w; 
                if(!vis[v]) 
                { 
                    vis[v] = true; 
                    stack[++top] = v; 
                    if(++sum[v] > n)return 0;//note 
                } 
            } 
        } 
        vis[u] = false;//访问完u的所有邻接顶点之后取消u的标记 
    } 
    return 1; 
} 
 
int main() 
{ 
    int m, s, t, c, i, j; 
    while(scanf("%d", &m) != EOF) 
    { 
        k = 1;//边的数目 
        n = -1;//区间端点最大值 
        memset(sum, 0, sizeof(sum));//每个顶点的入栈次数 
        memset(head, 0, sizeof(head)); 
        while(m--) 
        { 
            scanf("%d%d%d", &s, &t, &c); 
            n = max(n, t); 
            addedge(s - 1, t, c); 
        } 
        s = n + 2; 
        for(i = 0; i <= n; i++)//隐含的约束条件0<= dist[i] - dist[i-1] <= 1 
        { 
            addedge(i + 1, i, -1);//note 
            addedge(i, i + 1, 0); 
        } 
        for(i = 0; i <= n; i++) 
        { 
            addedge(s, i, 0); 
        } 
        spfa(s); 
        cout << dis[n] << endl; 
    } 
    return 0; 
} 
 
// 差分约束问题转化为最短路问题.
// 这道题求最长路是因为题目给出的是>=的关系,如果用dis[i]表示区间[1,i]被选择的最少元素个数,
// 那么区间[s,t]最少被选择c个元素可以表示为dis[t] - dis[s-1] >= c
// 增加一个附加汇点,向所有区间端点连接一条边,那么求出源点到所有顶点的最长距离,
// 那么对所有顶点之间的边,
// 都会有dis[v] >= dis[u] + w,这正是我们想要的形式.
// 至于隐含的约束条件,似乎比较不容易想到,增加这些边的必要性是什么呢?
// 差分约束的题目，题意是每个区间限制最少个数，在满足这些限制的前提下，找出符合的最少的个数。
// 用一个数组dist【i】来存小于等于i的数中留下的个数，这样就可以得出他们之间的关系dist【b】-dist【a-1】>=c，
// （[a，b]是区间，c是区间最少数），另外0<=dist【i】-dist【i-1】<=1，这样通过约束关系就可以得出约束图，
// 构造不等式时>=表示求最小值作为最长路，<=表示求最大值最为最短路，当然松弛技术中也就相应的改了，
// 此题中我们用>=，然后通过用bellman-ford来求解，当然用SPFA的形式来求解，不然的话会超时。


// 题意：在区间[1,50000]范围内，给定你一些区间以及区间内整数点的个数，问在[1,50000]区间内最小整数点的个数
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

#define maxN 50010
#define MAX 0x0fffff
int num;
int dis[maxN],vist[maxN],head[maxN];
struct point{
    int v,w,next;
}po[maxN*20];

void add(int u,int v,int w){
    po[num].v=v,po[num].w=w;
    po[num].next=head[u],head[u]=num++;
}
int spfa(int st,int en)
{
    int he=0,tail=0,qu[maxN*10];
    for(int i=st;i<=en;i++)
        dis[i]=-MAX;
    dis[st]=0;
    vist[st]=1;
    qu[tail++]=st;
    while(he<tail){
        int u=qu[he++];
        vist[u]=0;
        for(int i=head[u];i!=-1;i=po[i].next)
        {
            int v=po[i].v;
            if(dis[v]<dis[u]+po[i].w){
                dis[v]=dis[u]+po[i].w;
                if(!vist[v]){
                    vist[v]=1;
                    qu[tail++]=v;
                }
            }
        }
    }
    return dis[en];
}

int main()
{
    int u,v,w,n,st=maxN,en=0;
    memset(head,-1,sizeof(head));
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d%d%d",&u,&v,&w);
        add(u,v+1,w);
        st=min(st,u);
        en=max(en,v+1);
    }
    for(int i=st;i<=en;i++){
        add(i,i+1,0);
        add(i+1,i,-1);
    }
    printf("%d\n",spfa(st,en));
}
