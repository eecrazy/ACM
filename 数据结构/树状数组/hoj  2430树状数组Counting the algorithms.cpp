#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;
#define maxn 200500
long long c[maxn];
long long a[maxn];long long b[maxn];long long d[maxn];

int len;
int lowbit(int x)
{
    return x&(-x);
}

void modify(int i,long long x)
{
    while(i<=len)
    {
        c[i]+=x;
        i+=lowbit(i);
    }
}


long long sum(int x)
{
    long long ret=0;
    while(x>0)
    {
        ret+=c[x];
        x-=lowbit(x);
    }
    return ret;
}
int main()
{

   // freopen("in","r",stdin);
    int ans,i,n;
    while(scanf("%d",&n)!=EOF)
    {
        len=2*n;
         for(int i=1;i<=len;i++)
        {
            c[i]=0;a[i]=0;b[i]=0;
        }
        for(int i=1;i<=len;i++)
        {
            scanf("%d",&d[i]);
            modify(i,1);
            if(a[d[i]]==0)a[d[i]]=i;
            else b[d[i]]=i;
        }


        int ans=0;
        for(int i=len;i>=1;i--)
        {
            if(a[d[i]])
                ans+=sum(b[d[i]])-sum(a[d[i]]);
            if(a[d[i]]>=1)
            modify(a[d[i]],-1);
            a[d[i]]=b[d[i]]=0;
        }
        printf("%d\n",ans);
    }

}
