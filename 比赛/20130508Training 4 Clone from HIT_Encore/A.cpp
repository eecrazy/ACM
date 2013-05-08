#include <iostream>
#include<cstdio>
using namespace std;
//要判断大于1的有几堆，所有堆都等于1和有一堆大于1效果完全不同。
int main()
{
    int n,a,b,r;
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        r=0;
        scanf("%d",&a);
        n--;
        if(a>1)r++;
        while(n--)
        {
            scanf("%d",&b);
            a^=b;
            if(b>1)r++;
        }
        if(r!=0)
        {
            if(a==0)printf("Brother\n");
            else printf("John\n");
        }
        else
        {
            if(a==0)printf("John\n");
            else  printf("Brother\n");
        }
    }
}