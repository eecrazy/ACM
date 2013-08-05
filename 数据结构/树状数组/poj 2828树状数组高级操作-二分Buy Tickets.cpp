#include  <cstdio>
using namespace std;
#define maxn 200005
int n;
int c[maxn];
int Val[maxn][2];
int ans[maxn];
int lowbit(int x)
{
    return x & (-x);
}
//填充一  技巧性！！！
void fillone ()
{
    int i;
    for (i = 1; i <= n; i++)
        c[i] = lowbit(i);
    return;
}

int sum(int x)
{
    int ret = 0;
    while (x > 0)
    {
        ret += c[x];
        x -= lowbit(x);
    }
    return ret;
}
void add(int i)
{
    while (i <= n)
    {
        c[i]--;
        i += lowbit(i);
    }
}
// 这是树状数组的高级操作，找部分和
int sumseek (int k)
{
    int ans = 0, sum = 0, i;
    for (i = 18; i >= 0; i--)
    {
        ans += (1 << i);
        if (ans >= n || sum + c[ans] >= k) ans -= (1 << i);
        else sum += c[ans];
    }
    return ans + 1;
}
int main()
{
    while (scanf("%d", &n) == 1)
    {
        c[0] = 0;
        fillone();
        for (int i = 1; i <= n; i++)
            scanf("%d%d", &Val[i][0], &Val[i][1]);
        for (int i = n; i >= 1; i--)
        {
            int value = Val[i][0] + 1;
            int left = 1, right = n, mid;
            while (left < right)
            {
                mid = (left + right) >> 1;
                int tmp = sum(mid);
                if (tmp < value)left = mid + 1;
                else right = mid;
            }
            ans[left] = Val[i][1];
            add(left);

        }
        for (int i = 1; i < n; i++)
        {
            printf("%d ", ans[i]);
        }
        printf("%d\n", ans[n]);

    }
}