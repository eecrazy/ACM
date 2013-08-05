// 题意:区间操作,交,并,补等
// 思路:
// 我们一个一个操作来分析:(用0和1表示是否完全包含区间,-1表示该区间内既有包含又有不包含)
// U:把区间[l,r]覆盖成1
// I:把[-∞,l)(r,∞]覆盖成0
// D:把区间[l,r]覆盖成0
// C:把[-∞,l)(r,∞]覆盖成0 , 且[l,r]区间0/1互换
// S:[l,r]区间0/1互换
// 成段覆盖的操作很简单,比较特殊的就是区间0/1互换这个操作,我们可以称之为异或操作
// 很明显我们可以知道这个性质:当一个区间被覆盖后,不管之前有没有异或标记都没有意义了
// 所以当一个节点得到覆盖标记时把异或标记清空
// 而当一个节点得到异或标记的时候,先判断覆盖标记,如果是0或1,直接改变一下覆盖标记,不然的话改变异或标记

// 开区间闭区间只要数字乘以2就可以处理(偶数表示端点,奇数表示两端点间的区间),相当于把所有区间操作扩大了2倍
// 输出的时候在缩小
// 线段树功能:update:成段替换,区间异或 query:简单hash

#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
using namespace std;
#define lson l , m , rt << 1
#define rson m + 1 , r , rt << 1 | 1

const int maxn = 131072;
bool visit[maxn + 1];
int cover[maxn << 2];
int XOR[maxn << 2];
void FXOR(int rt)
{
    if (cover[rt] != -1) cover[rt] ^= 1；//全是0或者全是1，改变一下覆盖标记
    else XOR[rt] ^= 1;//区间有0也有1
}
void PushDown(int rt)//把父亲节点的信息更新到孩子节点，本身信息清零
{
    if (cover[rt] != -1)//区间全是0或者全是1
    {
        cover[rt << 1] = cover[rt << 1 | 1] = cover[rt];//左右孩子与父亲节点一样
        XOR[rt << 1] = XOR[rt << 1 | 1] = 0;//异或标记清零
        cover[rt] = -1;//标记为没有覆盖
    }
    if (XOR[rt])
    {
        FXOR(rt << 1);
        FXOR(rt << 1 | 1);
        XOR[rt] = 0;
    }
}
void update(char op, int L, int R, int l, int r, int rt)
{
    if (L <= l && r <= R)
    {
        if (op == 'U')//把区间覆盖成1
        {
            cover[rt] = 1;
            XOR[rt] = 0;
        }
        else if (op == 'D')//把区间覆盖成0
        {
            cover[rt] = 0;
            XOR[rt] = 0;
        }
        else if (op == 'C' || op == 'S')//区间0、1互换
        {
            FXOR(rt);
        }
        return ;
    }
    PushDown(rt);
    int m = (l + r) >> 1;
    if (L <= m) update(op , L , R , lson);
    else if (op == 'I' || op == 'C')
    {
        XOR[rt << 1] = cover[rt << 1] = 0;//左孩子覆盖成0
    }
    if (m < R) update(op , L , R , rson);
    else if (op == 'I' || op == 'C')
    {
    	//右孩子覆盖成0
        XOR[rt << 1 | 1] = cover[rt << 1 | 1] = 0;
    }
}
void query(int l, int r, int rt)
{
    if (cover[rt] == 1)
    {
        for (int it = l ; it <= r ; it ++)
        {
            visit[it] = true;
        }
        return ;
    }
    else if (cover[rt] == 0) return ;
    //  if (l == r) return ; // the leaf node never be -1
    PushDown(rt);
    int m = (l + r) >> 1;
    query(lson);
    query(rson);
}
int main()
{
    cover[1] = XOR[1] = 0;
    char op , l , r;
    int a , b;
    while ( ~scanf("%c %c%d,%d%c\n", &op , &l , &a , &b , &r) )
    {
        a <<= 1 , b <<= 1;//均变为了偶数
        if (l == '(') a ++;
        if (r == ')') b --;
        // if (a > b)
        // {
        //     if (op == 'C' || op == 'I')
        //     {
        //         cover[1] = XOR[1] = 0;
        //     }
        // }
        // else
        update(op , a , b , 0 , maxn , 1);
    }
    //只需进行一遍query(),结果就保存在visit数组里了
    query(0 , maxn , 1);
    
    bool flag = false;
    int s = -1 , e;
    for (int i = 0 ; i <= maxn ; i ++)
    {
        if (visit[i])
        {
            if (s == -1) 
            	s = i;
            e = i;
        }
        else
        {
            if (s != -1)
            {
                if (flag) printf(" ");
                flag = true;
                //偶数表示端点,奇数表示两端点间的区间
                printf("%c%d,%d%c", s & 1 ? '(' : '[' , s >> 1 , (e + 1) >> 1 , e & 1 ? ')' : ']');
                s = -1;
            }
        }
    }
    if (!flag) printf("empty set");
    puts("");
    return 0;
}
