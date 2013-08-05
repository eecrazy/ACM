// 题意：给你一个n节组成的起重机，而每两节直接可以旋转，一开始每节都在y轴上，现在对于每次旋转第i与i+1的角度，求末端的坐标。。。
// 分析：这题挺有趣的一题，它将线段树应用到了计算几何上，首先需要一些计算几何知识：
//1.向量(x,y)则，向量 逆时针 旋转a弧度 后的向量为(cos a *x-sin a*y,sin a*x+cos a*y)
//2.向量的和刚好指向这些向量头尾相连后所指向的地方，也就是把每条线段看做一个向量，那么这项向量的和正好指向末端的坐标
//3.旋转第i与i+1的角度是，i+1及其上的所有向量都旋转了同样的角度
// 通过上面的知识我们可以把为题转化为线段树来解决，构造一棵线段树，保存向量旋转的角度，向量坐标的和，角度是累计的，每次旋转 i 的时候，就将线段树中 i+1 到 n 的所有角度加上旋转的角度，当然是用延迟标记喽，而每次一个新的旋转角度过来时，直接旋转这个区间，然后再把角度加到延迟标记上，顺序反了就出错了，一开始这样写就wa了。。。向下更新时也是一样，先旋转再更新延迟标志，具体看代码吧。。。精度问题也比较恶心，居然输出 -0.00，每次都转了一下= =
// 代码：
#include <cstdio>
#include <string.h>
#include <cmath>
#include <iostream>
using namespace std;
#define maxn 10010
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
int sd[maxn<<2],degree[maxn<<2];
double sx[maxn<<2],sy[maxn<<2];
void rotate(int rt,int sd)
{
    double d=sd*asin(1.0)/90.0;//转化为弧度
    double x=(cos(d)*sx[rt]-sin(d)*sy[rt]);
    double y=sin(d)*sx[rt]+cos(d)*sy[rt];
    sx[rt]=x;
    sy[rt]=y;

}
void pushdown(int rt)
{
    rotate(rt<<1,sd[rt]);
    rotate(rt<<1|1,sd[rt]);
    sd[rt<<1]+=sd[rt];
    sd[rt<<1|1]+=sd[rt];
    sd[rt]=0;
}
void pushup(int rt)
{
    sx[rt]=sx[rt<<1]+sx[rt<<1|1];
    sy[rt]=sy[rt<<1]+sy[rt<<1|1];
}
void build(int l,int r,int rt)
{
    sd[rt]=0;
    if(l==r)
    {
        scanf("%lf",&sy[rt]);
        sx[rt]=0;
        return ;
    }
    int m=(l+r)>>1;
    build(lson);
    build(rson);
    pushup(rt);
}
void update(int L,int d,int l,int r,int rt)
{
    if(L<l)
    {
        rotate(rt,d);
        sd[rt]+=d;
        return ;
    }
    if(sd[rt])pushdown(rt);
    int m=(l+r)>>1;
    if(L<m)update(L,d,lson);
    update(L,d,rson);
    pushup(rt);
}
int main()
{
    int n,m,flag=0,a,b;
    while(scanf("%d%d",&n,&m))
    {
        if(flag)puts("");
        else flag=1;
        build(1,n,1);
        fill(degree,degree+n,180);
        while(m--)
        {
            scanf("%d%d",&a,&b);
            update(a,b-degree[a],1,n,1);
            degree[a]=b;
            //printf("ddd\n");
            printf("%.2lf %.2lf\n",fabs(sx[1])<1e-8?0:sx[1],fabs(sy[1])<1e-8?0:sy[1]);
        }
    }
}
