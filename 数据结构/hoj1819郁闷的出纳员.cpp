#include <cstdio>
#define inf 0x7FFFFFFF
#define maxn 100010
#include <string.h>
struct Splaytree
{
    int num[maxn],next[maxn][2],pre[maxn],key[maxn];
    int root,size;
    inline void PushUp(int x)
    {
        num[x] = num[next[x][0]] + num[next[x][1]] + 1;
    }
    inline void Rotate(int x, int kind)
    {
        int y, z;
        y = pre[x];
        z = pre[y];
        next[y][!kind] = next[x][kind];
        pre[next[x][kind]] = y;
        next[z][next[z][1] == y] = x;
        pre[x] = z;
        next[x][kind] = y;
        pre[y] = x;
        PushUp(y);
        PushUp(x);
    }
    void Splay(int x, int goal)
    {
        if (x != goal)
        {
            while (pre[x] != goal)
            {
                if (next[pre[x]][0] == x)
                    Rotate(x, 1);
                else
                    Rotate(x, 0);
            }
            if (!goal)
                root = x;
        }
    }
    inline void NewNode(int &x, int y, int val)
    {
        x = ++size;
        num[x] = 1;
        pre[x] = y;
        next[x][0] = next[x][1] = 0;
        key[x] = val;
        next[y][val > key[y]] = x;
    }
    void Insert(int val)
    {
        int x, y;
        for (x = root, y = 0; x; x = next[x][val > key[x]])
        {
            y = x;
            num[x]++;
        }
        NewNode(x, y, val);
        Splay(x, 0);
    }
    int Search(int val)
    {
        int res, x;
        for (res = 0, x = root; x; x = next[x][val > key[x]])
        {
            if (key[x] >= val && key[res] >= key[x])
                res = x;
        }
        return res;
    }
    int Select(int k)
    {
        int x;
        k = num[root] - k;
        for (x = root; num[next[x][0]] + 1 != k;)
        {
            if (num[next[x][0]] + 1 < k)
            {
                k -= num[next[x][0]] + 1;
                x = next[x][1];
            }
            else
                x = next[x][0];
        }
        Splay(x, 0);
        return key[x];
    }
    inline void Init()
    {
        root = size = 0;
        num[0] = next[0][0] = next[0][1] = pre[0]=0;
        key[0] = inf;
        Insert(inf);
    }
} tree;

int main()
{
    //freopen("in","r",stdin);
    char ch;
    int q,base,diff,ans,x;
    while(scanf("%d%d",&q,&base)!=EOF)
    {
        tree.Init();
        diff=ans=0;
        while(q--)
        {
            scanf(" %c%d",&ch,&x);
            if(ch=='I')
            {
                if(x>=base)
                {
                    tree.Insert(x-base+diff);
                }
            }
            else if(ch=='A')
                diff-=x;
            else if(ch=='S')
            {
                diff+=x;
                tree.Splay(tree.Search(diff),0);
                ans+=tree.num[tree.next[tree.root][0]];
                tree.num[tree.root]-=tree.num[tree.next[tree.root][0]];
                tree.next[tree.root][0]=0;
            }
            else
            {
                if(x>=tree.num[tree.root])
                    puts("-1");
                else
                    printf("%d\n",tree.Select(x)+base-diff);

            }
        }
        printf("%d\n",ans);
    }
    return 0;
}
