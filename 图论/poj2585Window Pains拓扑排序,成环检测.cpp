// 每个数字都占有一块固定的区域,如果在这个区域内出现了其他的数字,那么就说明后面的数字是后来才出现的,
// 规定,后出现的大于先出现的.在关系图中用有向边a->b表示a < b;如果发现图中成环,就说明出现了矛盾的情况.
// 也就是不可能出现题目给出的情形,否则就是可行的.
#include <cstdio>
#include <iostream>
#include <string.h>
using namespace std;
bool graph[10][10];
bool connect[10][10];
bool inconsistent;
int map[5][5];
void check()
{
    int id, row, col;
    for (id = 1; id <= 9; id++)
    {
        row = id / 3 + 1;
        col = id % 3;
        if (col == 0)
        {
            row--;
            col = 3;
        }
        if (map[row][col] != id)
            graph[id][map[row][col]] = true;
        if (map[row][col + 1] != id)
            graph[id][map[row][col + 1]] = true;
        if (map[row + 1][col] != id)
            graph[id][map[row + 1][col]] = true;
        if (map[row + 1][col + 1] != id)
            graph[id][map[row + 1][col + 1]] = true;
    }
}

bool have_ring()
{
    memset(connect, false, sizeof(connect));
    int i, j, k;
    for (i = 1; i <= 9; i++)
    {
        for (j = 1 ; j <= 9; j++)
        {
            connect[i][j] = graph[i][j];
        }
    }
    for (k = 1; k <= 9; k++)
    {
        for (i  = 1; i <= 9; i++)
        {
            for (j = 1; j <= 9; j++)
            {
                if (connect[i][k] && connect[k][j])
                {
                    connect[i][j] = true;
                }
            }
        }
    }
    for (i = 1; i  <= 9; i++)
    {
        if (connect[i][i])
        {
            return true;
        }
    }
    return false;
}
int main()
{
    int i, j;
    char temp[11];
    while (cin >> temp)
    {
        if (strcmp(temp, "ENDOFINPUT") == 0)
            break;
        for (i = 1; i <= 4; i++)
        {
            for (j = 1; j <= 4; j++)
                scanf("%d", &map[i][j]);
        }
        cin >> temp;
        inconsistent = false;
        memset(graph, 0, sizeof(graph));
        check();//建图
        if (have_ring())
            printf("THESE WINDOWS ARE BROKEN\n");
        else
            printf("THESE WINDOWS ARE CLEAN\n");
    }
}
