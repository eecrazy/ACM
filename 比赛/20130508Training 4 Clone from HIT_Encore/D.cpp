#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=10001;
struct datb
{
        int p,d;
}data[maxn];
bool cmp(datb a,datb b)
{
        if(a.d!=b.d)
        return a.d<b.d;
        return a.p<b.p;
}
int main()
{
        int n,l,i,j,top,tl,time,ans;
        priority_queue<int>now;
        while (scanf("%d%d",&n,&l)!=EOF)
        {
                top=n-1;
                ans=0;
                while(!now.empty())
                now.pop();
                for(i=0;i<n;i++)
                scanf("%d%d",&data[i].p,&data[i].d);
                sort(data,data+n,cmp);

                for(time=data[n-1].d;time>=0;time--)
                {
                        while(top!=-1&&data[top].d==time)
                        {
                                now.push(data[top].p);
                                top--;
                        }
                        tl=l;
                        while(tl>0&&!now.empty())
                        {
                                tl--;
                                ans+=now.top();
                                now.pop();
                        }
                }
                printf("%d\n",ans);
        }
        return 0;
}