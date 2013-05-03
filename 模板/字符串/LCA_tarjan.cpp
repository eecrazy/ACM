//POJ 3417
//offline O(na(n))
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef __int64 bigint;
const int MAX =  100010;
int n,m;
const int ENDFLAG  = 0;
struct EDGELIST
{
    int start[MAX];
    int last[MAX];
    int edge[MAX<<1][2];//pos,listnext
    int tot;
    void clear()
    {
        tot = ENDFLAG  +1;
        memset(last,ENDFLAG,sizeof(last));
        memset(start,ENDFLAG,sizeof(start));
    }
    void push_back(int s,int t)
    {
        edge[tot][0] = t;
        edge[tot][1] = ENDFLAG;
        if (last[s] != ENDFLAG)
        {
            edge[ last[s] ][1] = tot;
        }
        else
        {
            start[s] = tot;
        }
        last[s] = tot;
        tot ++;
        //swap
        if (s == t) return;
        edge[tot][0] = s;
        edge[tot][1] = ENDFLAG;
        if (last[t] != ENDFLAG)
        {
            edge[ last[t] ][1] = tot;
        }
        else
        {
            start[t] = tot;
        }
        last[t] = tot;
        tot ++;
    }
} tree,newed;
int cov[MAX];
bool vis[MAX];
bigint cnt[2];
int father[MAX];
int ancestor[MAX];
int find_set(int x)
{
    if (father[x] == x) return x;
    return father[x] = find_set(father[x]);
}
void union_set(int x,int y)
{
    father[ find_set(y) ] = x;
}
void tarjan(int pos,int pre)
{
    int i,j;
    father[pos]  = pos;
    ancestor[pos] = pos;
    for (i=tree.start[pos]; i != ENDFLAG  ; i=tree.edge[i][1])
    {
        int next = tree.edge[i][0];
        if (next == pre) continue;
        tarjan(next,pos);
        union_set(pos,next);
        cov[pos]  += cov[next];
    }
    vis[pos] = true;
    for (j=newed.start[pos]; j != ENDFLAG  ; j=newed.edge[j][1])
    {
        int next = newed.edge[j][0];
        if (vis[next]) cov[ ancestor[ find_set(next) ] ] -= 2;
    }
    if (cov[pos] <=  1) cnt[ cov[pos] ] ++;
}
int get_val()
{
    int ret = 0;
    char ch;
    while ((ch=getchar()) > '9' || ch < '0') ;
    do
    {
        ret = ret*10 + ch - '0';
    }
    while ((ch=getchar()) <= '9' && ch >= '0') ;
    return ret;
}
int main()
{
    int i,j,a,b,rt;
    n = get_val();
    m = get_val();
    if (n ==  1)
    {
        puts("0");
        return  0;
    }
    tree.tot = newed.tot = ENDFLAG  +1;
    for (i=0; i<n-1; i++)
    {
        a = get_val();
        b = get_val();
        tree.push_back(a,b);
        rt = a;
    }
    for (i=0; i<m; i++)
    {
        a = get_val();
        b = get_val();
        newed.push_back(a,b);
        cov[a] ++;
        cov[b]  ++;
    }
    tarjan(rt,rt);
    cnt[0] --;
    printf("%I64d\n",cnt[0]*m  + cnt[1]);
}
