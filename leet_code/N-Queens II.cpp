#include <iostream>
using namespace std;
#include <vector>
#include <memory.h>
#include <map>
#include <string>

class Solution {
public:
	int totalNQueens(int n) {
		q_num = 1;
		sum = 0;
		pro(n);
		return sum;
	}
	void pro(int n)
	{
		for (int i = 1; i <= n; i++)
		{
			if (is_valid(q_num, i))
			{
				queen_pos[q_num] = i;
				if (q_num == n)
				{
					// my_print(n);
					sum++;
					return ;
				}
				q_num++;
				pro(n);
				queen_pos[q_num] = 0;
				q_num--;
			}
		}
	}
	bool is_valid(int q_num, int pos)
	{
		for (int i = 1; i < q_num; i++)
		{
			if (queen_pos[i] + i == pos + q_num)
				return 0;
			if (queen_pos[i] - i == pos - q_num)
				return 0;
			if (queen_pos[i] == pos)
				return 0;
		}
		return 1;
	}
	int queen_pos[15];
	int q_num ;
	int sum ;
};

int main()
{
	Solution a;
	int b = a.totalNQueens(4);
	printf("%d\n", b );
}
