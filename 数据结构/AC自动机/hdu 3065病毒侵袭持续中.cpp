#include <cstdio>
#include <iostream>
#include <string.h>
using namespace std;
#define MAX 26
#define maxn 10000000
struct node
{
    int cnt;
    node *next[MAX],*fail;
    node()
    {
        cnt=0;
        fail=NULL;
        for(int i=0; i<MAX; i++)
            next[i]=0;
    }
}*root;
node *q[maxn];
char keyword[1005][52];
char str[2000005];
int head,tail;
void insert(char *s,node *p,int num)
{
    int i=0,k;
    while(s[i])
    {
        k=s[i++]-'A';
        if(p->next[k]==NULL)
            p->next[k]=new node();
        p=p->next[k];
    }
    p->cnt=num;//记录的是模式串的标号
}
void build_AC(node *root)
{
    head=0;
    tail=1;
    q[head]=root;
    node *temp,*p;
    while(head<tail)
    {
        temp=q[head++];
        for(int i=0; i<MAX; i++)
        {
            if(temp->next[i])
            {
                if(temp==root)
                    temp->next[i]->fail=root;
                else
                {
                    p=temp->fail;
                    while(p)
                    {
                        if(p->next[i])
                        {
                            temp->next[i]->fail=p->next[i];
                            break;
                        }
                        p=p->fail;
                    }
                    if(!p)temp->next[i]->fail=root;
                }
                q[tail++]=temp->next[i];
            }
        }
    }
}
int visit[1005];
void query(char *str,node *root)
{
    int k,len=strlen(str);
    node *p=root;
    for(int i=0; i<len; i++)
    {
        k=str[i]-'A';
        if(k<0||k>=26)
        {
            p=root;
            continue;
        }
        while(!p->next[k]&&p!=root)
            p=p->fail;
        p=p->next[k];
        if(!p)p=root;
        node *temp=p;
        while(temp!=root)//不需要清除标记
        {
            if(temp->cnt)
            {
                visit[temp->cnt]++;
            }
            temp=temp->fail;
        }
    }
}
void del(node *root)
{

    if(root!=NULL)
    {
        for(int i=0;i<26;i++)
        del(root->next[i]);
    }
    delete(root);
}
int main()
{
    //freopen("in","r",stdin);
    int t,n,m;
    while(scanf("%d",&n)!=EOF)
    {
        root=new node();
        for(int i=1; i<=n; i++)
        {
            scanf(" %s",keyword[i]);
            insert(keyword[i],root,i);
        }
        build_AC(root);
        memset(visit,0,sizeof(visit));
        scanf(" %s",str);
        query(str,root);
        for(int i=1; i<=n; i++)
        {
            if(visit[i])
            {
                printf("%s: %d\n",keyword[i],visit[i]);
            }
        }
        del(root);
    }
}



