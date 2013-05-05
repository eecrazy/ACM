#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int inf = 0x0fffffff;
const int maxN = 100010;
const int A = 1000000007;
const long long AI = 1000000007;
int X[maxN];
long long pre[2][maxN];

long long low(int X, int N)
{
    long long ans = 1, T = X;
    while (N)
    {
        if (N & 1)
            ans = (T * ans) % A;
        T = (T * T) % A;
        N = N >> 1;
    }
    return ans;
}

int main()
{
    long long  T, N;
    scanf("%lld", &T);
    while (T --)
    {
        int key[2], num[2] = {0, 0};
        key[0] = inf, key[1] = 0;//min 0
        scanf("%lld", &N);
        for (int i = 1; i <= N; ++ i)
        {
            scanf("%d", &X[i]);
            key[0] = min(key[0], X[i]);
            key[1] = max(key[1], X[i]);
        }
        if (key[0] == key[1])
        {
            long long L = 1;
            L = (L * N * (N + 1) / 2) % A;
            printf("%lld %lld\n", L, (low(2, N) - 1 + AI) % A);
            continue;
        }
        int t = 0, f = 1, k = 0;
        for (int i = 1; i <= N; ++ i)
        {
            if (key[0] == X[i])
            {
                if (f)f = 0, t = 0;
                num[0] ++;
            }
            else if (key[1] == X[i])
            {
                if (f)f = 0, t = 1;
                num[1] ++;
            }
            if (!f && X[i] == key[t])
            {
                pre[t][i] = i - k;
                k = i;
            }
        }
        long long len = 0, ans1 = 0;
        for (int i = N; i > 0; -- i)
        {
            if (key[t] == X[i])
                ans1 = (ans1 + (pre[t][i] * len) % A) % A;
            else if (key[!t] == X[i])
                len = N - i + 1;
        }
        k = N + 1;
        for (int i = N; i > 0; -- i)
            if (key[!t] == X[i])
            {
                pre[!t][i] = k - i;
                k = i;
            }
        k = -1;
        for (int i = 1; i <= N; ++ i)
            if (key[t] == X[i] && k != -1)
            {
                int HH = i - k;
                ans1 = (ans1 + ((pre[t][i] - HH) * (pre[!t][k] - HH)) % A) % A;
                k = -1;
            }
            else if (key[!t] == X[i])
                k = i;
        long long ans2 = 1;
        ans2 = ((ans2 * (low(2, num[0]) - 1 + AI) % A * ((low(2, num[1]) - 1 + AI) % A) % A) * low(2, N - num[0] - num[1])) % A;
        printf("%lld %lld\n", ans1, ans2);
    }
}