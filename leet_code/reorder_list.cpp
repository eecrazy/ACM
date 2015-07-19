#include <iostream>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
	void reorderList(ListNode *head) {
		ListNode *A = head;
		int num = 0;
		while (A != NULL)
		{
			A = A->next;
			num += 1;
		}
		// cout << num << endl;
		if (num <= 2)
			return;
		if (num == 3)
		{
			head->next->next->next = head->next;
			A = head->next;
			head->next = A->next;
			A->next = NULL;
			return;
		}
		A = head;
		int mid_num = 0;
		while (mid_num != num / 2)
		{
			A = A->next;
			mid_num += 1;
		}
		ListNode* mid = A;
		ListNode* B;
		ListNode* temp;
		ListNode* temp2;
		ListNode *tail = head;
		while (tail->next != NULL)
			tail = tail->next;
		A = mid;
		B = A->next;
		mid->next = NULL;
		// cout << mid->val << endl;
		while (B != tail)
		{
			temp = B->next;
			B->next = A;
			A = B;
			B = temp;
		}
		tail->next = A;
		if (num % 2 == 0)
		{
			A = head;
			B = tail;
			do
			{
				temp = A->next;
				A->next = B;
				temp2 = B->next;
				B->next = temp;
				A = temp;
				B = temp2;
			} while (B->next != NULL);
			A->next = B;

		}
		else
		{
			A = head;
			B = tail;
			do
			{
				temp = A->next;
				A->next = B;
				temp2 = B->next;
				B->next = temp;
				A = temp;
				B = temp2;
			} while (B->next->next != NULL);
			A->next = B;
		}
	}
};
int main() {
	// int n = 9;
	// printf("%d\n", n);
	ListNode *h = new ListNode(1);
	h->next = new ListNode(2);
	h->next->next = new ListNode(3);
	h->next->next->next = new ListNode(4);
	h->next->next->next->next = new ListNode(5);
	h->next->next->next->next->next = new ListNode(6);
	Solution a;
	a.reorderList(h);
	// return 0;
	while (h != NULL)
	{
		printf("%d ", h->val);
		h = h->next;
	}
	printf("\n");

}