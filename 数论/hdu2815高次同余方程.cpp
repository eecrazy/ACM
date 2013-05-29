/*hdu 2815 Mod Tree pku 3243 Clever Y
扩展Baby Step Giant Step

Baby Step Giant Step： A^X=B(mod C); C为素数。*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define INF 65535
int X,Y;
//int Hash[INF],val[INF];
struct hash{
    int a,b,next;
}Hash[INF << 1];
int flg[INF + 66];
int top,idx;
void ins(int a,int b){
    int k = b & INF;
    if(flg[k] != idx){
        flg[k] = idx;
        Hash[k].next = -1;
        Hash[k].a = a;
        Hash[k].b = b;
        return ;
    }
    while(Hash[k].next != -1){
        if(Hash[k].b == b) return ;
        k = Hash[k].next;
    }
    Hash[k].next = ++ top;
    Hash[top].next = -1;
    Hash[top].a = a;
    Hash[top].b = b;
}
int find(int b){
    int k = b & INF;
    if(flg[k] != idx) return -1;
    while(k != -1){
        if(Hash[k].b == b) return Hash[k].a;
        k = Hash[k].next;
    }
    return -1;
}

int gcd(int a,int b)
{
    int tmp;
    while(a%b)
    {
        tmp=a%b;
        a=b;
        b=tmp;
    }
    return b;
}
void extend_gcd(int a,int b)
{
    int X1,Y1;
    if(b==0)
    {
        X=1;
        Y=0;
        return;
    }
    extend_gcd(b,a%b);
    X1=Y;
    Y1=X-Y*(a/b);
    X=X1;
    Y=Y1;

}
int Inval(int a,int b,int n) // 求解方程a*x+b*y=n;
{
    int e;
    extend_gcd(a,b);
    e=(__int64)X*n%b;
    return e<0?e+b:e;
}
int pow_mod(int A,int m,int C)
{
    int mm,i;
    mm=1;
    for(i=1;i<=m;i++)
        mm=(__int64)mm*A%C;
    return mm;
}
int babystep(int A,int C,int B)
{
    int i,d,tmp,m,w,mm,ans;
    __int64 D;
    top = INF; ++ idx;
    d=0;
    D=1;
    ans=1;
    for(i=0;i<=100;i++)
    {
        if(ans==B) return i;
        ans=(__int64)ans*A%C;
    }
    tmp=gcd(A,C);
    while(tmp!=1)
    {
        if(B%tmp) return -1;
        ++d;
        C/=tmp;
        B/=tmp;
        D=D*A/tmp%C;
        tmp=gcd(A,C);
    }
    m=ceil(sqrt((double)C));
    ans=1;
    for(i=0;i<=m;i++)
    {
        ins(i,ans);
        ans=(__int64)ans*A%C;
    }
    mm=pow_mod(A,m,C); //A^m%C
    for(i=0;i<=m;i++) // mm^i
    {
        tmp=Inval((int)D,C,B);
        if(tmp>=0 && (w=find(tmp))!=-1) return i*m+w+d;
        D=D*mm%C;
    }
    return -1;
}
int main()
{
    int K,P,N,ans;
    while(scanf("%d%d%d",&K,&P,&N)!=EOF)
    {
        //if(K==0 && P==0 && N==0) break;
        if(N>=P) {printf("Orz,I can’t find D!\n");continue;}
        if(P==1)
        {
            if(N==0) printf("0\n");
            else printf("Orz,I can’t find D!\n");
            continue;
        }
        ans=babystep(K,P,N);
        if(ans==-1) printf("Orz,I can’t find D!\n");
        //if(ans==-1) printf("No Solution\n");
        else printf("%d\n",ans);
    }
    return 0;
}
