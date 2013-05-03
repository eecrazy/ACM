//典型的佩尔方程
#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
	int x,y,x1,y1,px,py,d;
	x1=3;
	y1=1;
	px=3;
	py=1;
	d=8;
	for(int i=1;i<=10;i++)
	{
		x=px*x1+d*py*y1;
		y=px*y1+py*x1;
		printf("%10d%10d\n",y,(x-1)/2);
		px=x;py=y;
	}
	return 0;
}