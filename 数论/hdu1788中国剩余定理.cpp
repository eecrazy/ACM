/*中国剩余定理，就这个定理本身，还是比较简单的：
假设m1,m2,…,mk两两互素，则下面同余方程组：
x≡a1(mod m1)
x≡a2(mod m2)
…
x≡ak(mod mk)
在0<=<m1m2…mk内有唯一解。
记Mi=M/mi(1<=i<=k),因为（Mi,mi）=1,故有二个整数pi,qi满足Mipi+miqi=1,如果记ei=Mi/pi,那么会有：
ei≡0(mod mj),j!=i
ei≡1(mod mj),j=i
很显然，e1a1+e2a2+…+ekak就是方程组的一个解，这个解加减M的整数倍后就可以得到最小非负整数解。
这就是中国剩余定理及其求解过程。*/

#include <cstdio>
#include <iostream>
using namespace std;
__int64 gcd(__int64 a,__int64 b)
{
	return b==0?a:gcd(b,a%b);
}

int main()
{
	int n,k;
	int temp;
	__int64 ans;
	while(cin>>n>>k,n+k)
	{
		ans=1;
		for(int i=0;i<n;i++)
		{
			cin>>temp;
			ans=(ans*temp)/gcd(ans,temp);
		}
		cout<<ans-k<<endl;
	}
}
