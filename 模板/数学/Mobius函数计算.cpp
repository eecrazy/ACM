const int n=1<<20;
int mu[n];
int getMu()
{
	for(int i=1;i<=n;i++)
	{
		int target=i==1?1:0;
		int delta=target-mu[i];
		mu[i]=delta;
		for(int j=i+i;j<=n;j+=i)
		{
			mu[j]+=delta;
		}
	}
}