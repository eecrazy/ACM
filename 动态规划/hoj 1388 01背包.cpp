#include <cstdio>
#include <string.h>
#define inf 0x3f3f3f3f
#include <iostream>
using namespace std;
int val[305],w[305],f[20105][25];
int main()
{
    //freopen("in","r",stdin);
    int N,V,M,flag=0;
    while(scanf("%d",&N)!=EOF)
    {
        if(flag==1)
            printf("\n");
        flag=1;
        for(int i=1; i<=N; i++)
        {
            scanf("%d%d",&w[i],&val[i]);
        }
        memset(f,inf,sizeof(f));
        f[0][0]=0;
        V=20050;
        M=min(N,20);
        for(int j=1; j<=N; j++)
        {
            for(int v=V; v>=w[j]; v--)
            {

                for(int i=1; i<=M; i++)
                {
                    if(f[v-w[j]][i-1]!=inf)
                        f[v][i]=min(f[v][i],f[v-w[j]][i-1]+val[j]);
                }
            }
        }
        int MIN,MAX,m,sum,n;
        scanf("%d",&m);
        while(m--)
        {
            scanf("%d%d%d",&n,&MIN,&MAX);
            if(n>N)
            {
                printf("impossible\n");
                continue;
            }
            sum=inf;
            for(int i=MIN*n; i<=MAX*n; i++)
            {
                if(sum>f[i][n])sum=f[i][n];
            }
            if(sum!=inf)
            printf("%d\n",sum);
            else printf("impossible\n");
        }

    }
}
