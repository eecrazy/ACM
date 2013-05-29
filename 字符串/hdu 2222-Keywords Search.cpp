// hdu 2222-Keywords Search

#include<iostream>

#include<string>

using namespace std;

const int kind=26;

struct node

{

    node* fail;//失败指针

    node* next[kind];//Tire每个节点的26个子节点（最多26个字母）

    int count;//是否为该单词的最后一个节点

    node()//构造函数初始化

    {

        fail=NULL;

        count=0;

        memset(next,0,sizeof(next));

    }

}*q[500001];//队列，方便用于bfs构造失败指针

char keyword[51];//输入的单词

char str[1000001];//模式串

int head,tail;//队列的头尾指针

void insert(char*str,node*root)

{

    node*p=root;

    int i=0,index;

    while(str[i])

    {

        index=str[i]-'a';

        if(p->next[index]==NULL)

        p->next[index]=new node();

        p=p->next[index];

        i++;

    }

    p->count++;

}

void build_ac_automation(node*root)

{

    int i;

    root->fail=NULL;

    q[head++]=root;

    while(head!=tail)

    {

        node*temp=q[tail++];

        node*p=NULL;

        for(i=0; i<26; i++)

        {

            if(temp->next[i]!=NULL)

            {

                if(temp==root)

                temp->next[i]->fail=root;

                else

                {

                    p=temp->fail;

                    while(p!=NULL)

                    {

                        if(p->next[i]!=NULL)

                        {

                            temp->next[i]->fail=p->next[i];

                            break;

                        }

                        p=p->fail;

                    }

                    if(p==NULL)temp->next[i]->fail=root;

                }

                q[head++]=temp->next[i];

            }

        }

    }

}

int query(node*root)

{

    int i=0,cnt=0,index,len=strlen(str);

    node*p=root;

    while(str[i])

    {

        index=str[i]-'a';

        while(p->next[index]==NULL&&p!=root)

        p=p->fail;



        p=p->next[index];

        p=(p==NULL)?root:p;

        node*temp=p;

        while(temp!=root&&temp->count!=-1)

        {

            cnt+=temp->count;

            temp->count=-1;

            temp=temp->fail;

        }

        i++;

    }

    return cnt;

}

int main()

{

    int n,t;

    scanf("%d",&t);

    while(t--)

    {

        head=tail=0;

        node*root=new node();

        scanf("%d",&n);

        getchar();

        while(n--)

        {

            gets(keyword);

            insert(keyword,root);

        }

        build_ac_automation(root);

        scanf("%s",str);

        printf("%d\n",query(root));

    }

    return 0;

}

/*

1

5

she

he

say

shr

her

yasherhs

*/

