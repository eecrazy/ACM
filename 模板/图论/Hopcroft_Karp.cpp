// 二分图最大匹配: Hopcroft_Karp算法，复杂度: O(n^2.5).前向星存图
// 用BFS找多条增广路，用distx, disty来记录下一个点，用DFS来遍历这些增广路.
#include <iostream>
using namespace std;
const int maxn=201;
const int maxm=40005;
const int INF=INT_MAX/2;
struct EDGE
{
    int b;
    int next;
};
int nx, ny, m;
EDGE edge[maxm];
int edge_num;
int first[maxn];
int cx[maxn],cy[maxn];// cx[i]表示xi对应的匹配，cy[i]表示yi对应的匹配.
int distx[maxn],disty[maxn]; // 层的概念，即在BFS中的第几层.
int que[maxn];
int ans;
inline void Init()
{
    fill(cx,cx+maxn,-1);
    fill(cy,cy+maxn,-1);
    fill(first,first+maxn,-1);
    edge_num=0;
    ans=0;
}
inline void AddEdge(int a, int b)
{
    edge[edge_num].b=b;
    edge[edge_num].next=first[a],first[a]=edge_num++;
}
inline bool BFS()
{
    int i,j,k;
    bool flag(0);
    int h,t;
    memset(distx,0,sizeof(distx));
    memset(disty,0,sizeof(disty));
    h=t=0;
    for(i=1;i<=nx;++i)
        if(cx[i]==-1)que[t++]=i;
    for(;h!=t;++h)
    {
        i=que[h];
        for(k=first[i];k!=-1;k=edge[k].next)
        {
            j=edge[k].b;
            if(!disty[j])
            {
                disty[j]=distx[i]+1;
                if(cy[j]==-1)flag=1;
                else distx[cy[j]]=disty[j]+1,que[t++]=cy[j];
            }
        }
    }
    return flag;
}
bool DFS(int i)
{
    int j,k;
    for (k=first[i];k!=-1;k=edge[k].next)
    {
        j=edge[k].b;
        if(disty[j]==distx[i]+1)
        { // 说明j是i的后继结点.
            disty[j]=0; // j被用过了，不能再作为其他点的后继结点了.
            if(cy[j]==-1||DFS(cy[j]))
            {
                cx[i]=j,cy[j]=i;
                return 1;
            }
        }
    }
    return 0;
}
inline void Hopcroft_Karp()
{
    int i,j;
    while(BFS())
        for(i=1;i<=nx;++i)
            if(cx[i]==-1 && DFS(i))++ans;
}
int main(void)
{
//    freopen("Input.txt", "r", stdin);
    int i, j;
    int a, b;
    while (scanf("%d%d",&nx,&ny)!=EOF)
    {
        Init();
        for(i=1;i<=nx;++i)
        {
            scanf("%d",&a);
            for(b=0;b<a;++b)scanf("%d",&j),AddEdge(i, j);
        }
        Hopcroft_Karp();
        printf("%d/n", ans);
    }
    return 0;
}