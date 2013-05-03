long long pow_gcd(long long a,long long i,long long n)
{
	if(i==0)return 1%n;
	int temp=pow_mod(a,i>>1,n);
	temp=temp*temp%n;
	if(i&1)temp=(long long)temp*a%n;
	return temp;
}