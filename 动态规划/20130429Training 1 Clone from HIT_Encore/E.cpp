// 题目：http://acm.uestc.edu.cn/problem.php?pid=1650
// 题意：给你n个城市的坐标，你可以随便选一个位置建立电站，来给n个城市供电，有的城市
// 也可以自己供电，但最多只能有k个城市自己供电
// 分析：当k等于0时，很显然，这个电站必须建在所有点x轴的中位数，和y轴的中位数，但是
// 如何考虑k个城市自己供电，使得答案更优呢
// 今天的模拟赛时，没细心去想，其实删掉k个点给中位数带来的波动不大，就原来中位数的
// 左右k / 2 + 1的波动，由于k相当小，直接暴力枚举所有电站的位置，然后统计答案即可，
// 怎么统计不用我说了吧。。。。
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int mm = 1111;
int x[mm], y[mm], a[mm], b[mm], c[mm];
int i, j, n, m, t, l, r, ans, cs = 0;
void work(int x0, int y0)
{
    priority_queue<int>q;
    int i, sum;
    for (sum = i = 0; i < n; ++i)
    {
        sum += fabs(x[i] - x0) + fabs(y[i] - y0);
        q.push(c[i] - fabs(x[i] - x0) - fabs(y[i] - y0));
        if (q.size() > m)q.pop();
        if (!q.empty() && q.top() >= 0)q.pop();
    }
    while (!q.empty())sum += q.top(), q.pop();
    ans = min(ans, sum);
}
int main()
{
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        for (i = 0; i < n; ++i)
            scanf("%d", &c[i]);
        for (i = 0; i < n; ++i)
            scanf("%d%d", &x[i], &y[i]), a[i] = x[i], b[i] = y[i];
        sort(a, a + n);
        sort(b, b + n);
        l = max(0, n / 2 - m / 2 - 1);
        r = min(n - 1, n / 2 + m / 2 + 1);
        ans = 2e9;
        for (i = l; i <= r; ++i)
            for (j = l; j <= r; ++j)
                work(a[i], b[j]);
        printf("Case #%d: %d\n", ++cs, ans);
    }
    return 0;
}
