#include <iostream>
using namespace std;
#include <cstdio>
#include <algorithm>

long long a[4];
int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        for (int i = 0; i < n; i++)scanf("%d", &a[i]);
        int m=unique(a,a+n);
    	cout<<m<<endl;
    
    }
}