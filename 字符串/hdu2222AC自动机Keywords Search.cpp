#include <cstdio>
const int LEN = 1000010;
const int N = 26;
const int MAX = 500010;
typedef struct Node
{
    Node *next[N], *fail;
    int cnt;
} Node;
Node *q[MAX] = {};
Node *NewNode()
{
    Node *ret = new Node;
    ret->fail = NULL;
    ret->cnt = 0;
    for (int i = 0; i < N; ++i) ret->next[i] = NULL;
    return ret;
}
void Insert(Node *head, char *str)
{
    for (int i = 0; str[i]; ++i)
    {
        int idx = str[i] - 'a';
        if (head->next[idx] == NULL)
            head->next[idx] =NewNode();
        head = head->next[idx];
    }
    ++(head->cnt);
}
void Del(Node *root)
{
    if (root == NULL) return;
    for (int i = 0; i < N; ++i) Del(root->next[i]);
    delete root;
}
void Build_AC_Automation(Node *root)
{
    Node *tmp, *p;
    int front = 0, rear = 0;
    root->fail = NULL;
    q[rear++] = root;
    while (front != rear)
    {
        tmp = q[front++];
        for (int i = 0; i < N; ++i)
        {
            if (tmp->next[i])
            {
                if (tmp == root) tmp->next[i]->fail = root;
                else
                {
                    p = tmp->fail;
                    while (p != NULL)
                    {
                        if (p->next[i])
                        {
                            tmp->next[i]->fail = p->next[i];
                            break;
                        }
                        p = p->fail;
                    }
                    if (p == NULL) tmp->next[i]->fail = root;
                }
                q[rear++] = tmp->next[i];
            }
        }
    }
}
int Quary(Node *root, char *str)
{
    int ret = 0;
    Node *p = root, *tmp;
    for (int i = 0; str[i]; ++i)
    {
        int idx = str[i] - 'a';
        while (p->next[idx] == NULL && p->fail) p = p->fail;
        p = p->next[idx];
        if (p == NULL) p = root;
        tmp = p;
        while (tmp != NULL)
        {
            ret += tmp->cnt;
            tmp->cnt = 0;
            tmp = tmp->fail;
        }
    }
    return ret;
}
char str[LEN] = {};
int main()
{
    Node *root;
    int t, n;
    scanf("%d", &t);
    while (t--)
    {
        root = NewNode();
        scanf("%d", &n);
        while (n--)
        {
            scanf("%s", str);
            Insert(root, str);
        }
        Build_AC_Automation(root);
        scanf("%s", str);
        printf("%d\n", Quary(root, str));
        Del(root);
    }
    return 0;
}
