// 最小路径覆盖，以任务为顶点建图。
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int M = 505;
int s[M],e[M];
bool g[M][M];
int un, vn;
int xm[M], ym[M];
bool check[M];
bool search(int u)
{
    int v;
    for (v = 0; v < vn; v++)
        if (g[u][v] && !check[v])
        {
            check[v] = true;
            if (ym[v] == -1 || search(ym[v]))
            {
                ym[v] = u; xm[u] = v;
                return true;
            }
        }
    return false;
}
int match()
{
    int u, ret = 0;
    memset(xm, -1, sizeof(xm));
    memset(ym, -1, sizeof(ym));
    for (u = 0; u < un; u++)
        if (xm[u] == -1)
        {
            memset(check, false, sizeof(check));
            if (search(u)) ret++;
        }
    return ret;
}

int main()
{
    int t, m, i,j,a,b,v;
    cin >> t;
    char ss[3];
    while (t--)
    {
        cin >> m;
        for (i = 0; i < m; i++)
        {
            scanf("%s",ss);
            if(ss[0]=='T')
                v=10;
            if(ss[0]=='J')
                v=11;
            if(ss[0]=='Q')
                v=12;
            if(ss[0]=='K')
                v=13;
            if(ss[0]=='A')
                v=14;
            if(ss[0]>='1'&&ss[0]<='9')
                v=ss[0]-'0';
               v*=100;
            if(ss[1]=='H')
                v+=4;
            if(ss[1]=='S')
                v+=3;
            if(ss[1]=='D')
                v+=2;
            if(ss[1]=='C')
                v+=1;
               s[i]=v;
        }
        for (i = 0; i < m; i++)
        {
            scanf("%s",ss);
            if(ss[0]=='T')
                v=10;
            if(ss[0]=='J')
                v=11;
            if(ss[0]=='Q')
                v=12;
            if(ss[0]=='K')
                v=13;
            if(ss[0]=='A')
                v=14;
            if(ss[0]>='1'&&ss[0]<='9')
                v=ss[0]-'0';
                v*=100;
            if(ss[1]=='H')
                v+=4;
            if(ss[1]=='S')
                v+=3;
            if(ss[1]=='D')
                v+=2;
            if(ss[1]=='C')
                v+=1;
                e[i]=v;
        }
        memset(g, false, sizeof(g));
        vn = un = m;
        for(i=0;i<m;i++)
            for(j=0;j<m;j++)
            {
                if(e[i]>s[j])
                   {
                       g[i][j]=true;
                   }
            }
        cout << match() << endl;
    }
    return 0;
}
