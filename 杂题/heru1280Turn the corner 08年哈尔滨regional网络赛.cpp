// http://acm.hrbeu.edu.cn/index.php?act=problem&id=1280
// 汽车拐弯问题，给定X, Y, l, d判断是否能够拐弯。
// 首先当X或者Y小于d，那么一定不能。
// 其次我们发现随着角度θ的增大，最大高度ｈ先增长后减小，
// 即为凸性函数，可以用三分法来求解。
// 这里的Calc函数需要比较繁琐的推倒公式：
// s = l * cos(θ) + w * sin(θ) - x;
// h = s * tan(θ) + w * cos(θ);
// 其中s为汽车最右边的点离拐角的水平距离, h为里拐点最高的距离, 
// θ范围从0到90。
#include <cstdio>
#include <cmath>
using namespace std;
double x,y,l,w;
#define eps 1e-8
double geth(double d)
{
	double	s = l * cos(d) + w * sin(d) - x;
	double  h = s * tan(d) + w * cos(d);
	return h;
}
int main()
{
	while(scanf("%lf%lf%lf%lf",&x,&y,&l,&w)!=EOF)
	{
		if(x<w||y<w)
		{
			printf("no\n");
			continue;
		}
		double left=0,right=asin(1.0);
		double mid1,mid2,h1,h2;
		int size=50;
		while(size--)
		{
			mid1=(left+right)/2;
			mid2=(mid1+right)/2;
			h1=geth(mid1);
			h2=geth(mid2);
			if(h1<h2)
				left=mid1;
			else
				right=mid2;
		}
		h1=geth(left);
		//printf("%lf\n",h1);
		if(h1+eps<y)
			printf("yes\n");
		else
			printf("no\n");
	}
}
