/**** **** **** **** **** ****
*      Function Name  :  二维线段树RMQ
*      Description  :          HDOJ  1823 Luck and Love
**** **** **** **** **** ****/
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
#define NMAX 500000
#define MQ(x,y) ((x)>(y)?(x):(y))
struct node
{
    int M;
} mem[NMAX];
node*pleft,*pright;
node * ytree;
int left, right;
int mem_pos;
node * new_node()
{
    node * pt =  &mem[mem_pos  ++];
    memset(pt,0,sizeof(node));
    pt ->M = -1;//maximum  or minimum
    return pt;
}
node * create_tree(int x1, int y1, int x2, int y2, bool flag)
{
    node * root =  new_node();
    if(flag)  // first dimension
    {
        root->left=x1;
        root->right =y1;
        root->ytree=create_tree(x1,y1,x2,y2, false);
        if(x1 !=  y1)
        {
            int mid  = (x1+y1)/2;
            root ->pleft =  create_tree(x1, mid,  x2, y2, true);
            root ->pright  =  create_tree(mid+1,  y1, x2, y2, true);
        }
    }
    else  // second dimension
    {
        root ->left =  x2;
        root ->right  =  y2;
        if(x2 !=  y2)
        {
            int mid  = (x2+y2)/2;
            root ->pleft =  create_tree(x1, y1, x2, mid, false);
            root ->pright  =  create_tree(x1, y1, mid+1,  y2, false);
        }
    }
    return root;
}
void update(node * root, int d1, int d2, int v, bool flag)
{
    int mid  =  (root ->left + root ->right)/2;
    if(flag)  // first dimension
    {
        update(root ->ytree, d1, d2, v, false);
        if(root ->left <  root ->right)
        {
            if(d1 <=  mid)
            {
                update(root ->pleft, d1, d2, v, true);
            }
            else
            {
                update(root ->pright,  d1, d2, v, true);
            }
        }
    }
    else  // second dimension
    {
        if(root ->left ==  root ->right)
        {
            root ->M =  MQ(root ->M, v);
        }
        else
        {
            if(d2 <=  mid)
            {
                update(root ->pleft, d1, d2, v, false);
            }
            else
            {
                update(root ->pright,  d1, d2, v, false);
            }
            root ->M = MQ(root ->pleft ->M, root ->pright ->M);
        }
    }
}
int query(node  * root, int x1, int y1, int x2, int y2, bool flag)
{
    int lmq,  rmq;
    int mid  = (root ->left +  root ->right)/2;
    if(flag)  // first dimension
    {
        if(root ->left ==  x1 && root ->right  ==  y1)
        {
            return query(root ->ytree, x1, y1, x2, y2, false);
        }
        else
        {
            if(y1 <=  mid)
            {
                return query(root ->pleft, x1, y1, x2, y2, true);
            }
            if(x1 >  mid)
            {
                return query(root ->pright,  x1, y1, x2, y2, true);
            }
            lmq  = query(root ->pleft, x1, mid,  x2, y2, true);
            rmq  = query(root ->pright,  mid+1,  y1, x2, y2, true);
        }
    }
    else  // second dimension
    {
        if(root ->left ==  x2 && root ->right  ==  y2)
        {
            return root ->M;
        }
        else
        {
            if(y2 <=  mid)
            {
                return query(root ->pleft, x1, y1, x2, y2, false);
            }
            if(x2 >  mid)
            {
                return query(root ->pright,  x1, y1, x2, y2, false);
            }
            lmq  = query(root ->pleft, x1, y1, x2, mid, false);
            rmq  = query(root ->pright,  x1, y1, mid+1,  y2, false);
        }
    }
    return MQ(lmq,  rmq);
}
int main()
{
    int m;
    char cmd;
    while(scanf("%d",  &m),  m)
    {
        mem_pos  =  0;
        node * root =  create_tree(100,200,0,1000,true);
        while(m --)
        {
            getchar();
            cmd =  getchar();
            if(cmd == 'I')
            {
                int h, ia, il;
                double a,l;
                scanf("%d  %lf %lf",  &h, &a, &l);
                ia =  10*(a+0.05);
                il  = 10*(l+0.05);
                update(root,  h, ia, il, true);
            }
            else
            {
                int h1, h2, ia1, ia2;
                double a1, a2;
                scanf("%d  %d %lf %lf",  &h1, &h2, &a1, &a2);
                ia1 = 10*(a1+0.05);
                ia2  = 10*(a2+0.05);
                if(h1 >  h2)
                {
                    swap(h1, h2);
                }
                if(ia1 >  ia2)
                {
                    swap(ia1, ia2);
                }
                int t =  query(root, h1, h2, ia1, ia2, true);
                if(t == -1)
                {
                    puts("-1");
                }
                else
                {
                    printf("%.1lf\n",  t / 10.0);
                }
            }
        }
    }
}