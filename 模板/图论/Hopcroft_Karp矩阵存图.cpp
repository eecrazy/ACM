// 二分图最大匹配: Hopcroft_Karp算法，复杂度: O(^nm).前向星存图
#include <iostream>
#include <queue>
using namespace std;
#define maxn 3000//最大顶点个数
#define INF　1<<28

int map[maxn][maxn];//存图
int cx[maxn],cy[maxn];//匹配到的顶点编号
int nx,ny;//a，b集合中的顶点个数
int dx[maxn],dy[maxn];//a,b集合顶点i的距离标号
bool mark[maxn];//寻找增广路时的标志数组
int dis;

bool search_pach()
{
    queue<int>Q;
    dis=INF;
    memset(dx,-1,sizeof(dx));
    memset(dy,-1,sizeof(dy));
    for (int i = 0; i < nx; ++i)
    {
        if (cx[i]==-1)
        {
            Q.push(i);dx[i]=0;
        }
    }
    while(!Q.empty())
    {
        int u=Q.front();Q.pop();
        if(dx[u]>dis)break;
        for (int v = 0; v < ny; ++v)
        {
            if (map[u][v]&&dy[v]==-1)
            {
                dy[v]=dx[u]+1;
                if (cy[v]==-1)
                {
                    dis=dy[v];
                }
                else
                {
                    dx[cy[v]]=dy[v]+1;
                    Q.push(cy[v]);
                }
            }
        }
    }
    return dis!=INF;
}
int find_path(int u)
{
    for (int v = 0; v < ny; ++v)
    {
        if (!mark[v]&&map[u][v]&&dy[v]==dx[u]+1)
        {
            mark[v]=1;
            if (cy[v]!=-1&&dy[v]==dis)
            continue;
            if(cy[v]==-1||find_path(cy[v]))
            {
                cy[v]=u;cx[u]=v;
                return 1;
            }
        }
    }
    return 0;
}

int maxmatch()
{
    int ans=0;
    memset(cx,-1,sizeof(cx));
    memset(cy,-1,sizeof(cy));
    while(search_pach())
    {
        memset(mark,0,sizeof(maek));
        for (int i = 0; i < nx; ++i)
        {
            if (cx[i]==-1)
            {
                ans+=find_path(i);
            }
        }
    }
    return ans;
}
int main()
{

}