#include <cstdio>
#include <iostream>
using namespace std;
#define maxn 500
#define maxm 10000
int top;//栈顶位置
int Bcnt;//强连通分量编号
int Index;//时间顺序
int DFN[maxn];//时间戳
int LOW[maxn];
int belong[maxn];//顶点i属于哪个强连通分量
int Stack[maxn];//栈
int instack[maxn];//是否在栈内
int n, m, p;
struct node
{
    int to;
    int next;
} edge[maxm];
int head[maxn];
int ansi;
void init()
{
    memset(head, -1, sizeof(head));
    memset(DFN, 0, sizeof(DFN));
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
    int a, b;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d", &a, &b);
        add(a, b + n);
        add(b, a + n);
    }
    for (int i = 1; i <= p; i++)
    {
        scanf("%d%d", &a, &b);
        add( b + n,a);
        add( a + n,b);
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
void solve()
{
    init();
    read();
    for (int i = 1; i <= 2*n; i++)
        if (!DFN[i])
            tarjan(i);
    for (int i = 1; i <= n; i++)
    {
        if(belong[i]==belong[i+n])
        {
            puts("No");
            return ;
        }
    }
    puts("Yes");
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    while (scanf("%d%d%d", &n, &m, &p) != EOF)
    {
        solve();
    }
}
