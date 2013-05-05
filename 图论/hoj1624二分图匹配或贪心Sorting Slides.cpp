// 题目大意： 这道题的意思是一些大小不等透明的幻灯片（只有轮廓和上面的数字可见）
// A、B、C、D、E…按顺序叠放在一起，现在知道每个幻灯片左上角和右下角的坐标，并且
// 由于幻灯片是透明的，所以能看到幻灯片上的数字（给出了每个数字的坐标，但不知道
// 这些数字分别属于哪个幻灯片），现在要你根据当前的已知信息，输出能够确定的幻灯
// 片编号和数字的匹配，例如(A,4) (B,1) (C,2) (D,3)；　解题思路：网上常说什么二分
// 图的必须边，需要先匈牙利一遍再一一删边求答案。但个人觉得没必要，这题一看，第一眼：
// 贪心。我每次贪一个维度为1的点，然后把他的对应点找出来，然后将与对应点相连的点的
// 维度都减去1.然后继续贪心。

#include <stdio.h>
#include <string.h>
#include <vector>
#define N 60
using namespace std;

vector<int>gra[N];
int dis[N], vis[N];
int map[N][4], n, mat[N];

void read()
{
    for (int i = 1; i <= 2 * n; i++)
        gra[i].clear();
    memset(dis, 0, sizeof(dis));
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d%d", &map[i][0], &map[i][1], &map[i][2], &map[i][3]);
    for (int i = 1; i <= n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        for (int j = 1; j <= n; j++)
            if ((x > map[j][0] && x < map[j][1]) && (y > map[j][2] && y < map[j][3]))
            {
                gra[i + n].push_back(j);
                gra[j].push_back(i + n);
                dis[i + n]++;
                dis[j]++;
            }
    }
}

void run()
{
    memset(vis, 0, sizeof(vis));
    memset(mat, 0, sizeof(mat));
    for (int i = 1; i <= n; i++)
    {
        int pos;
        for (pos = 1; pos <= 2 * n; pos++)
            if (!vis[pos] && dis[pos] == 1)
                break;
        if (pos > 2 * n)
        {
            break;
        }
        vis[pos] = 1;
        int opp;
        for (int i = 0; i < gra[pos].size(); i++)
            if (!vis[gra[pos][i]])
            {
                opp = gra[pos][i];
                break;
            }
        vis[opp] = 1;
        for (int i = 0; i < gra[opp].size(); i++)
            dis[gra[opp][i]]--;
        if (opp < pos)
        {
            int temp = pos;
            pos = opp; opp = temp;
        }
        mat[pos] = opp;
    }
    int flag = 0;
    for (int i = 1; i <= n; i++)
    {
        if (mat[i] < n)continue;
        if (flag)printf(" ");
        printf("(%c,%d)", i - 1 + 'A', mat[i] - n);
        flag++;
    }
    if (!flag)
        printf("none");
    puts("\n");
}
int main()
{
    int h = 1;
    while (scanf("%d", &n), n)
    {
        read();
        printf("Heap %d\n", h++);
        run();
    }
    return 0;
}
