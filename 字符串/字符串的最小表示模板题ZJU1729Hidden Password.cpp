#include <cstdio>
using namespace std;
#include <iostream>
char s[100005];
int l;
int MinimumRepresentation(char *s,int l)//串s[0~l-1]的最小表示位置
{
    int i = 0, j = 1, k = 0,t;
    while (i < l && j < l && k < l)//找不到比它还小的 或者 完全匹配
    {
        t = s[(i+k)%l] - s[(j+k)%l];
        //if (s[(i+k) >= l ? i+k-l : i+k] == s[(j+k) >= l ? j+k-l : j+k])
        if (t == 0)
            k++;//相等的话,检测长度加1
        else 
        {
            if (t > 0)//大于的话,s[i]为首的肯定不是最小表示,最大表示就改<
                i += k + 1;
            else
                j += k + 1;
            if (i == j)
                j++;
            k = 0;
        } 
    } 
    return min(i,j);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %s",&l,&s);
        printf("%d\n",MinimumRepresentation(s,l));
    }
}
/*
把一个长为len的字符串围成一个圈，然后以任意一个字符作为起点，都会产生一个新的长为len的字符串，字符串的最小表示就是所有新字符串中字典序最小的那个。

下面这个函数就是解决这个问题的，返回值为字典序最小的串的在原串中的起始位置。

int MinimumRepresentation(char *s,int l)//串s[0~l-1]的最小表示位置
{
    int i = 0, j = 1, k = 0,t;
    while (i < l && j < l && k < l)//找不到比它还小的 或者 完全匹配
    {
        t = s[(i+k)%l] - s[(j+k)%l];
        //if (s[(i+k) >= l ? i+k-l : i+k] == s[(j+k) >= l ? j+k-l : j+k])
        if (t == 0)
            k++;//相等的话,检测长度加1
        else 
        {
            if (t > 0)//大于的话,s[i]为首的肯定不是最小表示,最大表示就改<
                i += k + 1;
            else
                j += k + 1;
            if (i == j)
                j++;
            k = 0;
        } 
    } 
    return min(i,j);
}

基本想法就是两个位置的字符比较，如果s[i+k] > s[j+k]那么i到i+k位置都不是最小表示的位置，所以i直接跳k+1步，反之j直接跳k+1步。*/