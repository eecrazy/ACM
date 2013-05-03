#include <iostream>
using namespace std;
//辗转相除，求最大公约数
long long gcd(long long m,long long n)
{
    if(n==0)
        return m;
    else
        return gcd(n,m%n);
}
int main()
{
    long long m,n;
    while(cin>>m>>n)
        cout<<m*n/gcd(m,n)<<endl;
}
