// poj3243的算法也可以1000+ms
//下面的方法好NB!!!125ms
#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;
const long long mod=800000;
const long long MAX=800000;
struct data
{
    long long  m,n,next;
}ln[MAX];
long long st[MAX],s;
void insert(long long m,long long n)
{
    long long  mm = m%mod;
    long long  pos = st[mm];
    while(pos != -1 && ln[pos].m != m)
        pos = ln[pos].next;
    if(pos == -1)
    {
        ln[s].m = m;
        ln[s].n = n;
        ln[s].next = st[mm];
        st[mm] = s++;
    }
    else ln[pos].n = n;
}
long long find(long long m)
{
    long long  mm=m%mod;
    long long pos=st[mm];
    while(pos!=-1)
    {
        if(ln[pos].m==m)
            return ln[pos].n;
        pos=ln[pos].next;
    }
    return -1;
}
long long MOD(long long b,long long n,long long mod)
{
    long long t=1;
    while(n)
    {
        if(n & ((__int64)1))
            t = (t*b)%mod;
        b = (b*b)%mod;
        n >>= ((__int64)1);
    }
    return t%mod;
}
long long solve(long long X,long long Z,long long K)//用来求X^Y mod Z = k 中的Y
{
        long long  m,i,j,b;
        X %= Z;
        K %= Z;
        s = 0;
        memset(st, -1, sizeof(st));
        m = (int)sqrt((double)Z);
        long long t = K;
        for(i=0; i <= m; i++)
        {
            insert(t, i);
            t *= X;
            t %= Z;
        }
        b = MOD(X, m, Z);
        t = 1;
        long long ans = -1;
        for(i=1; i <= m; i++)
        {
            t *= b;
            t %= Z;
            long long x = find(t);
            if(x != -1)
            {
                ans = i*m-x;
                break;
            }
        }
        if(ans != -1 && MOD(X, ans, Z) == K)
        return ans;
        else return -1;
}
int main()
{
    long long Z,X,K;
    long long power;
    while(cin>>Z>>X>>K)
    {
        if(!X && !Z && !K)cout<<0<<endl;
        power=solve(X,Z,K);
        if(power!=-1)cout<<power<<endl;
        else printf("no solution\n");
    }
    return 0;
}
