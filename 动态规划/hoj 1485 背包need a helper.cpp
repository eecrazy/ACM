#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;
int f[1300],a,c;
int n,v[240];
int big,tmp=0,xi;
int tot;
void init()
{
    int i,temp;
    scanf("%d",&n);
    tot=0;
    for(i=1; i<=n; i++)
    {
        scanf("%d",&v[i]);
        tot+=v[i];
    }
    sort(v+1,v+n+1);
    big=v[n];
}
void work()
{
    int i,j;
    memset(f,0,sizeof(f));
    for (i=1; i<=n ; i++ )
    {
        for (j=a; j>=v[i]; j--)
        {

            f[j]=max(f[j-v[i]]+v[i],f[j]);
        }
    }
    if (f[a]+c>=tot) printf("Yes\n");
    else if (f[a]+c>=tot-big) printf("Need a helper\n");
    else printf("No\n");
}
int main()
{
    while (scanf("%d%d",&a,&c)!=EOF)
    {
        init();
        work();
    }
    return 0;
}
