//求出所有强连通分量,如果有矛盾点同处于一个连通分量则无解
//缩图，将原图反向，成为DAG
//按拓扑序着色，找一个未着色点x，染成红色
//将与x矛盾的顶点及其子孙染为蓝色
//直到所有顶点均被染色，红色即为2-SAT的一组解
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;
#define MAX 17000

int n, m;
vector< vector<int> > path;
vector< vector<int> > npath;
vector< vector<int> > dag;
char color[MAX];
bool ans;
vector< int > ans_seq;
queue< int > SQ;
queue< int > SQ2;

int scc;
int id[MAX];
int order[MAX], order_pos;
int vis[MAX];
int indegre[MAX];

void dfs(int pos)
{
    int i, j, l;
    vis[pos] = true;
    l = path[pos].size();
    for (i = 0; i < l; i++)
    {
        j = path[pos][i];
        if (!vis[j])
        {
            dfs(j);
        }
    }
    order[ order_pos ++ ] = pos;//make order
}

void ndfs(int pos)
{
    int i, j, l;
    vis[pos] = true;
    id[pos] = scc;
    l = npath[pos].size();
    for (i = 0; i < l; i++)
    {
        j = npath[pos][i];
        if (!vis[j])
        {
            ndfs(j);
        }
    }
}

void topological_sort()
{
    int i, j, ps, now, next;

    while (!SQ.empty())
    {
        now = SQ.front();
        SQ.pop();
        if (color[now] != 0)  //choose a scc without colored
        {
            continue ;
        }
        color[now] = 'R';//color it
        indegre[now] = -1;
        for (i = 1; i <= 2 * n; i++) //delete against scc
        {
            if (id[i] == now)
            {
                int ag_pos;
                if (i % 2 == 0)
                {
                    ag_pos = i - 1;
                }
                else
                {
                    ag_pos = i + 1;
                }
                int ag_id = id[ag_pos];

                while (!SQ2.empty())
                {
                    SQ2.pop();
                }
                SQ2.push(ag_id);
                while (!SQ2.empty())  //delete his son
                {
                    ag_id = SQ2.front();
                    SQ2.pop();
                    if (color[ag_id] == 'B')
                    {
                        continue ;
                    }
                    color[ag_id] = 'B';
                    int ps = dag[ag_id].size();
                    for (j = 0; j < ps; j++)
                    {
                        next = dag[ag_id][j];
                        SQ2.push(next);
                    }
                }//while SQ2
            }
        }//end of delete
        //find next scc
        ps = dag[now].size();
        for (i = 0; i < ps; i++)
        {
            next = dag[now][i];
            indegre[next] --;
            if (indegre[next] == 0)
            {
                SQ.push(next);
            }
        }
    }//while SQ
}

//check 2-sat, false mean no solution
bool Kosaraju()//statist scc O(E)
{
    int i, j;
    //dfs in original graph
    order_pos = 0;
    scc = 0;
    memset(vis, 0, sizeof(vis));
    for (i = 1; i <= 2 * n ; i++)
    {
        if (!vis[i])
        {
            dfs(i);
        }
    }
    //dfs in inverse graph
    memset(vis, 0, sizeof(vis));
    memset(id, 0, sizeof(id));
    scc = 1;
    for (i = order_pos - 1; i >= 0 ; i--)
    {
        if (!vis[ order[i] ])
        {
            ndfs(order[i]);
            scc ++;
        }
    }
    //statist
    for (i = 1; i <= n; i++)
    {
        if (id[i * 2 - 1] == id[i * 2])
        {
            return false;
        }
    }
    scc --;
    return true;
}

void print()
{
    int i, j;
    ans_seq.clear();
    for (i = 1; ans && i <= n ; i++) //O(V)
    {
        if ( color[ id[i * 2 - 1] ] == 'R')
        {
            ans_seq.push_back(i * 2 - 1);
        }
        else
        {
            ans_seq.push_back(i * 2);
        }
    }//for i
    if (!ans)
    {
        puts("NIE");
        return ;
    }
    j = ans_seq.size();
    for (i = 0; i < j; i++)
    {
        printf("%d\n", ans_seq[i]);
    }
}

int main()
{
    int i, j, l;

    while (scanf("%d %d", &n, &m) == 2)
    {
        path.resize(2 * n + 10);
        npath.resize(2 * n + 10);
        for (i = 2 * n + 4; i >= 0; i--)
        {
            path[i].clear();
            npath[i].clear();
        }
        //set up graph and inverse graph
        for (i = 0; i < m; i++)
        {
            int x, y, tx, ty;
            scanf("%d %d", &x, &y);
            if (x % 2 == 0)
            {
                tx = x - 1;
            }
            else
            {
                tx = x + 1;
            }
            if (y % 2 == 0)
            {
                ty = y - 1;
            }
            else
            {
                ty = y + 1;
            }
            path[x].push_back(ty);
            path[y].push_back(tx);
            npath[ty].push_back(x);
            npath[tx].push_back(y);
        }
        //find all scc and check 2-SAT whether have solution
        ans = Kosaraju();
        if (ans)
        {
            dag.resize(scc + 10);
            for (i = 0; i < scc + 10; i++)
            {
                dag[i].clear();
            }
            //set scc dag
            memset(indegre, 0, sizeof(indegre)); //prepare for top-sort
            for (i = 1; i <= 2 * n; i++) //O(E)
            {
                l = path[i].size();
                int id1 = id[i];
                for (j = 0; j < l; j++)
                {
                    int id2 = id[ path[i][j] ];
                    if (id1 != id2)  //id1 -> id2
                    {
                        dag[id2].push_back(id1);//inverse path id2 -> id1
                        indegre[id1] ++;
                    }
                }
            }//for i
            //toplogy sort
            l = SQ.size();
            while (l --)
            {
                SQ.pop();
            }
            for (i = 1; i <= scc; i++)
            {
                if (indegre[i] == 0)
                {
                    SQ.push(i);
                }
            }
            //selecte and delete, color it
            memset(color, 0, sizeof(color));
            topological_sort();
        }//if ans
        print();
    }
}
