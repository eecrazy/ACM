#include<iostream>
using namespace std;
#include<string.h>
char str[101];
int judge[101][101];//judge[i][j]表示将str[i]...str[j]从judge[i][j]处分开
// 即AB的形式,-1表示不分开即（S）
int res[101][101];
int inline match(int i, int j)
{
    return ((str[i] == '(' && str[j] == ')') || (str[i] == '[' && str[j] == ']'));
}
int brackets(int beg, int end)
{
    if (res[beg][end] != -1)
        return res[beg][end];
    if (beg == end)
    {
        res[beg][end] = 1;
        return res[beg][end];
    }
    if (beg > end)
    {
        res[beg][end] = 0;
        return 0;
    }

    int p = beg;
    int min = brackets(beg, p) + brackets(p + 1, end);
    for ( int s = beg + 1; s < end; s++)
    {
        if (min > brackets(beg, s) + brackets(s + 1, end))
        {
            p = s;
            min = brackets(beg, s) + brackets(s + 1, end);
        }
    }
    int m;
    if (match(beg, end))
    {
        m = brackets(beg + 1, end - 1);
        if (m > min)
        {
            judge[beg][end] = p;
            res[beg][end] = min;
            return min;
        }
        else
        {
            res[beg][end] = m;
            return m;
        }
    }

    judge[beg][end] = p;
    res[beg][end] = min;
    return min;
}
void display(int beg, int end)
{
    if (beg > end)
        return ;
    if (beg == end)
    {
        if (str[beg] == '(' || str[beg] == ')')
            cout << "()";
        else
            cout << "[]";
        return;
    }
    if (judge[beg][end] == -1)
    {
        cout << str[beg];
        display(beg + 1, end - 1);
        cout << str[end];
        return;
    }
    else
    {
        display(beg, judge[beg][end]);
        display(judge[beg][end] + 1, end);
        return ;
    }
}
int main()
{
    while (cin >> str)
    {
        size_t len = strlen(str);
        memset(res, -1, sizeof(res));
        memset(judge, -1, sizeof(judge)); //所有的分割值都初始化为-1

        for (size_t i = 0; i < len; i++)
            res[i][i] = 1;
        for (size_t i = 1; i < len; i++)
            for (size_t j = 0; j < i; j++)
                res[i][j] = 0;

        brackets(0, len - 1);
        display(0, len - 1);
        cout << endl;
    }
    return 0;
}