#include <stdio.h>
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
#define MAXN 1000010
int next[MAXN];
int len;
char s[MAXN];
void get_next ()
{
        int i=0,j=-1;
        next[0]=-1;
        while(i<len)
        {
                if(j==-1||s[i]==s[j])
                {
                        i++;
                        j++;
                        next[i]=j;
                }
                else j=next[j];
        }
}
int main()
{
        while(scanf("%s",s)!=EOF)
        {
                if(s[0]=='.')break;
                len =strlen(s);
                int k;
                get_next();
                if(len%(len-next[len])==0)

  /*
        因为next[i]存储的是s[i]为结尾的字符串的最大前缀
        而本题要求子串相连不能相交,所以为了避免相交,需加以判断
        如果能够整除则输出商 否则输出1
        */
                {
                        k=len/(len-next[len]);
                        printf("%d\n",k);
                }
                else printf("1\n");
        }
        return 0;
}
 