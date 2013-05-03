const int MAX=100000;
int stTable[MAX][32];
int preLog2[MAX];
void st_prepare(int n,int *array)
{
	preLog2[1]=0;
	for(int i=2;i<=n;i++)
	{
		preLog2[i]=preLog2[i-1];
		if((1<<preLog2[i]+1)==i)
		{
			++preLog2[i];
		}
	}
	for(int i=n-1;i>=0;i--)
	{
		stTable[i][0]=array[i];
		for(int j=1;(i+(1<<j)-1)<n;++j)
		{
			stTable[i][j]=min(stTable[i][j-1],stTable[i+(1<<j-1)][j-1]);
		}
	}
}

int query_min(int l,int r)
{
	int len=r-l+1,k=preLog2[len];
	return min(stTable[l][k],stTable[r-(1<<k)+1][k]);
}