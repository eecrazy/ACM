int const maxn=100000;
int tot,v[maxn],l[maxn],r[maxn],d[maxn];
int Merge(int x,int y)
{
	if(!x)
	{
		return y;
	}
	if(!y)
		return x;
	if(v[x]<v[y])
	{
		swap(x,y);
	}
	r[x]=Merge(r[x],y);
	if(d[l[x]]<d[r[x]])
	{
		swap(l[x],r[x]);
	}
	d[x]=[dr[x]]+1;
	return x;
}
int Init(int x)
{
	return (Merge(x,Init(y)));
}
int Top(int x)
{
	return (v[x]);
}
int Pop(int x)
{
	return (Merge(l[x],r[x]));
}