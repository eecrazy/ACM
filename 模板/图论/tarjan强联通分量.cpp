#include <iostream>
#include <cstdio>
using namespace std;
#define maxn 1000
int top;//栈顶位置
int Bcnt;//强连通分量编号
int index;//时间顺序
int DFN[maxn];//时间戳
int LOW[maxn];
int belong[maxn];//顶点i属于哪个强连通分量				
int Stack[maxn];//栈
int instack[maxn];//是否在栈内

struct node
{
	int t;
	node *next;
}V[maxn];


void tarjan(int i)
{
    int j;
    DFN[i]=LOW[i]=++index;
    instack[i]=true;
    Stack[++top]=i;
    for (node *e=V[i]; e; e=e->next)
    {
        j=e->t;
        if (!DFN[j])//j未访问，用dfn值标记是否已访问过
        {
            tarjan(j);
            if (LOW[j]<LOW[i])
                LOW[i]=LOW[j];
        }
        else if (instack[j] && DFN[j]<LOW[i])
            LOW[i]=DFN[j];
    }
    if (DFN[i]==LOW[i])//dfn和low相等，递归打印强连通分量
    {
        Bcnt++;//强连通分量编号
        do
        {
            j=Stack[top--];
            instack[j]=false;
            belong[j]=Bcnt;
        }
        while (j!=i);
    }
}
void solve()
{
    int i;
    top=Bcnt=index=0;
    memset(DFN,0,sizeof(DFN));
    for (i=1; i<=N; i++)
        if (!DFN[i])
            tarjan(i);
}
int main()
{

}