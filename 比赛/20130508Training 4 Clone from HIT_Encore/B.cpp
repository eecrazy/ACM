#include <stdio.h>
#include <map>
using namespace std;
struct datb
{
    int a,b;
    bool operator <(const datb& other) const // 注意是const函数！！
    {
        if (b != other.b) // 类型按升序排序
        {
            return (b > other.b);
        }
        else // 如果类型相同，按比例尺升序排序
        {
            return (a < other.a);
        }

    }
};
int main()
{
    int k,a,b;
    scanf("%d",&k);
    map<datb,int>now;
    map<datb,int>::iterator iter;
    map<datb,int>::reverse_iterator iter1;
    datb temp;now.clear();
    while(k)
    {

        if(k==1)
        {
            scanf("%d%d",&temp.a,&temp.b);
            now[temp]=1;
        }
        else
        {
                if(now.empty())
                {
                        printf("0\n");
                }
                else
                {
                        if(k==2)
                        {
                                iter=now.begin();
                                printf("%d\n",iter->first.a);
                                now.erase(iter);
                        }
                        else
                        {
                                iter1=now.rbegin();
                                printf("%d\n",iter1->first.a);
                                iter=now.find(iter1->first);
                                now.erase(iter);
                        }
                }
        }
        scanf("%d",&k);
    }
    return 0;
}