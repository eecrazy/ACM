#include <iostream>
#define MAX 40005  //10
using namespace std;
int n,data[MAX],M,t;
int dp[MAX],c[MAX]; //c数组的含义是c[dp[k]]=data[k];即当递增子序列的长度为dp[k]时子序列的末尾元素是data[k]
void Init()
{
    int i;
    scanf("%d",&n);
    for(i=1; i<=n; i++)
    {
        scanf("%d",&data[i]);
        c[i]=MAX;     //这里实际上是初始化为最大的序列长度
    }
}
int Find(int *a,int len,int n)
{
    int left,right,mid;
    left=1;
    right=n;
    mid=(left+right)/2;
    while(left<=right)
    {
        if(n>a[mid])
            left=mid+1;
        else if(n<a[mid])
            right=mid-1;
        else
            return mid;
        mid=(left+right)/2;
    }
    return left;
}
int LongLcs()
{
    int i,mmax,j,k;
    M=1;
    c[1]=data[1];
    dp[1]=1;
    for(i=2; i<=n; i++)
    {
        j=Find(c,n+1,data[i]);
        c[j]=data[i];
        dp[i]=j;
        if(j>M)
            M=j;
    }
    return M;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        Init();
        int len=LongLcs();
        printf("%d\n",len);
    }
    return 0;
}   