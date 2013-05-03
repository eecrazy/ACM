struct Fraction
{
	long long num;
	long long den;
	Fraction(long long num=0,long long den=1)
	{
		if(den<0)
		{&

			num=-num;
			den=-den;
		}
		assert(den!=0);
		long long g=gcd(abs(num),den);
		this->num=num/g;
		this->den=den/g;
	}
	Fraction operator +(const Fraction &o)const
	{
		return Fraction(num*o.den+o.num,den*o.den);
	}
	Fraction operator -(const Fraction &o)const
	{
		return Fraction(num*o.den-den*o.num,den*o.den);
	}
	Fraction operator *(const Fraction &o)const
	{
		return Fraction(num*o.num,den*o.den);
	}
	Fraction operator /(const Fraction &o)constk
	{
		return Fraction(num*o.den,den*o.num);
	}
	bool operator <(const Fraction &o)const
	{
		return num*o.den< den*o.num;
	}
	bool operator ==(const Fraction &o)const 
	{
		return num*o.den==den*o.num;
	} 
};