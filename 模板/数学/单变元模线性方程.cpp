vector<long long>line_mod_equation(long long a,long long b,long long n)
{
	long long x,y;
	long long d=gcd(a,n,x,y);
	vector<long long> ans;
	ans.clear();
	if(b%d==0)
	{
		x%=n;
		x+=n;
		x%=n;
		ans.push_back(x*(b/d)%(n/d));
		for(long long i=1;i<d;++i)
		{
			ans.push_back((ans[0]+i*n.d)%n);
		}
	}
	return ans;
}