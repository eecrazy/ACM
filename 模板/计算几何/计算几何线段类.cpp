struct line
{
	point a,b;
	line (){};
	line (point x,point y):a(x),b(y){}
};

line point_make_line(const point a,const point b)
{
	return line (a,b);
}

double dis_segment(const point p,const point s,const point t)
{
	if(cmp(dot(p-s,t-s))<0)return (p-s).norm();
	if(cmp(dot(p-t,s-t))<0)return (p-t).norm();
	return fabs(det(s-p,t-p)/dist(s,t));
}
void PointProjLine(const point p,point s,point t,point &cp)
{
	double r=dot((t-s),(p-s))/dot(t-s,p-s);
	cp=s+r*(t-s);
}

bool PointOnSegment(point p,point s, point t)
{
	return cmp(det(p-s,t-s))==0&&cmp(dot(p-s,p-t))<=0;
}
bool parallel()
{
	return !cmp(det(a.a-a.b,b.a-b.b));
}
bool line_make_point(line a,line b,point &res)
{
	if(parallel(a,b))return false;
	double s1=det(a.a-b.a,b.b-b.a);
	double s2=det(a.b-b.a,b.b-b.a);
	res=(s1*a.b-s2*a.a)/(s1-s2);
	return true;
}

line move_d(line a,const double &len)
{
	point d=a.b-a.a;
	d=d/d.norm();
	d=rotate_point(d,pi/2);
	return line(a.a+d*len,a.b+d*len);
}