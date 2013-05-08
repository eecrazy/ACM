// 采用Prim算法求最小生成树。

// 关于如何求球面上任意两点A（a1,b1）和 B(  a2,b2 ) 的球面距离，a1,a2是经度，b1,b2是纬度，参考公式：

// r * acos(cos(a1 - a2) * cos(b1) * cos(b2) + sin(b1) * sin(b2))
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <math.h>
#include <algorithm>

using namespace std;

double p[102][2];
double map[102][102];
double dist[102];
int visited[102];

double r = 16.7 / 2;

//ai-经度,bi-纬度
double dis(double a1, double b1, double a2, double b2)
{

    a1 = acos(-1) * a1 / 180;//度数转化为弧度制
    b1 = acos(-1) * b1 / 180;
    a2 = acos(-1) * a2 / 180;
    b2 = acos(-1) * b2 / 180;

    return r * acos(cos(a1 - a2) * cos(b1) * cos(b2) + sin(b1) * sin(b2));
}
int main()
{

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    int n;
    int t = 0;
    while (scanf(" %d", &n) != EOF && n != 0)
    {
        t++;
        for (int i = 0; i < n; i++)
        {
            scanf(" %lf %lf", &p[i][0], &p[i][1]); //经度、纬度
        }

        memset(map, 0, sizeof(map));

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                map[i][j] = map[j][i] = dis(p[i][0], p[i][1], p[j][0], p[j][1]);
            }
        }
        // 初始化
        memset(dist, 0x7f, sizeof(dist));
        memset(visited, 0, sizeof(visited));
        dist[0] = 0;
        double sum = 0;

        for (int i = 0; i < n; i++)//循环n次
        {
            int k = 0;
            double min = 0x7f;
            //最短的dist[k]
            for (int j = 0; j < n; j++)
            {
                if (!visited[j] && dist[j] < min)
                {
                    min = dist[j];
                    k = j;
                }
            }
            visited[k] = 1;
            sum += min;
            //松弛该点
            for (int j = 0; j < n; j++)
            {
                if (dist[j] > map[k][j])
                {
                    dist[j] = map[k][j];
                }
            }
        }
        printf("Case %d: %.2lf miles\n", t, sum);
    }
    return 0;

}
