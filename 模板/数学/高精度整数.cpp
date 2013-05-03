const int ten[4]={1,10,100.1000};
const int maxl=1000;
struct BigNumber
{
	int d[maxl];
	BigNumber (string s)
	{
		int len=s.size();
		d[0]=(len-1)/4+1;
		int i,j,k;
		for(i=1;i<maxl;i++)d[i]=0;
		for(i=len-1;i>=0;i--)
		{
			j=(len-i-1)/4+1；
			k=(len-i-1)%4;
			d[j]+=ten[k]*(s[i]-'0');

		}
		while(d[0]>1&&d[d[0]]==0)--d[0];
	}
	BigNumber()
	{
		*this=BigNumber(string("0"));
	}
	string toString()
	{
		string  s("");
		int i,j,temp;
		for(i=3;i>=1;--i)
		{
			if(d[d[0]]>=ten[i])
				break;
		}
		temp=d[d[0]];
		for(j=i;j>=0;--j)
		{
			s=s+(char)(temp/ten[j]+'0');
			temp%=ten[j];
		}
		for(i=d[0]-1;i>0;--i)
		{
			temp=d[i];
			for(j=3;j>=0;--j)
			{
				s=s+(char)(temp/ten[j]+'0');
				temp%=ten[j];
			}
		}
		return s;
	}
}zero("0"),d,temp,mid1[15];

bool operator <(const BigNumber &a,const BigNumber &b)
{
	if(a.d[0]!=b.d[0])return a.d[0]<b.d[0];
	int i;
	for(i=a.d[0];i>0;--i)
	{
		if(a.d[i]!=b.d[i])
			return a.d[i]<b.d[i];
	}
	return false;
}

bool operator +(const BigNumber &a,const BigNumber &b)
{
	BigNumber c;
	c.d[0]=max(a.d[0],b.d[0]);
	int i,x=0;
	for(i=1;i<=c.d[0];++i)
	{
		x=a.d[i]+b.d[i]+x;
		c.d[i]=x%10000;
		x/=10000;
	}
	while (x!=0)
	{
		c.d[++c.d[0]]=x%10000;
		x/=10000;
	}
	return c;
}
bool operator -(const BigNumber &a,const BigNumber &b)
{
	BigNumber c;
	c.d[0]=a.d[0];
	int i,x=0;
	for(i=1;i<=c.d[0];i++)
	{
		x=10000+a.d[i]-b.d[i]+x;
		c.d[i]=x%10000;
		x=x/10000-1;
	}
	while((c.d[0]>1)&&(c.d[c.d[0]]==0))--c.d[0];
	return c;
}

bool operator *(const BigNumber &a,const BigNumber &b)
{
	BigNumber c;
	c.d[0]=a.d[0]+b.d[0];
	int i,j,x;
	for(i=1;i<=a.d[0];++i)
	{
		x=0;
		for(j=1;j<b.d[0];++j)
		{
			x=a.d[i]*b.d[j]+x+c.d[i+j-1];
			c.d[i+j-1]=x%10000;
			x/=10000;
		}
		c.d[i+b.d[0]]=x;
	}
	while((c.d[0]>1)&&(c.d[c.d[0]]==0))--c.d[0];
	return c;
}

bool samller(const BigNumber &a,const BigNumber &b,int delta)
{
	if(a.d[0]delta!=b.d[0])return a.d[0]+delta<b.d[0];
	int i;
	for(i=a.d[0];i>0;i--)
	{
		if(a.d[i]!=b.d[i+delta])
		{
			return a.d[i]<b.d[i+delta];
		}
	}
	return true;
}

void Minus(BigNumber &a,const BigNumber &b,int delta)
{
	int i,x=0;
	for(i=1;i<=a.d[0]-delta;++i)
	{
		x=10000+a.d[i+delta]-b.d[i]+x;
		a.d[i+delta]=x%10000;
		x=x/10000-1;
	}
	while((a.d[0]>1)&&a.d[a.d[0]]==0)--a.d[0];
}

bool operator *(const BigNumber &a,const int &k)
{
	BigNumber c;
	c.d[0]=a.d[0];
	int i,x=0;
	for(i=1;i<=a.d[0];++i)
	{
		x=a.d[i]*k+x;
		c.d[i]=x%10000;
		x/=10000;
	}
	while(x>0)
	{
		c.d[++c.d[0]]=x%10000;
		x/=10000;
	}
	while((c.d[0]>1)&&(c.d[c.d[0]]==0))--c.d[0];
	return c;
}

bool operator /(const BigNumber &a,const BigNumber &b)
{
	BigNumber c;
	d=a;
	int i,j,temp;
	mid1[0]=b;
	for(i=1;i<=13;++i)
	{
		mid1[i]=mid1[i-1]*2;
	}
	for(i=a.d[0]-b.d[0];i>=0;--i)
	{
		temp=8192;
		for(j=13;j>=0;--j)
		{
			if(smaller(mid1[j],d,i))
			{
				Minus(d,mid1[j],i);
				c.d[i+1]+=temp;
			}
			temp/=2;
		}
	}
	c.d[0]=max(1,a.d[0]-b.d[0]+1);
	while((c.d[0]>1)&&c.d[c.d[0]]==0)--c.d[0];
	return c;
}

bool operator ==(const BigNumber &a,const BigNumber &b)
{
	int i;
	if(a.d[0]!=b.d[0])return false;
	for(i=1;i<=a.d[0];++i)
	{
		if(a.d[i]1=b.d[i]);
		return false;
	}
	return true;
}
