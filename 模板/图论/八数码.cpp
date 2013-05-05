//八数码
/**** **** **** **** **** ****
*    Function Name :        八数码Eight(Special Judge)
*    Description :        搜索 + 状态hash
*    PKU(1077)         HDOJ(1043)         ZOJ(1217)
*    BFS            广搜        PKU(312ms)     HDOJ(TLE)        ZOJ(TLE)
*    BFS2        双向广搜    PKU(31ms)     HDOJ(1325ms)     ZOJ(TLE)
*  以上均是每次计算的运行耗时，ZOJ的可以全部计算后保存状态
**** **** **** **** **** ****/
#include <cstdio>
#include <string>
#include <memory>
#include <queue>
using namespace std;
char input[100];
int state[10], s_num, e10[10], fac_n[10];
char hash_T[400000], step[10000], hash_T2[400000];
struct inf
{
    int pos;
    char mode;
};
queue<int>  SQ;
queue<inf>  SQ2;
int num_pos(int  num,int x,int y)
{
    int temp=(x-1)*3+y;
    if(temp ==  num%10)     return 9;
    if(temp > num%10)     return (num / e10[9-temp+1])  %10;
    else    return (num / e10[9-temp] )%10;
}
int state_pos(int num,int x,int y)
{
    int temp=(x-1)*3+y;
    if(temp ==  state[9])    return 9;
    if(temp > state[9])    return state[temp-1];
    else    return state[temp];
}
inline int move(int num,char op)
{
    int t0,t1,t2;
    switch(op)
    {
    case 'r':
        if(num%10%3  ==  0)    return 0;
        return num+1;
    case 'l':
        if((num-1)%10%3  ==0)     return 0;
        return num-1;
    case 'u':
        if(num%10  -3 <=  0)    return 0;
        t0 = 9-num%10  + 1;
        t1 = num / e10[t0];
        t2 = t1%1000;
        t1= t1- t2 + (t2 % 100) * 10 + t2 / 100;
        t1*= e10[t0];
        return (t1 + ( (num % e10[t0]) - 3));
    case 'd':
        if(num%10  +3 > 9)    return 0;
        t0 = 9-num%10  + 1 -3;
        t1 = num / e10[t0];
        t2 = t1%1000;
        t1= t1- t2 + (t2 % 10) * 100 + t2 / 10;
        t1*= e10[t0];
        return (t1 + ( (num % e10[t0]) + 3));
    }
}
bool be_solved()
{
    int i,j,anti=0;
    for(i=1; i<=8; i++)
        for(j=1; j<i; j++)
            if( state[i] < state[j] ) anti++;
    if(anti%2)     return false;
    else          return true;
}
inline int hash(int num)
{
    int dig[10],i=9,j,sum,anti;
    if(num==0)     return -1;
    while(num)     dig[i]=num%10  , num/=10  , i-- ;
    sum=(9-dig[9])*fac_n[8];
    for(i=1; i<9; i++)
    {
        for(anti=0,j=1; j<i; j++)
            if(dig[i] < dig[j])anti++;
        sum += anti*fac_n[i-1];
    }
    return sum;
}
void BFS()
{
    int k,to_num,to_hash,i;
    memset(hash_T,0,sizeof(hash_T));
    while(!SQ.empty())    SQ.pop();
    SQ.push(123456789);
    hash_T[ hash(123456789)  ]='e';
    while(!SQ.empty())
    {
        k=SQ.front();
        SQ.pop();
        to_num=move(k,'r');
        to_hash=hash(to_num);
        if(to_hash>=0&&hash_T[to_hash]==0)
            hash_T[ to_hash]='r',SQ.push(to_num);
        to_num=move(k,'l');
        to_hash=hash(to_num);
        if(to_hash>=0  && hash_T[ to_hash ]==0)
            hash_T[ to_hash ]='l' , SQ.push(to_num);
        to_num=move(k,'u');
        to_hash=hash(to_num);
        if(to_hash>=0  && hash_T[ to_hash ]==0)
            hash_T[ to_hash ]='u' , SQ.push(to_num);
        to_num=move(k,'d');
        to_hash=hash(to_num);
        if(to_hash>=0  && hash_T[ to_hash ]==0)
            hash_T[ to_hash ]='d' , SQ.push(to_num);
    }
}
void BFS2()
{
    int to_num,to_hash,i;
    char *phash,*phash2;
    char op;
    inf k,t;
    memset(hash_T,0,sizeof(hash_T));
    memset(hash_T2,0,sizeof(hash_T2));
    while(!SQ2.empty())
    SQ2.pop();

    k.pos=s_num;
    k.mode=1;
    SQ2.push(k);
    k.pos=123456789;
    k.mode=2;
    SQ2.push(k);
    hash_T[hash(s_num)]='s';
    hash_T2[hash(123456789)  ]='e';
    while(!SQ2.empty())
    {
        k=SQ2.front();
        SQ2.pop();
        to_hash=hash(k.pos);
        if(k.mode==1)
            if(hash_T2[ to_hash ]!=0)    break;
            else    phash=hash_T,phash2=hash_T2;
        if(k.mode==2)
            if(hash_T[ to_hash ]!=0)    break;
            else    phash=hash_T2,phash2=hash_T;
        t=k;
        t.pos=move(k.pos,'r');
        to_hash=hash(t.pos);
        if(to_hash>=0  && phash[ to_hash ]==0)
            phash[to_hash]='r',SQ2.push(t);
        t.pos=move(k.pos,'l');
        to_hash=hash(t.pos);
        if(to_hash>=0  && phash[ to_hash ]==0)
            phash[ to_hash ]='l'  , SQ2.push(t);
        t.pos=move(k.pos,'u');
        to_hash=hash(t.pos);
        if(to_hash>=0  && phash[ to_hash ]==0)
            phash[ to_hash ]='u' , SQ2.push(t);
        t.pos=move(k.pos,'d');
        to_hash=hash(t.pos);
        if(to_hash>=0  && phash[ to_hash ]==0)
            phash[ to_hash ]='d' , SQ2.push(t);
    }
    i=0;
    to_hash = hash(k.pos);
    to_num  = k.pos;
    while( hash_T[ to_hash ] != 's' )
    {
        switch( step[i++]=hash_T[  to_hash ] )
        {
        case 'r':
            op='l';
            break;
        case 'l':
            op='r';
            break;
        case 'u':
            op='d';
            break;
        case 'd':
            op='u';
            break;
        }
        to_num=move(to_num,op);
        to_hash=hash(to_num);
    }
    while(i>0)
     printf("%c",step[--i]);
    to_hash=hash(k.pos);
    to_num=k.pos;
    while( hash_T2[ to_hash ]!='e' )
    {
        switch( hash_T2[ to_hash ] )
        {
        case 'r':
            op='l';
            break;
        case 'l':
            op='r';
            break;
        case 'u':
            op='d';
            break;
        case  'd':
            op='u';
            break;
        }
        printf("%c",op);
        to_num=move(to_num, op );
        to_hash=hash(to_num);
    }
}
int main()
{
    int i,j;
    for(e10[0]=1,i=1; i<=9; i++)e10[i]  =e10[i-1]*10;
    for(fac_n[0]=0,fac_n[1]=1,i=2; i<=9; i++)
      fac_n[i] =fac_n[i-1]*i;
    while( gets(input) )
    {
        for(i=strlen(input)-1,j=8; i>=0; i--)
        {
            if(input[i]!='  ')
            {
                if(input[i]=='x')state[9]=j+1;
                else state[j--]=input[i]-'0';
            }
        }
        for(s_num=0,i=9,j=1; i>0; i--,j*=10)
        s_num  +=  state[i]*j;

        if( !be_solved() )printf("unsolvable\n");
        else
        {
            BFS2();
            printf("\n");
        }
    }
}
