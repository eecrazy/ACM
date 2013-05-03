const max=111111;
int minDiv[max],phi[max],sum[max];
void genPhi()
{
	for(int i=1;i<max;i++)
	{
		minDiv[i]=i;
	}
	for(int i=2;i*i<max;i++)
	{
		if(minDiv[i]==i)
		{
			for(int j=i*i;j<max;j+=i)
			{
				minDiv[j]=i;
			}
		}
	}
	phi[1]=1;
	for(int i=2;i<max;++i)
	{
		phi[i]=phi[i/minDiv[i]];
		if((i/minDiv[i])%minDiv[i]==0)
		{
			phi[i]*=minDiv[i];
		}
		else
		{
			phi[i]*=minDiv[i]-1;
		}
	}
}