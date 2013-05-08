#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
const int maxn=1000000;
struct point
{
        double l,r;
}p[maxn],u[maxn];
int n;
bool judge[maxn];
bool cmp(point a,point b)
{
        if(a.l!=b.l)
        return a.l<b.l;
        return a.r<b.r;
}
inline double max(double a,double b)
{
        return (a>b)?a:b;
}
inline double min(double a,double b)
{
        return (a<b)?a:b;
}
void f(int k,double l,double r)
{
        int i,ll,rr;
        for(i=k+1;i<=n;i++)
        if(!judge[i])
        {
                ll=u[i].l,rr=u[i].r;
                if(ll>r)
                continue;
                judge[i]=true;
                l=max(l,ll);
                r=min(r,rr);
        }
}
int main()
{
        int i,ans;
        double r,x,y,l,d;
        while(scanf("%lf%lf%d",&l,&d,&n)!=EOF)
        {
                ans=0;
                for(i=1;i<=n;i++)
                {
                        scanf("%lf%lf",&p[i].l,&p[i].r);
                        judge[i]=false;
                }
                sort(p+1,p+1+n,cmp);
                for(i=1;i<=n;i++)
                {
                        x=p[i].l;y=p[i].r;
                        r=sqrt(d*d-y*y);
                        //printf("(%lf %lf %lf)",x,y,d);
                        u[i].l=x-r;
                        u[i].r=x+r;
                        if(u[i].l<0)
                        u[i].l=0;
                        if(u[i].r>l)
                        u[i].r=l;
                }
                /*for(i=1;i<=n;i++)
                printf("%.0lf %.0lf\n",u[i].l,u[i].r);*/
                for(i=1;i<=n;i++)
                if(!judge[i])
                {
                        f(i,u[i].l,u[i].r);
                        ans++;
                }
                printf("%d\n",ans);
        }
}