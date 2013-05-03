int solve(int a[],int b[],int n,int t)
{
	Matrix M,F,E;
	M.clear(),F.clear(),E.clear();
	M.n=M.m=n;
	E.n=E.m=n;
	F.n=F.m=n;
	for(int i=0;i<n-1;i++)
	{
		M.a[i][i+1]=1;
	}
	for(int i=0;i<n;++i)
	{
		M.a[n-1][i]=a[i];
		F.a[i][0]=b[i];
		E.a[i][i]=b[i];
	}
	if(t<n)
	{
		return F.a[t][0];
	}
	for(t-=n-1;t;t/=2)
	{
		if(t&1)
			E=M*E;
		M=M*M;
	}
	F=E*F;
	return F.a[n-1][0];
}
