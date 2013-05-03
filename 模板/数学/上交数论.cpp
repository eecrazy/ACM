//上交数论算法
//1.  Greatest Common Divisor最大公约数
int GCD(int x, int y)
{
    int t;
    while(y > 0)
    {
        t = x % y;
        x = y;
        y = t;
    }
    return x;
}
//2.  Prime素数判断
bool is_prime(int  u)
{
    if(u ==  0 || u ==  1) return false;
    if(u ==  2)      return true;
    if(u%2 == 0)      return false;
    for(int i=3; i <=  sqrt(u) ; i+=2)
        if(u%i==0)      return false;
    return true;
}
//3.  Sieve Prime素数筛法
const int M = 1000; // M : size
bool mark[M];  // true : prime number
void sieve_prime()
{
    memset(mark,  true, sizeof(mark));
    mark[0]  = mark[1]  = false;
    for(int i=2; i <=  sqrt(M) ; i++)
    {
        if(mark[i])
        {
            for(int j=i*i; j < M ; j+=i)
                mark[j]  = false;
        }
    }
}
//4.  Module Inverse模逆元
// ax ≡ 1 (mod n)
int Inv(int a, int n)
{
    int d, x, y;
    d = extended_euclid(a, n, x, y);
    if(d == 1)  return (x%n + n) % n;
    else     return -1; // no solution
}
//5.  Extended Euclid扩展欧几里德算法
//如果GCD(a,b) = d, 则存在x, y, 使d =  ax +  by
// extended_euclid(a, b) = ax + by
int extended_euclid(int a, int b, int &x, int &y)
{
    int d;
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    d = extended_euclid(b, a % b, y, x);
    y -= a / b * x;
    return d;
}
//6.  Modular Linear Equation模线性方程(同余方程)
//如果GCD(a,  b)不能整除c, 则ax +  by =  c 没有整数解
// ax ≡ b (mod n) n > 0
//上式等价于二元一次方程ax  – ny = b
void modular_linear_equation(int  a, int b, int n)
{
    int d, x, y, x0, gcd;// 可以减少扩展欧几里德溢出的可能
    gcd = GCD(a, n);
    if (b%gcd !=  0)
    {
        cout <<  "no solution" << endl;
        return ;
    }
    a /= gcd;
    b /= gcd;
    n /= gcd;
    d = extended_euclid(a, n, x, y);
    if( b%d ==  0)
    {
        x0 = ( x*(b/d) ) % n; // x0 : basic solution
        int ans = n;
        for(int i=0; i < d ; i++)
        {
            ans = ( x0 + i*(n/d) ) % n;
            cout << ans <<  endl;
        }
    }
    else     cout << "no solution" <<  endl;
}
//7.  Chinese Remainder Theorem中国余数定理
// x ≡ b[i] (mod w[i]), i∈[1, len-1]
// 前提条件w[i] > 0, 且w[]中任意两个数互质
int chinese_remainder(int  b[], int w[], int len)
{
    int i, d, x, y, m, n;
    ret = 0;
    n = 1;
    for(i=0;  i < len ; i++)      n *= w[i];
    for(i=0;  i < len ; i++)
    {
        m = n / w[i] ;
        d = extended_euclid(w[i], m, x, y);
        ret = (ret + y*m*b[i]) % n;
    }
    return (n + ret%n) % n;
}
// m ≡r[i] (mod  a[i])
// a[i] 可以不互素
// -1表示无解
/*Pku 2891 Strange Way to Express Integers
假设C ≡ A1 (mod  B1)，C ≡ A2 (mod  B2)。
令C =  A1 +  X1B，那么X1B1 ≡ A2 - A1 (mod  B2)。
用扩展欧几里德算法求出X1，也就求出C。
令B =  lcm(B1,  B2)，那么上面两条方程就可以被C’  ≡ C (mod  B)代替。
迭代直到只剩下一条方程。*/
LL chinese_remainder2()
{
    int i, j;
    if (n ==  1)return r[0];
    LL m, x, apre;
    x = modular_linear_equation(a[0], r[1]-r[0], a[1]);
    if (x == -1)return -1;
    m = x*a[0] + r[0];
    apre = LCM(a[0], a[1]);
    for (i=2; i<n; i++)
    {
        x = modular_linear_equation(apre, r[i]-m, a[i]);
        if (x == -1)return -1;
        m = x*apre + m;
        apre = LCM(apre, a[i]);
    }
    return m;
}
//8.  Euler Function欧拉函数
//求..n-1中与n互质数的个数
int euler(int n)
{
    int ans = 1;
    int i;
    for(i=2;  i*i<=n  ; i++)
    {
        if(n%i  ==  0)
        {
            n /=  i;
            ans *= i-1;
            while(n%i  ==  0)
            {
                n /=  i;
                ans *= i;
            }
        }
    }
    if(n > 1)
    {
        ans *= n-1;
    }
    return ans;
}
//9.  Farey总数
//求MAX以内所有Farey的总数
const int MAX = 1000100;
int  n;
bool num[1100];//sqrt(MAX)
int prime[1100],  total;
__int64 f[MAX], inc[MAX];
void cal_prime()
{
    int i,j;
    memset(num,  false, sizeof(num));
    total  = 0;
    for(i=2; i<1100; i++)
    {
        if(!num[i])
        {
            prime[total  ++]  = i;
            j =  i+i;
            while(j  <  1100)
            {
                num[j]  = true;
                j +=  i;
            }
        }
    }
}
void cal_farey()
{
    int i,j,k;
    inc[1]  = 1;
    for(i=2; i<MAX; i++)
    {
        for(j=0; j<total; j++)
        {
            if(i%prime[j]  ==  0)
            {
                k =  i / prime[j];
                if(k%prime[j]  ==  0) inc[i] =  inc[k] * prime[j];
                else inc[i] = inc[k] * (prime[j]  -1);
                break;
            }
        }
        if(j ==  total) inc[i] = i -1;
    }
    f[1] =  0;
    for(i=2; i<MAX; i++)  f[i] =  f[i-1] +  inc[i];
}
int main()
{
    cal_prime();
    cal_farey();
    while(scanf("%d",  &n), n)
    {
        printf("%I64d\n",  f[n]);
    }
}
//10.  Farey序列构造
//构造5000以内的Farey序列
const int MAX = 8000000;
int  total;
int n,k;
int farey[2][MAX];
void make_farey_seq(int  x1,int y1,int x2, int y2)
{
    if(x1+x2  > n || y1+y2  >  n) return;
    make_farey_seq(x1,  y1,x1+x2,  y1+y2);
    total ++;
    farey[0][total] =  x1+x2;
    farey[1][total]  =  y1+y2;
    make_farey_seq(x1+x2,  y1+y2,x2,y2);
}
int main()
{
    int t;
    scanf("%d %d",  &n, &t);
    total =  1;
    farey[0][1] =  0;
    farey[1][1] =  1;
    make_farey_seq(0,1,1,1);
    farey[0][total+1]  =  1;
    farey[1][total+1]  = 1;
    total ++;
    while(t --)
    {
        scanf("%d",  &k);
        if(k >  total) puts("No  Solution");
        else printf("%d/%d\n",  farey[0][k], farey[1][k]);
    }
}
//11.  Miller_Rabbin素数测试，Pollard_rho因式分解
typedef __int64 I64;
const char * pformat  = "%I64d";
I64 big_rand(I64  m)
{
    I64 x = rand();
    x  *= rand();
    if(x <  0) x = -x;
    return x %=  m;
}//  x*y % n
I64 mod_mul(I64  x, I64 y, I64 n)
{
    if(x ==  0 || y ==  0) return 0;
    return ( ((x&1)*y)%n  +  (mod_mul(x>>1,y,n)<<1)%n  ) % n;
}// x^y % n
I64 mod_exp(I64  x, I64 y, I64 n)
{
    I64  ret = 1;
    while(y)
    {
        if(y&1) ret = mod_mul(ret,x,n);
        x = mod_mul(x,x,n);
        y  >>=  1;
    }
    return ret;
}
bool Miller_Rabbin(I64  n)  // O(times  * (log N)^3)
{
    I64 i,j,x,m,k;
    if(n ==  2) return true;
    if(n < 2 || !(n&1)) return false;
    m  = n - 1;
    k =  0;
    while(!(m&1))  m  >>=  1, k ++;//  binary  scan
    for(i=0; i<4; i++) // test times
    {
        x = big_rand(n-2)  +2;
        x  =  mod_exp(x,m,n);
        if(x ==  1) continue;
        for(j=0; j<k; j++)
        {
            if(x ==  n-1) break;
            x  = mod_mul(x,x,n);
        }
        if(j >=  k) return false;
    }
    return true;
    /*lrj P.218
    for(i=0;i<20;i++)  {
    x = big_rand(n-2)  +2;
    if(mod_exp(x,n-1,n)  !=  1) return false;
    }
    return true;
    */
}
I64 gcd(I64 x, I64 y)
{
    if(x >  y) std::swap(x,y);
    while(x)
    {
        I64  t =  y % x;
        y = x;
        x  =  t;
    }
    return y;
}
I64 func(I64 x, I64 m)
{
    return (mod_mul(x,x,m)+1)  % m;
}
I64 Pollard(I64  n)
{
    if(Miller_Rabbin(n))  return n;
    if(!(n&1)) return 2;
    I64 i,x,y,ret;
    i  = 1;
    while(true)
    {
        x = i ++;
        y  =  func(x,n);
        ret =  gcd(y-x,n);
        while(ret ==  1)
        {
            x =  func(x,n);
            y =  func(func(y,n),n);
            ret = gcd((y-x+n)%n,n)  % n;
        }
        if(0 < ret && ret <  n) return ret;
    }
}
I64 factor[100], nfac, minfac;
void cal_factor(I64 n)
{
    I64  x =  Pollard(n);
    if(x ==  n)  //factor[nfac ++]  =  x;
    {
        minfac =  min(minfac,x);
        return;
    }
    cal_factor(x);
    cal_factor(n/x);
}
void print_factor(I64  n)
{
    I64 i;
    nfac = 0;
    cal_factor(n);
    std::sort(factor,factor +  nfac);
    for(i=0; i<nfac; i++)
    {
        if(i > 0) putchar(' ');
        printf(pformat,factor[i]);
    }
    puts("");
}
const I64  lim  = 100000;
int main()
{
    I64  n,t,i;
    srand((unsigned)time(NULL));
    scanf(pformat,&t);
    while(t --)
    {
        scanf(pformat, &n);
        if(Miller_Rabbin(n))  puts("Prime");
        else
        {
            if(!(n&1))  puts("2");
            else
            {
                for(minfac=3;  minfac  < lim  && n % minfac ; minfac+=2)  ;
                if(minfac  >=  lim)
                {
                    I64  rn =  sqrt(1.0*n);
                    if(rn * rn ==  n)
                    {
                        minfac  = rn;
                        cal_factor(rn);
                    }
                    else
                    {
                        minfac  =  n;
                        cal_factor(n);
                    }
                }
                printf(pformat,minfac);
                puts("");
            }
        }
    }
}
