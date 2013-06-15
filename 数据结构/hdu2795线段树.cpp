#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#define MAXM 200005
#define MAXN 1000005
using namespace std;
const int INF = 0x3f3f3f3f;
int n, H, W, val;
int Tree[MAXN];
int GetTree(int l, int r, int k)
{
    if (l == r)
    {
        Tree[k] += val;
        return l;
    }
    int mid = (l + r) >> 1, num;
    if (Tree[k << 1] + val <= W) num = GetTree(l, mid, k << 1);
    else if (Tree[k << 1 | 1] + val <= W) num = GetTree(mid + 1, r, k << 1 | 1);
    Tree[k] = min(Tree[k << 1], Tree[k << 1 | 1]);
    return num;
}

int main()
{
    int i;
    //  freopen("input.txt","r",stdin);
    while (scanf("%d%d%d", &H, &W, &n)!=EOF)
    {
        memset(Tree, 0, sizeof(Tree));
        for (H = min(H, n), i = 1; i <= n; i++)
        {
            scanf("%d", &val);
            if (Tree[1] + val <= W) printf("%d\n", GetTree(1, H, 1));
            else printf("-1\n");
        }
    }
    return 0;
}