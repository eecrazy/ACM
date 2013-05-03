#include <iostream>
#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;
//poor snoopy
#define N 150
#define maxn 150
#define M 99999999
int n, m;
double map[N][N];//从0开始存图
//求2点之间的距离
double dis(double &x1, double &y1, double &x2, double &y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
//朱刘算法返回最小权
double zhuliu()//int n,double map[maxn][maxn]参数。
{
    bool visit[maxn];
    bool flag[maxn];//缩点标记为true,则该点已经被缩掉
    int pre[maxn];
    double sum = 0;
    int i, j, k;
    for (i = 0; i < n; i++)
    {
        flag[i] = false;
        map[i][i] = M;
    }
    pre[0] = 0;
    while (true)
    {
        for (i = 1; i < n; i++)
        {
            //求最短弧集合E0
            if (flag[i])continue;
            pre[i] = i;
            for (j = 0; j < n; j++)
                if (!flag[j] && map[j][i] < map[pre[i]][i])
                    pre[i] = j;
            if (pre[i] == i)return -1;
        }
        //检查E0
        for (i = 1; i < n; i++)
        {
            if (flag[i])continue;
            //从当前点开始找环
            for (j = 0; j <= n; j++)
            {
                visit[j] = false;
            }
            visit[0] = true;
            j = i;
            do
            {
                visit[j] = true;
                j = pre[j];
            }
            while (!visit[j]);
            if (!j)continue; //没找到环
            //收缩G中的有向环
            i = j;
            //将整个环的权值保存，累计入原图的最小树形图
            do
            {
                sum += map[pre[j]][j];
                j = pre[j];
            }
            while (j != i);
            j = i;
            //对与环上的点有关的边，修改边权
            do
            {
                for (k = 0; k < n; k++)
                    if (!flag[k] && map[k][j] < M && k != pre[j])
                        map[k][j] -= map[pre[j]][j];
                j = pre[j];
            }
            while (j != i);
            //缩点，将整个点缩成i号点所有与环上有关的点有关的边转移到点。
            for (j = 0; j < n; j++)
            {
                if (j == i)continue;
                for (k = pre[i]; k != i; k = pre[k])
                {
                    if (map[k][j] < map[i][j])map[i][j] = map[k][j];
                    if (map[j][k] < map[j][i])map[j][i] = map[j][k];
                }
            }
            //标记环上其他的点为被缩掉
            for (j = pre[i]; j != i; j = pre[j])flag[j] = true;
            break;
        }
        //如果所有的点都被检查且被没有环存在，现在的最短弧集合E0就是最小树形图，累计入
        //sum，算法结束。
        if (i == n)
        {
            for (i = 1; i < n; i++)
            {
                if (!flag[i])
                    sum += map[pre[i]][i];
            }
            break;
        }
    }
    return sum;
}

int main()
{
    double x[N][2]; int a, b;
    while (scanf("%d%d", &n, &m) != EOF)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                map[i][j] = M;
        }
        for (int i = 1; i <= n; i++)
            cin >> x[i][0] >> x[i][1];
        for (int i = 0; i < m; i++)
        {
            cin >> a >> b;
            map[a - 1][b - 1] = dis(x[a][0], x[a][1], x[b][0], x[b][1]);
        }
        double ans = zhuliu();
        if (ans > 0.0)
            printf("%.2lf\n", ans);
        else
            cout << "poor snoopy\n";
    }
}


/*

最小树形图，就是给有向带权图中指定一个特殊的点root，求一棵

以root为根的有向生成树T，并且T中所有边的总权值最小。最小树

形图的第一个算法是1965年朱永津和刘振宏提出的复杂度为O(VE)

的算法。
判断是否存在树形图的方法很简单，只需要以v为根作一次图的遍

历就可以了，所以下面的算法中不再考虑树形图不存在的情况。
在所有操作开始之前，我们需要把图中所有的自环全都清除。很明

显，自环是不可能在任何一个树形图上的。只有进行了这步操作，

总算法复杂度才真正能保证是O(VE)。


首先为除根之外的每个点选定一条入边，这条入边一定要是所有入

边中最小的。现在所有的最小入边都选择出来了，如果这个入边集

不存在有向环的话，我们可以证明这个集合就是该图的最小树形图

。这个证明并不是很难。如果存在有向环的话，我们就要将这个有

向环缩成一个人工顶点，同时改变图中边的权。假设某点u在该环

上，并设这个环中指向u的边权是in[u]，那么对于每条从u出发的

边(u, i, w)，在新图中连接(new, i, w)的边，其中new为新加的

人工顶点; 对于每条进入u的边(i, u, w)，在新图中建立边(i,

new, w-in[u])的边。为什么入边的权要减去in[u]，这个后面会解

释，在这里先给出算法的步骤。然后可以证明，新图中最小树形图

的权加上旧图中被收缩的那个环的权和，就是原图中最小树形图的

权。
上面结论也不做证明了。现在依据上面的结论，说明一下为什么出

边的权不变，入边的权要减去in [u]。对于新图中的最小树形图T

，设指向人工节点的边为e。将人工节点展开以后，e指向了一个环

。假设原先e是指向u的，这个时候我们将环上指向u的边 in[u]删

除，这样就得到了原图中的一个树形图。我们会发现，如果新图中

e的权w'(e)是原图中e的权w(e)减去in[u]权的话，那么在我们删除

掉in[u]，并且将e恢复为原图状态的时候，这个树形图的权仍然是

新图树形图的权加环的权，而这个权值正是最小树形图的权值。所

以在展开节点之后，我们得到的仍然是最小树形图。逐步展开所有

的人工节点，就会得到初始图的最小树形图了。
如果实现得很聪明的话，可以达到找最小入边O(E)，找环 O(V)，

收缩O(E)，其中在找环O(V)这里需要一点技巧。这样每次收缩的复

杂度是O(E)，然后最多会收缩几次呢？由于我们一开始已经拿掉了

所有的自环，我门可以知道每个环至少包含2个点，收缩成1个点之

后，总点数减少了至少1。当整个图收缩到只有1个点的时候，最小

树形图就不不用求了。所以我们最多只会进行V-1次的收缩，所以

总得复杂度自然是O(VE)了。由此可见，如果一开始不除去自环的

话，理论复杂度会和自环的数目有关。
*/