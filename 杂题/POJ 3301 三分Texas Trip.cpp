// POJ 3301 三分Texas Trip
// http://acm.pku.edu.cn/JudgeOnline/problem?id=3301
// 题意为给定n(n <= 30)个点，求出饱含这些点的面积最小的正方形。
// 有两种解法，一种为逼近法，就是每次m分角度，求出最符合的角度，再继续m分，
// 如此进行times次，即可求出较为精确的解。(m 大概取10, times取30即可)
// 第二种解法即为三分法，首先旋转的角度只要在0到180度即可，超过180度跟前面
// 的相同的。坐标轴旋转后，坐标变换为：
// X’ = x * cosa - y * sina;
// y’ = y * cosa + x * sina;
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
int n;
double x[35],y[35];
double getDis1(double d)
{
	double dis=0,t;
	for(int i=0;i<n-1;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			 t=fabs(cos(d)*(y[i]-y[j])+sin(d)*(x[i]-x[j]));
			 if(t>dis)
			 	dis=t;
		}
	}
	return dis;
}
double getDis2(double d)
{
	double dis=0,t;
	for(int i=0;i<n-1;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			 t=fabs(cos(d)*(x[i]-x[j])-sin(d)*(y[i]-y[j]));
			 if(t>dis)
			 	dis=t;
		}
	}
	return dis;
}
double gets(double a,double b)
{
	if(a>b)
		return a*a;
	else return b*b;
}
int main()
{
    //freopen("in.txt","r",stdin);
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			scanf("%lf%lf",&x[i],&y[i]);
		}
		double left=0.0,right=asin(1.0);
		double ans;
		double mid1,mid2,s1,s2;
		int size=50;
//		while(right - left >= 0.00000001)
        while(size--)
		{
			mid1=(left+right)/2;
			mid2=(mid1+right)/2;
			s1=gets(getDis1(mid1),getDis2(mid1));
			s2=gets(getDis1(mid2),getDis2(mid2));
			if(s1<s2)
			{
				right=mid2;
				ans=s1;
			}
			else
			{
				left=mid1;
				ans=s2;
			}
		}
		printf("%.2lf\n",ans);
	}
	return 0;
}
