#include <iostream>
#include <cstring>
using namespace std;
#define X 52
int dp[X][X],dp2[X][X][X],dp3[X][X],dp4[X][X],n,k;
void f_1_3()
{
   for(int i=1;i<X;i++)  //初始化
      dp[i][0] = 0;
    for(int i=0;i<X;i++)  //初始化
      dp[0][i] = 1;
   for(int i=0;i<X;i++)  //实现状态转移方程
      for(int j=1;j<X;j++)
         if(i>=j)
            dp[i][j] = dp[i-j][j]+dp[i][j-1];
         else
            dp[i][j] = dp[i][i];
}
void f_2()
{
   memset(dp2,0,sizeof(dp2));
   for(int i=1;i<X;i++)  //初始化
      dp2[i][1][i] = 1;
   for(int i=0;i<X;i++)  //初始化
      for(int j=0;j<X;j++)
         if(j>i)
            dp2[i][1][j] = dp2[i][1][i];

   for(int i=1;i<X;i++)  //状态转移
      for(int p=2;p<X;p++)
         for(int j=1;j<X;j++)
            if(j>i)
                dp2[i][p][j] = dp2[i][p][i];
            else
                dp2[i][p][j] = dp2[i-j][p-1][j]+dp2[i][p][j-1];
}
void f_4()
{
   memset(dp3,0,sizeof(dp3));
   for(int i=1;i<X;i++)  //初始化，当最大值为1时，只能由i自己本身组成，划分数为1
      dp3[i][1] = 1;
   for(int i=1;i<X;i+=2) //涉及到后面的状态转移时i会减少到0，但实际上，当j为奇数时，必须得加1
      dp3[0][i] = 1;
   dp3[0][0] = 1;        //初始化1
   for(int i=1;i<X;i++)  //实现状态转移方程
      for(int j=3;j<X;j+=2)
      {
         if(j>i)
         {
            if(i%2)
                dp3[i][j] = dp3[i][i];
            else
                dp3[i][j] = dp3[i][i-1];
         }
         else
            dp3[i][j] = dp3[i-j][j]+dp3[i][j-2];
      }
}
void f_5()
{
   memset(dp4,0,sizeof(dp4));
   for(int i=1;i<X;i++)  //初始化
   {
      dp4[1][i] = 1;
      dp4[0][i] = 1;
   }
   for(int i=2;i<X;i++)  //状态转移方程
      for(int j=1;j<X;j++)
         if(i<j)
            dp4[i][j] = dp4[i][i];
         else
            dp4[i][j] = dp4[i][j-1]+dp4[i-j][j-1];
}
int main()
{
   f_1_3();
   f_2();
   f_4();
   f_5();
   while(cin>>n>>k)
   {
      cout<<dp[n][n]<<endl;
      cout<<dp2[n][k][n]<<endl;
      cout<<dp[n][k]<<endl;
      if(n%2)
         cout<<dp3[n][n]<<endl;
      else
         cout<<dp3[n][n-1]<<endl;
      cout<<dp4[n][n]<<endl;
      cout<<endl;
   }
   return 0;
}