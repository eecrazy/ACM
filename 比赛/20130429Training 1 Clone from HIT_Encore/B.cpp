// 分析：简单贪心，显然电池能用则用 
// 因为 1、以后用要花费更多的电量；2、以后充电比现在充电要得到更多的电量。 
// 第 S 天电池没电，充完电之后剩余 S 的电量 
// 第 S+1 天因为电量不够还需要充电，充完电之后剩下 2*S+1 的电量 
// 第 S+2 天使用电池，用完之后剩下 S-1 的电量，以后重复这样的步骤，也就
// 是说充一天电，使用一天。每进行一次这样的步骤，剩余电量减 1。所以 S 的电
// 量可以进行 S 次这样的步骤，也就使用了 S 天。第 3*S 天，剩余电量为 0 。然
// 后第 3*S+1 天又是相同的问题。因为每次 3 倍的增长，直接模拟就好了。
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int main()
{
    int t,cas=1,k,a,b,ans;
    scanf("%d",&t);
    while(t--)
    {
        ans=0;
        scanf("%d%d",&a,&b);
        while(a<b)
        {
            k=3*a;
            if(k<=b)
            {
                ans+=a;
                a=3*a+1;
            }
            else
            {
                ans+=(b-a)/2;break;
            }
        }
        printf("Case #%d: %d\n",cas++,ans);
    }
}
