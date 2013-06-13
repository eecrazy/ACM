#include <iostream>
#include <cstdio>
#include <math.h>
#include <algorithm>
#include <map>
using namespace std;
//16 7 8 1 1 2 3
map<char,int> a;
int main()
{
    a['A']=16;
    a['B']=7;
    a['C']=8;
    a['D']=1;
    a['E']=1;
    a['F']=2;
    a['G']=3;
    int t;
    int n,m,sum1,sum2;
    scanf("%d",&t);
    while(t--)
    {
        sum1=0;sum2=0;
        scanf("%d",&n);
        char ch;
        int f1=0,f2=0,f3=0,f4=0;
        while(scanf("%c",&ch)&&ch!='\n')
        {
            if(ch>='A'&&ch<='G')
            sum1+=a[ch];
            else  continue;
            if(ch=='B')f1++;
            if(ch=='C')f2++;

        }
        scanf("%d",&m);
        while(scanf("%c",&ch)&&ch!='\n')
        {
            if(ch>='A'&&ch<='G')
            sum2+=a[ch];
            else  continue;
            if(ch=='B')f3++;
            if(ch=='C')f4++;
        }
        if(f1>=1&&f2>=1);else sum1--;
        if(f3>=1&&f4>=1);else sum2--;
        if(sum1==0)sum1=1;
        if(sum2==0)sum2=1;
        if(sum1==sum2)printf("tie\n");
        if(sum1<sum2)printf("black\n");
        if(sum1>sum2)printf("red\n");

    }
}
