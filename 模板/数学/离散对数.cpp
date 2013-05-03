long long discreat_log(int x,int n,int m)
{
	map<long long,int> rec;
	int s=(int)(sqrt)(double(m));
	for(;(long long)s*s<=m;)s++;
	long long cur=1;
	for(int i=0;i<s;++i)
	{
		long long more=(long long)n*pow_mod(cur,m-2,m)%m;
		if(rec.count(more))
		{
			return i*s+rec[more];
		}
		cur=cur*mul%m;
	}	
	return -1;
}