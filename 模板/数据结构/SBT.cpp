//给出一个更加简洁的版本，对maintain操作的使用提出了简化（事实上分拆了maintain, 省略相当一部分没有必要的判断，主要用leftBalance和rightBalance替换maintain的操作），使用了一些编程技巧（主要是哨兵技巧）
/**********************************************************************
     Size Balance Tree的精简实现
     2012.02.11   汪子逸 Copyright Reserved.
     转载请注明.

     代码与注释一起给出，以对部分技巧进行说明
     重点是使用哨兵结点简化NULL判断
     Insert操作带入平衡，省略maintain操作
     Delete操作给出一个略微复杂的实现
     Search Select Rank操作都十分简单
***********************************************************************/
#include <cstdio>
#include <iostream>
#include <time.h>

using namespace std;
/*基本存储结构*/
struct SBTNode
{
    int data;
    int size;
    struct SBTNode *lchild;
    struct SBTNode *rchild;
};

/*Nil哨兵结点，用来代替NULL表示空，可以极大地简化NULL判断*/
SBTNode Nil = {0, 0, &Nil, &Nil};

/*左旋操作，两个平衡树基本操作之一*/
void lRotate(SBTNode *&t)
{
    /*交接*/
    SBTNode *p = t->rchild;
    t->rchild  = p->lchild;
    p->lchild  = t;

    /*调整*/
    p->size = t->size;
    t->size = t->lchild->size + t->rchild->size + 1;

    /*返回*/
    t = p;
}

/*右旋操作，两个平衡树基本操作之二*/
void rRotate(SBTNode *t)
{
    /*交接*/
    SBTNode *p = t->lchild;
    t->lchild  = p->rchild;
    p->rchild  = t;

    /*调整*/
    p->size = t->size;
    t->size = t->lchild->size + t->rchild->size + 1;

    /*返回*/
    t = p;
}

/*左平衡操作，用于平衡LL型和LR型*/
void leftBalance(SBTNode *&t)
{
    if (t->lchild->lchild->size > t->rchild->size)
        rRotate(t);
    else if (t->lchild->rchild->size > t->rchild->size)
        lRotate(t->lchild), rRotate(t);
}

/*右平衡操作，用于平衡RR型和RL型*/
void rightBalance(SBTNode *&t)
{
    if (t->rchild->rchild->size > t->lchild->size)
        lRotate(t);
    else if (t->rchild->lchild->size > t->lchild->size)
        rRotate(t->rchild), lRotate(t);
}

/*插入操作，注意可以这里使用leftBalance和rightBalance,省略maintain操作*/
void insert(SBTNode *&t, int x)
{
    if (t == &Nil)
    {
        SBTNode *p = new SBTNode ;
        p->data = x;
        p->size = 1;
        p->lchild = &Nil;
        p->rchild = &Nil;
        t = p;
    }
    else
    {
        if (x < t->data)
        {
            t->size++;
            insert(t->lchild, x);
            leftBalance(t) ;
        }
        else
        {
            t->size++;
            insert(t->rchild, x);
            rightBalance(t);
        }
    }
}
/********************************************************************
   删除操作，也是最难正确实现的操作了，但其实一般题目中很少用，
   如果直接假设int x在树中是存在的，那么将简单很多，但这并不十分合理
   删除的总体是思路是这样的：

   如果比当前结点值小，到左树上面去删除
   如果比当前结点值大，到右树上面去删除
   如果等于当前结点值，那么应该删除本结点，但直接删除可能会破坏树的结构
       如果左子树为空，返回右子树
       如果右子树为空，返回左子树
       如果左右子树都不为空，应该找到其中序前驱，或者后继来替换这个结点

   在不考虑size域的情况下，自此应该可以写出递归版本的删除了
   但考虑size域呢，如果假设int x一定存在，那么只需要沿路径size--就可以
   但如果还可能int x不存在呢，能直接沿路size--吗？这是不可以的
   那么只有先尝试递归向下删除，查看删除结果，再判断是否size--，那么一些
   简洁的写法不得不变的略复杂一下

   如果不需要Delete操作，那么数组静态实现是更好的选择，因为简单很多
*********************************************************************/

SBTNode *Delete(SBTNode *&t, int x) /*删除t为根的树中，第一个含x的结点*/
{
    /*t被修改为新的根*/
    /*空树不需要删除*/
    if (t == &Nil) return &Nil;

    SBTNode *p = &Nil;/*记录被删除的结点，并返回*/
    /*应该到左子树上寻找删除结点*/
    if     (x < t->data)
    {
        p = Delete(t->lchild, x);
    }

    /*应该到右子树上寻找删除结点*/
    else if (x > t->data)
    {
        p = Delete(t->rchild, x);
    }

    /*删除本结点*/
    else/* x==t->data */
    {
        /*如果左右子树都不为空*/
        if (t->lchild != &Nil && t->rchild != &Nil)
        {
            /*找到中序的前驱，左子树的最右结点*/
            SBTNode *f = t;
            p = f->lchild;
            while (p->rchild != &Nil)
            {
                f = p;
                p = p->rchild;
            }

            /*p为用来替换根的结点，f是其父结点*/
            if  (p == f->rchild)
            {
                f->rchild = p->lchild;
            }
            else/*p==f->lchild*/
            {
                f->lchild = p->lchild;
            }

            /*t和p互换数据*/
            t->data ^= p->data;
            p->data ^= t->data;
            t->data ^= p->data;
        }
        /*如果左子树为空*/
        else if (t->lchild == &Nil)
        {
            p = t;
            t = t->rchild;
        }
        /*如果右子树为空*/
        else
        {
            p = t;
            t = t->lchild;
        }
    }
    /*调整大小,删除后t可能是Nil*/
    if (t != &Nil) t->size = t->lchild->size + t->rchild->size + 1;
    return p;
}

SBTNode *Search(SBTNode *t, int x)
{
    if (t == &Nil || t->data == x)
        return t;
    else
        Search(x < t->data ? t->lchild : t->rchild, x);
}

/*返回第k大的结点,返回最小值Select(t,1)即可*/
SBTNode *Select(SBTNode *t, int k)
{
    if (t == &Nil || k > t->size) return &Nil;

    int off = k - t->lchild->size - 1; /*off表示比根大多少个位置*/
    if     (off == 0) return t;
    else if (off < 0)  return Select(t->lchild, k);
    else            return Select(t->rchild, off);
}

/*返回x如果插入t，排在第多少的位置,x可以目前还不在t中*/
int Rank(SBTNode *t, int x)
{
    if (t == &Nil) return 1; /*空树，插入即是最大*/

    if     (x < t->data) return Rank(t->lchild, x);
    else if (x > t->data) return t->lchild->size + 1 + Rank(t->rchild, x);
    else /*x==t->data)*/return t->lchild->size + 1;
}

/*中序遍历，方便调试用的*/
void InOrder(SBTNode *t)
{
    if (t != &Nil)
    {
        InOrder(t->lchild);
        printf("%d\n", t->data);
        InOrder(t->rchild);
    }
}

/*测试树的高度，方便测试树的形态*/
int height(SBTNode *t)/*返回树的高度*/
{
    if (t == &Nil) return 0;
    return
        height(t->lchild) >= height(t->rchild) ?
        height(t->lchild) + 1 :
        height(t->rchild) + 1;
}
/*下面是测试用的主函数，因为使用了时间测试，请include<time.h>*/
int main()
{
    SBTNode *root = &Nil;

    const int n = 10000000;
    clock_t start = clock();
    /*********************/
    for (int i = 0; i < n; ++i)
    {
        insert(root, i);
    }
    /*********************/
    clock_t end = clock();
    printf("insert %d data time used is %d ms\n", n, end - start);
    for (int i = 4000; i < n; ++i)
    {
        Delete(root, i);
    }
    /*求height的函数会遍历整棵树，所以比较耗时*/
    printf("the size of left  SBTree is %d\n", root->lchild->size);
    printf("the size of right SBTree is %d\n", root->rchild->size);
    printf("the height of left  SBTree is %d\n", height(root->lchild));
    printf("the height of right SBTree is %d\n", height(root->rchild));
    printf("the height of SBTree is %d\n", height(root));

    printf("the rank of 15 is %d \n", Rank(root, 15));

    return 0;
}
