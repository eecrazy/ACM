//poor snoopy
double zhuliu(int n,double map[maxn][maxn])
{
	bool visit[maxn];
	bool flag[maxn];
	int pre[maxn];
	double sum=0;
	int i,j,k;
	for(i=0;i<n;i++)
	{
		flag[i]]=false;
		map[i][i]=INF;
	}
	pre[0]=0;
	while(true)
	{
		for(i=1;i<n;i++)
		{
			if(flag[i])continue;
			pre[i]=i;
			for(j=0;j<n;j++)
				if(!flag[j]&&map[j][i]<map[pre[i][i]])
					pre[i]=j;
			if(pre[i]==i)return -1;
		}

		for(i=1;i<n;i++)
		{
			if(falg[i])continue;
			for(j=0;j<n;j++)
				{visit[j]=false;}
			visit[0]=true;
			j=i;
			do
			{
				visit[j]=true;
				j=pre[j];
			}while(!visit[j]);
			if(!j)continue;

			i=j;
			do
			{
				sum+=map[pre[j]][j];
				j=pre[j];
			}while(j!=i);
			j=i;

			do
			{
				for(k=0;k<n;k++)
					if(!flag[k]&&map[k][j]<INF&&k!=pre[j])
						map[k][j]-=map[pre[j]][j];
				j=pre[j];
			}while(j!=i);

			for(j=0;j<n;j++)
			{
				if(j==i)continue;
				for(k=pre[i];k!=i;k=pre[k])
				{
					if(map[k][j]<map[i][j])map[i][j]<map[k][j];
					if(map[j][k]<map[j][i])map[j][i]=map[j][k];
				}
			}
			for(j=pre[i];j!=i;j=pre[j])flag[j]=true;
			break;
		}
		if(i==n)
		{
			for(i=1;i<n;i++)
				{if(!flag[i])sum+=map[pre[i]][i]}
			break;
		}
	}
	return sum;
}