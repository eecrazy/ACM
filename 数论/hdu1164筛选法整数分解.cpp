#include <iostream>
#include <cstdio>
using namespace std;
#define N 65536
#include <string.h>
#include <cmath>

int prime[N];
int vis[N];
int ant;
void get_prime()
{
    ant=0;
    for(int i=2; i<N; i++)
    {
        if(!vis[i])prime[ant++]=i;
        for(int j=0; j<ant&&prime[j]*i<N; j++)
        {
            vis[prime[j]*i]=1;
            if(!(i%prime[j]))break;
        }
    }
}
void divide(int n)
{
    int i,ct=0,factor[N];
    int temp=sqrt(n+0.0);
    for(i=0; i<=temp; i++)
    {
        if(prime[i]>temp)break;
        while(n%prime[i]==0)
        {
            ct++;
            factor[ct]=prime[i];
            n/=prime[i];
            if(ct!=1)
                printf("*");
            printf("%d",prime[i]);
        }
    }
    if(n!=1)
    {
        ct++;
        factor[ct]=n;
        if(ct!=1)
            printf("*");
        printf("%d",n);

    }
}
int main()
{
    int n;
    get_prime();
    while(cin>>n)
    {
        divide(n);
        printf("\n");
    }
}

