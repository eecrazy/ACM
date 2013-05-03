#define maxn 1000000
bool valid[maxn];
void getPrime(int n,int &tot,int ans[maxn])
{
	memset(valid,true,sizeof(valid));
	for(int i=2;i<=n;i++)
	{
		if(valid[i])
		{
			tot++;
			ans[tot]=i;
		}
		for(int j=1;((j<=tot)&&(i*ans[j]<=n));j++)
		{
			valid[i*ans[j]]=false;
			if(i%ans[j]==0)break;
		}
	}
}