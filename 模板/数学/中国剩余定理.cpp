int CRT(int a[],int m[],int n[])
{
	int M=1;
	for(int i=0;i<n;i++)
		M*=m[i];
	int ret=0;
	for(int i=0;i<n;i++)
	{
			int x,y;
			int tm=M/m[i];
			extend_gcd(tm,m[i],x,y);
			ret=(ret+tm*x*a[i])%M;
	}
	return (ret+M)%M;
}