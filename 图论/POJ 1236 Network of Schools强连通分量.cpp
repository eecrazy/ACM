/*相当经典的题目了. 题的描述有点儿长, 我就不想再描述了...
题中的任务A, 其本质就是求这个有向图中所有强连通分量中, 入度为0的个数. 原理还是挺好理解的:
入度不为0的强连通分量, 显然可以由其他强连通分量达到. 也就是说, 要想让所有学校都拿到软件,
需要且只需要从入度为0的那些强连通分量出发即可.
题中的任务B稍微复杂些., 意思是增加多少条边, 可以使整个图变成强连通的. 这时需要分别统计入度
为0和出度为0的点, 设它们的个数分别是a, b. 首先, 我们可以在入度为0和出度为0的点之间连边. 之后,
如果入度 / 出度为0的点有剩余, 就把它们和其他点连边. 因此, 需要连的边条数为 max(a, b).*/

#include <cstdio>
#include <iostream>
using namespace std;
#define maxn 105
#define maxm 3000
int top;//栈顶位置
int Bcnt;//强连通分量编号
int Index;//时间顺序
int DFN[maxn];//时间戳
int LOW[maxn];
int belong[maxn];//顶点i属于哪个强连通分量
int Stack[maxn];//栈
int instack[maxn];//是否在栈内
int n, m;
struct node
{
    int to;
    int next;
} edge[maxm];
int head[maxn];
bool Judge[maxn];
bool Judge2[maxn];
int ansi;
void init()
{
    fill(head, head + n + 1, -1);
    fill(DFN, DFN + n + 1, 0);
    fill(Judge, Judge + n + 1, true);
    fill(Judge2, Judge2 + n + 1, true);
    ansi = 0;
    top = 0;
    Bcnt = 0;
    Index = 0;
}
void add(int a, int b)
{
    edge[ansi].to = b;
    edge[ansi].next = head[a];
    head[a] = ansi++;
}
void read()
{
    int a;
    for (int i = 1; i <= n; i++)
    {
        while (scanf("%d", &a) && a)
            add(i, a);
    }
}
void tarjan(int i)
{
    int j, k;
    DFN[i] = LOW[i] = ++Index;
    instack[i] = true;
    top++;
    Stack[top] = i;
    for (k = head[i]; k != -1; k = edge[k].next)
    {
        j = edge[k].to;
        if (!DFN[j])//j未访问，用dfn值标记是否已访问过
        {
            tarjan(j);
            if (LOW[j] < LOW[i])
                LOW[i] = LOW[j];
        }
        else if (instack[j] && DFN[j] < LOW[i])
            LOW[i] = DFN[j];
    }
    if (DFN[i] == LOW[i]) //dfn和low相等，递归打印强连通分量
    {
        Bcnt++;//强连通分量编号
        do
        {
            j = Stack[top--];
            instack[j] = false;
            belong[j] = Bcnt;
        }
        while (j != i);
    }
}
void judge1()
{
    for (int i = 1; i <= n; i++)
        for (int k = head[i]; k != -1; k = edge[k].next)
        {
            if (belong[i] != belong[edge[k].to])
                Judge[belong[i]] = false;
        }
}
void judge2()
{
    for (int i = 1; i <= n; i++)
        for (int k = head[i]; k != -1; k = edge[k].next)
        {
            if (belong[i] != belong[edge[k].to])
                Judge2[belong[edge[k].to]] = false;
        }
}
void solve()
{
    init();
    read();
    for (int i = 1; i <= n; i++)
        if (!DFN[i])
            tarjan(i);
    judge1();
    judge2();
    int s1 = 0; //所有出度为零的
    int s2 = 0; //所有入度为零的
    for (int i = 1; i <= Bcnt; i++)
    {
        if (Judge[i])s1++;
        if (Judge2[i])s2++;
    }
    printf("%d\n", s2);
    int ss;//注意这里，只有一个联通块的时候，输出零。因为不需要添加边
    if (Bcnt == 1)ss = 0;
    else ss = max(s1, s2);
    printf("%d\n", ss);
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while (scanf("%d", &n) != EOF)
    {
        solve();
    }
}
