#include <iostream>
#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;
//poor snoopy
#define N 150
#define maxn 150
#define M 99999999
int n,m;
double map[N][N];//从0开始存图
//求2点之间的距离
double dis(double &x1,double &y1,double &x2,double &y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
//朱刘算法返回最小权
double zhuliu()//int n,double map[maxn][maxn]参数。
{
    bool visit[maxn];
    bool flag[maxn];
    int pre[maxn];
    double sum=0;
    int i,j,k;
    for(i=0; i<n; i++)
    {
        flag[i]=false;
        map[i][i]=M;
    }
    pre[0]=0;
    while(true)
    {
        for(i=1; i<n; i++)
        {
            if(flag[i])continue;
            pre[i]=i;
            for(j=0; j<n; j++)
                if(!flag[j]&&map[j][i]<map[pre[i]][i])
                    pre[i]=j;
            if(pre[i]==i)return -1;
        }

        for(i=1; i<n; i++)
        {
            if(flag[i])continue;
            for(j=0; j<=n; j++)
            {
                visit[j]=false;
            }
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
            }
            while(j!=i);
            j=i;
            do
            {
                for(k=0; k<n; k++)
                    if(!flag[k]&&map[k][j]<M&&k!=pre[j])
                        map[k][j]-=map[pre[j]][j];
                j=pre[j];
            }while(j!=i);

            for(j=0; j<n; j++)
            {
                if(j==i)continue;
                for(k=pre[i]; k!=i; k=pre[k])
                {
                    if(map[k][j]<map[i][j])map[i][j]=map[k][j];
                    if(map[j][k]<map[j][i])map[j][i]=map[j][k];
                }
            }
            for(j=pre[i]; j!=i; j=pre[j])flag[j]=true;
            break;
        }
        if(i==n)
        {
            for(i=1; i<n; i++)
            {
                if(!flag[i])
                    sum+=map[pre[i]][i];
            }
            break;
        }
    }
    return sum;
}

int main()
{
    double x[N][2];int a,b;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            map[i][j]=M;
        }
        for(int i=1;i<=n;i++)
        cin>>x[i][0]>>x[i][1];
        for(int i=0;i<m;i++)
        {
            cin>>a>>b;
            map[a-1][b-1]=dis(x[a][0],x[a][1],x[b][0],x[b][1]);
        }
        double ans=zhuliu();
        if(ans>0.0)
        printf("%.2lf\n",ans);
        else
        cout<<"poor snoopy\n";
    }

}
