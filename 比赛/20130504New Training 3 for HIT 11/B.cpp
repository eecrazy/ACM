#include<stdio.h>
#include<string.h>
#include<math.h>
using namespace std;
#define maxn 305 
#define eps 1e-7
#define max(a,b) (a>b?a:b)
#define min(a,b) (a<b?a:b)

struct point_float
{
	float x,y;
};
bool used[maxn][maxn];
int ans;

int Len(int x1,int y1,int x2,int y2)
{
	return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}

void make_C(int x,int y,int r)  //点是否在圆内
{
	int i,j;
	for(i=x-r;i<=x+r;i++)
		for(j=y-r;j<=y+r;j++)
			if(!used[i][j])
				if(Len(i,j,x,y)<=r*r)
				{
					used[i][j]=true;
					ans++;
				}
}

void make_S(int x,int y,int l)  //点是否在正方形内
{
	int i,j;
	for(i=x;i<=x+l;i++)
		for(j=y;j<=y+l;j++)
			if(!used[i][j])
			{
				used[i][j]=true;
				ans++;
			}		
}

float GetTriangleSquar(const point_float pt0,const point_float pt1,const point_float pt2)  //求三角形面积
{
	point_float AB,BC;
	AB.x=pt1.x-pt0.x;
	AB.y=pt1.y-pt0.y;
	BC.x=pt2.x-pt1.x;
	BC.y=pt2.y-pt1.y;
	return fabs((AB.x*BC.y-AB.y*BC.x))/2.0f;
}
void make_T(const point_float A,const point_float B,const point_float C) //点是否在三角形内，面积法
{
	float SABC,SADB,SBDC,SADC;
	int i,j;
	point_float D;
	//以三角形最大外围遍历，直接遍历本题最大数据范围要超时 
	int minx=min(min((int)A.x,(int)B.x),(int)C.x);
	int miny=min(min((int)A.y,(int)B.y),(int)C.y);
	int maxx=max(max((int)A.x,(int)B.x),(int)C.x);
	int maxy=max(max((int)A.y,(int)B.y),(int)C.y);
	for(i=minx;i<=maxx;i++)
		for(j=miny;j<=maxy;j++)
			if(!used[i][j])
			{
				D.x=i*1.0,D.y=j*1.0;
				SABC=GetTriangleSquar(A,B,C);
				SADB=GetTriangleSquar(A,D,B);
				SBDC=GetTriangleSquar(B,D,C);
				SADC=GetTriangleSquar(A,D,C);
				float SumSquar=SADB+SBDC+SADC;
				if(fabs(SABC-SumSquar)<eps)
				{
					used[i][j]=true;
					ans++;
				}
			}
}

int main()
{
	int t,n,x,y,r,l;
	char s[2];
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		ans=0;
		memset(used,false,sizeof(used));
		while(n--)
		{
			scanf("%s",s);
			if(s[0]=='C')
			{
				scanf("%d%d%d",&x,&y,&r);
				x+=100,y+=100;  //数据输入为1-50,但是圆可能覆盖到为负值的点
				make_C(x,y,r);
			}
			else if(s[0]=='S')
			{
				scanf("%d%d%d",&x,&y,&l);
				x+=100,y+=100;
				make_S(x,y,l);
			}
			else if(s[0]=='T')
			{
				point_float A,B,C;
				scanf("%f%f%f%f%f%f",&A.x,&A.y,&B.x,&B.y,&C.x,&C.y);
				A.x+=100.0,A.y+=100.0; 
				B.x+=100.0,B.y+=100.0;
				C.x+=100.0,C.y+=100.0;
				make_T(A,B,C);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}