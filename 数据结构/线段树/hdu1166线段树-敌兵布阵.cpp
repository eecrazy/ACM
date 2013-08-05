#include <iostream>
#include <cstdio>
using namespace std;
const int maxn=50005;
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
int sum[maxn<<2];
void pushup(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];//父节点等于2个孩子节点之和
}
void build(int l,int r,int rt)
{
	if(l==r)
	{
		scanf("%d",&sum[rt]);
		return ;
	}
	int m=(l+r)>>1;
	build(l,m,rt<<1);
	build(m+1,r,rt<<1|1);
	pushup(rt);
}
void update(int p,int add,int l,int r,int rt)//p是要更新的位置下标
{
	if(l==r)//单点更新，一直到叶子节点
	{
		sum[rt]+=add;
		return ;
	}
	int m=(l+r)>>1;
	if(p<=m)
	update(p,add,l,m,rt<<1);
	else
	update(p,add,m+1,r,rt<<1|1);
	pushup(rt);
}
int query(int L,int R,int l,int r,int rt)
{
	if(L<=l&&r<=R)
		return sum[rt];
	int m=(l+r)>>1;
	int ret=0;

	if(L<=m)ret+=query(L,R,lson);
	if(R>m)ret+=query(L,R,rson);
	return ret;
}
int main()
{
//    freopen("in","r",stdin);
	int t,n;
	scanf("%d",&t);
	int c=1;
	while(t--)
	{
		printf("Case %d:\n",c++);
		scanf("%d",&n);
		build(1,n,1);
//		for(int i=1;i<=30;i++)
//		printf("%d ",sum[i]);
//		printf("\n");
		char op[10];
		int a,b;
		while(scanf("%s",op)&&op[0]!='E')
		{
			scanf("%d%d",&a,&b);
			if(op[0]=='Q')
				printf("%d\n",query(a,b,1,n,1));
			else if(op[0]=='A')
				update(a,b,1,n,1);
			else
				update(a,-b,1,n,1);
		}
	}
	return 0;
}
