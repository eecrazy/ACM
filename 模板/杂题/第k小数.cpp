//序列a[]中的第k小数

void quickSelect(int a[],int l,int r,int rank)
{
	int i=l,j=r,mid=a[(l+r)/2];
	do
	{
		while(a[i]<mid)++i;
		while(a[j]>mid)--j;
		if(i<=j)
		{
			swap(a[i],a[j]);
			++i;--j;
		}
	}while(i<=j);
	if(l<=j&&rank<=j-l+1)quickSelect(a,l,j,rank);
	if(i<=r&&rank>=i-l+1)quickSelect(a,i,r,rank-(i-l));
}
int quick_select(int a[],int n,int k)
{
	quickSelect(a,1,n,k);
	return a[k-1];
}

int main()
{
	
}