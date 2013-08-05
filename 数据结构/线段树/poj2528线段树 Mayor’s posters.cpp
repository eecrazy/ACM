#include <iostream>
#include <cstdio>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAXN = 20005 ;
struct NODE
{
    int l, r, c//c表示第几个矩形;
} tree[MAXN * 4];
struct L
{
    int li, num;
    bool operator < ( const L &r ) const
    {
        return li < r.li;
    };
};
L line[MAXN];
int post[MAXN][2];
bool vis[MAXN];
int cnt;
void make_tree ( int v, int l, int r )
{
    int mid = (l + r) >> 1;
    tree[v].c = 0, tree[v].l = l, tree[v].r = r;
    if ( l != r )
    {
        make_tree( v << 1, l, mid );
        make_tree( (v << 1) + 1, mid + 1, r );
    }
}
void update ( int v, int l, int r, int c )
{
    int mid;
    if ( tree[v].l == l && tree[v].r == r )
    {
        tree[v].c = c;
        return;
    }
    if ( tree[v].c > 0 && tree[v].c != c )//pushdown()
    {
        tree[v << 1].c = tree[v].c;
        tree[(v << 1) + 1].c = tree[v].c;
        tree[v].c = 0;
    }
    mid = (tree[v].l + tree[v].r) >> 1;
    //分三种情况更新
    if ( r <= mid )  update( v << 1, l, r, c );
    else if ( l > mid ) update( (v << 1) + 1, l, r, c );
    else
    {
        update( v << 1, l, mid, c );
        update( (v << 1) + 1, mid + 1, r, c );
    }
}

void sum ( int v )
{
    if ( tree[v].c )
    {
        if ( !vis[tree[v].c] )
        {
            vis[tree[v].c] = true;
            cnt++;
        }
        return;
    }
    sum( v << 1 );
    sum( (v << 1) + 1 );
}

int main ( )
{
    int n, N, i;
    scanf("%d", &N);
    while ( N-- )
    {
        cnt = 0;
        scanf("%d", &n);
        memset( vis, false, sizeof(vis) );
        //记录端点
        for ( i = 0 ; i < n ; i++ )
        {
            scanf("%d%d", &post[i][0], &post[i][1]);
            line[i << 1].li = post[i][0];
            line[i << 1].num = -(i + 1);     //负数表示起点
            line[(i << 1) + 1].li = post[i][1];
            line[(i << 1) + 1].num = i + 1;  //正数表示终点
        }
        //离散化坐标
        sort( line, line + n * 2 );
        int tp = 1, temp = line[0].li;
        for ( i = 0; i < 2 * n; i++ )
        {
            if ( line[i].li != temp )
            {
                tp++;
                temp = line[i].li;
            }
            if ( line[i].num < 0 ) post[-line[i].num - 1][0] = tp; //表示起点
            else  post[line[i].num - 1][1] = tp; //表示终点
        }
        //计算离散化之后不同点的个数，存在tp中
        make_tree( 1, 1, tp );
        for ( i = 0 ; i < n ; i++ )
            update( 1, post[i][0], post[i][1], i + 1 );
        sum(1);
        printf("%d\n", cnt);
    }
}


// 另一个线段树版本
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1

const int maxn = 11111;
bool hash[maxn];
int li[maxn] , ri[maxn];
int X[maxn * 3];
int col[maxn << 4];
int cnt;

void PushDown(int rt)
{
    if (col[rt] != -1)//被染色了
    {
        col[rt << 1] = col[rt << 1 | 1] = col[rt];
        col[rt] = -1;
    }
}
void update(int L, int R, int c, int l, int r, int rt)
{
    if (L <= l && r <= R)
    {
        col[rt] = c;
        return ;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if (L <= m) update(L , R , c , lson);
    if (m < R) update(L , R , c , rson);
}
void query(int l, int r, int rt)
{
    if (col[rt] != -1)
    {
        if (!hash[col[rt]]) cnt ++;
        hash[ col[rt] ] = true;
        return ;
    }
    if (l == r) return ;
    int m = (l + r) >> 1;
    query(lson);
    query(rson);
}
int Bin(int key, int n, int X[])//二分实现离散化，查找key数组下标
{
    int l = 0 , r = n - 1;
    while (l <= r)
    {
        int m = (l + r) >> 1;
        if (X[m] == key) return m;
        if (X[m] < key) l = m + 1;
        else r = m - 1;
    }
    return -1;
}
int main()
{
    int T , n;
    scanf("%d", &T);
    while (T --)
    {
        scanf("%d", &n);
        int nn = 0;
        for (int i = 0 ; i < n ; i ++)
        {
            scanf("%d%d", &li[i] , &ri[i]);
            X[nn++] = li[i];
            X[nn++] = ri[i];
        }
        sort(X , X + nn);
        int m = 1;
        for (int i = 1 ; i < nn; i ++)
        {
            if (X[i] != X[i - 1]) X[m ++] = X[i];
        }
        for (int i = m - 1 ; i > 0 ; i --)
        {
            if (X[i] != X[i - 1] + 1) X[m ++] = X[i - 1] + 1;
        }
        sort(X , X + m);
        memset(col , -1 , sizeof(col));
        for (int i = 0 ; i < n ; i ++)
        {
            int l = Bin(li[i] , m , X);
            int r = Bin(ri[i] , m , X);
            update(l , r , i , 0 , m , 1);
        }
        cnt = 0;
        memset(hash , false , sizeof(hash));//hash就是visit
        query(0 , m , 1);
        printf("%d\n", cnt);
    }
    return 0;
}
