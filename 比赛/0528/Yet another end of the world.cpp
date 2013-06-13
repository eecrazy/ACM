#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
#include <cmath>
int a[1005][3];
bool judge(int i,int j)
{
    int high=a[j][2]-a[i][1];
    int low=a[j][1]-a[i][2];
    int num=__gcd(a[i][0],a[j][0]);
    if(high/num>low/num)return false;
    if(high%num==0)return false;
    if(low%num==0)
    return false;
    return true;
}

int main()
{
    int n,b;
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0;i<n;i++)
        {
              scanf("%d %d %d",&a[i][0],&a[i][1],&a[i][2]);
        }
        int flag=1;
        for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
        {
            if(judge(i,j))
            continue;
            else
            {
                flag=0;
                break;
            }
        }
        if(flag)
        printf("Can Take off\n");
        else
        printf("Cannot Take off\n");
    }
}
