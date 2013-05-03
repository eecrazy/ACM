//综合型很强
#include <cstdio>
#include <iostream>
using namespace std;
#define maxn 32
struct Ma
{
	int m[maxn][maxn];
};

Ma a,per;
int n,M;

void init()//矩阵初始化
{
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			scanf("%d",&a.m[i][j]);
			a.m[i][j]%=M;
			per.m[i][j]=(i==j);
		}
}

Ma add(Ma a,Ma b)//矩阵加法
{
	Ma c;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			c.m[i][j]=(a.m[i][j]+b.m[i][j])%M;
		}
	}
	return c;
}

Ma multi(Ma a,Ma b)//矩阵乘法
{
	Ma c;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			c.m[i][j]=0;
			for(int k=0;k<n;k++)
			{
				c.m[i][j]+=a.m[i][k]*b.m[k][j];
			}
			c.m[i][j]%=M;
		}
	return c;
}

Ma power(int k)//矩阵快速幂
{
	Ma c,p,ans=per;
	p=a;
	while(k)
	{
		if(k&1)
		{
			ans=multi(ans,p);
			k--;
		}
		k/=2;
		p=multi(p,p);
	}
	return ans;
}


Ma sum(int k)//幂相加
{
	if(k==1)
	{
		return a;
	}
	Ma tmp,b;
	tmp=sum(k/2);
	if(k&1)
	{
		b=power(k/2+1);
		tmp=add(tmp,multi(tmp,b));
		tmp=add(tmp,b);
	}
	else
	{
		b=power(k/2);
		tmp=add(tmp,multi(tmp,b));
	}
	return tmp;
}

int main()
{
	int k,i,j;
	while(scanf("%d%d%d",&n,&k,&M)!=EOF)
	{
		init();
		Ma ans=sum(k);
		for(i=0;i<n;i++)
		{
			for(j=0;j<n-1;j++)
			{
				printf("%d ",ans.m[i][j]);
			}
			printf("%d\n",ans.m[i][j]);
		}
	}
}
