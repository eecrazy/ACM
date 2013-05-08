POJ2127

int n1,n2;
int A[maxn+1][maxn+1],B[maxn+1][maxn+1];
int dp[maxn+1][maxn+1];
int pre[maxn+1][maxn+1];
int lcis[maxn+1][maxn+1];

void getLcis()
{
	memset(dp,0,sizeof(dp));
	memset(pre,0,sizeof(pre));
	for(int i=1;i<=n1;i++)
	{
		int k=0;
		for(int j=1;j<=n2;j++)
		{
			if(A[i]!=B[j])
				dp[i][j]=dp[i-1][j];
			if(A[i]>B[j]&&dp[i][j]>dp[i][k])k=j;
			if(A[i]==B[j])
			{
				dp[i][j]=dp[i][k]+1;
				pre[i][j]=k;
			}
		}
	}
	int ans=-1,x=n1,y=0;
	for(int i=1;i<=n2;i++)
	{
		if(dp[n1][i]>ans)
		{
			ans=dp[n1][i];
			y=i;
		}
	}
	int cnt=1;
	while(dp[x][y])
	{
		if(A[x]!=B[y])
		{
			x--;
		}
		else
		{
			lcis[ans-cnt]=B[y];
			cnt++;
			y=pre[x][y];
		}
	}
}