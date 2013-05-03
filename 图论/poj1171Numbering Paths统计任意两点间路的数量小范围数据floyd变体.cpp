#include <cstdio>
int map[30][30];
int main()
{
    int n,a,b,t,ca=0;
    while(scanf("%d",&n)!=EOF)
    {
        t=0;
        for(int i=0; i<=29; i++)
                for(int j=0; j<=29; j++)
                map[i][j]=0;
        for(int i=0; i<n; i++)
        {
            scanf("%d%d",&a,&b);
            map[a][b]=1;
            if(t<a)t=a;
            if(t<b)t=b;
        }
        for(int k=0; k<=t; k++)
            for(int i=0; i<=t; i++)
                for(int j=0; j<=t; j++)
                {
                    map[i][j]+=map[i][k]*map[k][j];
                }
        for(int k=0; k<=t; k++)
        {
            if(map[k][k])
            {
                map[k][k]=-1;
                for(int i=0; i<=t; i++)
                    for(int j=0; j<=t; j++)
                        if(map[i][k]&&map[k][j])
                            map[i][j]=-1;
            }
        }
        printf("matrix for city %d\n",ca);
        ca++;
        for(int i=0; i<=t; i++)
            for(int j=0; j<=t; j++)
                if(j==t)
                printf("%d\n",map[i][j]);
                else
                printf("%d ",map[i][j]);
    }
}
