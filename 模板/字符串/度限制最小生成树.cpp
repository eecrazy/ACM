//度限制最小生成树
/**** **** **** **** **** ****
*      Function Name  :  度限制最小生成树
*      Description  :          PKU  1639  Picnic Planning
*            有一个顶点有度限制，如果所有点都有限制，当限制>4时是NP
**** **** **** **** **** ****/
#include <cstdio>
#include <string>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
const int MAX = 50;
int t,n,m;
map<string  , int>  names;
int path[MAX][MAX];
//dmax[i]:  vi->park，不与park相连的边的最大权值
int dmax[MAX];
struct node
{
    int s,t;
    int dis;
    bool operator < (const node & tt) const
    {
        return dis > tt.dis;
    }
};
bool vis[MAX];
//block[i]:  vi所属连通分量
//bs: 连通分量数目
//v0min[i][2]:  park与第i个连通分量的最小权值[0]，连接顶点[1]
int block[MAX], v0min[MAX][2],  bs;
//mst: 度限制生成树
vector<int>  mst[MAX];
queue<int>  sq;
//最小花费，park下标，限制度数
int cost, park, deg;
//O(NlogN)  prime求所有连通分量mst
void prime_all_mst()
{
    int i,j;
    priority_queue<node>  pq;
    node now, next;
    memset(vis,  0,sizeof(vis));
    for(i=0; i<=n; i++)  mst[i].clear();
    vis[park]  = true;
    block[park]  = 1;
    bs =  1;//park为第个连通分量
    cost =  0;
    for(i=1; i<=n; i++)
    {
        if(!vis[i])
        {
            bs ++;
            while(!pq.empty())  pq.pop();
            now.s =  i;
            now.t =  i;
            now.dis =  0;
            pq.push(now);
            while(!pq.empty())
            {
                now =  pq.top();
                pq.pop();
                if(vis[now.t]) continue;
                vis[now.t] = true;
                mst[now.s].push_back(now.t);
                mst[now.t].push_back(now.s);
                block[now.t] =  bs;
                cost +=  now.dis;
                next.s =  now.t;
                for(j=1; j<=n; j++)
                {
                    if(!vis[j]  && path[next.s][j] != -1)
                    {
                        next.t =  j;
                        next.dis =  path[next.s][j];
                        pq.push(next);
                    }
                }
            }
        }
    }
}
//O(N) park连接各连通分量
bool connect_block()
{
    int i,j,k;
    //选取连接相邻连通分量的最小边
    for(i=2; i<=bs; i++)  v0min[i][0]  =  INT_MAX;
    while(!sq.empty())  sq.pop();
    for(i=1; i<=n; i++)
    {
        if(path[park][i]  != -1 && v0min[block[i]][0]  > path[park][i])
        {
            v0min[block[i]][0]  = path[park][i];
            v0min[block[i]][1]  = i;
        }
    }
    k = 0;
    for(i=2; i<=bs; i++)
    {
        if(v0min[i][0]  !=  INT_MAX)
        {
            cost +=  v0min[i][0];
            path[park][  v0min[i][1]  ] = -1;
            dmax[  v0min[i][1]  ] =  INT_MIN;
            sq.push(v0min[i][1]);//用来初始化dmax
            k ++;//能连通的分量数}}
            //图连通，且限制度数大于等于连通分量数
            deg -= bs-1;
            return k >=  bs-1 && deg >=  0;
        }
//O(N) 计算dmax
        void cal_dmax()
        {
            int i;
            memset(vis,  0, sizeof(vis));
            while(!sq.empty())
            {
                int now =  sq.front();
                sq.pop();
                vis[now]  = true;
                for(i=0; i<mst[now].size(); i++)
                {
                    int next = mst[now][i];
                    if(!vis[next])
                    {
                        dmax[next]  = max(dmax[now],  path[now][next]);
                        sq.push(next);
                        vis[next]  = true;
                    }
                }
            }
        }
//O(N) 差额最小删除操作
        void del_path(int pos, int val)
        {
            int i;
            queue<int>  sq2;
            memset(vis,  0, sizeof(vis));
            sq2.push(pos);
            vis[pos]  = true;
            while(!sq2.empty())
            {
                int now =  sq2.front();
                sq2.pop();
                for(i=0; i<mst[now].size(); i++)
                {
                    int next = mst[now][i];
                    if(!vis[next])
                    {
                        if(val ==  path[now][next])
                        {
                            mst[now].erase(mst[now].begin()  +i);
                            return;
                        }
                        sq2.push(next);
                        vis[next]  = true;
                    }
                }
            }
        }
//O(deg*N)
        bool deg_limit_mst()
        {
            int i,j,v;
            int minv,minp;
            cal_dmax();
            for(i=0; i<deg; i++)
            {
                minv  =  INT_MAX;
                minp  = -1;
                for(j=1; j<=n; j++)
                {
                    if(path[park][j]  != -1)  //差额最小选择操作
                    {
                        if(minv  >  path[park][j] - dmax[j])
                        {
                            minv  = path[park][j] - dmax[j];
                            minp  =  j;
                        }
                    }
                }
                v = cost +  minv;
                if(minp  == -1 || v >=  cost) return false;
                cost =  v;
                path[park][minp]  = -1;//差额最小添加删除操作
                del_path(minp,  dmax[minp]);
                mst[park].push_back(minp);
                while(!sq.empty())  sq.pop();
                sq.push(minp);
                dmax[minp]  =  INT_MIN;
                cal_dmax();
            }
            for(i=0; i<mst[park].size(); i++)  mst[ mst[park][i]  ].push_back(park);
            return true;
        }
        int main()
        {
            int i,j;
            char n1[20],  n2[20];
            names.clear();
            scanf("%d",  &m);
            memset(path,  -1, sizeof(path));
            n = 1;
            for(i=0; i<m; i++)
            {
                int x,y,z;
                scanf("%s %s %d",  n1,n2,&z);
                x = names[string(n1)];
                y  = names[string(n2)];
                if(x ==  0) names[string(n1)]  =  x =  n ++;
                if(y ==  0) names[string(n2)]  =  y =  n ++;
                if(strcmp(n1,"Park")  ==  0) park =  x;
                else if(strcmp(n2,"Park")  ==  0) park  = y;
                path[x][y] = path[y][x] =  z;
            }
            n --;
            scanf("%d", &deg);
            prime_all_mst();
            connect_block();
            deg_limit_mst();
            printf("Total miles  driven:  %d\n",  cost);
        }
