#include <cstdio>
using namespace std;
#define maxn 33000
int c[maxn],cnt[maxn]= {0};
int lowbit(int x)
{
    return x&(-x);
}
int sum(int x)
{
    int ret=0;
    while(x>0)
    {
        ret+=c[x];
        x-=lowbit(x);
    }
    return ret;
}
void modify(int i,int x)
{
    while(i<maxn-5)
    {
        c[i]+=x;
        i+=lowbit(i);
    }

}
int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        int x,y;
        for(int i=0; i<n; i++)
        {
            scanf("%d%d",&x,&y);
            int rank=sum(x+1);

            cnt[rank]++;
            modify(x+1, 1);
        }

        for(int i=0; i<n; i++)
            printf("%d\n",cnt[i]);
    }
}
