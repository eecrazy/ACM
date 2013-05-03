POJ 2299.cpp
#include<iostream>//代码简化了很多，只用一个函数，一个tem数组
using namespace std;
#define MAX 1000000000
int a[500001];
int tmp[500001];
long long ans;//逆序数
void Mergesort(int b, int e)
{
    if (e - b <= 0) return;
    int mid = (b + e) / 2, p1 = b, p2 = mid + 1, i = b;
    Mergesort(b, mid);
    Mergesort(mid + 1, e);
    while (p1 <= mid || p2 <= e)
    {
        if (p2 > e || (p1 <= mid && a[p1] <= a[p2]))
            tmp[i++] = a[p1++];
        else
        {
            tmp[i++] = a[p2++];
            ans += (mid - p1 + 1);
        }
    }
    for (i = b; i <= e; i++)a[i] = tmp[i];
}
int main()
{
    int n;
    while(cin>>n,n)
    {
        for(int i=1; i<=n; i++)
            cin>>a[i];
        ans=0;
        Mergesort(1,n);
        cout<<ans<<endl;
        for(int i=1; i<=n; i++)cout<<a[i]<<" ";
        cout<<endl;
    }
    return 0;
}
