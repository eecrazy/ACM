#include <cstdio>
#include <algorithm>
#include<string.h>
//#include<iostream>
using namespace std;
//#include<stack>
//#include<queue>
char ch;
char ch1[1000];
char ch2[1000];
int a,b;
int f[1000][1000];
int main()
{
    while(scanf("%s%s",ch1,ch2)!=EOF)
    {
        a=strlen(ch1);
        b=strlen(ch2);
        for(int i=0; i<=a; i++)f[i][0]=0;
        for(int i=0; i<=b; i++)f[0][i]=0;
        for(int i=1; i<=a; i++)
        {
            for(int j=1; j<=b; j++)
            {
                if(ch1[i-1]==ch2[j-1])f[i][j]=f[i-1][j-1]+1;
                else if(ch1[i-1]!=ch2[j-1])
                f[i][j] = max(f[i-1][j],f[i][j-1]);
            }
        }
        printf("%d\n",f[a][b]);
        char ch1[1000];
        char ch2[1000];
    }
}
 