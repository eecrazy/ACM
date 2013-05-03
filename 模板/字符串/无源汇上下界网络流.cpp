//无源汇上下界网络流
/*  2314  ZJU Reactor Cooling
*  无源汇上下界网络流
*  (1) 新建S，T
*  (2) D(u) = ∑B(i,u) - ∑B(u,i)
*    D(u)  > 0, 建弧(S,u)，权值为D(u)
*    D(u)  < 0, 建弧(u,T)，权值为-D(u)
*  (3) 求最大流，判定是否满流*/
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
struct NODE
{
    int x, y;
    int b, c;
    NODE (int _x = 0,int_y=0,int _b=0,int _c =0): x(_x),y(_y), b(_b), c(_c) {}};
vector <NODE> nodes;
int make_net()
{
    int i, j;
    int D[NMAX]  =  {0};
    memset(net,  0, sizeof(net));
    n +=  2;
    vector <NODE>::iterator  iter;
    foreach (iter,nodes)
    {
        i = iter->x;
        j = iter->y;
        net[i][j]  = iter->c - iter->b;
        D[j]  += iter->b;
        D[i] -= iter->b;
    }
    int ret = 0;
    for (i=2; i<n; i++)
    {
        if (D[i] >  0)net[1][i] = D[i];
        else if (D[i]  <  0)net[i][n] = - D[i];
        ret += net[1][i];
    }
    return ret;
}
void solve()
{
    int i, j;
    int cap = make_net();
    int flow = Edmonds_Karp();
    if (flow != cap)puts("NO\n");
    else
    {
        puts("YES");
        vector <NODE>::iterator  iter;
        foreach (iter,nodes)
        printf("%d\n", iter->c - net[iter->x][iter->y]);
    }
}
int main()
{
    int i, j, cas;
    scanf("%d", &cas);
    while (cas --)
    {
        scanf("%d %d",  &n, &m);
        nodes.clear();
        for (i=0; i<m; i++)
        {
            int x, y, l, cap;
            scanf("%d %d %d %d",  &x, &y, &l, &cap);
            x ++;
            y ++;
            nodes.push_back(NODE(x,y,l,cap));
        }
        solve();
    }
}
