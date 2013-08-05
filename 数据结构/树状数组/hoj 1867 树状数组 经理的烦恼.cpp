#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;
#define maxn 1005000
long long c[maxn];
long long a[maxn];
int s,n,m;
int lowbit(int x)
{
    return x&(-x);
}
bool judge(long long x)
{
    if(x==0||x==1)return false;
    if(x==2||x==3)return true;
    long long ff=int(sqrt(x))+1;
    for(long long i=2; i<=ff; i++)
    {
        if((x%i)==0)
            return false;
    }
    return true;
}
void modify(int i,long long x)
{
    while(i<=s)
    {
        c[i]+=x;
        i+=lowbit(i);
    }

}
void init()
{
    for(int i=1; i<=s; i++)
    {
        c[i]=0;
        a[i]=m;
    }
    c[0]=0;
    if(judge(m))
        for(int i=1; i<=s; i++)
            modify(i,1);
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

    freopen("in","r",stdin);
    int Case=1;
    while(scanf("%d%d%d",&s,&n,&m)==3&&s+n+m)
    {
        printf("CASE #%d:\n",Case++);
        int  d,x,b;
        init();

        while(n--)
        {
            scanf("%d%d%d",&d,&x,&b);
            if(d==0)
            {
                long long tmp=a[x];
                a[x]+=b;
                if(judge(a[x])&&!judge(tmp))
                {
                    modify(x,1);
                }
                else if(judge(tmp)&&!judge(a[x]))
                    modify(x,-1);
            }
            if(d==1)
            {

                    printf("%lld\n",sum(b)-sum(x-1));

            }

        }
        printf("\n");
    }
}
