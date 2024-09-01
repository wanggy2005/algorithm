//链表
struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

//反转链表 https://leetcode.cn/problems/UHnkqh/description/
/*给定单链表的头节点 head ，请反转链表，并返回反转后的链表的头节点。*/
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

//合并两个有序链表 https://leetcode.cn/problems/merge-two-sorted-lists/description/?envType=problem-list-v2&envId=GeEuTcJ8&
// 将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
class Solution {
public:
	ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
		if (list1 == nullptr || list2 == nullptr)	return list1 == nullptr ? list2 : list1;//处理空链表
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

//两数相加 https://leetcode.cn/problems/add-two-numbers/description/?envType=problem-list-v2&envId=GeEuTcJ8&
/*给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
请你将两个数相加，并以相同形式返回一个表示和的链表。
你可以假设除了数字 0 之外，这两个数都不会以 0 开头。*/
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

//分隔链表 https://leetcode.cn/problems/partition-list/description/?envType=problem-list-v2&envId=GeEuTcJ8&
/*给你一个链表的头节点head和一个特定值x，请你对链表进行分隔，使得所有小于x的节点都出现在大于或等于x的节点之前。你应当保留两个分区中每个节点的初始相对位置。*/
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