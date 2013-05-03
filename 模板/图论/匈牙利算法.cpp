#include<iostream>
using namespace std;
int p[100];//
int f[100][100];//图
bool b[100];//点是否已用
int n,m;
bool path(int x)
{
    int i;
    for(i=1; i<=m; i++)
        if(!b[i]&&f[x][i])
        {
            b[i]=1;
            if(p[i]==0||path(p[i]))
            {
                p[i]=x;
                return true;
            }
        }
    return false;
}
int main()
{
    int ans,x,y,i;
    cin>>n>>m;
    memset(f,0,sizeof(f));
    while(cin>>x>>y&&x+y>0) f[x][y]=1;

    ans=0;
    memset(p,0,sizeof(p));
    for(i=1; i<=n; i++)
    {
        memset(b,0,sizeof(b));
        if(path(i)) ans++;
    }
    cout<<ans<<endl;
    return 0;
}
