#include <cstdio>
#include <cstring>
const int maxn=26;
int visit[maxn];//该字母是否存在
int in[maxn],out[maxn];//入度和出度
int a[maxn];//并查集合
int find(int x)
{
    int k1,k2;
    k1=x;
    if(k1!=a[k1])
    {
        k1=a[k1];
    }
    while(x!=a[x])
    {
        k2=a[x];
        a[x]=k1;
        x=k2;
    }
    return k1;
}
void Union(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x!=y)
    {
        a[x]=y;
    }
}
void init()
{
    for(int i=0; i<=25; i++)
    {
        a[i]=i;
        visit[i]=0;
        in[i]=0;
        out[i]=0;
    }
}
int main()
{
    int i,n,s,t,l;
    int x,y,s2,s3;
    char s1[1024];
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        init();
        while(n--)
        {
            scanf("%s",s1);
            x=s1[0]-'a';
            y=s1[strlen(s1)-1]-'a';
            visit[x]=1;
            visit[y]=1;
            in[y]++;
            out[x]++;
            Union(x,y);
        }
        s=0;
        for(i=0; i<=25; i++)
        {
            if(visit[i]&&a[i]==i)
                s++;
        }
        if(s==1)
        {
            s2=0;
            s3=0;
            for(i=0; i<=25; i++)
            {
                if(visit[i]==1)
                {
                    if(in[i]==out[i])
                        continue;
                    else if(in[i]-out[i]==1)
                    {
                        s2++;
                        if(s2>1)break;
                    }
                    else if(in[i]-out[i]==-1)
                    {
                        s3++;
                        if(s3>1)break;
                    }
                    else break;
                }
            }
            if(i==26)
                printf("Ordering is possible.\n");
            else
                printf("The door cannot be opened.\n");
        }
        else
            printf("The door cannot be opened.\n");
    }
}
