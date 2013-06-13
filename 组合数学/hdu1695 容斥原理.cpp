// 用到了欧拉函数,素因子分解,筛选法,组合数学上的容斥原理等,也不失为一道好题!!!

// 题目意思好懂,在[1...b]中选x,在[1....d]中选y,使gcd(x,y)=k,求不重复的对数

// 有一个小小的变形:在[1...b/k]中选x,在[1....d/k]中选y,使gcd(x,y)=k,求不重复的对数

// 我们让d>=b;　　然后在[1....d/k]进行枚举,对于每一个i,我们只要在1...min(i-1,b)中找到与i互质数,
// 记录个数,然后累加就得到结果了

// 当i<=b/k时,我们可以直接用欧拉函数计算出与i互质的个数　(当然要先进行因子分解,才能求欧拉函数)

// 当b/k<i<=d/k时,就比较难求了,我们用b/k减去与i不互质的数的个数得到,求与i不互质的数的个数时就用到
// 容斥原理,设i的素因子分别的p1,p2...pk,则1..b/k中p1的倍数组成集合A1,p2的倍数组成集合A2,p3到A3.....
// pk到Ak,　由于集合中会出现重复的元素,　所以用容斥原理来求A1并A2并A3.....并Ak的元素的数的个数.
#include <iostream>
using namespace std;
const int MAXN = 100005;
int a, b, c, d, k;
__int64 euler[MAXN];	//存放每个数的欧拉函数值；
int num[MAXN];			//存放当前数的素因子个数；
int primes[MAXN][10];	//存放当前数的素因子；
void EulerPrime()	//筛选法，求每个数的素数因子 和 每个数的欧拉函数值；
{
	int i, j;
	euler[1] = 1;
	for(i=2; i<MAXN; i++)
	{
		if( ! euler[i])
		{
			for(j=i; j<MAXN; j+=i)
			{
				if( ! euler[j])
					euler[j] = j;
				euler[j] = euler[j] * (i - 1) / i;
				primes[j][num[j]++] = i;
			}
		}
		euler[i] += euler[i-1];
	}
}
__int64 dfs(int x, int b, int now)	//求不大于b的数中与now不互质的数的个数；
{									//dfs()的容斥原理
	__int64 res = 0;
	for(int i=x; i<num[now]; i++)//容斥原理来求A1并A2并A3.....并Ak的元素的数的个数.
		res += b / primes[now][i] - dfs(i+1, b/primes[now][i], now);
	return res;
}
int main()
{
	int i, cs, t;
	__int64 ans;
	EulerPrime();
	while(scanf("%d",&t) != EOF)
	{
		for(cs=1; cs<=t; cs++)
		{
			printf("Case %d: ",cs);
			scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
			if(k == 0)
			{
				printf("0/n"); continue;
			}
			if(b > d)
				swap(b, d);
			b /= k; d /= k;
			ans = euler[b];	
			for(i=b+1; i<=d; i++)	//求 b+1—>d 之间
				ans += b - dfs(0, b, i);//0—>b 之间；用b减去与i不互质的数的个数得到
			printf("%I64d/n", ans);
		}
	}
	return 0;
}