#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;
const int sonnum = 26, base = 'a';
const int maxn = 500002;
//定义字典树的节点类型
struct Trie
{
    int pos;
    struct Trie *son[sonnum];
};
struct Trie Memory[250010 * 2];
int allocp = 0;
int num;//字典树的有效节点
int p[maxn], rank[maxn]; //p[x]表示x的父节点，rank[x]表示x的级别
int degree[maxn];//记录点得度
Trie *NewTrie()//创建节点
{
    Trie *temp = &Memory[allocp++];
    temp->pos = -1; //表示节点未访问
    for (int i = 0; i < sonnum; ++i)temp->son[i] = NULL; //初始化孩子指针
    return temp;
}
int Insert(Trie *pnt, char *s, int len) //向字典树pnt中插入字符串s，len为字符串的长度
{
    Trie *temp = pnt;
    for (int i = 0; i < len; ++i)
    {
        if (temp->son[s[i] - base] == NULL) //节点不存在需要重新创建一个新的节点
            temp->son[s[i] - base] = NewTrie();
        temp = temp->son[s[i] - base]; //指向它孩子的节点
    }
    if (temp->pos == -1)
        temp->pos = ++num;
    return temp->pos;
}
void MarkSet()//初始化
{
    int i;
    for (i = 0; i <= maxn; i++)
    {
        p[i] = i;
        rank[i] = 1;
    }
    memset(degree, 0, sizeof(degree));
    num = 0;
}
int Find(int a)//非递归的查找a的父亲节点
{
    int pa = a;
    while (pa != p[pa])
        pa = p[pa];
    return pa;
}
void Union(int a, int b) //将a，b合并在同一个集合
{
    int pa, pb, t;
    pa = Find(a);
    pb = Find(b);
    t = rank[a] + rank[b];
    if (rank[pa] > rank[pb])
    {
        p[pb] = pa;
        rank[pa] = t;
    }
    else
    {
        p[pa] = pb;
        rank[pb] = t;
    }
}
int main()
{
    int len, i;
    char s1[11], s2[11];
    int x, y;
    while (scanf("%s", s1) != EOF)
    {
        if (s1[0] == '*')
        {
            printf("Possible\n");
            continue;
        }
        Trie *p;
        p = NewTrie(); //创建根节点
        MarkSet();//初始化集合
        scanf("%s", s2);
        len = strlen(s1);
        x = Insert(p, s1, len); //得到字符串s1的颜色序号
        len = strlen(s2);
        y = Insert(p, s2, len); //得到字符串s2的颜色序号
        degree[x]++;//s1的颜色序号的度+1
        degree[y]++;//s2的颜色序号的度+1
        Union(x, y); //合并s1和s2
        while (scanf("%s", s1))
        {
            if (s1[0] == '*')break;
            scanf("%s", s2);
            len = strlen(s1);
            x = Insert(p, s1, len); //得到字符串s1的颜色序号
            len = strlen(s2);
            y = Insert(p, s2, len); //得到字符串s2的颜色序号
            degree[x]++;//s1的颜色序号的度+1
            degree[y]++;//s2的颜色序号的度+1
            Union(x, y); //合并s1和s2
        }
        int sumdeg = 0, t;
        for (i = 1; i <= num; i++)
        {
            if (degree[i] % 2) //求奇度的顶点个数
                sumdeg++;
        }
        if (sumdeg > 2 || sumdeg == 1) //奇度的顶点个数>2,输出不可能
        {
            printf("Impossible\n");
            continue;
        }
        t = Find(1);
        int flag = 1;
        for (i = 2; i <= num; i++) //查看所有节点是否在同一个集合中
        {

            if (Find(i) != t)
            {
                printf("Impossible\n");
                flag = 0;
                break;
            }
        }
        if (flag == 1)
            printf("Possible\n");
    }
    return 0;
}
