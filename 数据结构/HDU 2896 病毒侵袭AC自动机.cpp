// 题目大意：给你一堆病毒串，再给你一些网站，问每个网站是否包含病毒串，若包括，
// 包括哪几个病毒串，还有一共有几个网站包含病毒串。

// 啊啊，自己第一道AC自动机的题，还是比较简单的模板题吧，过几天要总结一下AC自动机呀。
// 思路很简单了，将所有病毒串构成trie树，然后求AC自动机，再用每个网站在AC自动机上跑
// 就行了。跑的时候开一个数组记录每个网站包含的病毒串。每经过一个节点由失败指针向上移，
// 看是否有病毒串（即flag为1的节点）。

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#define maxn 100100
#define knum 128
using namespace std;
struct trie
{
    int flag;
    trie *fail;
    trie *go[knum];
}node[maxn],*root;
int tot;
trie * newnode()
{
    memset(node[tot].go,NULL,sizeof(node[tot].go));
    node[tot].fail=NULL;
    node[tot].flag=0;
    return &node[tot++];
}
queue <trie *> q;
char keyword[210];
char str[maxn];
void insert(char *str,int x)
{
    trie *p=root;
    int i,k,len=strlen(str);
    for(i=0;i<len;i++)
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
        trie *tmp=q.front();q.pop();
        trie *p=NULL;
        for(i=0;i<knum;i++)
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
int vis[510];
int solve()
{
    int i,len=strlen(str),tru=0;
    trie *p=root;
    for(i=0;i<len;i++)
    {
        int k=str[i]-' ';
        while(p!=root&&p->go[k]==NULL)
        p=p->fail;
        p=p->go[k];
        p=(p==NULL)?root:p;
        trie *tmp=p;
        while(tmp!=root)
        {
            if(tmp->flag)
            {
                vis[tmp->flag]=1,tru=1;
            }
            tmp=tmp->fail;
        }
    }
    return tru;
}
int main()
{

    int n,i;
    while(scanf("%d",&n)!=EOF)
    {tot=0;
    root=newnode();
    for(i=1;i<=n;i++)
    {
        scanf("%s",keyword);
        insert(keyword,i);
    }
    build_ac_automation();
    int qq,ans=0;
    scanf("%d",&qq);
    for(i=1;i<=qq;i++)
    {
        memset(vis,0,sizeof(vis));
        scanf("%s",str);
        if(solve())
        {
            printf("web %d:",i);
            ans++;
            for(int j=1;j<=n;j++)
            if(vis[j])
            printf(" %d",j);
            printf("\n");
        }
    }
    printf("total: %d\n",ans);
    }
    return 0;
}
