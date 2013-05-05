/*
HDU 4251 The Famous ICPC Team Again
划分树，求区间上的中间值
*/
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
const int MAXN=100010;
int tree[20][MAXN];//表示每层上每个位置的值
int sorted[MAXN];//排好序的数
int toleft[20][MAXN];//每层1-i有多少个数到左边

void build(int l,int r,int dep)
{
    if(l==r)return;
    int mid=(l+r)>>1;
    int same=mid-l+1;//same表示等于中间值且到左边的数的个数
    for(int i=l;i<=r;i++)
      if(tree[dep][i]<sorted[mid])
        same--;
    int lpos=l;
    int rpos=mid+1;
    for(int i=l;i<=r;i++)
    {
        if(tree[dep][i]<sorted[mid])//去左边
        {
            tree[dep+1][lpos++]=tree[dep][i];

        }
        else if(tree[dep][i]==sorted[mid]&&same>0)//去左边
        {
            tree[dep+1][lpos++]=tree[dep][i];
            same--;
        }
        else//去右边
           tree[dep+1][rpos++]=tree[dep][i];
        toleft[dep][i]=toleft[dep][l-1]+lpos-l;//从1到i放左边的个数
    }
    build(l,mid,dep+1);//递归建树
    build(mid+1,r,dep+1);
}




int query(int L,int R,int l,int r,int dep,int k)
{
    if(l==r)return tree[dep][l];
    int mid=(L+R)>>1;
    int cnt=toleft[dep][r]-toleft[dep][l-1];
    if(cnt>=k)
    {
        //L+查询区间前去左边的数的个数
        int newl=L+toleft[dep][l-1]-toleft[dep][L-1];
        //左端点+查询区间会分入左边的数的个数
        int newr=newl+cnt-1;
        return query(L,mid,newl,newr,dep+1,k);//注意
    }
    else
    {
        //r+区间后分入左边的数的个数
        int newr=r+toleft[dep][R]-toleft[dep][r];
        //右端点减去区间分入右边的数的个数
        int newl=newr-(r-l-cnt);
        return query(mid+1,R,newl,newr,dep+1,k-cnt);//注意
    }
}

int main()
{
   // freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int iCase=0;
    int n,m;
    int A,B;
    while(scanf("%d",&n)!=EOF)
    {
        iCase++;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&tree[0][i]);
            sorted[i]=tree[0][i];
        }
        sort(sorted+1,sorted+n+1);//建树
        build(1,n,0);
        scanf("%d",&m);
        printf("Case %d:\n",iCase);
        while(m--)
        {
            scanf("%d%d",&A,&B);
            int k=(B-A)/2+1;
            printf("%d\n",query(1,n,A,B,0,k));
        }
    }
    return 0;
}