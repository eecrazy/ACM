const int maxn=100;

struct polygon()
{
	int n;
	point a[maxn];
	polygon (){}
	double perimeter()
	{
		double sum=0;
		s[n]=a[0];
		for(int i=0;i<n;i++)
			sum+=(a[i+1]-a[i]).norm();
		return sum;
		double area()
		{
			double sum=0;
			a[n]=a[0];
			for(int i=0;i<n;i++)
			{
				sum+=det(a[i+1],a[i]);
			}
			return sum/2;
		}
	}
	int Point_In(point t)
	{
		int num=0,i,d1,d2,k;
		a[n]=a[0];
		for(int i=0;i<n;i++)
		{
			if(PointOnSegment(t,a[i],a[i+1]))
			{
				return 2;
			}
			k=cmp(det(a[i+1]-a[i],t-a[i]));
			d1=cmp(a[i].y-t.y);
			d2=cmp(a[i+1].y-t.y);
			if(k>0&&d1<=0&&d2>0)num++;
			if(k<0&&d1<=0&&d2>0)num--;
		}
		return num!=0;
	}
	//重心
	point MassCenter()
	{
		point ans=point(0,0);
		if(cmp(area())==0)return ans;
		a[n]=a[0];
		for(int i=0;i<n;i++)
		{
			ans=ans+(a[i]+a[i+1])*det(a[i+1],a[i]);
		}
		return ans/area()/6.0;
	}
	//多边形内格点数
	int Border_Int_Point_Num()
	{
		int num=0;
		a[n]=a[0];
		for(int i=0;i<n;i++)
		{
			num+=gcd(abs(int(a[i+1].x-a[i].x)),abs(int(a[i+1].y-a[i].y)));
		}
		return num;
	}
	int Inside_Int_Point_num()
	{
		return int(area())+1-Border_Int_Point_Num()/2;
	}

};