#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
const int len = 510;
char ch[len][len];
int map[len][len];
struct P
{
    int r,c,step;
    char e;
} star;
int d[4][2] = {1,0,-1,0,0,1,0,-1};
int main()
{
    //freopen("in.txt","r",stdin);
    int t;
    scanf("%d", &t);
    while(t --)
    {
        memset( map, 0,sizeof(map));
        int r ,c;
        scanf("%d %d", &r, &c);
        for(int i = 0; i< r; i++)
        {
            scanf("%s", ch[i]);
        }
        queue<P> q;
        for(int i =0; i < r; i++)
        {
            for( int j =0; j < c; j++)
            {
                if(ch[i][j] >= 'a' && ch[i][j] <= 'z')
                {
                    star.r = i ;
                    star.c= j ;
                    star.step=1;
                    star.e=ch[i][j];
                    q.push(star);
                }
            }
        }
        while(!q.empty())
        {
            P tp = q.front();
            q.pop();
            for( int k =0; k< 4; k++)
            {
                if(ch[tp.r][tp.c]=='*')continue;
                int x = tp.r + d[k][0];
                int y = tp.c + d[k][1];
                if(x>=0&&x<=r-1&&y>=0&&y<=c-1&&ch[x][y]!='*'&&ch[x][y]!='#'&&ch[x][y]!=tp.e)
                {
                    if( ch[x][y]=='.' )
                    {
                        star.r = x;
                        star.c = y;
                        star.step=tp.step+1;
                        star.e=tp.e;
                        map[x][y]=tp.step+1;
                        ch[x][y]=tp.e;
                        q.push(star);
                    }
                    else
                    {
                        if(map[x][y]==tp.step+1)
                        ch[x][y]='*';
                    }
                }
            }
        }
        for(int i = 0; i< r; i++)
        {
            printf("%s\n", ch[i]);
        }
        if(t !=0)puts("");
    }
}
