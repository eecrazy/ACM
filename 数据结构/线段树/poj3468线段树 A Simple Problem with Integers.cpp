#include <cstdio>
#include <iostream>
using namespace std;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
#define LL long long
#define maxn 100005
LL add[maxn<<2];
LL sum[maxn<<2];
void pushup(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void pushdown(int rt,int m)
{
    if(add[rt])
    {
        add[rt<<1]+=add[rt];
        add[rt<<1|1]+=add[rt];
        sum[rt<<1]+=add[rt]*(m-(m>>1));
        sum[rt<<1|1]+=add[rt]*(m>>1);
        add[rt]=0;
    }
}
void build(int l,int r,int rt)
{
	add[rt]=0;
	if(l==r)
	{
		scanf("%lld",&sum[rt]);
		return ;
	}
	int m=(l+r)>>1;
	build(lson);
	build(rson);
	pushup(rt);
}
void update(int L,int R,int c,int l,int r,int rt)
{
	if(L<=l&&r<=R)
	{
		add[rt]+=c;
		sum[rt]+=(LL)c*(r-l+1);
		return ;
	}
	pushdown(rt,r-l+1);
	int m=(l+r)>>1;
	if(L<=m)update(L,R,c,lson);
	if(R>m)update(L,R,c,rson);
	pushup(rt);
}
LL query(int L,int R,int l,int r,int rt)
{
	if(L<=l&&r<=R)
	{
		return sum[rt];
	}
	pushdown(rt,r-l+1);
	int m=(l+r)>>1;
	LL ret=0;
	if(L<=m)ret+=query(L,R,lson);
	if(R>m)ret+=query(L,R,rson);
	return ret;
}
int main()
{
	int n,q;
	while(scanf("%d%d",&n,&q)!=EOF)
	{
		build(1,n,1);
		int a,b,c;
			char ch;
		while(q--)
		{
			scanf(" %c",&ch);
			if(ch=='Q')
			{
				scanf("%d%d",&a,&b);
				printf("%lld\n",query(a,b,1,n,1));
			}
			else
			{
				scanf("%d%d%d",&a,&b,&c);
				update(a,b,c,1,n,1);
			}
		}
	}
}
