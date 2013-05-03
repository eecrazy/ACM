void intToArray(int x,int a[maxn])
{
	bool used[maxn];
	int i,j,temp;
	for(i=1;i<=n;i++)used[i]=false;
	for(i=1;i<=n;++i)
	{
		temp=x/factorial[n-i];
		for(j=1;j<=n;++j)
		{
			if(!used[j])
			{
				if(temp==0)break;
				--temp;
			}
		}
		a[i]=j;
		used[j]=true;
		x%=factorial[n-i];
	}
}

int arrayToInt(int a[maxn])
{
	int ans,i,j,temp;
	for(i=1;i<=n;i++)
	{
		temp=a[i]-1;
		for(j=1;j<i;j++)
		{
			if(a[j]<a[i])--temp;
			ans+=factorial[n-i]*temp;
		}
	}
	return ans;
}