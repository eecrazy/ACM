#include <cstdio>
int n,m;
int map[410][410];
int ans[410];
void reverse(int s,int t)
{
    int temp;
    while(s<t)
    {
        temp=ans[s];
        ans[s]=ans[t];
        ans[t]=temp;
        s++;
        t--;
    }
}
void hamilton()
{
    int s=1,t;
    int ansi=2,i,j,w;
    int temp;
    bool visit[410]= {false};
    for(i=1; i<=n; i++)
    {
        if(map[s][i])break;
    }
    t=i;
    visit[s]=visit[t]=true;
    ans[0]=s;
    ans[1]=t;
    while(true)
    {
        while(true)
        {
            for ( i = 1; i <=n; ++i)
            {
                if(map[t][i]&&!visit[i])
                {
                    ans[ansi++]=i;
                    visit[i]=true;
                    t=i;
                    break;
                }
            }
            if(i>n)break;
        }
        w=ansi-1;
        i=0;
        reverse(i,w);
        temp=s;
        s=t;
        t=temp;
        while(true)
        {
            for ( i = 1; i <=n; ++i)
            {
                if(map[t][i]&&!visit[i])
                {
                    ans[ansi++]=i;
                    visit[i]=true;
                    t=i;
                    break;
                }
            }
            if(i>n)
                break;
        }
        if(!map[s][t])
        {
            for(i=1; i<ansi-2; i++)
                if(map[ans[i]][t]&&map[s][ans[i+1]])break;
            w=ansi-1;
            i++;
            t=ans[i];
            reverse(i,w);
        }
        if(ansi==n)
            return ;
        for(j=1; j<=n; j++)
        {
            if(visit[j])continue;
            for(i=1; i<ansi-1; i++)if(map[ans[i]][j])break;
            if(map[ans[i]][j])break;
        }
        s=ans[i-1];
        t=j;
        reverse(0,i-1);
        reverse(i,ansi-1);
        ans[ansi++]=j;
        visit[j]=true;
    }
}
void init()
{
    for(int i=0; i<=n; i++)
        for(int j=0; j<=n; j++)
        {
            if(i!=j)
            map[i][j]=1;
            else map[i][j]=0;
        }
    for(int i=0; i<=n; i++)ans[i]=0;
}
int main()
{
    int x,y;
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        if(n==0&&m==0)break;
        n*=2;
        init();
        for(int i=0; i<m; i++)
        {
            scanf("%d%d",&x,&y);
            map[x][y]=0;
            map[y][x]=0;
        }
        hamilton();
        for(int i=0; i<n; i++)
        {
            if(i!=n-1)
            printf("%d ",ans[i]);
            else printf("%d\n",ans[i]);
        }
    }
}
