/****************************************
*              SBT.cpp
*
*     2008-11-17 17:06:02 Fixed a bug in function SBT_Delete, it's now be test.
*     2008-11-15 16:34:19 Give a new versin SBT_Delete that we don't need to using key-1.
*     Any problem contact yonggangluo@hotmail.com
*     Copyright  2008  Yonggang Luo base on 巨菜逆铭
*
******************************************/
#include <string.h>
#include <stdio.h>
#include <iostream>
typedef int32_t key_t;
struct SBTNode
{
    SBTNode *p, *ch[2]; ///ch[0]、ch[1]分别为左右孩子，p为双亲
    size_t size;
    key_t key;///这里省略了卫星数据域
    SBTNode(key_t _key, size_t _size); ///构造函数：未考虑卫星数据
} NULL_NODE(0, 0);
typedef SBTNode *SBTree;
SBTree NULL_TREE = &NULL_NODE;
SBTNode::SBTNode(key_t _key, size_t _size = 1)
{
    p = ch[0] = ch[1] = NULL_TREE;
    key = _key, size = _size;
}

bool cmp(key_t x, key_t y);

//————SBT的旋转操作————
inline void SBT_Rotate(SBTree &x, bool flag)
{
    //flag: 0为将左子节点移到根, 1为将右子节点移到根
    SBTree sub = x->ch[flag], &leaf = sub->ch[!flag];
    x->ch[flag] = leaf;
    if (leaf != NULL_TREE) leaf->p = x; /*设置双亲p*/
    sub->p = x->p; /*设置双亲p*/
    x->p = sub; /*设置双亲p*/
    leaf = x;
    sub->size = x->size;
    x->size = x->ch[0]->size + x->ch[1]->size + 1;
    x = sub;
}

//————SBT的维护操作————
void SBT_Maintain(SBTree &T, bool flag)
{
    if (T->ch[flag]->ch[!flag]->size > T->ch[!flag]->size) SBT_Rotate(T->ch[flag], !flag);
    else if (T->ch[flag]->ch[flag]->size <= T->ch[!flag]->size) return;
    SBT_Rotate(T, flag);
    SBT_Maintain(T->ch[0], 0);  //修复左子树
    SBT_Maintain(T->ch[1], 1);  //修复右子树
    SBT_Maintain(T, 0);         //修复整棵树
    SBT_Maintain(T, 1);
}

//————SBT的插入操作————
void SBT_Insert(SBTree &T, SBTNode *x)
{
    //将节点x插入树中
    if (T != NULL_TREE)
    {
        ++T->size;
        x->p = T; /*设置双亲p*/
        SBT_Insert(T->ch[cmp(T->key, x->key)], x);
        SBT_Maintain(T, cmp(T->key, x->key));  /* here  must be verify*/
    }
    else T = x;
}

//————SBT的查找————
SBTree &SBT_Search(SBTree *T, key_t key, int resize = 0)
{
    //在T中中寻找关键字为key的结点
    //若能找到则返回指向它的指针，否则返回NULL_TREE
    while (*T != NULL_TREE && (*T)->key != key)
    {
        (*T)->size += resize;
        T = &((*T)->ch[cmp((*T)->key, key)]);
    }
    return *T;
}

//————SBT的极值————
SBTree &SBT_Extremum(SBTree *T, bool maximum = true, int resize = 0) /*返回一棵树的极值 */
{
    while ((*T)->ch[maximum] != NULL_TREE)
    {
        (*T)->size += resize;
        T = &(*T)->ch[maximum];
    }
    return *T;
}

/*删除一棵树的根节点，并返回被删节点*/
SBTNode *SBT_Delete(SBTree &T)
{
    --T->size; ///维护size
    int flag = T->ch[0] == NULL_TREE || T->ch[1] == NULL_TREE;
    SBTree *P = flag ? &T : &SBT_Extremum(&T->ch[1] , 0, -1); ///如果T有两棵子树，那么我们就先删T的后继
    SBTree D = *P; ///D用来保存 真正 被删的节点
    *P = D->ch[D->ch[0] == NULL_TREE]; ///把被删节点设为此节点的其中一个儿子
    if (*P != NULL_TREE) (*P)->p = D->p; //设置双亲p
    if (flag) return D; ///如果 flag，则T是真正应当被删的节点，故直接返回D，否则继续处理D
    T->key = D->key;///简单替换
    /*std::swap(T, D);///本质替换
    memcpy(T, D, sizeof(*T)-sizeof(T->key)); //把关系复制过去
    if (T->ch[0]!=NULL_TREE) T->ch[0]->p = T; //设置双亲p
    if (T->ch[1]!=NULL_TREE) T->ch[1]->p = T; //设置双亲p
    */
    return D;
}

//————SBT的删除————
SBTNode *SBT_Delete(SBTree &T, key_t key)
{
    //如果树中没有一个这样的结点，则返回 NULL_TREE
    if (SBT_Search(&T, key) == NULL_TREE) return NULL_TREE; /*表示key不在树中**/
    return SBT_Delete(SBT_Search(&T, key, -1)); /*RP 就是指向待删子树的指针*/
}

SBTree &SBT_Near(SBTree &T, key_t key, bool flag)
{
    ///flag: 0 前驱 ;  1 后继
    if (T == NULL_TREE)  return T;
    if (key == T->key || cmp(T->key, key) == flag ) return SBT_Near(T->ch[flag], key, flag);
    SBTree &near = SBT_Near(T->ch[!flag], key, flag);
    return near != NULL_TREE ? near : T;
}

//————SBT的选取第i个元素————
SBTree SBT_Select(SBTree T, size_t i)
{
    ///从树T中找到关键字第i的结点并返回其指针,从1开始计数，如果没有就返回NULL_TREE
    if (i > T->size) return NULL_TREE;
    size_t r = T->ch[0]->size + 1;
    return i == r ? T : SBT_Select(T->ch[i > r], i > r ? i - r : i);
}

//————SBT的给定节点是第几个元素————
size_t SBT_Rank(SBTree T, key_t key)
{
    ///此功能不完善，如果同一个key有两个不同的rank,那么返回值是其中的任意一个的rank。
    ///可以考虑用二分法加 SBT_Select实现
    ///若不存在此节点则返回0
    if (T == NULL_TREE) return 0;
    if (key == T->key) return T->ch[0]->size + 1;
    if (cmp(key, T->key)) return SBT_Rank(T->ch[0], key);
    size_t r = SBT_Rank(T->ch[1], key);
    return r == 0 ? 0 : r + T->ch[0]->size + 1;
}

inline void SBT_Free(SBTNode *t)
{
    if (t != NULL_TREE) delete t;
}

/**下面是一些测试代码**/

bool cmp(key_t x, key_t y)
{
    return x < y;
}

#include <stdlib.h>
#include <time.h>

int deep;
size_t count;
SBTree root = NULL_TREE;

void SBT_Print(SBTree T, int d)
{
    if (T == NULL_TREE) return;
    SBT_Print(T->ch[0], d + 1);
    static size_t r;
    key_t value;
    printf("Rank = %d\n", r = SBT_Rank(root, T->key));
    printf("value = %d\n", value = SBT_Select(root, r)->key);
    if (value != T->key)
    {
        printf("Error!");
        exit(1);
    }
    for (int i = 0; i < d; ++i) printf("  ");
    printf("%d\n", T->key);
    if ( (T->ch[0]->p != NULL_TREE && T->ch[0]->p != T) || (T->ch[1]->p != NULL_TREE && T->ch[1]->p != T) )
    {
        printf("Error parent!\n");
        exit(0);
    }
    SBT_Print(T->ch[1], d + 1);
}

void show()
{
    if (root->p != NULL_TREE) printf("Error!\n");
    printf("The size of the tree is %d\n", root->size);
    printf("The tree is\n");
    count = 0;
    SBT_Print(root, 0);
    if (root->size != count)
    {
        printf("root->size = %u\n count = %u \n Error size!\n", root->size, count);
    }
    printf("End of the tree!\n\n");
}

int main()
{

    srand(time(NULL));
    size_t n = 3000000;
    key_t x;
    freopen("output.txt", "w", stdout);
    //#define READFILE
#ifdef READFILE
    char order;
    freopen("input.txt", "r", stdin);
    scanf("%d\n", &n);
    for (size_t i = 0; i < n; ++i)
    {
        printf("i=%u\n", i);
        scanf("%c %d\n", &order, &x);
        printf("x=%d\n", x);
        if (order == 'I')
            SBT_Insert(root, new SBTNode(x));
        else
            SBT_Free(SBT_Delete(root, x));
        show();
        if (NULL_TREE->key != 0) printf("Error NULL");

    }
#else
    for (size_t i = 0; i < n; ++i)
    {

        if (i % 3 == 0)
            //printf("D %ld\n", x), SBT_Free(SBT_Delete(&root, x));
            SBT_Free(SBT_Delete(root, x));
        else
            //printf("I %ld\n",x = rand()),SBT_Insert(root, new SBTNode(x));
            SBT_Insert(root, new SBTNode(x = rand()));
        //show();

        if (NULL_TREE->key != 0) printf("Error NULL");
    }
    //  show();
    SBTNode *pre, *suc;
    FILE *compare = fopen("compare.txt", "w");
    for (int i = 0; i < 32767; ++i)
    {
        pre = SBT_Near(root, i, 0);
        suc = SBT_Near(root, i, 1);
        //        fprintf(compare,"pre=%d i=%d suc=%d\n",pre->key, i, suc->key);
    }
#endif
    return 0;
}
