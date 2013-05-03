//后缀数组
/**** **** **** **** **** ****
*      Function Name  :  后缀数组O(NLogN)
*      Description  :          PKU  2774  Long Long Message
**** **** **** **** **** ****/
#include <cstdio>
#include <string>
using namespace std;
const int MAX = 250000;
char txt[MAX];
int mem[3][MAX],  c[MAX], height[MAX];
int*SA,*nSA,*Rank,*nRank;
int  len,l1,l2;
//O(NlogN)
//SA[ rank  ] = who;
//Suffix(SA[i]) < Suffix(SA[i+1])  , 1≤i<n
//Rank[  who ] =  rank;
//k-Rank[i]代表加上满足Suffix(j)  <k  Suffix(i)的j的个数
void init()
{
    l1 =  strlen(txt);
    txt[l1] = 1;//特殊结尾
    gets(txt + l1+1);
    l2  = strlen(txt +  l1+1);
    len  =  l1 + l2+1;
    txt[len ++]  = 1; //特殊结尾
}
//性质.1 对k≥n ，Suffix(i)  <k  Suffix(j) 等价于Suffix(i)  < Suffix(j)
//性质.2 Suffix(i)  =2k  Suffix(j)  等价于
//Suffix(i)  =k  Suffix(j) 且Suffix(i+k)  =k  Suffix(j+k)
//性质.3 Suffix(i)  <2k  Suffix(j)  等价于
//Suffix(i)  <k  Suffix(j) 或(Suffix(i)  =k  Suffix(j) 且Suffix(i+k)  <k  Suffix(j+k))
void suffix_array()
{
    int i, j, k;
    SA = mem[0];
    nSA =  mem[1];
    Rank  =  mem[2];
    memset(c,  0, sizeof(c));
    for(i=0; i<len; i++)
    {
        c[ txt[i] ] ++;
    }
    for(i=0; i<128; i++)
    {
        c[i+1]  +=  c[i];
    }
    for(i=0; i<len; i++)
    {
        SA[ -- c[txt[i]] ] = i;
    }
    Rank[  SA[0] ] = 0;
    for(i=1; i<len; i++)
    {
        Rank[  SA[i] ] = Rank[  SA[i-1] ];
        if(txt[ SA[i] ] !=  txt[ SA[i-1] ])
        {
            Rank[  SA[i] ] ++;
        }
    }
    for(k=1; k<len  &&  Rank[SA[len-1]]<len-1; k* =2)
    {
        memset(c,  0, sizeof(c));
        for(i=0; i<len; i++)
        {
            c[ Rank[SA[i]]  ] ++;
        }
        for(i=1; i<len; i++)
        {
            c[i] +=  c[i-1];
        }
        for(i=len-1; i>=0; i--)
        {
            if(SA[i] >=  k)
            {
                nSA[ -- c[ Rank[SA[i]-k]  ] ] = SA[i] - k;
            }
        }
        for(i=len-k; i<len; i++)
        {
            nSA[ -- c[ Rank[i]  ] ] =  i;
        }
        nRank  = SA;
        nRank[  nSA[0] ] =  0;
        for(i=1; i<len; i++)
        {
            nRank[  nSA[i] ] = nRank[  nSA[i-1] ];
            if(Rank[nSA[i]]  !=  Rank[nSA[i-1]]  || Rank[nSA[i]+k]  !=
                    Rank[nSA[i-1]+k])
            {
                nRank[nSA[i]]  ++;
            }
        }
        SA =  nSA;
        nSA = Rank;
        Rank  =  nRank;
    }
}
//LCP(i,j)=lcp(Suffix(SA[i]),Suffix(SA[j])
//height[i]=LCP(i,i+1)，≤i<n
int getlcp()
{
    int i, j, k, rs;
    for (i = 0, k = 0; i <  len; i++)
    {
        if (Rank[i]  ==  len - 1)
        {
            height[Rank[i]]  =  k =  0;
        }
        else
        {
            if (k >  0)
            {
                k --;
            }
            j =  SA[Rank[i]  +1];
            while(txt[i +  k] ==  txt[j +  k])
            {
                k ++;
            }
            height[Rank[i]]  =  k;
        }
    }
    for (i = 0, rs = 0; i <  len - 1; i++)
    {
        if (rs <  height[i]  && (SA[i] <  l1) !=  (SA[i+1]  <  l1))
        {
            rs = height[i];
        }
    }
    int t =  min(l1,l2);
    return  min(t,  rs);
}
int main()
{
    gets(txt);
    init();
    suffix_array();
    printf("%d\n",  getlcp());
    return 0;
}
