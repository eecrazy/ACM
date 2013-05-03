#include<stdio.h>
#include<stdlib.h>
typedef long long llong;
#define MAX 3
llong Pow(llong a,llong b,llong n)//速度最快
{
     llong t=1;
     //  a^(2^i) = a^(2^(i-1) * 2) = ( a^( p(i) * 2^(i-1) ) )^2
     for(;b;b>>=1,a=a*a%n)
     if(b&1) t=t*a%n;
     return t;
}
bool MillerRobbin(llong n)
{
    llong a,b=n-1;
    llong t;
    for(int i=0;i<MAX;i++)
    {
        a=rand()%(n-1)+1;
        //while((b&1)==0)b>>=1;
        t=Pow(a,b,n);
        /*while(b!=n-1&&t!=1&&t!=n-1)//二测探测原理:如果n是素数，x^2=1mod n解只能是x=1或x=n-1
        {
            t=t*t%n;
            b<<=1;
        }
        if(t==n-1||(b&1)==1)continue;*/
       if(t==1)continue;
        else return 0;
    }
    return 1;
}
int main()
{
     int sel;
    llong n;
    while(scanf("%lld",&n)!=EOF)
    {
        sel=1;
//times为每个数进行测试的次数
        if(n<=1)sel=0;
        else if(n==2||n==3)sel=1;
        else if((n&1)==0)sel=0;
        else
        {
                if(!MillerRobbin(n))
                    sel=0;
        }
        if(sel)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}
 