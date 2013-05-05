#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
#define maxn 1007
int phi[maxn];

void make_phi()
{
     for(long long i=1;i<maxn;++i) phi[i]=i;
     for(long long i=2;i<maxn;++i)
     {
         if(phi[i]==i)
         {
             for(long long j=i;j<maxn;j+=i)
             {
                 phi[j]=phi[j]-phi[j]/i;
             }
         }
     }
}

int main()
{
    int ca,n,num=0;
    int k=1;
    scanf("%d",&ca);
    make_phi();
    while(k<=ca)
    {
        scanf("%d",&n);
        for(long long i=1;i<=n;i++)
        {
           num+=phi[i];
        }
        printf("%ld %d %d\n",k,n,num*2+1);
        num=0;
        k++;
    }
}