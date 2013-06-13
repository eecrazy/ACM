#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string.h>
using namespace std;

void calc(int num[],int n)//计算0~n所以数中累加的各位二进制1的个数
{
    for(int i=0;i<63;i++)num[i]=0;
    int tmp=1;
    n++;
    for(int i=0;i<63;i++)
    {
        if(tmp>n)break;
        tmp*=2;
        num[i]+=(n-n%tmp)/2;
        if(n%tmp > tmp/2)num[i]+=n%tmp-tmp/2;
    }
}
int num1[70],num2[70];
int main()
{
    int a,b;
    while(scanf("%d%d",&a,&b)==2)
    {
        calc(num1,a-1);
        calc(num2,b);
        for(int i=0;i<63;i++)num2[i]-=num1[i];
        long long ans=0;
        for(int i=0;i<63;i++)
        {
            ans+=num2[i]/2;
            num2[i+1]+=num2[i]/2;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
