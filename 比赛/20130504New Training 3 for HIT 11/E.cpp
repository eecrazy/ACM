#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace std;

#define MAX 60000

int noprime[MAX];

void Prime()
{
    int k;
    noprime[0]=noprime[1]=1;
    noprime[2]=0;
    for (int i=2; i<50000; i++)
        if (!noprime[i])
        {
            k=i;
            while(k+i<50000)
            {
                k=k+i;
                noprime[k]=1;
            }
        }
}

bool judge(int n)
{
    int num=0;
    for (int i=2; i<40000; i++) //求一个数的素因子
        if (!noprime[i])
        {
            if (n%i==0) num++;
            if (num>=3) break;
            while (n%i==0)
                n/=i;
        }
    if (num>=3) return true;
    else return false;
}

int main()
{
    int t;
    cin>>t;
    Prime();
    int num=0,i,n,a[2010];
    int pre=29;
    for ( i=pre+1; i<=3000; i++)
        if (judge(i))
        {
            pre=i;

            a[num++]=i;
        }
    while (t--)
    {
        cin>>n;
        cout<<a[n-1]<<endl;

    }
    return 0;
}
