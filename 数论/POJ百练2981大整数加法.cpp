#include <iostream>
#include <string.h>
#define DIGIT 4
#define DEPTH 10000
#define MAX 300
using namespace std;
typedef int bignum[MAX+1];
int read(bignum a,istream& is=cin)//输入函数
{
    char buf[MAX*DIGIT+1],ch;
    int i,j;
    memset((void*)a,0,sizeof(bignum));
    if (!(is>>buf)) return 0;
    for (a[0]=strlen(buf),i=a[0]/2-1; i>=0; i--)
        ch=buf[i],buf[i]=buf[a[0]-1-i],buf[a[0]-1-i]=ch;
    for (a[0]=(a[0]+DIGIT-1)/DIGIT,j=strlen(buf); j<a[0]*DIGIT; buf[j++]='0');
    for (i=1; i<=a[0]; i++)
        for (a[i]=0,j=0; j<DIGIT; j++)
            a[i]=a[i]*10+buf[i*DIGIT-1-j]-'0';
    for (; !a[a[0]]&&a[0]>1; a[0]--);
    return 1;
}
void write(const bignum a,ostream& os=cout)//写函数
{
    int i,j;
    for (os<<a[i=a[0]],i--; i; i--)
        for (j=DEPTH/10; j; j/=10)
            os<<a[i]/j%10;
}
int comp(const bignum a,const bignum b)//比较函数
{
    int i;
    if (a[0]!=b[0])
        return a[0]-b[0];
    for (i=a[0]; i; i--)
        if (a[i]!=b[i])
            return a[i]-b[i];
    return 0;
}
int comp(const bignum a,const int b)//比较函数
{
    int c[12]= {1};
    for (c[1]=b; c[c[0]]>=DEPTH; c[c[0]+1]=c[c[0]]/DEPTH,c[c[0]]%=DEPTH,c[0]++);
    return comp(a,c);
}
int comp(const bignum a,const int c,const int d,const bignum b)
{
    int i,t=0,O=-DEPTH*2;
    if (b[0]-a[0]<d&&c)
        return 1;
    for (i=b[0]; i>d; i--)
    {
        t=t*DEPTH+a[i-d]*c-b[i];
        if (t>0) return 1;
        if (t<O) return 0;
    }
    for (i=d; i; i--)
    {
        t=t*DEPTH-b[i];
        if (t>0) return 1;
        if (t<O) return 0;
    }
    return t>0;
}
void add(bignum a,const bignum b)//加法
{
    int i;
    for (i=1; i<=b[0]; i++)
        if ((a[i]+=b[i])>=DEPTH)
            a[i]-=DEPTH,a[i+1]++;
    if (b[0]>=a[0])
        a[0]=b[0];
    else
        for (; a[i]>=DEPTH&&i<a[0]; a[i]-=DEPTH,i++,a[i]++);
    a[0]+=(a[a[0]+1]>0);
}
void add(bignum a,const int b)//加法
{
    int i=1;
    for (a[1]+=b; a[i]>=DEPTH&&i<a[0]; a[i+1]+=a[i]/DEPTH,a[i]%=DEPTH,i++);
    for (; a[a[0]]>=DEPTH; a[a[0]+1]=a[a[0]]/DEPTH,a[a[0]]%=DEPTH,a[0]++);
}
void sub(bignum a,const bignum b)//减法
{
    int i;
    for (i=1; i<=b[0]; i++)
        if ((a[i]-=b[i])<0)
            a[i+1]--,a[i]+=DEPTH;
    for (; a[i]<0; a[i]+=DEPTH,i++,a[i]--);
    for (; !a[a[0]]&&a[0]>1; a[0]--);
}
void sub(bignum a,const int b)//减法
{
    int i=1;
    for (a[1]-=b; a[i]<0; a[i+1]+=(a[i]-DEPTH+1)/DEPTH,a[i]-=(a[i]-DEPTH+1)/DEPTH*DEPTH,i++);
    for (; !a[a[0]]&&a[0]>1; a[0]--);
}
void sub(bignum a,const bignum b,const int c,const int d)//减法
{
    int i,O=b[0]+d;
    for (i=1+d; i<=O; i++)
        if ((a[i]-=b[i-d]*c)<0)
            a[i+1]+=(a[i]-DEPTH+1)/DEPTH,a[i]-=(a[i]-DEPTH+1)/DEPTH*DEPTH;
    for (; a[i]<0; a[i+1]+=(a[i]-DEPTH+1)/DEPTH,a[i]-=(a[i]-DEPTH+1)/DEPTH*DEPTH,i++);
    for (; !a[a[0]]&&a[0]>1; a[0]--);
}
void mul(bignum c,const bignum a,const bignum b)//乘法
{
    int i,j;
    memset((void*)c,0,sizeof(bignum));
    for (c[0]=a[0]+b[0]-1,i=1; i<=a[0]; i++)
        for (j=1; j<=b[0]; j++)
            if ((c[i+j-1]+=a[i]*b[j])>=DEPTH)
                c[i+j]+=c[i+j-1]/DEPTH,c[i+j-1]%=DEPTH;
    for (c[0]+=(c[c[0]+1]>0); !c[c[0]]&&c[0]>1; c[0]--);
}
void mul(bignum a,const int b)//乘法
{
    int i;
    for (a[1]*=b,i=2; i<=a[0]; i++)
    {
        a[i]*=b;
        if (a[i-1]>=DEPTH)
            a[i]+=a[i-1]/DEPTH,a[i-1]%=DEPTH;
    }
    for (; a[a[0]]>=DEPTH; a[a[0]+1]=a[a[0]]/DEPTH,a[a[0]]%=DEPTH,a[0]++);
}
void mul(bignum b,const bignum a,const int c,const int d)//乘法
{
    int i;
    memset((void*)b,0,sizeof(bignum));
    for (b[0]=a[0]+d,i=d+1; i<=b[0]; i++)
        if ((b[i]+=a[i-d]*c)>=DEPTH)
            b[i+1]+=b[i]/DEPTH,b[i]%=DEPTH;
    for (; b[b[0]+1]; b[0]++,b[b[0]+1]=b[b[0]]/DEPTH,b[b[0]]%=DEPTH);
    for (; !b[b[0]]&&b[0]>1; b[0]--);
}
void div(bignum c,bignum a,const bignum b)//除法
{
    int h,l,m,i;
    memset((void*)c,0,sizeof(bignum));
    c[0]=(b[0]<a[0]+1)?(a[0]-b[0]+2):1;
    for (i=c[0]; i; sub(a,b,c[i]=m,i-1),i--)
        for (h=DEPTH-1,l=0,m=(h+l+1)>>1; h>l; m=(h+l+1)>>1)
            if (comp(b,m,i-1,a)) h=m-1;
            else l=m;
    for (; !c[c[0]]&&c[0]>1; c[0]--);
    c[0]=c[0]>1?c[0]:1;
}
void div(bignum a,const int b,int& c)//除法
{
    int i;
    for (c=0,i=a[0]; i; c=c*DEPTH+a[i],a[i]=c/b,c%=b,i--);
    for (; !a[a[0]]&&a[0]>1; a[0]--);
}
void sqrt(bignum b,bignum a)//开根号
{
    int h,l,m,i;
    memset((void*)b,0,sizeof(bignum));
    for (i=b[0]=(a[0]+1)>>1; i; sub(a,b,m,i-1),b[i]+=m,i--)
        for (h=DEPTH-1,l=0,b[i]=m=(h+l+1)>>1; h>l; b[i]=m=(h+l+1)>>1)
            if (comp(b,m,i-1,a)) h=m-1;
            else l=m;
    for (; !b[b[0]]&&b[0]>1; b[0]--);
    for (i=1; i<=b[0]; b[i++]>>=1);
}
int length(const bignum a)//长度
{
    int t,ret;
    for (ret=(a[0]-1)*DIGIT,t=a[a[0]]; t; t/=10,ret++);
    return ret>0?ret:1;
}
int digit(const bignum a,const int b)
{
    int i,ret;
    for (ret=a[(b-1)/DIGIT+1],i=(b-1)%DIGIT; i; ret/=10,i--);
    return ret%10;
}
int zeronum(const bignum a)
{
    int ret,t;
    for (ret=0; !a[ret+1]; ret++);
    for (t=a[ret+1],ret*=DIGIT; !(t%10); t/=10,ret++);
    return ret;
}
void comp(int* a,const int l,const int h,const int d)
{
    int i,j,t;
    for (i=l; i<=h; i++)
        for (t=i,j=2; t>1; j++)
            while (!(t%j))
                a[j]+=d,t/=j;
}
void convert(int* a,const int h,bignum b)
{
    int i,j,t=1;
    memset(b,0,sizeof(bignum));
    for (b[0]=b[1]=1,i=2; i<=h; i++)
        if (a[i])
            for (j=a[i]; j; t*=i,j--)
                if (t*i>DEPTH)
                    mul(b,t),t=1;
    mul(b,t);
}
void combination(bignum a,int m,int n)
{
    int* t=new int[m+1];
    memset((void*)t,0,sizeof(int)*(m+1));
    comp(t,n+1,m,1);
    comp(t,2,m-n,-1);
    convert(t,m,a);
    delete []t;
}
void permutation(bignum a,int m,int n)
{
    int i,t=1;
    memset(a,0,sizeof(bignum));
    a[0]=a[1]=1;
    for (i=m-n+1; i<=m; t*=i++)
        if (t*i>DEPTH)
            mul(a,t),t=1;
    mul(a,t);
}
#define SGN(x) ((x)>0?1:((x)<0?-1:0))
#define ABS(x) ((x)>0?(x):-(x))
int read(bignum a,int &sgn,istream& is=cin)
{
    char str[MAX*DIGIT+2],ch,*buf;
    int i,j;
    memset((void*)a,0,sizeof(bignum));
    if (!(is>>str)) return 0;
    buf=str,sgn=1;
    if (*buf=='-') sgn=-1,buf++;
    for (a[0]=strlen(buf),i=a[0]/2-1; i>=0; i--)
        ch=buf[i],buf[i]=buf[a[0]-1-i],buf[a[0]-1-i]=ch;
    for (a[0]=(a[0]+DIGIT-1)/DIGIT,j=strlen(buf); j<a[0]*DIGIT; buf[j++]='0');
    for (i=1; i<=a[0]; i++)
        for (a[i]=0,j=0; j<DIGIT; j++)
            a[i]=a[i]*10+buf[i*DIGIT-1-j]-'0';
    for (; !a[a[0]]&&a[0]>1; a[0]--);
    if (a[0]==1&&!a[1]) sgn=0;
    return 1;
}

int main()
{
    bignum a,b,c;
    read(a);
    read(b);
    add(a,b);
    mul(c,a,b);
    write(a);

return 0;
}
