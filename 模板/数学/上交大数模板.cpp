//上交大数模板
typedef int hugeint;
//应不大于,以防乘法时溢出
const int Base =  1000;
const int Capacity = 1000;
struct xnum
{
    int Len;
    int Data[Capacity];
    xnum()  : Len(0) {}
    xnum(const xnum&V):Len(V.Len)
    {
        memcpy(Data,V.Data,Len*sizeof  *Data);
    }
    xnum(int  V) : Len(0)
    {
        for (; V >  0; V /= Base) Data[Len++]  = V % Base;
    }
    xnum(char  S[]);
    xnum& operator=(const xnum& V)
    {
        Len = V.Len;
        memcpy(Data, V.Data, Len * sizeof *Data);
        return *this;
    }
    int& operator[](int Index)
    {
        return Data[Index];
    }
    int operator[](int Index) const
    {
        return Data[Index];
    }
    void print()
    {
        printf("%d",Len==0?0:Data[Len-1]);
        for(int i=Len-2; i>=0; i--)
            for(int j=Base/10; j>0; j/=10)printf("%d",Data[i]/j%10);
    }
};
xnum::xnum(char  S[])
{
    int I, J;
    Data[Len =  0] = 0;
    J = 1;
    for (I = strlen(S)-1; I>=0; I--)
    {
        Data[Len] +=  (S[I] - '0') * J;
        J *=  10;
        if (J >= Base) J =  1, Data[++Len]  = 0;
    }
    if (Data[Len] >  0) Len++;
}
int compare(const xnum& A, const xnum& B)
{
    int I;
    if (A.Len != B.Len) return A.Len > B.Len ? 1 : -1;
    for (I = A.Len - 1; I >=  0 && A[I] == B[I]; I--);
    if (I <  0) return 0;
    return A[I] > B[I]  ? 1 : -1;
}
xnum operator+(const xnum& A, const xnum& B)
{
    xnum  R;
    int I;
    int Carry =  0;
    for (I =  0; I < A.Len || I < B.Len || Carry > 0; I++)
    {
        if (I < A.Len) Carry += A[I];
        if (I < B.Len) Carry += B[I];
        R[I]  = Carry % Base;
        Carry /= Base;
    }
    R.Len = I;
    return R;
}
xnum operator-(const xnum& A, const xnum& B)
{
    xnum  R;
    int Carry = 0;
    R.Len = A.Len;
    int I;
    for (I =  0; I < R.Len; I++)
    {
        R[I]  = A[I] - Carry;
        if (I < B.Len) R[I] -= B[I];
        if (R[I]  <  0) Carry =  1, R[I]  += Base;
        else Carry = 0;
    }
    while (R.Len > 0 && R[R.Len - 1] ==  0) R.Len--;
    return R;
}
xnum operator*(const xnum& A, const int B)
{
    int I;
    if (B ==  0) return 0;
    xnum R;
    hugeint Carry =  0;
    for (I =  0; I < A.Len || Carry > 0; I++)
    {
        if (I < A.Len) Carry += hugeint(A[I])  * B;
        R[I]  = Carry % Base;
        Carry /= Base;
    }
    R.Len  = I;
    return R;
}
xnum operator*(const xnum& A, const xnum& B)
{
    int I;
    if (B.Len ==  0) return 0;
    xnum R;
    for (I =  0; I < A.Len; I++)
    {
        hugeint Carry = 0;
        for (int J =  0; J < B.Len || Carry >  0; J++)
        {
            if (J < B.Len) Carry += hugeint(A[I])  * B[J];
            if (I + J < R.Len) Carry += R[I + J];
            if (I + J >= R.Len) R[R.Len++]  = Carry % Base;
            else R[I + J] = Carry % Base;
            Carry /= Base;
        }
    }
    return R;
}
xnum operator/(const xnum& A, const int B)
{
    xnum  R;
    int I;
    hugeint C =  0;
    for (I = A.Len - 1; I >=  0; I--)
    {
        C = C * Base + A[I];
        R[I]  = C / B;
        C %= B;
    }
    R.Len = A.Len;
    while (R.Len > 0 && R[R.Len - 1] ==  0) R.Len--;
    return R;
}//div
xnum operator/(const xnum& A, const xnum& B)
{
    int I;
    xnum  R, Carry = 0;
    int Left, Right, Mid;
    for (I = A.Len - 1; I >=  0; I--)
    {
        Carry = Carry * Base + A[I];
        Left = 0;
        Right = Base - 1;
        while (Left < Right)
        {
            Mid = (Left + Right + 1) / 2;
            if (compare(B * Mid, Carry) <=  0) Left = Mid;
            else Right = Mid - 1;
        }
        R[I]  = Left;
        Carry = Carry - B * Left;
    }
    R.Len = A.Len;
    while (R.Len > 0 && R[R.Len - 1] ==  0) R.Len--;
    return R;
}//mod
xnum operator%(const xnum& A, const xnum& B)
{
    int I;
    xnum  R, Carry =  0;
    int Left, Right, Mid;
    for (I = A.Len - 1; I >=  0; I--)
    {
        Carry = Carry * Base + A[I];
        Left =  0;
        Right = Base - 1;
        while (Left < Right)
        {
            Mid =  (Left + Right +  1) / 2;
            if (compare(B * Mid, Carry) <=  0) Left = Mid;
            else Right = Mid - 1;
        }
        R[I]  = Left;
        Carry = Carry - B * Left;
    }
    R.Len = A.Len;
    while (R.Len > 0 && R[R.Len - 1] ==  0) R.Len--;
    return Carry;
}
istream& operator>>(istream& In, xnum& V)
{
    char Ch;
    for (V = 0; In >> Ch;)
    {
        V = V * 10 +  (Ch - '0');
        if (cin.peek() <= ' ') break;
    }
    return In;
}
ostream& operator<<(ostream& Out, const xnum& V)
{
    int I;
    Out <<  (V.Len ==  0 ? 0 : V[V.Len - 1]);
    for (I = V.Len - 2; I >=  0; I--)
        for (int J = Base / 10; J > 0; J /= 10) Out << V[I] / J % 10;
    return Out;
}
xnum gcd(xnum  a,xnum b)
{
    if(compare(b,0)==0)  return a;
    else return gcd(b,a%b);
}
int div(char *A,int B)
{
    int I;
    int C =  0;
    int Alen=strlen(A);
    for (I =  0; I <Alen; I++)
    {
        C = C * Base + A[I]-'0';
        C %= B;
    }
    return C;
}
xnum C(int n,int m)
{
    int i;
    xnum  sum = 1;
    for(i = n; i >= n-m+1; i --)sum = sum*i;
    for(i = 1; i <= m; i ++)sum  = sum/i;
    return  sum;
}
#define MAXN 9999
#define DLEN 4
class BigNum
{
private:
    int a[1000];//可以控制大数的位数int  len; //大数长度
public:
    BigNum()
    {
        len =  1;
        memset(a,0,sizeof(a));
    }
    BigNum(const  int);
    BigNum(const char*);
    BigNum(const  BigNum  &);
    BigNum  &operator=(const BigNum  &);
    BigNum  operator+(const BigNum  &) const;
    BigNum  operator-(const BigNum  &) const;
    BigNum  operator*(const BigNum  &) const;
    BigNum  operator/(const int    &) const;
    BigNum  operator^(const int   &) const;
    int operator%(const int  &) const;
    bool operator>(const BigNum  & T)const;
    void print();
};
BigNum::BigNum(const  int b)
{
    int c,d = b;
    len = 0;
    memset(a,0,sizeof(a));
    while(d > MAXN)
    {
        c = d - (d / (MAXN + 1)) * (MAXN + 1);
        d = d / (MAXN + 1);
        a[len++] = c;
    }
    a[len++]  = d;
}
BigNum::BigNum(const  char*s)
{
    int t,k,index,l,i;
    memset(a,0,sizeof(a));
    l=strlen(s);
    len=l/DLEN;
    if(l%DLEN)len++;
    index=0;
    for(i=l-1; i>=0; i-=DLEN)
    {
        t=0;
        k=i-DLEN+1;
        if(k<0)k=0;
        for(int j=k; j<=i; j++)t=t*10+s[j]-'0';
        a[index++]=t;
    }
}
BigNum::BigNum(const  BigNum  & T) : len(T.len)
{
    int i;
    memset(a,0,sizeof(a));
    for(i = 0 ; i < len ; i++)a[i]  = T.a[i];
}
BigNum  & BigNum::operator=(const  BigNum  & n)
{
    len = n.len;
    memset(a,0,sizeof(a));
    int  i;
    for(i = 0 ; i < len ; i++)a[i]  = n.a[i];
    return *this;
}
BigNum  BigNum::operator+(const BigNum  & T) const
{
    BigNum  t(*this);
    int i,big;//位数big  = T.len > len ? T.len : len;
    for(i = 0 ; i < big ; i++)
    {
        t.a[i] +=T.a[i];
        if(t.a[i] > MAXN)
        {
            t.a[i +  1]++;
            t.a[i] -=MAXN+1;
        }
    }
    if(t.a[big] !=  0) t.len = big + 1;
    else t.len = big;
    return t;
}
BigNum  BigNum::operator-(const BigNum  & T) const
{
    int i,j,big;
    bool flag;
    BigNum  t1,t2;
    if(*this>T)
    {
        t1=*this;
        t2=T;
        flag=0;
    }
    else
    {
        t1=T;
        t2=*this;
        flag=1;
    }
    big=t1.len;
    for(i = 0 ; i < big ; i++)
    {
        if(t1.a[i] < t2.a[i])
        {
            j = i +  1;
            while(t1.a[j]  ==  0) j++;
            t1.a[j--]--;
            while(j > i) t1.a[j--] += MAXN;
            t1.a[i] += MAXN + 1 - t2.a[i];
        }
        else t1.a[i] -= t2.a[i];
    }
    t1.len = big;
    while(t1.a[len - 1] ==  0 && t1.len > 1)
    {
        t1.len--;
        big--;
    }
    if(flag)t1.a[big-1]=0-t1.a[big-1];
    return t1;
}
BigNum  BigNum::operator*(const BigNum  & T) const
{
    BigNum  ret;
    int i,j,up;
    int temp,temp1;
    for(i = 0 ; i < len ; i++)
    {
        up = 0;
        for(j =  0 ; j < T.len ; j++)
        {
            temp = a[i] * T.a[j] + ret.a[i + j] + up;
            if(temp > MAXN)
            {
                temp1 = temp - temp / (MAXN +  1) * (MAXN +  1);
                up = temp / (MAXN +  1);
                ret.a[i + j] = temp1;
            }
            else
            {
                up = 0;
                ret.a[i + j] = temp;
            }
        }
        if(up !=  0)ret.a[i + j] = up;
    }
    ret.len = i + j;
    while(ret.a[ret.len - 1] ==  0 && ret.len >  1) ret.len--;
    return ret;
}
BigNum  BigNum::operator/(const int & b) const
{
    BigNum  ret;
    int i,down = 0;
    for(i = len - 1 ; i >=  0 ; i--)
    {
        ret.a[i] = (a[i] + down * (MAXN +  1)) / b;
        down = a[i] + down * (MAXN +  1) - ret.a[i] * b;
    }
    ret.len = len;
    while(ret.a[ret.len - 1] ==  0 && ret.len >  1) ret.len--;
    return ret;
}
int BigNum::operator  %(const int & b) const
{
    int i,d=0;
    for (i = len-1; i>=0; i--)
    {
        d =  ((d * (MAXN+1))% b + a[i])% b;
    }
    return d;
}
BigNum  BigNum::operator^(const int & n) const
{
    BigNum  t,ret(1);
    if(n<0)exit(-1);
    if(n==0)return  1;
    if(n==1)return  *this;
    int m=n;
    while(m>1)
    {
        t=*this;
        int i;
        for(i=1; i<<1<=m; i<<=1)
        {
            t=t*t;
        }
        m-=i;
        ret=ret*t;
        if(m==1)ret=ret*(*this);
    }
    return ret;
}
bool BigNum::operator>(const BigNum  & T) const
{
    int ln;
    if(len > T.len) return true;
    else if(len == T.len)
    {
        ln = len - 1;
        while(a[ln]  == T.a[ln] && ln >=  0) ln--;
        if(ln >=  0 && a[ln] > T.a[ln]) return true;
        else return false;
    }
    else return false;
}
void BigNum::print()
{
    int i;
    cout << a[len - 1];
    for(i = len - 2 ; i >=  0 ; i--)
    {
        cout.width(DLEN);
        cout.fill('0');
        cout << a[i];
    }
}//读取整数
const int ok =  1;
int get_val(int & ret)
{
    ret = 0;
    char ch;
    while ((ch=getchar()) > '9' || ch < '0')  ;
    do
    {
        ret = ret*10 + ch - '0';
    }
    while ((ch=getchar()) <= '9' && ch >= '0') ;
    return ok;
}//带负数
int get_val(int & ret)
{
    ret = 0;
    char ch;
    bool neg = false;
    while (((ch=getchar()) > '9' || ch < '0')  && ch!='-') ;
    if (ch == '-')
    {
        neg = true;
        while ((ch=getchar()) > '9' || ch < '0') ;
    }
    do
    {
        ret = ret*10 + ch - '0';
    }
    while ((ch=getchar()) <= '9' && ch >= '0') ;
    ret = (neg? -ret : ret);
    return ok;
}//读取整数,可判EOF和EOL
const int eof = -1;
const int eol = -2;
int get_val(int & ret)
{
    ret = 0;
    char ch;
    while (((ch=getchar()) > '9' || ch < '0')  && ch!=EOF)  ;
    if (ch == EOF) return eof;
    do
    {
        ret = ret*10 + ch - '0';
    }
    while ((ch=getchar()) <= '9' && ch >= '0') ;
    if (ch == '\n') return eol;
    return ok;
}//读取浮点数
int get_val(double & ret)
{
    ret = 0;
    double base =  0.1;
    char ch;
    bool dot = false, neg = false;
    while (((ch=getchar()) > '9' || ch < '0')  && ch != '.' && ch != '-') ;
    if (ch == '-')
    {
        neg = true;
        while (((ch=getchar()) > '9' || ch < '0') && ch != '.' && ch != '-') ;
    }
    do
    {
        if (ch == '.')
        {
            dot = true;
            continue;
        }
        if (dot)
        {
            ret +=  (ch-'0') * base;
            base *= 0.1;
        }
        else ret = ret*10 +  (ch-'0');
    }
    while (((ch=getchar()) <= '9' && ch >= '0') || ch == '.') ;
    ret =  (neg? -ret : ret);
    return ok;
}
