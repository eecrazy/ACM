const int maxn=100000;
int Tree[maxn+10];
inline int lowbit(int x)
{
	return (x&-x);
}

void add(int x,int value)
{
	for(int i=x;i<=maxn;i+=lowbit[i])
	{
		Tree[i]+=value;
	}
}

int get(int x)
{
	int sum=0;
	for(int i=x;i;i-=lowbit[i])
	{
		sum+=Tree[i];
	}
	return sum;
}