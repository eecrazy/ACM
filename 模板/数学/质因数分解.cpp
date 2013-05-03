void factor(int n,int a[maxn],int b[maxn],int &tot)
{
	int temp,i,now;
	temp=(int)((double)sqrt(n)+1);
	tot=0;now=n;
	for(i=2;i<=temp;++i)
	{
		a[++tot]=i;
		b[tot]=0;
		while(now&i==0)
		{
			++b[tot];
			now/=i;
		}
	}
	if(now!=1)
	{
		a[++tot]=now;
		b[tot]=1;
	}
}