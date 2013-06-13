#include <stdio.h>
const int maxn=51;
bool board[maxn][maxn];
int n,px[11],py[11],r[11],k,on[11],ans;
void init()
{
    int i,j;
    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
            board[i][j]=false;
}
void f()
{
    int t,i,j,x,y,s,z;
    bool qq;
    while(1)
    {
        init();
        s=0;
        qq=true;
        on[1]++;
        t=1;
        while(on[t]>1)
        {
            on[t]=0;
            on[++t]++;
        }
        if(t>k)
            return ;
        for(i=1; i<=k; i++)
            if(on[i])
            {
                for(j=0; j<=r[i]; j++)
                {
                    for(z=0; z<=r[i]-j; z++)
                    {
                        x=px[i]+j,y=py[i]+z;
                        if(x>0&&x<=n&&y>0&&y<=n)
                            board[x][y]=true;
                        x=px[i]-j,y=py[i]+z;
                        if(x>0&&x<=n&&y>0&&y<=n)
                            board[x][y]=true;
                        x=px[i]+j,y=py[i]-z;
                        if(x>0&&x<=n&&y>0&&y<=n)
                            board[x][y]=true;
                        x=px[i]-j,y=py[i]-z;
                        if(x>0&&x<=n&&y>0&&y<=n)
                            board[x][y]=true;
                    }
                }
            }
        for(i=1; i<=n; i++)
        {
            for(j=1; j<=n; j++)
                if(!board[i][j])
                {
                    qq=false;
                    break;
                }
            if(!qq)
                break;
        }
        if(qq)
        {
            for(i=1; i<=k; i++)
                s+=on[i];
            if(s<ans)
                ans=s;
        }
    }
}
int main()
{
    int i,j;
    while(scanf("%d",&n)!=EOF)
    {
        if(!n)
            break;
        scanf("%d",&k);
        for(i=1; i<=k; i++)
            scanf("%d%d",&px[i],&py[i]);
        /*if(k==n*n)
        {
            printf("0\n");
            continue;
        }*/
        for(i=1; i<=k; i++)
        {
            scanf("%d",&r[i]);
            on[i]=0;
        }
        ans=99;
        f();
        if(ans!=99)
            printf("%d\n",ans);
        else
            printf("-1\n");
    }
}
