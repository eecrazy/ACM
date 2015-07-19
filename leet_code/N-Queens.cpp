#include <iostream>
using namespace std;
#include <vector>
#include <memory.h>
#include <map>
#include <string>

class Solution {
public:
	vector<vector<string> > solveNQueens(int n) {
		q_num = 1;
		sum = 0;
		pro(n);
		return a;
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
					vector<string> v;
					for (int i = 1; i <= n; i++)
					{

						string s = "";
						for (int j = 1; j <= n; j++)
						{

							if (queen_pos[i] == j)
								s += "Q";
							else
								s += ".";
						}
						v.push_back(s);
					}
					a.push_back(v);
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
	vector<vector<string> > a;
	int queen_pos[15];
	int q_num ;
	int sum ;

};
int main()
{
	Solution a;
	vector<vector<string> > b = a.solveNQueens(12);
	for (int i = 0; i < b.size(); i++)
	{
		for (int j = 0; j < b[i].size(); j++)
			cout << b[i][j] << endl;
		cout << endl;
	}
	printf("%d\n", a.sum );
}
