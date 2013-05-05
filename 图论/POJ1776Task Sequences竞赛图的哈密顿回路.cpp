// 竞赛图的哈密顿回路.
// 本题要求用最少的简单回路将所有的顶点覆盖,可以看成是最小路径覆盖问题.
// 如果注意到题目给出的图是竞赛图的话,那么就可以直接得到一个结论:竞赛图必然存在一条覆盖所有顶点的简单回路,也就是哈密顿回路.因此本题要做的就是构造出一条竞赛图的哈密顿回路就行了.
// 构造方法：
// 初始：将点1加入没有边的路中。
// 考虑点2。如果有（1，2），则将2加入1之后，形成1    2路，否则，将2加入1之前，形成2     1。
// 依次考虑点3，4，5 ………i；设形成路     a1,a2,a3,………,ai;
// 现在将i+1加入此路，
// 如果有（i+1，a1),则将i+1加入a1之前；否则，有（a1,i+1),      如果有（i+1,a2),则将i+1加入a1和a2之间；否则，考虑（a2,i+1)………。直到最后，如果有(ai,i+1),则将i+1加入ai之后。
// 这道题如果用scanf读入的话竟然会超时,改用gets()整行读取才110MS.

#include <cstdio>
#include <string.h>
using namespace std;
#define MAXN 1000
bool map[MAXN][MAXN];
int next[MAXN];
int head;
int n;
char line[2500];
int main()
{
    int i, j, k;
    while(scanf("%d", &n) != EOF)
    {

        getchar();
        for(i = 0; i < n; i++)
        {
            gets(line);
            int ct;
            for(j = 0, ct = 0; j < 2 * n - 1; j += 2)
            {
                map[i][ct++] = line[j] - '0';
            }
            next[i] = -1;
        }
        head = 0;
        for(i = 1; i < n; i++)
        {
            if(map[i][head])
            {
                next[i] = head;
                head = i;
                continue;
            }
            j = head;
            k = next[j];
            while(k != -1)
            {
                if(map[j][i] && map[i][k])
                    break;
                j = k;
                k = next[j];
            }
            next[i] = k;
            next[j] = i;
        }
        printf("1\n%d\n", n);
        for(i = 0; i < n; i++)
        {
            if(i > 0)printf(" ");
            printf("%d", head + 1);
            head = next[head];
        }
        printf("\n");
    }
    return 0;
}
