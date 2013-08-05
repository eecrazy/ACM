#include <iostream>
using namespace std;
#include <cstdio>
const int maxn =200005;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
int most[maxn<<2];
void pushup(int rt)//区间最值
{
	most[rt]=max(most[rt<<1],most[rt<<1|1]);
}

void build(int l,int r,int rt)
{
	if(l==r)
	{
		scanf("%d",&most[rt]);
		return ;
	}
	int m=(l+r)>>1;
	build(l,m,rt<<1);
	build(m+1,r,rt<<1|1);
	pushup(rt);
}
void update(int p,int value,int l,int r,int rt)
{
	if(l==r)//单点替换
	{
		most[rt]=value;
		return ;
	}
	int m=(l+r)>>1;
	if(p<=m)update(p,value,lson);
	else update(p,value,rson);
	pushup(rt);
}

int query(int L,int R,int l,int r,int rt)
{
	if(L<=l&&r<=R)
		return most[rt];
	int m=(l+r)>>1;
	int ret=0;
	if(L<=m)ret=max(ret,query(L,R,lson));
	if(R>m)ret=max(ret,query(L,R,rson));
	return ret;
}
int main()
{
	int n,m,a,b;
	while(scanf("%d %d",&n,&m)==2)
	{
		 build(1,n,1);
		 char op;
		 while(m--)
		 {
		 	scanf(" %s%d%d",&op,&a,&b);
		 	if(op=='Q')
		 	{
		 		printf("%d\n",query(a,b,1,n,1));
		 	}
		 	else update(a,b,1,n,1);
		 }

	}
}
