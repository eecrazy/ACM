#include <cstdio>
#include <iostream>
using namespace std;
int cube[30330],nr[30330];
int n;
void make_set()
{
    for(int i=0; i<=30030; ++i)
    {
        cube[i] = -1;
        nr[i] = 0;
    }
}
int find_set(int x)
{
    int tmp = cube[x];
    if(cube[x]<0)
        return x;
    cube[x] = find_set(cube[x]);
    nr[x] += nr[tmp];
    return cube[x];
}
void union_set(const int& root1,const int& root2)
{
    int tmp = cube[root1];
    cube[root1] = root2;
    nr[root1] =nr[root1] - cube[root2];
    cube[root2] += tmp;
}
int main()
{
    int i,j,root1,root2,n1,n2;
    char ch;
    while(scanf("%d",&n)!=EOF)
    {
        make_set();
        while(n--)
        {
            scanf(" %c",&ch);
            if(ch=='M')
            {
                scanf("%d%d",&n1,&n2);
                int root1 = find_set(n1);
                int root2 = find_set(n2);
                if(root1!=root2)
                    union_set(root1,root2);
            }
            else if(ch=='C')
            {
                scanf("%d",&n1);
                int tmp =find_set(n1);
                printf("%d\n",nr[n1]);
            }
        }
    }
    return 0;
}
