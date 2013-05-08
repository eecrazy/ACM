#include <iostream>
#include <sstream>
#include <cstdio>
#include <vector>
using namespace std;
vector<long long> X, Y, Z;
const long long INF = 100000000000;

int count(int k)
{
    int ans = 0;
    for(int i=0; i<X.size(); i++)
    {
        if (k >= X[i] && k <= Y[i] && (k - X[i]) % Z[i] == 0)
            ans++;
    }
    return ans;
}
bool judge(long long k)
{
    long long count = 0;
    for(int i=0; i<X.size(); i++)
    {
        long long num = max(0LL, (min(k, Y[i]) - X[i]) / Z[i] + 1);
        count += num;
    }
    return count % 2 != 0;
}
void solve()
{
    long long left = 0, right = INF;
    while (right>left+1)
    {
        long long mid = (left + right) / 2;
        if (judge(mid))
            right = mid;
        else left = mid;
    }
    if (right == INF)
        printf("no corruption\n");
    else
        printf("%lld %d\n",right,count(right));
}
int main()
{
    //freopen("in.txt","r",stdin);
    string s;
    while (getline(cin, s))
    {
        if (s=="")
        {
            if (X.size() != 0)
            {
                solve();
                X.clear();
                Y.clear();
                Z.clear();
            }
        }
        else
        {
            istringstream iss(s);
            int x, y, z;
            iss>>x>>y>>z;
            X.push_back(x);
            Y.push_back(y);
            Z.push_back(z);
        }
    }
    if (X.size() != 0)
    solve();
}