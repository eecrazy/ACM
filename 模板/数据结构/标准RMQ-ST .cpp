//标准RMQ-ST
/**** **** **** **** **** ****
*      Function Name  :  标准RMQ-ST
*      Description  :          PKU  3264  Balanced Lineup
**** **** **** **** **** ****/
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
const int MAX = 51000;
const int LOGMAX  = 16;
int n,q;
int st_max[LOGMAX][MAX],  st_min[LOGMAX][MAX];
void make_st()
{
    int i,j,k;
    for(j=1; (1<<j)  <=  n ; j++)
    {
        k =  1<<(j-1);
        for(i=0;  i+k  < n ; i++)
        {
            st_max[j][i]  = max(st_max[j-1][i],
                                st_max[j-1][i+k]);
            st_min[j][i]  =  min(st_min[j-1][i],  st_min[j-1][i+k]);
        }
    }
}
int rmq(int a,int b,int flag)
{
    int dis =  abs(b-a) +1;
    int k;
    for(k=0;  (1<<k)  <=  dis ; k++)  ;
    k --;
    if(flag > 0)
    {
        return max(st_max[k][a],  st_max[k][b-(1<<k)+1]);
    }
    else
    {
        return min(st_min[k][a],  st_min[k][b-(1<<k)+1]);
    }
}
int main()
{
    while(scanf("%d  %d",  &n,&q)==2)
    {
        int i;
        for(i=0; i<n; i++)
        {
            scanf("%d",  &st_max[0][i]);
            st_min[0][i]  = st_max[0][i];
        }
        make_st();
        for(i=0; i<q; i++)
        {
            int a,b;
            scanf("%d  %d",  &a,&b);
            printf("%d\n",  rmq(a-1,b-1,1) - rmq(a-1,b-1,-1));
        }
    }
}
