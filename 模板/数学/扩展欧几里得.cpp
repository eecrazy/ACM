int extend_gcd(int a,int b,int &x,int &y)
{
	if(b==0)
	{
		x=1;y=0;
		return a;
	}
	else
	{
		int r=extend_gcd(b,a%b,y,x);
		y-=x*(a/b);
		return r;
	}
}