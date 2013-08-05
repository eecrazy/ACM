// Keywords Search
// 网络流上流传最广的AC自动机模板题，问你目标串中出现了几个模式串
// 如果一个结点是单词末尾的话out标记为true,在search的时候对于每个结点都向fail指针找
// 找到out为true的就将其标记为false,且ans++
#include <cstdio>
#include <iostream>
#include <string.h>
using namespace std;
#define maxn 10000000
struct node
{
    int cnt;//是否为单词最后一个节点
    node *next[26],*fail;//Trie每个节点的26个子节点and失败指针
    node()
    {
        cnt=0;
        fail=NULL;
        for(int i=0; i<26; i++)
            next[i]=0;
    }
}*root;
node *q[maxn];//构造失败指针的bfs队列
char keyword[55];//输入单词,模式串
char str[1000010];//需要查找的主串
int head,tail;//队列头尾指针
void insert(char *s,node *p)//插入字符串函数
{
    int i=0,k;
    while(s[i])
    {
        k=s[i++]-'a';
        if(p->next[k]==NULL)
            p->next[k]=new node();
        p=p->next[k];//指针移动至下一层
    }
    p->cnt++;//单词结尾节点count + 1做标记
}
void build_AC(node *root)//构造失败指针
{
    head=0;
    tail=1;
    q[head]=root;
    node *temp,*p;
    while(head<tail)//bfs构造Trie树的失败指针
    {
        temp=q[head++];
        for(int i=0; i<26; i++)
        {
            if(temp->next[i])//判断实际存在的节点
            {
                // root下的第一层节点的失败指针都指向root
                if(temp==root)
                temp->next[i]->fail=root;
                else
                {
                    //依次回溯该节点的父节点的失败指针
                    //直到某节点的next[i]与该节点相同，则
                    //把该节点的失败指针指向该next[i]节点
                    //若回溯到 root 都没有找到,则该节点的失败指针 指向 root
                    p=temp->fail;//temp 为节点的父指针
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
                //每处理一个点,就把它的所有儿子加入队列
                //直到队列为空
                q[tail++]=temp->next[i];
            }
        }
    }
}
int query(char *str,node *root)
{
    int ans=0,k,len=strlen(str);
    node *p=root;
    //i为主串指针，p为匹配串指针
    for(int i=0; i<len; i++)
    {
        k=str[i]-'a';
        //由失败指针回溯寻找,判断str[i]是否存在于Trie树中
        while(!p->next[k]&&p!=root)
            p=p->fail;
        p=p->next[k];//找到后p指向该节点
        if(!p)p=root;//指针仍为空，则没有找到与之匹配的字符
        //指针重新回到根节点root,下次从root开始搜索Trie树
        node *temp=p;//匹配该节点后,沿其失败指针回溯,判断其他节点是否匹配
        while(temp!=root&&temp->cnt!=-1)//匹配结束控制and未被访问控制
        {
            ans+=temp->cnt;
            temp->cnt=-1;//标记已访问
            temp=temp->fail;//回溯失败指针继续寻找下一个满足条件的节点
        }
    }
    return ans;
}
void del(node *root)
{
    if(root==NULL)return ;
    for(int i=0;i<26;i++)del(root->next[i]);
    delete(root);
}
int main()
{
    int t,n;
    scanf("%d",&t);
    while(t--)
    {
        root=new node();
        scanf("%d",&n);
        for(int i=0; i<n; i++)
        {
            scanf(" %s",keyword);
            insert(keyword,root);
        }
        build_AC(root);
        scanf(" %s",str);
        printf("%d\n",query(str,root));
        del(root);
    }
}
