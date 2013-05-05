#include <iostream>
#include <cstring>
#include <cmath>
#include <climits>
#include <algorithm>
#include <cstdio>
using namespace std;
#define typec int                     // type of cost
const typec inf = 0x3f3f3f3f;       // max of cost
#define E 1000010
#define N 1000010
struct  edge
{
    int  x, y, nxt;
    typec c;
} bf[E];
int  ne, head[N], cur[N], ps[N], dep[N];
void addedge(int  x, int  y, typec c)
{
    // add an arc(x -> y, c); vertex: 0 ~ n-1;
    bf[ne].x = x;
    bf[ne].y = y;
    bf[ne].c = c;
    bf[ne].nxt = head[x];
    head[x] = ne++;
    bf[ne].x = y;
    bf[ne].y = x;
    bf[ne].c = 0;
    bf[ne].nxt = head[y];
    head[y] = ne++;
}
typec dinic( int  n, int  s, int  t)
{
    typec tr, res = 0;
    int  i, j, k, f, r, top;
    while (1)
    {
        memset(dep, -1, n * sizeof ( int ));
        for  (f = dep[ps[0] = s] = 0, r = 1; f != r; )
            for  (i = ps[f++], j = head[i]; j; j = bf[j].nxt)
            {
                if (bf[j].c && -1 == dep[k = bf[j].y])
                {
                    dep[k] = dep[i] + 1;
                    ps[r++] = k;
                    if (k == t)
                    {
                        f = r;
                        break;
                    }
                }
            }
        if (-1 == dep[t])  break;

        memcpy(cur, head, n * sizeof ( int ));
        for  (i = s, top = 0; ; )
        {
            if (i == t)
            {
                for  (k = 0, tr = inf; k < top; ++k)
                    if (bf[ps[k]].c < tr)
                        tr = bf[ps[f = k]].c;
                for  (k = 0; k < top; ++k)
                    bf[ps[k]].c -= tr, bf[ps[k]^1].c += tr;
                res += tr;
                i = bf[ps[top = f]].x;
            }
            for  (j=cur[i]; cur[i]; j = cur[i] = bf[cur[i]].nxt)
                if (bf[j].c && dep[i]+1 == dep[bf[j].y]) break;
            if (cur[i])
            {
                ps[top++] = cur[i];
                i = bf[cur[i]].y;
            }
            else
            {
                if (0 == top) break;
                dep[i] = -1;
                i = bf[ps[--top]].x;
            }
        }
    }
    return  res;
}
int main()
{
    int i,a,b,c,n,m,s,t,cases;
    char ch[10];
    scanf("%d",&cases);
    while(cases--)
    {
        ne=2;
        memset(head,0,sizeof(head));
        scanf("%s%d",ch,&n);
        scanf("%d%d%d%d",&n,&m,&s,&t);
        //s++;t++;
        for(i=0;i<m;i++)
        {
            scanf("%d%d%d",&a,&b,&c);
            //a++;b++;
            addedge(a,b,c);
        }
        printf("%d\n",dinic(n,s,t));
    }
}