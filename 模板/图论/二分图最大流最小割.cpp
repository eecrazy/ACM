//二分图网络最大流最小割
// PKU  2125 Destroying  The Graph
// 二分图最小点权覆盖集，求割集
// 1.设置一个集合A, 最开始A={s},按如下方法不断扩张A:
// 2.若存在一条边(u,v), 其流量小于容量，且u属于A,则v加入A
// 3.若存在(v,u), 其流量大于0，且u属于A,则v加入A
// 4.A计算完毕，设B=V-A，最小割集E={(u,v)  | u∈A,v∈B}
// Character '+' means that Bob removes all arcs incoming into the specified vertex
//and '-' that Bob removes  all arcs outgoing from  the specified vertex.
#include <cstdio>
#include <string>
#include <memory>
#include <queue>
using namespace std;
bool S[MAX];

void dfs(int pos)
{
    int i;
    S[pos] =  1;
    for (i = 1; i <= m; i++)
    {
        if (!S[i]  && net[pos][i]) dfs(i);
    }
}
struct node
{
    int num;
    char sign;
} cs[MAX];
void find_cut()
{
    int i, ps = 0;
    memset(S,  0, sizeof(S));
    dfs(1);
    for (i = 2; i <= n + 1; i++)
    {
        if (!S[i] && net[1][i] ==  0)
        {
            //printf("%d -\n", i-1);
            cs[ps].num = i - 1;
            cs[ps].sign = '-';
            ps ++;
        }
    }
    for (i = n + 2; i <= 2 * n + 1; i++)
    {
        if (S[i] && net[i][m]  == 0)
        {
            //printf("%d  +\n",  i-n-1);
            cs[ps].num = i - n - 1;
            cs[ps].sign = '+';
            ps ++;
        }
    }
    printf("%d\n", ps);
    for (i = 0; i < ps; i++) printf("%d  %c\n", cs[i].num, cs[i].sign);
    //puts("------");
    //for(i=1;i<=m;i++)  if(S[i]) printf("%d  ",i);
    //puts("\n------");
}
int win[MAX], wout[MAX];
int main()
{
    int i, j;
    while (scanf("%d  %d",  &n, &m) == 2)
    {
        memset(net,  0, sizeof(net));
        for (i = 2; i <= n + 1; i++) scanf("%d", win + i);
        for (i = 2; i <= n + 1; i++) scanf("%d", wout + i);
        while (m --)
        {
            int x, y;
            scanf("%d  %d",  &x, &y);
            x ++;
            y += n + 1;
            net[x][y] = INT_MAX;
        }
        for (i = 2; i <= n + 1; i++)
        {
            net[1][i] = wout[i];
        }
        for (i = n + 2; i <= 2 * n + 1; i++)
        {
            net[i][2 * n + 2]  = win[i - n];
        }
        m = 2 * n +  2;
        printf("%d\n",  Edmonds_Karp());
        find_cut();
    }
}
