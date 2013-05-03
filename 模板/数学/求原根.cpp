vector<long long>a;
bool g_test(long long g,long long p)
{
	for(long long i=1;i<a.size();i++)
	{
		if(pow_mod(g,(p-1)/a[i],p)==1)
			return 0;
	}
	return 1;
}

long long primitive(long long p)
{
	long long tmp=p-1;
	for(long long i=2;i<=tmp/i;i++)
	{
		if(tmp%i==0)
		{
			a/push_back(i);
			while(tmp%i==0)
			{
				tmp/=i;
			}
		}
	}
	if(tmp!=1)
	{
		a.push_back(tmp);
	}
	long long g=1;
	while(true)
	{
		if(g_test(g.p))
		return g;
		++g;
	}
}