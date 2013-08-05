#include <iostream>
#include <string>
#include <vector>
#include<string.h>
#include<stdio.h>
#include<stack>
//#include<fstream>
using namespace std;
char s1[110][35];
char s2[110][35];
int n, m;

int main()
{
    int a = 0;
    while (scanf("%s", &s1[a]) != EOF)
    {
        a++;
        if (s1[a - 1][0] == '#')
        {
            a--;
            int b = 0;
            while (scanf("%s", &s2[b]))
            {
                b++;
                if (s2[b - 1][0] == '#')
                {
                    b--;
                    break;
                }
            }
            int f[100][100];
            int c[100][100];
            for (int i = 0; i <= a; i++)f[i][0] = 0;
            for (int i = 0; i <= b; i++)f[0][i] = 0;
            for (int i = 1; i <= a; i++)
            {
                for (int j = 1; j <= b; j++)
                {
                    if (strcmp(s1[i - 1], s2[j - 1]) == 0)
                    {
                        f[i][j] = f[i - 1][j - 1] + 1;
                        c[i][j] = 1;
                    }
                    else if (f[i - 1][j] >= f[i][j - 1])
                    {
                        f[i][j] = f[i - 1][j];
                        c[i][j] = 2;
                    }
                    else if (f[i - 1][j] < f[i][j - 1])
                    {
                        f[i][j] = f[i][j - 1];
                        c[i][j] = 3;
                    }
                }
            }
            stack<int> INT_stack;
            n = a; m = b;
            while (a != 0 && b != 0)
            {
                if (c[a][b] == 1)
                {
                    INT_stack.push(a - 1);
                    a--; b--;
                }
                if (c[a][b] == 2)
                    a--;
                if (c[a][b] == 3)
                    b--;
            }
            while (!INT_stack.empty())
            {
                printf("%s", s1[INT_stack.top()]);
                INT_stack.pop();
                if (!INT_stack.empty())printf(" ");
            }
            printf("\n");
        }
    }
}