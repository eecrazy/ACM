/*
HDU2825 Wireless Password
*/
#include <cstdio>
#include <cstdlib>
#include <string>
#include <climits>
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <map>
#include <cstring>
#include <queue>
using namespace std;

//MAX_NODE = StringNumber * StringLength
const int MAX_NODE = 101;
//节点个数,一般字符形式的题26个
const int CHILD_NUM = 26;
//特定题目需要
const int mod = 20090717;

class ACAutomaton
{
private:
    //每个节点的儿子,即当前节点的状态转移
    int chd[MAX_NODE][CHILD_NUM];
    //记录题目给的关键数据
    int val[MAX_NODE];
    //传说中的fail指针
    int fail[MAX_NODE];
    //队列,用于广度优先计算fail指针
    int Q[MAX_NODE];
    //字母对应的ID
    int ID[128];
    //已使用节点个数
    int sz;
    //特定题目需要
    int dp[2][MAX_NODE][1 << 10];
public:
    //初始化,计算字母对应的儿子ID,如:'a'->0 ... 'z'->25
    void Initialize()
    {
        fail[0] = 0;
        for (int i = 0 ; i < CHILD_NUM ; i ++)
        {
            ID[i + 'a'] = i;
        }
    }
    //重新建树需先Reset
    void Reset()
    {
        memset(chd[0] , 0 , sizeof(chd[0]));
        sz = 1;
    }
    //将权值为key的字符串a插入到trie中
    void Insert(char *a, int key)
    {
        int p = 0;
        for ( ; *a ; a ++)
        {
            int c = ID[*a];
            if (!chd[p][c])
            {
                memset(chd[sz] , 0 , sizeof(chd[sz]));
                val[sz] = 0;
                chd[p][c] = sz ++;
            }
            p = chd[p][c];
        }
        val[p] = key;
    }
    //建立AC自动机,确定每个节点的权值以及状态转移
    void Construct()
    {
        int *s = Q , *e = Q;
        for (int i = 0 ; i < CHILD_NUM ; i ++)
        {
            if (chd[0][i])
            {
                fail[ chd[0][i] ] = 0;
                *e ++ = chd[0][i];
            }
        }
        while (s != e)
        {
            int u = *s++;
            for (int i = 0 ; i < CHILD_NUM ; i ++)
            {
                int &v = chd[u][i];
                if (v)
                {
                    *e ++ = v;
                    fail[v] = chd[ fail[u] ][i];
                    //以下一行代码要根据题目所给val的含义来写
                    val[v] |= val[ fail[v] ];
                }
                else
                {
                    v = chd[ fail[u] ][i];
                }
            }
        }
    }
    //解题,特定题目需要
    int Work(int n, int m, int k)
    {
        memset(dp[0] , 0 , sizeof(dp[0]));
        dp[0][0][0] = 1;
        int S = 0;
        while (n --)
        {
            int T = 1 - S;
            memset(dp[T] , 0 , sizeof(dp[T]));
            for (int i = 0 ; i < sz ; i ++)
            {
                for (int j = 0 ; j < m ; j ++)
                {
                    if (dp[S][i][j])
                    {
                        for (int k = 0 ; k < CHILD_NUM ; k ++)
                        {
                            int p = chd[i][k];
                            int st = (j | val[p]);
                            dp[T][p][st] += dp[S][i][j];
                            if (dp[T][p][st] >= mod)
                            {
                                dp[T][p][st] -= mod;
                            }
                        }
                    }
                }
            }
            S = T;
        }
        int ret = 0;
        for (int j = 0 ; j < m; j ++)
        {
            int cnt = 0;
            int a = j;
            for ( ; a ; cnt += (a & 1) , a >>= 1);
            if (cnt < k) continue;
            for (int i = 0 ; i < sz ; i ++)
            {
                ret += dp[S][i][j];
                if (ret >= mod)
                {
                    ret -= mod;
                }
            }
        }
        return ret;
    }
} AC;

int main()
{
    AC.Initialize();
    int n , m , k;
    while (~scanf("%d%d%d", &n, &m, &k))
    {
        if (n == 0 && m == 0 && k == 0) break;
        AC.Reset();
        for (int i = 0 ; i < m ; i ++)
        {
            char temp[11];
            scanf("%s", temp);
            AC.Insert(temp , 1 << i);
        }
        AC.Construct();
        printf("%d\n", AC.Work(n , 1 << m , k));
    }
    return 0;
}
