// 题意：给定一系列的单词要求按照字典序把他们全部输出来。
// 解法：首先判定能不能构成欧拉回路，然后就是O(E)的dfs计算出来。这题
// 使用Fleury模板没搞出来，原因这里要根据单词来走边，而该算法得到的
// 是节点访问序列。后面看到一种dfs，既能够保留边又能够保留点又简单多
// 了，以后果断专注这种写法。
//vector实现

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

int N;

char str[50];
int set[30];
int vis[30];
int id[30], od[30];
vector<string>v[30];
vector<string>ans;

int find(int x)
{
    return set[x] = x == set[x] ? x : find(set[x]);
}

void merge(int x, int y)
{
    int a = find(x), b = find(y);
    if (a != b)
    {
        
        set[a] = b;
    }
}

int stk[1005];
int top;

vector<int>nn;

void dfs(int x)
{
    string t;
    int nd;
    while (v[x].size() > 0)   // 每次都将
    {
        t = v[x][0];
        nd = v[x][0][v[x][0].size() - 1] - 'a';
        v[x].erase(v[x].begin());
        dfs(nd);
        ans.push_back(t);
        // 当从一条边走不下去了，那么就从另一条边开始走，注意这个序列的反过来的
    }
    //    nn.push_back(x); 存储遍历节点的储存方式
    //  当从一个节点走不下去了，那么就从返回上一层节点
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(id, 0, sizeof (id));
        memset(od, 0, sizeof (od));
        scanf("%d", &N);
        for (int i = 0; i < 26; ++i)
        {
            set[i] = i;
            vis[i] = 0;
            v[i].clear();
        }
        int s, e;
        for (int i = 0; i < N; ++i)
        {
            scanf("%s", str);
            s = str[0] - 'a';
            e = str[strlen(str) - 1] - 'a';
            vis[s] = vis[e] = 1;
            ++od[s], ++id[e];
            merge(s, e);
            v[s].push_back(str);
        }
        int ss = -1;
        int cnt1 = 0, cnt2 = 0, cnt3 = 0, flag = 0;
        for (int i = 0; i < 26; ++i)
        {
            if (id[i] != od[i])   // 如果某一个节点的入度和出度不一致
            {
                if (abs(id[i] - od[i]) != 1) // 如果这个差值不为1
                {
                    flag = 1;
                    break;
                }
                else     // 如果这个差值为1
                {
                    if (id[i] - od[i] == 1) ++cnt1;
                    else ss = i, ++cnt2; // 如果一个点的出度比入度大1，欧拉回路中该点作为起点
                }
            }
            if (vis[i] && set[i] == i)
            {
                ++cnt3;
            }
        }
        if (cnt3 != 1 || flag || cnt1 != cnt2 || cnt1 > 1)
        {
            puts("***");
        }
        else
        {
            for (int i = 0; i < 26; ++i)
            {
                if (ss == -1 && od[i] > 0)
                {
                    ss = i;
                }
                sort(v[i].begin(), v[i].end());
                /*    for (int j = 0; j < v[i].size(); ++j) {
                        printf("%s ", v[i][j].c_str());
                    }
                    puts("");*/
                // 将邻接表进行排序
            }
            ans.clear();
            nn.clear();
            dfs(ss);
            for (int i = ans.size() - 1, j = 0; i >= 0; --i, ++j)
            {
                printf(j == 0 ? "%s" : ".%s", ans[i].c_str());
            }
            puts("");

            /*    for (int i = nn.size()-1; i >= 0; --i) {
                    printf("%c ", nn[i]+'a');
                }
                puts("");*/
        }
    }
    return 0;
}