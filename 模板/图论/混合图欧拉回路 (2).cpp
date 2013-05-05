// 1637 PKU
#include <cstdio>
#include <string>
#include <memory>
#include <queue>
using namespace std;
bool solve()
{
    int i, j;
    for (i=2; i<n; i++)
    {
        x[i] = indeg[i] - outdeg[i];
        if (x[i] %  2)return false;
        if (x[i] >  0)net[i][m]  += x[i]  >>  1;
        else if (x[i]  < 0)net[1][i]  +=  (-x[i]) >>  1;
    }
    int cap =  0;
    for (i=2; i<n; i++)cap += net[1][i];
    int flow = Edmonds_Karp();
    // when flow==cap,  say it exist euler circuit
    // print the undirected edge's direction
    /*for (i=2;  i<m;  i++)
      for (j=2;  j<m;  j++)
        if (net[i][j] !=  0)
          printf("%d -> %d\n",  i-1,j-1);*/
    return (flow == cap);
}
int main()
{
    int i, j, cas;
    scanf("%d", &cas);
    while (cas --)
    {
        memset(indeg,  0, sizeof(indeg));
        memset(outdeg,  0, sizeof(outdeg));
        memset(net,  0, sizeof(net));
        scanf("%d  %d",  &m,  &s);
        for (i=0; i<s; i++)
        {
            int x, y, d;
            scanf("%d  %d  %d",  &x, &y, &d);
            x ++;
            y ++;
            // if d=0,  make  x->y
            indeg[y] ++;
            outdeg[x]  ++;
            if (d ==  0)net[x][y] ++;
        }
        n = m + 2;
        puts(solve() ? "possible"  : "impossible");
    }
}
