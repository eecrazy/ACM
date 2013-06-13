#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
#include <string.h>
#define N 200000
struct node
{
    int fail;//失败指针
    int nxt[128];//trie树节点
    int pos;//字符串标记
    void init()//初始化
    {
        fail = -1;
        pos = -1;
        memset(nxt, 0, sizeof(nxt));
    }
} trie[N];

char s[1000][50];//模式串
char str[N];//匹配串
int top;//用到的节点数
int n;
int ans[1001];//储存每个字符串出现多少次
void ini()
{
    top = 1;
    trie[0].init();
}
void ins(char *s, int k) //构造trie树
{
    int p = 0;
    for (int i = 0; s[i]; ++i)
    {
        if (!trie[p].nxt[s[i]])
        {
            trie[top].init();
            trie[p].nxt[s[i]] = top++;
        }
        p = trie[p].nxt[s[i]];
    }
    trie[p].pos = k;
}
void ac()//宽度优先构造AC自动机
{
    int f, v, p = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        p = q.front();
        q.pop();
        for (int i = 0; i < 128; i++)
        {
            f = trie[p].fail;
            if (trie[p].nxt[i])
            {
                v = trie[p].nxt[i];
                if (p == 0)
                    trie[v].fail = 0;
                else
                    trie[v].fail = trie[f].nxt[i];
                q.push(v);
            }
            else
            {
                if (p == 0)
                    trie[p].nxt[i] = 0;
                else
                    trie[p].nxt[i] = trie[f].nxt[i];
            }
        }
    }
}
void que(char *t)//查询，具体题目，具体分析
{
    int p = 0;
    memset(ans, 0, sizeof(ans));
    for (int i = 0; t[i]; i++)
    {
        while (p && trie[p].nxt[t[i]] == 0)
            p = trie[p].fail;
        int tmp = (p = trie[p].nxt[t[i]]);
        while (tmp)
        {
            ans[trie[tmp].pos]++;
            tmp = trie[tmp].fail;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (ans[i] > 0)
            printf("%s: %d\n", s[i], ans[i]);
    }
}
int main()
{
    //    int n;
    while (scanf("%d", &n) != EOF)
    {
        ini();
        for (int i = 0; i < n; i++)
        {
            scanf("%s", s[i]);
            ins(s[i], i);
        }
        // puts("ff");
        ac();
        scanf("%s", str);
        que(str);
    }
    return 0;
}


/*
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
#define maxn 2001000
#define knum 128
using namespace std;
struct trie
{
    int flag;
    trie *fail;
    trie *go[knum];
} node[maxn],*root;
int tot;
trie * newnode()
{
    memset(node[tot].go,NULL,sizeof(node[tot].go));
    node[tot].fail=NULL;
    node[tot].flag=0;
    return &node[tot++];
}
queue <trie *> q;
char keyword[1002][51];
char str[maxn];
void insert(char *str,int x)
{
    trie *p=root;
    int i,k;
    for(i=0; str[i] ; i++)
    {
        k=str[i]-' ';
        if(!p->go[k])
        {
            p->go[k]=newnode();
        }
        p=p->go[k];
    }
    p->flag=x;
}
void build_ac_automation()
{
    int i;
    root->fail=NULL;
    q.push(root);
    while(!q.empty())
    {
        trie *tmp=q.front();
        q.pop();
        trie *p=NULL;
        for(i=0; i<knum; i++)
        {
            if(tmp->go[i])
            {
                if(tmp==root)
                    tmp->go[i]->fail=root;
                else
                {
                    p=tmp->fail;
                    while(p)
                    {
                        if(p->go[i])
                        {
                            tmp->go[i]->fail=p->go[i];
                            break;
                        }
                        p=p->fail;
                    }
                    if(p==NULL)
                        tmp->go[i]->fail=root;
                }
                q.push(tmp->go[i]);
            }
        }
    }
}
int vis[1005];
void solve(int n,char *str)
{
    int i,len=strlen(str),tru=0;
    trie *p=root;
    for(i=0; i<len; i++)
    {
        int k=str[i]-' ';
        while(p!=root&&p->go[k]==NULL)
            p=p->fail;
        p=p->go[k];
        p=(p==NULL)?root:p;
        trie *tmp=p;
        //这里是判断的关键，具体问题不同就是这里统计不同
        while(tmp!=root)
        {
            if(tmp->flag)
            {
                vis[tmp->flag]++;//统计flag出现次数
            }
            tmp=tmp->fail;
        }
    }
    for(int i=1; i<=n; i++)
    {
        if(vis[i])
        {
            printf("%s: %d\n",keyword[i],vis[i]);
        }
    }
}
int main()
{
    int n,i;
    while(scanf("%d",&n)!=EOF)
    {
        tot=0;
        root=newnode();
        for(i=1; i<=n; i++)
        {
            scanf("%s",keyword[i]);
            insert(keyword[i],i);
        }
        build_ac_automation();
        memset(vis,0,sizeof(vis));
        scanf("%s",str);
        solve(n,str);
    }
    return 0;
}

 */