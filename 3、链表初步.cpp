//����
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

//��ת���� https://leetcode.cn/problems/UHnkqh/description/
/*�����������ͷ�ڵ� head ���뷴ת���������ط�ת��������ͷ�ڵ㡣*/
class Solution {
public:
	ListNode* reverseList(ListNode* head) {
		ListNode* pre = nullptr;
		ListNode* next = nullptr;
		while (head != nullptr) {
			next = head->next;
			head->next = pre;
			pre = head;
			head = next;
		}
		return pre;
	}
};

//�ϲ������������� https://leetcode.cn/problems/merge-two-sorted-lists/description/?envType=problem-list-v2&envId=GeEuTcJ8&
// ��������������ϲ�Ϊһ���µ������������ء���������ͨ��ƴ�Ӹ�����������������нڵ���ɵġ�
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
		if (list1 == nullptr || list2 == nullptr)	return list1 == nullptr ? list2 : list1;//���������
		ListNode* head = list1->val > list2->val ? list2 : list1;
		ListNode* cur1 = head == list1 ? list1->next : list1;
		ListNode* cur2 = head == list1 ? list2 : list2->next;
		ListNode* pre = head;
		while (cur1 != nullptr && cur2 != nullptr) {
			if (cur1->val > cur2->val) {
				pre->next = cur2;
				cur2 = cur2->next;
			}else {
				pre->next = cur1;
				cur1 = cur1->next;
			}
			pre = pre->next;
		}
		pre->next = cur1 == nullptr ? cur2 : cur1;
		return head;
	}
};

//������� https://leetcode.cn/problems/add-two-numbers/description/?envType=problem-list-v2&envId=GeEuTcJ8&
/*�������� �ǿ� ��������ʾ�����Ǹ�������������ÿλ���ֶ��ǰ��� ���� �ķ�ʽ�洢�ģ�����ÿ���ڵ�ֻ�ܴ洢 һλ ���֡�
���㽫��������ӣ�������ͬ��ʽ����һ����ʾ�͵�����
����Լ���������� 0 ֮�⣬���������������� 0 ��ͷ��*/
class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		if (l1 == nullptr || l2 == nullptr)	return l1 == nullptr ? l2 : l1;
		ListNode* ans = nullptr;
		ListNode* cur = nullptr;
		int carry = 0;
		while (l1 != nullptr || l2 != nullptr) {
			int sum = (l1 == nullptr ? 0 : l1->val) + (l2 == nullptr ? 0 : l2->val) + carry;
			int val = sum % 10;
			carry = sum / 10;
			if (ans == nullptr) {
				ans = new ListNode(val);
				cur = ans;
			}else {
				cur->next = new ListNode(val);
				cur = cur->next;
			}
			l1 = l1 == nullptr ? nullptr : l1->next;
			l2 = l2 == nullptr ? nullptr : l2->next;
		}
		if (carry) {
			cur->next = new ListNode(carry);
		}
		return ans;
	}
};

//�ָ����� https://leetcode.cn/problems/partition-list/description/?envType=problem-list-v2&envId=GeEuTcJ8&
/*����һ�������ͷ�ڵ�head��һ���ض�ֵx�������������зָ���ʹ������С��x�Ľڵ㶼�����ڴ��ڻ����x�Ľڵ�֮ǰ����Ӧ����������������ÿ���ڵ�ĳ�ʼ���λ�á�*/
class Solution {
public:
	ListNode* partition(ListNode* head, int x) {
		ListNode* lefthead = nullptr;
		ListNode* lefttail = nullptr;
		ListNode* righthead = nullptr;
		ListNode* righttail = nullptr;
		if (head == nullptr)	return head;
		while (head != nullptr) {
			if (head->val < x) {
				if (lefthead == nullptr) {
					lefthead = lefttail = head;
				}else {
					lefttail->next = head;
					lefttail = head;
				}
			}else {
				if (righthead == nullptr) {
					righthead = righttail = head;
				}else {
					righttail->next = head;
					righttail = head;
				}
			}
			head = head->next;
		}
		if (lefttail)	lefttail->next = righthead;
		if (righthead)	righttail->next = nullptr;
		return lefthead ? lefthead : righthead;
	}
};