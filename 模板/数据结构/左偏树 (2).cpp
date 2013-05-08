//左偏树
/**** **** **** **** **** ****
*      Function Name  :  左偏树
*      Description  :          HDOJ  1512 Monkey  King
*            二叉堆的变形，方便堆的合并
**** **** **** **** **** ****/
#include <cstdio>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;
const int MAX = 101000;
struct node
{
    int v, dis;//键值，距离node * pl, * pr;//左右子树node * pf;//父节点}mem[MAX];
    int mem_pos;
    int  value[MAX], n;
    node * new_node()
    {
        node * pt =  mem  + (mem_pos  ++);
        memset(pt,  0,
               sizeof(node));
        return pt;
    }
//清除节点休息
    inline void clear(node * pos)
    {
        if(pos ==  NULL) return;
        pos->pl  =  pos->pr  = pos->pf =  NULL;
        pos->dis  =  0;
    }
//合并堆O(log  N)
    node * merge(node  * pa, node * pb)
    {
        if(pa ==  NULL) return pb;
        if(pb ==  NULL) return pa;
        //maximum  vertex heap
        if(pb->v  > pa->v) std::swap(pa, pb);
        pa->pr  = merge(pa->pr,  pb);
        if(pa->pr)
        {
            if(pa->pl  ==  NULL  || pa->pr->dis  > pa->pl->dis)
            {
                std::swap(pa->pl,  pa->pr);
            }
        }
        if(pa->pr  ==  NULL)  pa->dis  =  0;
        else pa->dis =  pa->pr->dis  +1;
        if(pa->pl)  pa->pl->pf  =  pa;
        if(pa->pr)  pa->pr->pf  = pa;
        return pa;
    }
//插入节点
    inline node * insert(node  * root, node * val)
    {
        return merge(root,  val);
    }
//删除最大顶
    inline node * delete_max(node  * root)
    {
        node * pt = root;
        root = merge(root ->pl,  root ->pr);
        if(root) root->pf =  NULL;
        clear(pt);
        return  root;
    }
//取得最大值
    inline int get_max(node  * root)
    {
        return root ->v;
    }
//构建左偏树O(N)
    inline node * make_leftist_tree()
    {
        queue<node  *> SQ;
        node * ptemp;
        int i;
        ptemp =  new_node();
        for(i=0; i<n; i++)
        {
            ptemp->v  = value[i];
            SQ.push(ptemp);
        }
        while(!SQ.empty())
        {
            int l = SQ.size();
            if(l ==  1) return SQ.front();
            while(l --)
            {
                node * pa =  SQ.front();
                SQ.pop();
                node * pb =  SQ.front();
                SQ.pop();
                SQ.push(merge(pa,  pb));
            }
        }
    }
//删除已知任意点O(log  N)
    inline void delete_any(node  * pos)
    {
        node * ppre =  pos->pf;
        node * pnew =  delete_max(pos);
        if(pnew) pnew->pf =  ppre;
        if(ppre)
        {
            if(ppre->pl  ==  pos) ppre->pl  = pnew;
            else ppre->pr  =  pnew;
        }
        while(ppre)
        {
            int vl = -1, vr = -1;
            if(ppre->pl)  vl = ppre->pl->dis;
            if(ppre->pr)  vr = ppre->pr->dis;
            if(vl < vr) std::swap(ppre->pl,  ppre->pr);
            if(vr +1  ==  ppre->dis) return;
            ppre->dis  = vr +1;
            pnew  =  ppre;
            ppre  =  ppre->pf;
        }
    }
}
node ltree[MAX];
int main()
{
    int i,j;
    int m,t;
    while(scanf("%d",  &n)==1)
    {
        for(i=0; i<n; i++)
        {
            scanf("%d",  &t);
            ltree[i].v=t;
            ltree[i].dis=0;
            ltree[i].pl  =ltree[i].pr=ltree[i].pf=NULL;
        }
        scanf("%d",  &m);
        int a,b;
        while(m --)
        {
            scanf("%d  %d",  &a,&b);
            a --;
            b --;
            node * pa, * pb;
            pa =  ltree +a;
            pb  =  ltree +b;
            while(pa->pf)  pa = pa->pf;
            while(pb->pf)  pb =  pb->pf;
            if(pa ==  pb)       puts("-1");
            else
            {
                node * p1 = delete_max(pa);
                node  * p2 =  delete_max(pb);
                pa->v /=  2;
                pb->v /=  2;
                p1 =  insert(p1, pa);
                p1 = insert(p1,  pb);
                p1 =  merge(p1,  p2);
                printf("%d\n",  get_max(p1));
            }
        }
    }
}
