// 题意：有个人想访问所有的好友，不走重复的路，街道有编号，如果访问好友有很多种选择的话，选择编号最小的走，判断是否存在这样的路，如果存在输出路径标号。
// 输入：街道和交叉口的编号，起点是第一条街道中的较小点。
// 输出：如果有路输出路径编号，如果没有输出信息。
// 思路：这道题目首先题目告诉是个连通图，所以不用判断是否连通，然后判断欧拉回路。之后就是DFS走一遍这条路，保存在栈中，然后倒序打印即可。
// 程序：
#include <cstdio>
const int MAX = 2000;
const int MAX_JUNCTION = 45;
struct Street
{
    int junc1, junc2;
    bool visited;
};
Street street[MAX];
int degree[MAX_JUNCTION];
int start, n, m, top, stack[MAX];
void init()
{
    for(int i=0;i<MAX_JUNCTION;i++)degree[i]=0;
    start = 0, n = 0, m = 0, top = 0;
    for (int i = 0; i < MAX; i++)
        street[i].visited = false;
}
bool isEuler()//判断欧拉回路是否存在，所有点度均为0
{
    for (int i = 1; i <= m; i++)
        if (degree[i] % 2)
            return false;
    return true;
}
void DFS(int v)//递归遍历这条路。这里让定点序最小的技巧很好
{
    for (int i = 1; i <= n; i++)
    {
        if (!street[i].visited && (street[i].junc1 == v || street[i].junc2 == v))
        {
            street[i].visited = true;
            int next = street[i].junc1 == v ? street[i].junc2 : street[i].junc1;
            DFS(next);
            stack[top++] = i;
        }
    }
}
int max(int x,int y)
{
    if(x>=y)return x;
    return y;
}
int min(int x,int y)
{
    if(x<=y)return x;
    return y;
}
int main()
{
    int x, y, z;
    while (scanf("%d%d",&x,&y)!=EOF&& !(x == 0 && y == 0))
    {
        init();//初始化
        do
        {
            if (start == 0)start=min(x,y);
            scanf("%d",&z);
            n++;
            m = max(m, max(x, y));
            degree[x]++, degree[y]++;
            street[z].junc1 = x, street[z].junc2 = y;
        }while (scanf("%d%d",&x,&y)!=EOF&& !(x == 0 && y == 0));
        if (isEuler())
        {
            DFS(start);
            for (int i = top - 1; i >= 0; i--)
            {
                printf("%d",stack[i]);
                if (i != 0)printf(" ");
            }
            printf("\n");
        }
        else
        printf("Round trip does not exist.\n");
    }
}
