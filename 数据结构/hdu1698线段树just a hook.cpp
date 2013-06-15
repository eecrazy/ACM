//好强的代码！！！
#include <stdio.h>
const int n = 1000005;
int map[n][3];
int main()
{
    int i,M,z,N,sum,v;
    scanf("%d",&N);
    for(i=1; i<=N; i++)
    {
        sum = 0;
        int Q,j;
        scanf("%d%d",&M,&Q);
        for(j=1; j<=Q; j++)
            scanf("%d%d%d",&map[j][0],&map[j][1],&map[j][2]);
        for(j=1; j<=M; j++)
        {
            v = 1;
            for(int k=Q; k>=1; k--)//从末尾开始 即从更新的最后一次算起
                if(map[k][0]<=j && j<=map[k][1])
                {
                    v = map[k][2];
                    break;//覆盖便弹出
                }
                sum += v;
        }
        printf("Case %d: The total value of the hook is %d.\n",i,sum);
    }
}
//+++++++++++++++++++++++++++下面是线段树版本
#include <cstdio>
#include <iostream>
using namespace std;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1

#define maxn 100000
int col[maxn<<2];
int sum[maxn<<2];
void pushup(int rt)
{
    sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void pushdown(int rt,int m)
{
    if(col[rt])
    {
        col[rt<<1]=col[rt<<1|1]=col[rt];
        sum[rt<<1]=(m-(m>>1))*col[rt];
        sum[rt<<1|1]=(m>>1)*col[rt];
        col[rt]=0;
    }
}
void build(int l,int r,int rt)
{
    col[rt]=0;
    sum[rt]=1;
    if(l==r)return ;
    int m=(l+r)>>1;
    build(lson);
    build(rson);
    pushup(rt);
}
void update(int L,int R,int c,int l,int r,int rt)
{
    if(L<=l&&r<=R)
    {
        col[rt]=c;
        sum[rt]=c*(r-l+1);
        return ;
    }
    pushdown(rt,r-l+1);
    int m=(l+r)>>1;
    if(L<=m)update(L,R,c,lson);
    if(R>m)update(L,R,c,rson);
    pushup(rt);
}
int main()
{
    int t;
    int n,m;
    scanf("%d",&t);
    for(int cas=1;cas<=t;cas++)
    {
        scanf("%d%d",&n,&m);
        build(1,n,1);
        while(m--)
        {
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            update(a,b,c,1,n,1);
        }
        printf("Case %d: The total value of the hook is %d.\n",cas,sum[1]);
    }
    return 0;
}
