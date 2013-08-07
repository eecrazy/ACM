#include <cstdio>
const int MAX = 32;
int main()
{
	long long e[MAX][MAX] = {0};
	int i, j, n, m;
	for(i = 0; i < MAX; i++) {
		e[i][i] = 1;//i个数分成i组
	}
	//i表示数据大小，j表示分成的组数
	for(i = 1; i < MAX; i++) {
		for(j = 1; j < i; j++) {
			//i个数分成j组，等于i-1个数分成j组，剩下一个加入其中一组。加上i-1个数分成j-1组，剩下一个数单独为一组。
			e[i][j] += e[i-1][j]*j + e[i-1][j-1];
		}
	}
	while(scanf("%d %d", &n, &m) == 2) {
		printf("%lld\n", e[n][m]);
	}
	
	return 0;
}
