//转化为整数划分问题,划分成不同数字的和,有多少种分法
#include <iostream>
#include <cstring>
using namespace std;
#define X 502
long long dp4[X][X];//结果很大
void f_5()
{
    memset(dp4,0,sizeof(dp4));
    for(int i=1;i<X;i++)    //初始化
    {
        dp4[1][i] = 1;
        dp4[0][i] = 1;
    }
    for(int i=2;i<X;i++)    //状态转移方程
        for(int j=1;j<X;j++)
            if(i<j)
                dp4[i][j] = dp4[i][i];
            else
                dp4[i][j] = dp4[i][j-1]+dp4[i-j][j-1];
}
int main()
{
    int n;
    f_5();
    while(cin>>n&&n)
        cout<<dp4[n][n]-1<<endl;
    return 0;
}
