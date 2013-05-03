求置换的循环节,polya 原理
//求置换的循环节,polya 原理
//perm[0..n-1]为0..n-1的一个置换(排列)
//返回置换最小周期,num 返回循环节个数
#define MAXN 1000

int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}

int polya(int*  perm,int n,int& num)
{
    int i,j,p,v[MAXN]= {0},ret=1;
    for (num=i=0; i<n; i++)
        if (!v[i])
        {
            for (num++,j=0,p=i; !v[p=perm[p]]; j++)
                v[p]=1;
            ret*=j/gcd(ret,j);
        }
    return ret;
}
