#include <iostream>
using namespace std;
long long extgcd(long long a, long long b, long long &x, long long &y)
{
    long long d, t;
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    d = extgcd(b, a % b, x, y);
    t = x - a / b * y;
    x = y;
    y = t;
    return d;
}

int main()
{
    long long n,d,x,y,A,B;
    long long c,dd;
    cin>>c;
    while(c--)
    {
        cin>>n>>d>>x>>y;
        long long tmp=(y-x+n)%n;
        dd=extgcd(d,n,A,B);
        if(tmp%dd)
            cout<<"Impossiable"<<endl;
        else
        {
            long long r=n/dd;
            A=A*tmp/dd;
            cout<<(A%r+r)%r<<endl;
        }

    }
}