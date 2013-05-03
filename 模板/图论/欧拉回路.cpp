#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;
int e[2000][2];                                                              //e[i][0],e[i][1]分别存放编号为i的街道的两个交点
int degree[50];                                                             //存放顶点的度数
bool vis[2000];
int s[2000];                                                                 //用来存放路径的栈
int edgenum,start,top,maxnum;
bool check()                                                               //欧拉回路存在的充要条件是不存在度数为奇数的顶点
{
     int i;
     for(i=1;i<=maxnum;i++)
        if(degree[i]%2==1)
          return false;                                                                       //不存在欧拉回路
     return true;
}
void euler(int u)                                                                          //从顶点u开始递归求解欧拉回路
{
     int i;
     for(i=1;i<=edgenum;i++)
       if(!vis[i]&&(e[i][0]==u||e[i][1]==u))                                        //即编号为i的街道有有一个交点为u
       {
           vis[i]=true;
           euler(e[i][0]+e[i][1]-u);                                                    //递归的访问该条街道的另一个顶点
           s[top++]=i;                                                                     //这里存入的是边的编号,注意不是顶点
       }
}
int main()
{
    int x,y,z,i;
    scanf("%d%d",&x,&y);
    while(x&&y)
    {
        memset(e,0,sizeof(e));
        memset(degree,0,sizeof(degree));
        memset(vis,0,sizeof(vis));
        maxnum=edgenum=top=0;
        start=min(x,y);                                                                   //题目中说起点为第一组输入数据中最小的交点
        do
        {
              scanf("%d",&z);
              e[z][0]=x;                                     
              e[z][1]=y;
              degree[x]++;                                                                //相应的增加顶点的度数
              degree[y]++;
              edgenum++;
              maxnum=max(maxnum,max(x,y));                                 //最大的交点
        }
        while(scanf("%d%d",&x,&y)!=EOF&&(x&&y));
        if(!check())
           printf("Round trip does not exist.\n");
        else
        {
            euler(start);
            for(i=top-1;i>=0;i--)                                                         //逆序输出
               printf("%d ",s[i]);
            printf("\n");                        
        }
        scanf("%d%d",&x,&y);
    }
    system("pause");
    return 0;
}