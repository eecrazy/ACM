//给出一段0,1序列.初始全为1
//单点更新,给出x,求x所在处的连续为1的最长序列长度
#include <cstdio>
#define maxn 50005
#include <iostream>
#define lson l,m,k<<1
#define rson m+1,r,k<<1|1
using namespace std;
struct node
{
    int lm,rm,m;//左边最长，右边最长，全局最长
    int len;//区间长度
};
node st[maxn<<2];
void pushup(int k)
{
    int ls=k<<1,rs=k<<1|1;
    st[k].lm=st[ls].lm==st[ls].len?st[ls].len+st[rs].lm:st[ls].lm;
    st[k].rm=st[rs].rm==st[rs].len?st[rs].len+st[ls].rm:st[rs].rm;
    st[k].m=max(max(st[ls].m,st[rs].m),st[ls].rm+st[rs].lm);
}
void build(int l,int r,int k)
{
    st[k].len=r-l+1;
    if(l==r)
    {
        st[k].lm=st[k].rm=st[k].m=1;
        return ;
    }
    int m=(l+r)>>1;
    build(lson);
    build(rson);
    pushup(k);
}
int flag;//摧毁或者是建造标记
void update(int p,int l,int r,int k)
{
    if(l==r)
    {
        st[k].lm=st[k].rm=st[k].m=flag;
        return ;
    }
    int m=(l+r)>>1;
    if(p<=m)update(p,lson);
    else update(p,rson);
    pushup(k);
}
// 这个写好了，其它都是浮云呀
int query(int a,int l,int r,int k)
{
    if(st[k].m==0)return 0;
    if(st[k].m==st[k].len)return st[k].len;
    int m=(l+r)>>1;
    if(st[k].lm&&st[k].lm+l-1>=a)return st[k].lm;//左边
    if(st[k].rm&&r-st[k].rm+1<=a)return st[k].rm;//右边
    if(st[k<<1].rm&&a<=m&&m-st[k<<1].rm+1<=a)
        return st[k<<1].rm+st[k<<1|1].lm;
    if(st[k<<1|1].lm&&a>m&&st[k<<1|1].lm+m>=a)
        return st[k<<1|1].lm+st[k<<1].rm;
    if(a<=m)query(a,lson);
    else query(a,rson);
}
int main()
{
    char op;
    int n,m,a;
    int data[maxn+10];
    int t=0;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        build(1,n,1);
        while(m--)
        {
            scanf(" %c",&op);
            if(op=='D')
            {
                scanf("%d",&a);
                data[t++]=a;
                flag=0;
                update(a,1,n,1);
            }
            if(op=='Q')
            {
                scanf("%d",&a);
                printf("%d\n",query(a,1,n,1));
            }
            if(op=='R')
            {
                flag=1;
                update(data[--t],1,n,1);
            }
        }
    }


}
