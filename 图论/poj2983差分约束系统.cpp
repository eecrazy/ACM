/*
排位赛的E题，纠结了好久，做的时候猜到就是用差分约束来做。
对于每个防御点作为一个点，
（1）由P条件可以知, a - b = c(随便假设个方向)，化成不等式组得{a - b >= c &&  a - b <= c} ，在移向得{b - a <= -c && a - b <= c} （建边a ->b, len = -c & b->a, len=c）
（2）由V条件可知，a - b >= 1 即 b - a <= -1 (建边 a -> b, 长度为-1)
根据以上构图，注意，如果用SPFA做的话，必须加一个超级源点，令它到每个点距离<=0就好，然后该怎么做就怎么做，存在负环表示无解，否则存在正解。
如果不加源点的话可以用Bellman_ford()做，否则有些不在统一图上的点是搜不到的
对于差分约束系统的一个资料参考：
1)         建图后求最短路（对应 <= 的差分约束）
从求最短路后分析开始。求最短路后一定有：d(u) + w(u,v) >= d(v) 转换为：d(v) – d(u) <= w(u,v)。然后这个式子与我们差分约束条件得到的不等式（ X(a) - X(b) <= c ）相似。
所以得到建图的规则为：一条b到a的边权值为c。
建图后求最短路即为一组解。
2)         建图后求最长路（对应 >= 的差分约束）
同上。求最长路后一定得到：d(u) + w(u,v) <= d(v) 转换为：d(v)-d(u)>=w(u,v)。然后对比差分约束条件的不等式（ X(a) - X(b) >= c ）。
所以得到建图的规则为：一条b到a的边权值为c。
建图后求最长路即为一组解。
*/

#include <iostream>
#include <cstdio>
#include <string.h>
using namespace std;
#define MAX 99999999
const int maxn=8010;
const int maxm=2000000;
int head[maxn];
int dist[maxn];
bool visit[maxn];
int s,n,m,cnt;
struct node
{
    int to;
    int w;
    int next;
};
node edge[maxm];
bool spfa()
{
    s=n;
    int i,k,iq=0,top;
    int queue[maxn];
    int outque[maxn];
    for(i=0; i<=n; i++)
    {
        outque[i]=0;
    }
    queue[iq++]=s;
    visit[s]=true;
    i=0;
    while(i!=iq)
    {
        top=queue[i];
        visit[top]=false;
        outque[top]++;
        if(outque[top]>n+1)return false;
        k=head[top];
        while(k>=0)
        {
            if(dist[edge[k].to]>edge[k].w+dist[top])
            {
                dist[edge[k].to]=dist[top]+edge[k].w;
                if(!visit[edge[k].to])
                {
                    visit[edge[k].to]=true;
                    queue[iq]=edge[k].to;
                    iq++;
                }
            }
            k=edge[k].next;
        }
        i++;
    }
    return true;
}
void init()
{
    memset(visit,0,sizeof(visit));
    memset(dist,10000,sizeof(dist));
    dist[n]=0;
    memset(head,-1,sizeof(head));
}
void add(int a,int b,int w)
{
    edge[cnt].to=b;
    edge[cnt].w=w;
    edge[cnt].next=head[a];
    head[a]=cnt++;
}
void read()
{
    int a,b,w;
    char ch;
    init();
    cnt=1;
    for(int i=0; i<m; i++)
    {
        getchar();
        cin>>ch;
        if(ch=='P')
        {
            cin>>a>>b>>w;
            add(a,b,-w);
            add(b,a,w);
        }
        else
        {
            cin>>a>>b;
            add(a,b,-1);
        }
    }
    for(int i=0; i<=n; i++)
    {
        add(n,i,0);
    }
}
int main()
{
    while(scanf("%d",&n)!=EOF&&n!=0)
    {
        n++;
        scanf("%d",&m);
        read();
        if(spfa())
            cout<<"Reliable\n";
        else
            cout<<"Unreliable\n";

    }
}
