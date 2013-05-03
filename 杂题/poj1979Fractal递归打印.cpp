//看不明白啊，这种题怎么做啊？

#include <cstdio>
#include <cstring>
#define  MAX  800
bool box[MAX][MAX];
int f[8] = {1};
void tran(int n, int x, int y)
{
    int i, j;
    for(i = 0; i < f[n]; i++)
    {
        for(j = 0; j < f[n]; j++)
            box[x+i][y+j] = box[i][j];
    }
}
int main()
{
    int i, j, k;
    int n, space;
    for(i = 1; i < 8; i++)
        f[i] = f[i-1] * 3;
    memset(box, false, sizeof(box));
    box[0][0] = true;
    for(i = 0; i < 6; i++)
    {
        tran(i, f[i], f[i]);
        tran(i, 0, 2*f[i]);
        tran(i, 2*f[i], 0);
        tran(i, 2*f[i], 2*f[i]);
    }
    while(scanf("%d", &n) == 1)
    {
        if(n < 0)
            return 0;
        else
        {
            for(i = 0; i < f[n-1]; i++)
            {
                space = 0;
                for(j = 0; j < f[n-1]; j++)
                {
                    if(box[i][j])
                    {
                        for(k = 0; k < space; k++)
                            putchar(' ');
                        space = 0;
                        putchar('X');
                    }
                    else
                        space++;
                }
                putchar('\n');
            }
        }
        printf("-\n");
    }
}


