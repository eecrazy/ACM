// 关于RMQ的ST算法，以前也大略上看过，也写过程序，可是后来时间长了就忘记了，
// 今天再看到，觉得并没有以前觉得的那么难理解。唉。毕竟以前弱。虽然现在也蒟蒻。
// ST算法的原理就是，nlogn预处理出Min[][]和Max[][]，查询的时候O(1)查询。
// Max[j][i]或Min[j][i]代表，从j的位置开始，长度为2^i的子段中的最大值或最小值。
// 然后预处理的时候递推。
// 询问的时候先算出[l,r]的长度的2的对数，然后取出答案即可。
// 下面贴代码，程序中Min[][],Max[][]存的是最小值最大值的位置，如果这个区间有两个最小值，则保留靠左的那个。查询的时候，若q为0代表查询最小值，q为1代表查询最大值。
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;
#define mx 100010
int Min[mx][20],Max[mx][20],n,m,a[mx];
void makermq()
{
    for (int i = 1; i <= n; i ++) Min[i][0] = Max[i][0] = i;

    for (int i = 1; (1 << i) <= n; i ++)
    {
        for(int j = 1; j + (1 << i) - 1 <= n; j ++)
        {
            int p = Min[j][i - 1],q = Min[j + (1 << i - 1)][i - 1];
            if (a[p] < a[q] || (a[p] == a[q] && p < q)) Min[j][i] = p;
            else Min[j][i] = q;
            p = Max[j][i - 1],q = Max[j + (1 << i - 1)][i - 1];
            if (a[p] > a[q] || (a[p] == a[q] && p < q)) Max[j][i] = p;
            else Max[j][i] = q;
        }
    }
}
int ask(int l,int r,int q)
{
    int tmp = int(log(r - l + 1) / log(2));
    int k1,k2;
    if (q == 0)
    {
        k1 = Min[l][tmp],k2 = Min[r - (1 << tmp) + 1][tmp];
        if (a[k1] < a[k2] || (a[k1] == a[k2] && k1 < k2)) return k1;
        else return k2;
    }
    else
    {
        k1 = Max[l][tmp],k2 = Max[r - (1 << tmp) + 1][tmp];
        if (a[k1] > a[k2] || (a[k1] == a[k2] && k1 < k2)) return k1;
        else return k2;
    }
}
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    makermq();
    int l,r,q;
    for (int i = 1; i <= m; i ++)
    {
        cin >> l >> r >> q;
        cout << ask(l,r,q) << endl;
    }
}
// ++++++++++++++++++++++++++++++++++++++++++++
#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;
#define maxn 50001

int a[maxn];
int dpmax[maxn][40];
int dpmin[maxn][40];

int getmin(int a,int b)
{
    if(a<b) return a;
    else    return b;
}
int getmax(int a,int b)
{
    if(a>b) return a;
    else    return b;
}
void Make_Big_RMQ(int n)
{
    int i,j;
    for(i=1;i<=n;i++) dpmax[i][0]=a[i];
    for(j=1;j<=log((double)n)/log(2.0);j++)
        for(i=1;i+(1<<j)-1<=n;i++)
        {
            dpmax[i][j]=getmax(dpmax[i][j-1],dpmax[i+(1<<(j-1))][j-1]);
        }
}
void Make_Min_RMQ(int n)
{
    int i,j;
    for(i=1;i<=n;i++) dpmin[i][0]=a[i];
    for(j=1;j<=log((double)n)/log(2.0);j++)
        for(i=1;i+(1<<j)-1<=n;i++)
        {
            dpmin[i][j]=getmin(dpmin[i][j-1],dpmin[i+(1<<(j-1))][j-1]);
        }
}

int get_big_rmq(int a,int b)
{
    int k=(int)(log((double)(b-a+1))/log(2.0));
    return getmax(dpmax[a][k],dpmax[b-(1<<k)+1][k]);
}
int get_min_rmq(int a,int b)
{
    int k=(int)(log((double)(b-a+1))/log(2.0));
    return getmin(dpmin[a][k],dpmin[b-(1<<k)+1][k]);
}
int main()
{
    int n,i,q,x,y;
    while(scanf("%d %d",&n,&q)!=EOF)
    {
        for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
        Make_Big_RMQ(n);

        Make_Min_RMQ(n);

        for(i=1;i<=q;i++)
        {
            scanf("%d%d",&x,&y);
            printf("%d\n",get_big_rmq(x,y)-get_min_rmq(x,y));
        }

    }
    return 0;
}
// +++++++++++++++++++++++++++++++++++++++++++++
ST算法（Sparse Table）:它是一种动态规划的方法。 
以最小值为例。a为所寻找的数组. 
用一个二维数组f(i,j)记录区间[i,i+2^j-1](持续2^j个)区间中的最小值。其中f[i,0] = a[i]; 
所以，对于任意的一组(i,j)，f(i,j) = min{f(i,j-1),f(i+2^(j-1),j-1)}来使用动态规划计算出来。 
这个算法的高明之处不是在于这个动态规划的建立，而是它的查询：它的查询效率是O(1). 
假设我们要求区间[m,n]中a的最小值，找到一个数k使得2^k<n-m+1. 
这样，可以把这个区间分成两个部分：[m,m+2^k-1]和[n-2^k+1,n].我们发现，这两个区间是已经初始化好的. 
前面的区间是f(m,k)，后面的区间是f(n-2^k+1,k). 
这样，只要看这两个区间的最小值，就可以知道整个区间的最小值！ 
Cpp代码  
#include<iostream>  
#include<cmath>  
#include<algorithm>  
using namespace std;  
  
#define M 100010  
#define MAXN 500  
#define MAXM 500  
int dp[M][18];  
/* 
*一维RMQ ST算法 
*构造RMQ数组 makermq(int n,int b[]) O(nlog(n))的算法复杂度 
*dp[i][j] 表示从i到i+2^j -1中最小的一个值(从i开始持续2^j个数) 
*dp[i][j]=min{dp[i][j-1],dp[i+2^(j-1)][j-1]} 
*查询RMQ rmq(int s,int v) 
*将s-v 分成两个2^k的区间 
*即 k=(int)log2(s-v+1) 
*查询结果应该为 min(dp[s][k],dp[v-2^k+1][k]) 
*/  
  
void makermq(int n,int b[])  
{  
    int i,j;  
    for(i=0;i<n;i++)  
        dp[i][0]=b[i];  
    for(j=1;(1<<j)<=n;j++)  
        for(i=0;i+(1<<j)-1<n;i++)  
            dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);  
}  
int rmq(int s,int v)  
{  
    int k=(int)(log((v-s+1)*1.0)/log(2.0));  
    return min(dp[s][k],dp[v-(1<<k)+1][k]);  
}  
  
void makeRmqIndex(int n,int b[]) //返回最小值对应的下标  
{  
    int i,j;  
    for(i=0;i<n;i++)  
        dp[i][0]=i;  
    for(j=1;(1<<j)<=n;j++)  
        for(i=0;i+(1<<j)-1<n;i++)  
            dp[i][j]=b[dp[i][j-1]] < b[dp[i+(1<<(j-1))][j-1]]? dp[i][j-1]:dp[i+(1<<(j-1))][j-1];  
}  
int rmqIndex(int s,int v,int b[])  
{  
    int k=(int)(log((v-s+1)*1.0)/log(2.0));  
    return b[dp[s][k]]<b[dp[v-(1<<k)+1][k]]? dp[s][k]:dp[v-(1<<k)+1][k];  
}  
  
int main()  
{  
    int a[]={3,4,5,7,8,9,0,3,4,5};  
    //返回下标  
    makeRmqIndex(sizeof(a)/sizeof(a[0]),a);  
    cout<<rmqIndex(0,9,a)<<endl;  
    cout<<rmqIndex(4,9,a)<<endl;  
    //返回最小值  
    makermq(sizeof(a)/sizeof(a[0]),a);  
    cout<<rmq(0,9)<<endl;  
    cout<<rmq(4,9)<<endl;  
    return 0;  
}  

// ++++++++++++++++++++++++++++++++++++
RMQ (Range Minimum/Maximum Query)问题是指：对于长度为n的数列A，回答若干询问RMQ(A,i,j)(i,j<=n)，返回数列A中下标在[i,j]里的最小(大）值，也就是说，RMQ问题是指求区间最值的问题 

主要方法及复杂度(处理复杂度和查询复杂度)如下: 
1.朴素（即搜索） O(n)-O(n) 
2.线段树(segment tree) O(n)-O(qlogn) 
3.ST（实质是动态规划） O(nlogn)-O(1) 

线段树方法: 
线段树能在对数时间内在数组区间上进行更新与查询。 
定义线段树在区间[i, j] 上如下： 
第一个节点维护着区间 [i, j] 的信息。 
if i<j , 那么左孩子维护着区间[i, (i+j)/2] 的信息，右孩子维护着区间[(i+j)/2+1, j] 的信息。 
可知 N  个元素的线段树的高度 为 [logN] + 1(只有根节点的树高度为0) . 
下面是区间 [0, 9]  的一个线段树: 

线段树和堆有一样的结构, 因此如果一个节点编号为 x ，那么左孩子编号为2*x  右孩子编号为2*x+1. 
使用线段树解决RMQ问题，关键维护一个数组M[num]，num=2^(线段树高度+1). 
M[i]:维护着被分配给该节点(编号:i 线段树根节点编号:1)的区间的最小值元素的下标。 该数组初始状态为-1. 
Cpp代码  
#include <iostream>    
using namespace std;  
#define MAXN 100  
#define MAXIND 256 //线段树节点个数  
  
//构建线段树,目的:得到M数组.  
void initialize(int node, int b, int e, int M[], int A[])  
{  
    if (b == e)  
        M[node] = b; //只有一个元素,只有一个下标  
    else  
    {  
    //递归实现左孩子和右孩子  
        initialize(2 * node, b, (b + e) / 2, M, A);  
        initialize(2 * node + 1, (b + e) / 2 + 1, e, M, A);  
    //search for the minimum value in the first and  
    //second half of the interval  
    if (A[M[2 * node]] <= A[M[2 * node + 1]])  
        M[node] = M[2 * node];  
    else  
        M[node] = M[2 * node + 1];  
    }  
}  
//找出区间 [i, j] 上的最小值的索引  
int query(int node, int b, int e, int M[], int A[], int i, int j)  
{  
    int p1, p2;  
    //查询区间和要求的区间没有交集  
    if (i > e || j < b)  
        return -1;  
    //if the current interval is included in  
    //the query interval return M[node]  
    if (b >= i && e <= j)  
        return M[node];  
    //compute the minimum position in the  
    //left and right part of the interval  
    p1 = query(2 * node, b, (b + e) / 2, M, A, i, j);  
    p2 = query(2 * node + 1, (b + e) / 2 + 1, e, M, A, i, j);  
    //return the position where the overall  
    //minimum is  
    if (p1 == -1)  
        return M[node] = p2;  
    if (p2 == -1)  
        return M[node] = p1;  
    if (A[p1] <= A[p2])  
        return M[node] = p1;  
    return M[node] = p2;  
} 
int main()  
{  
    int M[MAXIND]; //下标1起才有意义,保存下标编号节点对应区间最小值的下标.  
    memset(M,-1,sizeof(M));  
    int a[]={3,1,5,7,2,9,0,3,4,5};  
    initialize(1, 0, sizeof(a)/sizeof(a[0])-1, M, a);  
    cout<<query(1, 0, sizeof(a)/sizeof(a[0])-1, M, a, 0, 5)<<endl;  
    return 0;  
}  