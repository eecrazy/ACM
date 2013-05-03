// HDU 1814 
// 任意输出一组可行解。
// 在HDU上不能AC，HDU 上要求字典序最小的解
// 2-SAT问题
// 求出所有强连通分量,如果有矛盾点同处于一个连通分量则无解
// 缩点，将原图反向建立DAG图//按拓扑排序着色，找一个未着色点x，染成红色
// 将与x矛盾的顶点及其子孙染为蓝色
// 直到所有顶点均被染色，红色即为2-SAT的一组解
// 点的编号从1开始，2*i和2*i+1是一组的
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

const int MAXN = 16010; //8000*2
char color[MAXN];//染色
bool visit[MAXN];
queue<int>q1, q2;
//vector建图方法很妙
vector<vector<int> >adj; //原图    //中间一定要加空格把两个'>'隔开
vector<vector<int> >radj;//逆图
vector<vector<int> >dag;//缩点后的逆向DAG图
int n, m, cnt;
int id[MAXN], order[MAXN], indegree[MAXN]; //强连通分量，访问顺序，入度
void dfs(int u)
{
    visit[u] = true;
    int i, len = adj[u].size();
    for (i = 0; i < len; i++)
        if (!visit[adj[u][i]])
            dfs(adj[u][i]);
    order[cnt++] = u;
}
void rdfs(int u)
{
    visit[u] = true;
    id[u] = cnt;
    int i, len = radj[u].size();
    for (i = 0; i < len; i++)
        if (!visit[radj[u][i]])
            rdfs(radj[u][i]);
}
void korasaju()
{
    int i;
    memset(visit, false, sizeof(visit));
    for (cnt = 0, i = 1; i <= 2 * n; i++)
        if (!visit[i])
            dfs(i);

    memset(id, 0, sizeof(id));
    memset(visit, false, sizeof(visit));
    for (cnt = 0, i = 2 * n - 1; i >= 0; i--)
        if (!visit[order[i]])
        {
            cnt++;//这个一定要放前面来
            rdfs(order[i]);
        }
}
bool solvable()
{
    for (int i = 1; i <= n; i++)
        if (id[2 * i - 1] == id[2 * i])
            return false;
    return true;
}
void topsort()
{
    int i, j, len, now, p, pid;
    while (!q1.empty())
    {
        now = q1.front();
        q1.pop();
        if (color[now] != 0)continue;
        color[now] = 'R';
        indegree[now] = -1;
        for (i = 1; i <= 2 * n; i++)
        {
            if (id[i] == now)
            {
                p = (i % 2) ? i + 1 : i - 1;
                pid = id[p];
                q2.push(pid);
                while (!q2.empty())
                {
                    pid = q2.front();
                    q2.pop();
                    if (color[pid] == 'B')continue;
                    color[pid] = 'B';
                    len = dag[pid].size();
                    for (j = 0; j < len; j++)
                        q2.push(dag[pid][j]);
                }
            }
        }
        len = dag[now].size();
        for (i = 0; i < len; i++)
        {
            indegree[dag[now][i]]--;
            if (indegree[dag[now][i]] == 0)
                q1.push(dag[now][i]);
        }
    }
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int i, j, x, y, xx, yy, len;
    while (scanf("%d%d", &n, &m) != EOF)
    {
        adj.assign(2 * n + 1, vector<int>());
        radj.assign(2 * n + 1, vector<int>());
        for (i = 0; i < m; i++)
        {
            scanf("%d%d", &x, &y);
            xx = (x % 2) ? x + 1 : x - 1;
            yy = (y % 2) ? y + 1 : y - 1;
            adj[x].push_back(yy);
            adj[y].push_back(xx);
            radj[yy].push_back(x);
            radj[xx].push_back(y);
        }
        korasaju();
        if (!solvable())printf("NIE\n");
        else
        {
            dag.assign(cnt + 1, vector<int>());
            memset(indegree, 0, sizeof(indegree));
            memset(color, 0, sizeof(color));
            for (i = 1; i <= 2 * n; i++)
            {
                len = adj[i].size();
                for (j = 0; j < len; j++)
                    if (id[i] != id[adj[i][j]])
                    {
                        dag[id[adj[i][j]]].push_back(id[i]);
                        indegree[id[i]]++;
                    }
            }
            for (i = 1; i <= cnt; i++)
                if (indegree[i] == 0)
                    q1.push(i);
            topsort();
            for (i = 1; i <= n; i++) //小心别写错，是color[id[
                if (color[id[2 * i - 1]] == 'R')printf("%d\n", 2 * i - 1);
                else printf("%d\n", 2 * i);
        }
    }
}
