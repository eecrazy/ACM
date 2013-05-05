//DFS找增广路，速度慢。O(nm)二分图最大匹配。
#include <iostream>
using namespace std;
#define maxn 300//顶点个数
bool map[maxn][maxn];//存图
bool mark[maxn];//寻找增广路时的标志数组
int nx,ny;//A,B集合中的点数
int cx[maxn],cy[maxn];//匹配到的顶点序号

int findpath(int u)
{
    int i,j;
    for (int i = 0; i < ny; ++i)
    {
        if (map[u][i]&&!mark[i])        
        {
            mark[i]=1;
            if (cy[i]==-1||findpath(cy[i]))
            {
                    cy[i]=u;
                    cx[u]=i;
                    return 1;
            }    
        }
    }
    return 0;
}

int maxmatch()
{
    int ans=0,i,j;
    for (int i = 0; i < nx; ++i)
        cx[i]=-1;
    for (int i = 0; i < ny; ++i)
        cy[i]=-1;
    for (int i = 0; i < nx; ++i)
    {
        if (cx[i]==-1)
        {
            for (int j = 0; j < ny; ++j)
                mark[j]=0;
            ans+=findpath(i);
        }
    }
    return ans;
}
int main()
{

}