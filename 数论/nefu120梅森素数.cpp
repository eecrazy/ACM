
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
typedef long long llong;
using namespace std;
#define MAX 5
llong Pow(llong a,llong b,llong n)
{
     llong t=1;
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
        t=Pow(a,b,n);
       if(t==1)continue;
        else return 0;
    }
    return 1;
}
int main()
{
    //freopen("out.txt","w",stdout);
     int sel;
    llong n=0,p=0;
    int c;
    scanf("%d",&c);
    while(c--)
    {
        scanf("%lld",&n);
        if(n==61)
        {

            cout<<"yes"<<endl;
            continue;
        }
        n=(((long long)1<<n)-1);
        //cout<<n<<endl;
        sel=1;
        if(n<=1)sel=0;
        else if(n==2||n==3)sel=1;
        else if((n&1)==0)sel=0;
        else
        {
                if(!MillerRobbin(n))
                    sel=0;
        }
        if(sel)
            printf("yes\n");
        else
            printf("no\n");
    }
    return 0;
}
//以上代码WA,当n=61时出错。2^61-1也是梅森素数。

// Lucas-Lehmer判别法：
#include <cstdio>
#include <iostream>
using namespace std;

long long multi(long long a,long long b,long long m)
{
    long long ret=0;
    while(b>0)
    {
        if(b&1)
        {
            ret=(ret+a)%m;
        }
        b=b>>1;
        a=(a<<1)%m;
    }
    return ret;
}
int main()
{
    long long sum=1,data[66],tmp;
    int n,p;
    data[1]=4;
    cin>>n;
    while(n--)
    {
        sum=1;
        cin>>p;
        sum=sum<<p;
        sum-=1;
        //printf("%lld\n",sum);
        for(int i=2;i<=p-1;i++)
        {
            tmp=multi(data[i-1],data[i-1],sum);
            data[i]=(tmp-2)%sum;
        }
        if(p==2)
        {
            cout<<"yes"<<endl;
        }
        else
        {
            if(data[p-1]==0)
                cout<<"yes"<<endl;
            else
                cout<<"no"<<endl;
        }
    }
}