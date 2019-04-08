//当n为long long 时, a * i 可能会溢出，使用ksm和ksc
long long pow_gcd(long long a,long long i,long long n)
{
	if(i==0)return 1%n;
	int temp=pow_mod(a,i>>1,n);
	temp=temp*temp%n;
	if(i&1)temp=(long long)temp*a%n;
	return temp;
}

ll ksc(ll a, ll b, ll c) {
    ll ret = 0;
    while(b > 0) {
        if (b&1) ret = (ret + a) % c;
        a = (a + a) % c;
        b >>= 1;
    }
    return ret;
}

ll ksm(ll a, ll b, ll c) {
    ll ret = 1;
    while(b > 0) {
        if (b & 1) ret = ksc(ret, a, c) % c;
        a = ksc(a, a, c) % c;
        b >>= 1;
    }
    return ret;
}
