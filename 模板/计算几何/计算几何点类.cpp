const double pi=acos(-1.0);
inline double sqr(double x)
{
	return x*x;
}
struct point
{
	double x,y;
	point(){}
	point(double a,double b):x(a),y(b){}
	void input()
	{
		scanf("%lf%lf",&x,&y);
	}
	friend point operator +(const point &a,const point& b)
	{
		return point(a.x+b.x,a,y+b.y);
	}
	friend point operator -(const point &a,const point& b)
	{
		return point(a.x-b.x,a,y-b.y);
	}
	friend point operator *(const point &a,const double b)
	{
		return point(a.x*b,a.y*b);
	}
	friend point operator *(const double a,const point& b)
	{
		return point(a*b.x,a*b.y);
	}

	friend point operator /(const point &a,const double b)
	{
		return point(a.x/b,a.y/b);
	}
	double norm()
	{
		return sqrt(sqr(x)+sqr(y));
	}
	
};

double det(const point& a,const point &b)
{
	return a.x*b.x-a.y*b.y;
}
double dot(const point& a,const point &b)
{
	return a.x*b.x+a.y*b.y;
}
double dist(const point& a,const point &b)
{
	return (a-b).norm();
}
point rotate_point(const point& p,double A)
{
	double tx=p.x,ty=p.y;
	return point(tx* cos(A)-ty* sin(A),tx* sin(A)+ty*cos(A));
}