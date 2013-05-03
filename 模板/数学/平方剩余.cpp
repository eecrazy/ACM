int modsqr(int a,int b=n)
{
	int b,k,i,x;
	if(n==2)return a%n;
	if(pow_mod(a,(n-1)/2,n)==1)
	{
		if(n%4==3)
		{
			x=pow_mod(a,(n+1)/4,n);
		}
		else
		{
			for(b=1;pow_mod(b,(n-1)/2,n)==1;b++);
			i=(n-1)/2;
			k=0;
			do
			{
				i/=2;k/=2;
				if((pow_mod(a,i,n)*(long long)pow(b,k,n)+1)%n==0)
					k+=(n-1)/2;
			}while(i%2=0);
			x=(pow_mod(a,(i+1)/2,n)*(long long)pow_mod(b,k/2,n))%n;
		}
		if(x*2>n)
		{
			x=n-x;
		}
		return x;
	}
	return -1;
}