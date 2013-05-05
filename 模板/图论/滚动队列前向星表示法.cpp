//滚动队列，前向星表示法
int que[2][2000];
int qf[2],qe[2],qnow;
#define push_que(a)  (que[qnow][ qe[qnow]++  ] = (a))
#define pop_que2  (que[qnow^1][ qf[qnow^1]++  ])
#define switch_que qnow ^=  1; \
          qf[qnow] = qe[qnow] =  0;
#define empty_que2  (qf[qnow^1] >= qe[qnow^1])
#define size_que2  (qe[qnow^1] - qf[qnow^1])
/*前向星表示法
空间O(E+N)
存储所有边，并用链表来实现读取s为起点的有向边
方便插入和遍历所有边,删除是O(E)*/
const int ENDFLAG  = -1;
struct EDGELIST
{
    int start[NMAX];
    int last[NMAX];
    int edge[MMAX][2];//pos,listnext
    int tot;
    void clear()
    {
        tot = ENDFLAG  +1;
        memset(last,ENDFLAG,sizeof(last));
    }
    void push_back(int s,int t)
    {
        edge[tot][0] = t;
        edge[tot][1] = ENDFLAG;
        if (last[s] != ENDFLAG) edge[ last[s] ][1] = tot;
        else start[s] = tot;
        last[s] = tot;
        tot ++;
    }
    int get_start(int s)
    {
        return start[s];
    }
    int get_next(int & p)
    {
        p = edge[p][1];
        return edge[p][0];
    }
    void erase(int s, int t)
    {
        int i,pre = ENDFLAG;
        int p,v;
        for (p=start[s]; p!=ENDFLAG;  p=edge[p][1])
        {
            v = edge[p][0];
            if (v == t)
            {
                if (pre == ENDFLAG) start[s] = edge[p][1];
                else edge[pre][1]  = edge[p][1];
            }
            else pre = p;
        }
        last[s] = pre;
    }
};
