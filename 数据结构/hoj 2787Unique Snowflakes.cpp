//还没看懂呢！！！！
#include <iostream>
#include <map>
using namespace std;
int main()
{
    map<int,int> mp;
    map<int,int>::iterator it;
    int cas,i,cur,Max,n,k,b;
    scanf("%d",&cas);
    while(cas--)
    {
        mp.clear();
        scanf("%d",&n);
        i=cur=Max=b=0;
        while(n--)
        {
            ++i;
            scanf("%d",&k);
            if((it=mp.find(k))==mp.end())
            {
                mp.insert(make_pair(k,i));
                if(++cur>Max)
                    Max=cur;
            }
            else if(it->second>=b)
            {
                b=it->second+1;
                cur=i-it->second;
                it->second=i;
                if(cur>Max)
                    Max=cur;
            }
            else
            {
                if(++cur>Max)
                    Max=cur;
                it->second=i;
            }
        }
        printf("%d\n",Max);
    }
    return 0;
}
