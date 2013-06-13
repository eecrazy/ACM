#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define MAXL 256
#define MAXN 50010
using namespace std;
char str[MAXN];
int dg[MAXN], code[MAXN], size;
bool vis[MAXN];
struct node
{
    int fail, cnt, next[MAXL];
    void Init()
    {
        fail = cnt = 0;
        memset(next, 0, sizeof(next));
    }
};
node tree[MAXN];
inline int GET(char ch)
{
    if (ch >= 'A' && ch <= 'Z')
        return ch - 'A';
    if (ch >= 'a' && ch <= 'z')
        return ch - 'a' + 26;
    if (ch >= '0' && ch <= '9')
        return ch - '0' + 52;
    if (ch == '+')
        return 62;
    return 63;
}
void DoIt()
{
    int len, i, j, k, g;
    vector<int> t;
    memset(dg, 0, sizeof(dg));
    for (len = strlen(str); str[len - 1] == '='; len--)
        ;
    str[len] = 0;
    for (i = 0; i < len; i++)
        t.push_back(GET(str[i]));
    for (i = 0; i < t.size(); i++)
    {
        for (j = 6 * (i + 1) - 1; j >= 6 * i; j--)
        {
            if (t[i] & 1)
                dg[j] = 1;
            t[i] >>= 1;
        }
    }
    k = t.size() * 6 / 8;
    for (i = 0; i < k; i++)
    {
        for (g = 0, j = 8 * i; j < 8 * (i + 1); j++)
            g = (g << 1) + dg[j];
        code[i] = g;
    }
    code[i] = -1;
}
void Insert()
{
    int now, t, i;
    for (now = i = 0; code[i] >= 0; i++)
    {
        t = code[i];
        if (!tree[now].next[t])
        {
            tree[++size].Init();
            tree[now].next[t] = size;
        }
        now = tree[now].next[t];
    }
    tree[now].cnt++;
}
void BFS()
{
    int i, now, p;
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        now = q.front();
        q.pop();
        for (i = 0; i < MAXL; i++)
        {
            if (tree[now].next[i])
            {
                p = tree[now].next[i];
                if (now)
                    tree[p].fail = tree[tree[now].fail].next[i];
                q.push(p);
            }
            else
                tree[now].next[i] = tree[tree[now].fail].next[i];
        }
    }
}
int Match()
{
    int now, i, t, p, ans;
    for (ans = now = i = 0; code[i] >= 0; i++)
    {
        t = code[i];
        now = tree[now].next[t];
        for (p = now; p; p = tree[p].fail)
        {
            if (!vis[p])
            {
                ans += tree[p].cnt;
                vis[p] = true;
            }
        }
    }
    return ans;
}
int main()
{
    int n, i, q, ans;
    while (scanf(" %d", &n))
    {
        tree[0].Init();
        for (i = size = 0; i < n; i++)
        {
            scanf(" %s", str);
            DoIt();
            Insert();
        }
        BFS();
        scanf("%d", &q);
        while (q--)
        {
            memset(vis, false, sizeof(vis));
            scanf(" %s", str);
            DoIt();
            ans = Match();
            printf("%d\n", ans);
        }
        putchar('\n');
    }
    return 0;
}
