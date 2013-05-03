//动态规划，矩阵快速幂。这道题什么意思？？
#include <stdio.h>
#include <string.h>
int n,MOD;
class Mat
{
public:
	int v[2][2];
	Mat(int x)//为什么这么初始化？？
	{
		memset(v,0,sizeof(v));
		if(x==1)
			v[0][0]=v[1][1]=v[1][0]=1,v[1][0]=0;
		
	}
	Mat friend operator*(const Mat& a,const Mat &b)//矩阵乘法
	{
		Mat c(0);
		int i,j,k;
		for( i=0;i<4;i++)
			for( j=0;j<4;j++)
			{
				for(k=0;k<4;k++)
				c.v[i][j]=(c.v[i][j]+a.v[i][k]*b.v[k][j]%MOD)%MOD;//边乘边取余
				if(c.v[i][j]<0)c.v[i][j]+=MOD;//小于mod加上一个mod
			}

		return c;
	}
};
void solve()
{
	int ans;
	Mat V(1),B(1);
	while(n)//矩阵快速幂
	{
		if(n&1)V=V*B;//如果n是奇数
		n>>=1;
		B=B*B;
	}
	printf("%d\n",V.v[0][0]);
}
int main()
{
	while(scanf("%d",&n)!=EOF&&n!=-1)
		solve();
	return 0;
}