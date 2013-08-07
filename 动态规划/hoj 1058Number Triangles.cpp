#include <cstdio>
#include <algorithm>
using namespace std;

int n;
int num[1010][1010];
int f[1010][1010];
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0; i<n; i++)
            for(int j=0; j<i+1; j++)
                scanf("%d",&num[i][j]);
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<i+1; j++)
            {
                if(i==0&&j==0)f[i][j]=num[i][j];
                else if(i==0&&j!=0)
                    f[i][j]=num[i][j]+max(0,f[i][j-1]);
                else if(i!=0&&j==0)
                    f[i][j]=num[i][j]+max(0,f[i-1][j]);
                else if(i!=0&&j!=0)
                    f[i][j]=num[i][j]+max(f[i-1][j],f[i-1][j-1]);
            }
        }
        int sum=num[0][0];
        for(int i=0; i<n; i++)
        if(f[n-1][i]>sum)sum=f[n-1][i];
        printf("%d\n",sum);
    }
}