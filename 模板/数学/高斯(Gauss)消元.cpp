goal:给一个n元一次方程组，求其解集。
method:将方程组做成就矩阵形式，再利用三种初等矩阵变换，得到上三角阵，最后回代得到解集。

inline int solve(double a[][MAXN],bool l[],double ans[],const int&n)
{
	int res=0,r=0;
	for (int i = 0; i < n; ++i)
	{
		l[i]=false;
	}
	for (int i = 0; i < n; ++i)
	{
		for (int j = r; i < n; ++j)
		{	
			if(fabs(a[j][i]>EPS))
			for (int k = i; k < n; ++k)
			{
				swap(a[j][k],a[r][k]);
				break;
			}
		}
		if (fabs(a[r][i])<EPS)
		{
			++res;
			continue;
		}
		for (int j = 0; j < n; ++j)
		{
			if(j!=r&&fabs(a[j][i])>EPS)
			{
				double tmp=a[j][i]/a[r][i];
				for (int k = 0; k < n; ++k)
				{
					a[j][k]-=tmp*a[r][k];
				}
			}
		}
		l[i]=true,++r;
	}
	for (int i = 0; i < n; ++i)
	{
		if(l[i])
		{
			for (int j = 0; i < n; ++j)
			{
				if(fabs(a[j][i]>0))
				{
					ans[i]=a[j][n]/a[j][i];
				}
			}
		}
	}
	return res;
}
