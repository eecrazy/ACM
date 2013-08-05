#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define kind 26
const int MAXN = 10000000;
struct node
{
    int count; //是否为单词最后一个节点
    node *next[26];//Trie每个节点的26个子节点
    node *fail; //失败指针
};
node *q[MAXN]; //队列，采用bfs 构造失败指针
char keyword[55];//输入单词 模式串
char str[1000010];// 需要查找的主串
int head,tail;//队列 头尾指针
node *root;
void insert(char *word,node *root)
{
    int index,len;
    node *p = root,*newnode;
    len = strlen(word);
    for(int i=0 ; i < len ; i++ )
    {
        index=word[i]-'a';
        if(!p->next[index])//该字符节点不存在，加入Trie树中
        {
            // 初始化 newnode 并 加入 Trie 树
            newnode=(struct node *)malloc(sizeof(struct node));
            for(int j=0; j<26; j++) newnode->next[j]=0;
            newnode->count=0;
            newnode->fail=0;
            p->next[index]=newnode;
        }
        p=p->next[index];//指针移动至下一层
    }
    p->count++;  //单词结尾 节点 count + 1 做标记
}
void build_ac_automation(node *root)
{
    head=0;
    tail=1;
    q[head]=root;
    node *temp,*p;
    while(head<tail)//bfs构造 Trie树的失败指针
    {
        //算法类似 kmp ，这里相当于得到 next[]数组
        //重点在于，匹配失败时，由fail指针回溯到正确的位置

        temp=q[head++];
        for(int i=0; i< 26 ; i ++)
        {
            if(temp->next[i])//判断实际存在的节点
            {
                // root 下的第一层 节点 都 失败指针都 指向root
                if(temp==root)temp->next[i]->fail=root;
                else
                {
                    //依次回溯 该节点的父节点的失败指针
                    //知道某节点的next[i]与该节点相同，则
                    //把该节点的失败指针指向该next[i]节点
                    //若回溯到 root 都没有找到，则该节点
                    //的失败指针 指向 root

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
                //每处理一个点，就把它的所有儿子加入队列，
                //直到队列为空
                q[tail++]=temp->next[i];
            }
        }
    }
}
int query(node *root)//类似于 kmp算法。
{
    //i为主串指针，p为匹配串指针
    int i,cnt=0,index,len=strlen(str);
    node *p=root;
    for(i=0; i < len ; i ++)
    {
        index=str[i]-'a';
        //由失败指针回溯寻找，判断str[i]是否存在于Trie树种
        while( !p->next[index] && p != root)p=p->fail;
        p=p->next[index];//找到后 p 指向该节点
        //指针回为空，则没有找到与之匹配的字符
        if(!p)p=root;//指针重新回到根节点root，下次从root开始搜索Trie树
        node *temp=p;//匹配该节点后，沿其失败指针回溯，判断其他节点是否匹配
        while(temp != root )//匹配 结束控制
        {
            if(temp->count>=0)//判断 该节点是否被访问
            {
                //统计出现的单词个数cnt，由于节点不是单词结尾时count为0，
                //故 cnt+=temp->count; 只有 count >0时才真正统计了单词个数

                cnt+=temp->count;
                temp->count=-1; //标记已访问
            }
            else break;//节点已访问，退出循环
            temp=temp->fail;//回溯失败指针继续寻找下一个满足条件的节点
        }
    }
    return cnt;
}
int main()
{
    int i,t,n,ans;
    scanf("%d",&t);
    while(t--)
    {
        root=(struct node *)malloc(sizeof(struct node));
        for(int j=0; j<26; j++) root->next[j]=0;
        root->fail=0;
        root->count=0;
        scanf("%d",&n);
        getchar();
        for(i=0; i<n; i++)
        {
            gets(keyword);
            insert(keyword,root);
        }
        build_ac_automation(root);
        gets(str);
        ans=query(root);
        printf("%d\n",ans);
    }
    return 0;
}
