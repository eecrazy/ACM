#include <cstdio>
#include <cstring>
#include <queue>
#define MAXN 26
#define MOD 10330176681277348905LL
typedef unsigned long long LL;
using namespace std;
char str[MAXN];
int size;
LL total, ans;
struct node
{
    int fail, next[MAXN];
    bool end;
    void Init()
    {
        end = false;
        fail = 0;
        memset(next, 0, sizeof(next));
    }
};
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
Matrix a, b;
node tree[MAXN];
Matrix operator +(const Matrix &a, const Matrix &b)
{
    int i, j;
    Matrix temp;
    temp.Zero();
    for (i = 0; i <= size; i++)
    {
        for (j = 0; j <= size; j++)
            temp.mat[i][j] = a.mat[i][j] + b.mat[i][j];
    }
    return temp;
}
Matrix operator *(const Matrix &a, const Matrix &b)
{
    int i, j, k;
    Matrix temp;
    temp.Zero();
    for (i = 0; i <= size; i++)
    {
        for (j = 0; j <= size; j++)
        {
            for (k = 0; k <= size; k++)
                temp.mat[i][j] += a.mat[i][k] * b.mat[k][j];
        }
    }
    return temp;
}
Matrix operator ^(Matrix x, int k)
{
    Matrix temp;
    temp.Zero();
    temp.Unit();
    for (; k; k >>= 1)
    {
        if (k & 1)
            temp = temp * x;
        x = x * x;
    }
    return temp;
}
inline int GET(char ch)
{
    return ch - 'a';
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
        for (i = 0; i < MAXN; i++)
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
void GetTotal(int k)
{
    LL temp;
    total = 1;
    for (temp = 26; k; k >>= 1)
    {
        if (k & 1)
            total *= temp;
        temp *= temp;
    }
    total = 26 * (total - 1) * MOD;
}
void Build()
{
    int i, j, p;
    a.Zero();
    for (i = 0; i <= size; i++)
    {
        if (!tree[i].end)
        {
            for (j = 0; j < MAXN; j++)
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
}
Matrix DFS(int k)
{
    if (k == 1)
        return a;
    if (k & 1)
        return DFS(k - 1) + (a ^ k);
    else
    {
        Matrix temp = DFS(k >> 1);
        return temp + ((a ^ (k >> 1)) * temp);
    }
}
int main()
{
    int n, m, i;
    while (~scanf("%d%d", &n, &m))
    {
        GetTotal(m);
        tree[0].Init();
        for (i = size = 0; i < n; i++)
        {
            scanf(" %s", str);
            Insert(str);
        }
        BFS();
        Build();
        b = DFS(m);
        for (ans = i = 0; i <= size; i++)
            ans += b.mat[0][i];
        printf("%I64u\n", total - ans);
    }
    return 0;
}