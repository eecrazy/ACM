#include <cstdio>
#define keyTree (ch[ ch[root][1] ][0])
const int maxn = 222222;
struct SplayTree
{
    int sz[maxn];
    int ch[maxn][2];
    int pre[maxn];
    int root , top1 , top2;
    int ss[maxn] , que[maxn];

    inline void Rotate(int x, int f)
    {
        int y = pre[x];
        push_down(y);
        push_down(x);
        ch[y][!f] = ch[x][f];
        pre[ ch[x][f] ] = y;
        pre[x] = pre[y];
        if (pre[x]) ch[ pre[y] ][ ch[pre[y]][1] == y ] = x;
        ch[x][f] = y;
        pre[y] = x;
        push_up(y);
    }
    inline void Splay(int x, int goal)
    {
        push_down(x);
        while (pre[x] != goal)
        {
            if (pre[pre[x]] == goal)
            {
                Rotate(x , ch[pre[x]][0] == x);
            }
            else
            {
                int y = pre[x] , z = pre[y];
                int f = (ch[z][0] == y);
                if (ch[y][f] == x)
                {
                    Rotate(x , !f) , Rotate(x , f);
                }
                else
                {
                    Rotate(y , f) , Rotate(x , f);
                }
            }
        }
        push_up(x);
        if (goal == 0) root = x;
    }
    inline void RotateTo(int k, int goal) //把第k位的数转到goal下边
    {
        int x = root;
        push_down(x);
        while (sz[ ch[x][0] ] != k)
        {
            if (k < sz[ ch[x][0] ])
            {
                x = ch[x][0];
            }
            else
            {
                k -= (sz[ ch[x][0] ] + 1);
                x = ch[x][1];
            }
            push_down(x);
        }
        Splay(x, goal);
    }
    inline void erase(int x)  //把以x为祖先结点删掉放进内存池,回收内存
    {
        int head = 0 , tail = 0;
        for (que[tail++] = x ; head < tail ; head ++)
        {
            ss[top2 ++] = que[head];
            if (ch[ que[head] ][0]) que[tail++] = ch[ que[head] ][0];
            if (ch[ que[head] ][1]) que[tail++] = ch[ que[head] ][1];
        }
    }
    //以上一般不修改//////////////////////////////////////////////////////////////////////////////
    void debug()
    {
        printf("%d\n", root);
        Treaval(root);
    }
    void Treaval(int x)
    {
        if (x)
        {
            Treaval(ch[x][0]);
            printf("结点%2d:左儿子 %2d 右儿子 %2d 父结点 %2d size = %2d ,val = %2d\n", x, ch[x][0], ch[x][1], pre[x], sz[x], val[x]);
            Treaval(ch[x][1]);
        }
    }
    //以上Debug


    //以下是题目的特定函数:
    inline void NewNode(int &x, int c)
    {
        if (top2) x = ss[--top2];//用栈手动压的内存池
        else x = ++top1;
        ch[x][0] = ch[x][1] = pre[x] = 0;
        sz[x] = 1;

        val[x] = sum[x] = c;/*这是题目特定函数*/
        add[x] = 0;
    }

    //把延迟标记推到孩子
    inline void push_down(int x)  /*这是题目特定函数*/
    {
        if (add[x])
        {
            val[x] += add[x];
            add[ ch[x][0] ] += add[x];
            add[ ch[x][1] ] += add[x];
            sum[ ch[x][0] ] += (long long)sz[ ch[x][0] ] * add[x];
            sum[ ch[x][1] ] += (long long)sz[ ch[x][1] ] * add[x];
            add[x] = 0;
        }
    }
    //把孩子状态更新上来
    inline void push_up(int x)
    {
        sz[x] = 1 + sz[ ch[x][0] ] + sz[ ch[x][1] ];
        /*这是题目特定函数*/
        sum[x] = add[x] + val[x] + sum[ ch[x][0] ] + sum[ ch[x][1] ];
    }

    /*初始化*/
    inline void makeTree(int &x, int l, int r, int f)
    {
        if (l > r) return ;
        int m = (l + r) >> 1;
        NewNode(x , num[m]);        /*num[m]权值改成题目所需的*/
        makeTree(ch[x][0] , l , m - 1 , x);
        makeTree(ch[x][1] , m + 1 , r , x);
        pre[x] = f;
        push_up(x);
    }
    inline void init(int n)  /*这是题目特定函数*/
    {
        ch[0][0] = ch[0][1] = pre[0] = sz[0] = 0;
        add[0] = sum[0] = 0;

        root = top1 = 0;
        //为了方便处理边界,加两个边界顶点
        NewNode(root , -1);
        NewNode(ch[root][1] , -1);
        pre[top1] = root;
        sz[root] = 2;


        for (int i = 0 ; i < n ; i ++) scanf("%d", &num[i]);
        makeTree(keyTree , 0 , n - 1 , ch[root][1]);
        push_up(ch[root][1]);
        push_up(root);
    }
    /*更新*/
    inline void update( )  /*这是题目特定函数*/
    {
        int l , r , c;
        scanf("%d%d%d", &l, &r, &c);
        RotateTo(l - 1, 0);
        RotateTo(r + 1, root);
        add[ keyTree ] += c;
        sum[ keyTree ] += (long long)c * sz[ keyTree ];
    }
    /*询问*/
    inline void query()  /*这是题目特定函数*/
    {
        int l , r;
        scanf("%d%d", &l, &r);
        RotateTo(l - 1 , 0);
        RotateTo(r + 1 , root);
        printf("%lld\n", sum[keyTree]);
    }


    /*这是题目特定变量*/
    int num[maxn];
    int val[maxn];
    int add[maxn];
    long long sum[maxn];
} spt;


int main()
{
    int n , m;
    scanf("%d%d", &n, &m);
    spt.init(n);
    while (m --)
    {
        char op[2];
        scanf("%s", op);
        if (op[0] == 'Q')
        {
            spt.query();
        }
        else
        {
            spt.update();
        }
    }
    return 0;
}
