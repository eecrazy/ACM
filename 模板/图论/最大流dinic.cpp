#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
#define N 2000
#include <fstream>
#define inf 2000000000
using namespace std;
int p[N];
int level[N];
int idx;
bool mark[N];
int que[N*N];

struct node 
{
    int v, cap, next;
} e[N*N];

void add(int u, int v, int c) {
    e[idx].v = v, e[idx].cap = c, e[idx].next = p[u], p[u] = idx, idx++;
    e[idx].v = u, e[idx].cap = 0, e[idx].next = p[v], p[v] = idx, idx++;
}

bool bfs(int s, int t) {
    int i, j;
    int u, v;
    int head = 0;
    int tail = 1;
    memset(level, -1, sizeof (level));
    level[s] = 0;
    que[0] = s;
    while (head != tail) {
        u = que[head];
        head++;
        if (head == N * N)
            head = 0;
        for (i = p[u]; i != -1; i = e[i].next) {
            v = e[i].v;
            if (level[v] == -1 && e[i].cap) {
                level[v] = level[u] + 1;
                que[tail++] = v;
                if (tail == N * N)
                    tail = 0;
            }
        }
    }
    return (level[t] >= 0);
}

int dfs(int s, int t, int c) {
    mark[s] = 1;
    if (s == t)
        return c;
    int i, j;
    int v;
    int sum = c;
    int ans;
    for (i = p[s]; i != -1; i = e[i].next) {
        v = e[i].v;
        if ((!mark[v]) && (level[v] == level[s] + 1) && e[i].cap) {
            ans = dfs(v, t, min(c, e[i].cap));
            if (ans > 0) {
                e[i].cap -= ans;
                e[i^1].cap += ans;
                return ans;
            }
        }
    }
    return 0;
}

int dinic(int s, int t) {
    int ans = 0;
    int i, flow;
    while (bfs(s, t)) {
        while (1) {
            memset(mark, false, sizeof (mark));
            flow = dfs(s, t, inf);
            if (flow == 0)
                break;
            ans += flow;
        }
    }
    return ans;
}

int main() {
    int m, end;
    int u, v, c;
    int cs;
    int T;
    int s, t;
    ifstream in;
    ifstream on;
    char ss[12];
    ofstream dd;
    on.open("321.txt");
    dd.open("222.txt");
    in.open("123.txt");
    in >> T;
    int n;
    while (T--) {
    memset(p, -1, sizeof (p));
    idx=0;
        in >> ss >> cs;
        in >> n >> m >> s >> t;
        for (int i = 0; i < m; i++) {
            in >> u >> v >> c;
            add(u, v, c);
        }
        int ans2;
        int ans1 = dinic(s, t);
        on >> ans2;
        if (ans1 != ans2)
            cout << cs << endl;
        dd << ans1 << endl;
    }
    return 0;
}

// +++++++++++++++++++++++++++++++++++++++++++
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <string>
#define INF 0x3fffffff
#define F(x) (x)
#define N(x) (205+(x))
#define CPN(x) (410+(x))
#define D(x) (615+(x))
#define maxn 250
#define CL(a,b) memset(a,b,sizeof(a))
#define Pnum 210
using namespace std;

int next[maxn*20],dis[maxn*10];
int s,e;
int  n, fnum ,dnum ,f[maxn],d[maxn],cnt;
struct node
{
  int to;
  int cap ;
  int next ;
}p[200000] ;
int que[maxn*maxn] ,idx;
void add(int x,int y,int cap)// 建边 注意 反向边的流量为 0
{
  p[cnt].to = y;
  p[cnt].cap = cap ;
  p[cnt].next = next[x];
  next[x] = cnt++ ;

  p[cnt].to = x;
  p[cnt].cap = 0;
  p[cnt].next = next[y];
  next[y] = cnt++ ;
}
int bfs()// 重新 建 图 （按 层数 建图）
{

  memset(dis,0xff,sizeof(dis)) ;
  dis[s] = 0 ;
  queue<int>que;
  que.push(s);
  while(!que.empty())
  {
      int  k = que.front();que.pop() ;
      for( int i = next[k];i!=-1;i = p[i].next)
      {
          int v = p[i].to;
          int cap = p[i].cap ;
          if(cap > 0 && dis[v] < 0 )// 如果 可以  可以到达 但 还没有 访问
          {
              dis[v] = dis[k]+ 1 ;
              que.push(v) ;
          }
      }
  }

  if(dis[e] > 0) return 1;
  else return  0 ;
}
int  dfs(int x,int mx)// 查找  路径上的 最小 的 流量
{
  int i , a ,tf =  0;
  if(x == e) return mx ;
  for(i = next[x];i!= - 1;i = p[i].next)
  {
      int v = p[i].to ;
      int cap = p[i].cap ;
      if(cap > 0 && dis[v] == dis[x] + 1  && (a =dfs(v,min(cap,mx))))
      {
          p[i].cap -= a;
          p[i^1].cap += a;

            return a;
      }
  }
  if(!tf) dis[x] = -1;// 没有 找到 最小流量 ，说明 从这个点到不了 终点 ，所以  标记一下
  return tf ;
}
int main()
{
 int i , j ;
 char c[250] ;
  //freopen("data.txt","r",stdin) ;
 while(scanf("%d%d%d",&n,&fnum,&dnum)!=EOF)
 {

     CL(next,-1) ;
     cnt = 0;
      s = 0;
      e = 2000;
      for(i = 1 ; i <= fnum;i++)
      {
          scanf("%d",&f[i]);
      }
      for(i = 1 ; i<= dnum;i++)
      {
          scanf("%d",&d[i]) ;
      }
      for(i = 1; i <= n;i++)//  人 和 吃的
      {
          scanf("%s",c);
          for(j = 0 ;  j< fnum ;j++)
          {
              if(c[j] == 'Y')
              {
                  add(j + 1,i + Pnum,1) ;
              }
          }
      }
      for(i = 1; i<= n;i++)//  人 和 喝的
      {
          scanf("%s",c);
          for(j = 0 ;  j< dnum ;j++)
          {
              if(c[j] == 'Y')
              {
                  add(i + Pnum*2,j + Pnum*3 + 1,1) ;
              }
          }
      }
      for(i = 1; i <= fnum;i++)//增加源点
      {
          add(0,i,f[i]) ;
      }
      for(i = Pnum*3  + 1,j = 1; j <= dnum;i++,j++)//增加 汇点
      {
          add(i,e,d[j]) ;
      }
      for(i = 1; i <= n;i++)//  将人 拆分
      {
          add(i + Pnum,i +Pnum*2,1);
      }
        int ans = 0;
    int res;
    while(bfs())
    {
       while(res = dfs(s,INF)) ans+= res ;
    }
    printf("%d\n",ans);
 }
}