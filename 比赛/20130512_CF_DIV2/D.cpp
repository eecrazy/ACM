//别人的ac代码！
//http://codeforces.com/contest/304/problem/D
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstring>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;

const int INF = 2147483647;
const double PI = 3.1415926536;

int gcd(int a, int b){
	if(!min(a, b)) return max(a, b);
	else return gcd(min(a, b), max(a, b)%min(a, b));
}

int main() {

	int n, m, x, y, a, b;
	cin >> n >> m >> x >> y >> a >> b;
	int g = gcd(a, b);
	a/=g;
	b/=g;

	int maxS = min(n/a, m/b);
	a*=maxS, b*=maxS;

	int x1 = x+a/2-a, y1 = y+b/2-b;
	x1 = min(x1, n-a), y1 = min(y1, m-b);
	x1 = max(x1, 0), y1 = max(y1, 0);


	cout << x1 << " " << y1 << " " << x1+a << " " << y1+b << endl;

	return 0;

}