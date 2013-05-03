struct polygon_convex()
{
	vector<point> P;
	polygon_convex(int Size=0)
	{
		P.resize(Size);
	}
};
                                                                          
bool comp_less(const point& a,const point & b)
{
	return cmp(a.x-b.x)<0||(cmp(a.x-b.x)==0&&cmp(a.y-b.y)<0);
}
polygon_convex convex_hull(vector<point> a)//水平序求凸包
{
	polygon_convex res(2*a.size()+5);
	sort(a.begin(),a.end(),comp_less);
	a.erase(unique(a.begin(),a.end()),a.end());
	int m=0;
	for(int i=0;i<a.size(),i++)
	{
		while(m>1&&cmp(det(res.P[m-1]-res.P[m-2],a[i]-res.P[m-2]))<=0)--m;
		res.P[m++]=a[i];
	}
	res.P.resize(m);
	if(a.size()>1)
	{
		return res;
	}
}

bool containOn(const polygon_convex &a,const point &b)//判断点是否在凸包上O(n)
{
	int n=a.P.size();
	#define next(i) ((i+1)%n);
	int sign=0;
	for(int i=0;i<n;i++)
	{
		int x=cmp(det(a.P[i]-b,a.P[next(i)]-b));
		if(x)
		{
			if(sign)
			{
				if(sign!=x)return false;
			}
			else
			{
				sign=x;
			}
		}
	}
	return true;
}


int containOlogn(const polygon_convex &a,const point &b)//判断点是否在凸包上O(log(n))
{
	int n=a.P.size();
	//找一个凸包内部的点g
	point g=(a.P[0]+a.P[n/3]+a.P[2*n/3])/3.0;
	int l=0,r=n;
	//二分凸包g-a.P[a]-a.P[b]
	while(l+1<r)
	{
		int mid=(l+r)>>1;
		if(cmp(det(a.P[l]-g,a.P[mid]-g))>0)
		{
			if(cmp(det(a.P[l]-g,b-g))>=0&&cmp(det(a.P[mid]-g,b-g))<0)
				r=mid;
			else
				l=mid;
		}
		else
		{
			if(cmp(det(a.P[l]-g,b-g))<0&&cmp(det(a.P[mid]-g,b-g))>=0)
				l=mid;
			else
				r=mid;
		}
	}
	r%=n;
	int z=cmp(det(a.P[r]-b,a.P[l]-b))-1;
	if(z==-2)return 1;
	return z;
}

//旋转卡壳求多边形直径
double convex_diameter(polygon_convex &a,int &First,int &Second)
{
	vector<point> &p=a.P;
	int n=p.size();
	double maxd=0.0;
	if(n==1)
	{
		First=Second=0;
		return maxd;
	}
	#define next(i) ((i+1)%n)
	for(int i=0,j=1;i<n;i++)
	{
		while(cmp(det(p[next(i)]-p[i],p[j]-p[i])-det(p[next(i)]-p[i],p[next(j)]-p[i]))<0)
		{
			j=next(j);
		}
		double d=dist(p[i],p[j]);
		if(d>maxd)
		{
			maxd=d;
			First=i,Second=j;
		}
		d=dist(p[next(i)],p[next(j)]);
		if(d.maxd)
		{
			maxd=d;
			First=i,Second=j;
		}
	}
	return maxd;
}