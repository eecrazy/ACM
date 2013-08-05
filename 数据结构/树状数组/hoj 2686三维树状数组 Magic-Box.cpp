#include <stdio.h>
#include <cstring>

#define maxn 202
int c[maxn][maxn][maxn];
int lowbit(int x)
{
	return x&-x;
}
void modify(int x,int y,int  z,int p)
{
	for(int i=x;i<maxn;i+=lowbit(i))
	{
		for(int j=y;j<maxn;j+=lowbit(j))
		{
			for(int k=z;k<maxn;k+=lowbit(k))
			{
				c[i][j][k]+=p;
			}
		}
	}
}
int sum(int x,int y,int z)
{
	int ans=0;
	for(int i=x;i>0;i-=lowbit(i))
	{
		for(int j=y;j>0;j-=lowbit(j))
		{
			for(int k=z;k>0;k-=lowbit(k))
			{
				ans+=c[i][j][k];
			}
		}
	}
	return ans;
}
int main()
{
	int t,x1,y1,z1,x2,y2,z2,p;
	char op[10];
	while(scanf("%d",&t)==1)
	{
		memset(c,0,sizeof(c));
		while(t--)
		{
			scanf("%s",op);
			if(op[0]=='A')
			{
				scanf("%d%d%d%d%d%d%d",&x1,&y1,&z1,&x2,&y2,&z2,&p);
				modify(x2+1,y2+1,z2+1,-p);
                modify(x2+1,y1,z2+1,p);
                modify(x1,y2+1,z2+1,p);
                modify(x2+1,y2+1,z1,p);
                modify(x1,y1,z2+1,-p);
                modify(x2+1,y1,z1,-p);
                modify(x1,y2+1,z1,-p);
                modify(x1,y1,z1,p);
			}
			else if(op[0]=='Q')
			{
				scanf("%d%d%d",&x1,&y1,&z1);
				printf("%d\n",sum(x1,y1,z1));
			}
		}
	}
}
