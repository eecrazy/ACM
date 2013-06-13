#include<cstdio>
#include<cstring>
#include<queue>
typedef long long LL;
#define MAXN 110
#define MOD 100000
using namespace std;
char str[MAXN];
int size;
struct Matrix
{
    LL mat[MAXN][MAXN];
    void Zero()
    {
        memset(mat, 0, sizeof(mat));
    }
    void Unit()
    {
        int i;
        for (i = 0; i <= size; i++)
            mat[i][i] = 1;
    }
};
struct Trie
{
    int fail, next[4];
    bool end;
    void Init()
    {
        fail = 0;
        end = false;
        memset(next, 0, sizeof(next));
    }
};
Matrix a, b;
Trie tree[MAXN];
Matrix operator *(const Matrix &a, const Matrix &b)
{
    Matrix temp;
    int i, j, k;
    temp.Zero();
    for (i = 0; i <= size; i++)
    {
        for (j = 0; j <= size; j++)
        {
            for (k = 0; k <= size; k++)
                temp.mat[i][j] += a.mat[i][k] * b.mat[k][j];
            temp.mat[i][j] %= MOD;
        }
    }
    return temp;
}
inline int GET(char ch)
{
    if (ch == 'A')
        return 0;
    if (ch == 'C')
        return 1;
    if (ch == 'G')
        return 2;
    return 3;
}
void Insert(char *s)
{
    int now, t;
    for (now = 0; *s; s++)
    {
        t = GET(*s);
        if (!tree[now].next[t])
        {
            tree[++size].Init();
            tree[now].next[t] = size;
        }
        now = tree[now].next[t];
    }
    tree[now].end = true;
}
void BFS()
{
    int now, i, p;
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        now = q.front();
        q.pop();
        for (i = 0; i < 4; i++)
        {
            if (tree[now].next[i])
            {
                p = tree[now].next[i];
                if (now)
                    tree[p].fail = tree[tree[now].fail].next[i];
                tree[p].end |= tree[tree[p].fail].end;
                q.push(p);
            }
            else
                tree[now].next[i] = tree[tree[now].fail].next[i];
        }
    }
}
void DoIt(int m)
{
    int i, j, p;
    a.Zero();
    for (i = 0; i <= size; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (!tree[i].end)
            {
                p = tree[i].next[j];
                if (p)
                {
                    if (!tree[p].end)
                        a.mat[i][p]++;
                }
                else
                    a.mat[i][0]++;
            }
        }
    }
    b.Zero();
    b.Unit();
    for (; m; m >>= 1)
    {
        if (m & 1)
            b = b * a;
        a = a * a;
    }
}
int main()
{
    LL ans;
    int n, m, i;
    while (~scanf("%d%d", &n, &m))
    {
        tree[0].Init();
        for (size = i = 0; i < n; i++)
        {
            scanf(" %s", str);
            Insert(str);
        }
        BFS();
        DoIt(m);
        for (ans = i = 0; i <= size; i++)
            ans += b.mat[0][i];
        printf("%lld\n", ans % MOD);
    }
    return 0;
}
