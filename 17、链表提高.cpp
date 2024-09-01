#include<unordered_set>
#include<unordered_map>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
//һ�����������޻������ཻ�ĵ�һ���ڵ� https://leetcode.cn/problems/intersection-of-two-linked-lists/
/*���������������ͷ�ڵ� headA �� headB �������ҳ������������������ཻ����ʼ�ڵ㡣����������������ཻ�ڵ㣬���� null ��
��Ŀ���� ��֤ ������ʽ�ṹ�в����ڻ���
ע�⣬�������ؽ����������� ������ԭʼ�ṹ ��*/

//����HashSet
//ʱ�临�Ӷȣ�O(m+n)������ m �� n �Ƿֱ������� headA �� headB �ĳ��ȡ���Ҫ�������������һ�Ρ�
//�ռ临�Ӷȣ�O(m)������ m ������ headA �ĳ��ȡ���Ҫʹ�ù�ϣ���ϴ洢���� headA �е�ȫ���ڵ㡣
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        unordered_set<ListNode*> visited;
        ListNode* temp = headA;
        while (temp != nullptr) {
            visited.insert(temp);
            temp = temp->next;
        }
        temp = headB;
        while (temp != nullptr) {
            if (visited.count(temp)) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
};
//���õĽⷨ��
class Solution {
    ListNode* getIntersectionNode(ListNode* h1, ListNode* h2) {
        if (h1 == nullptr || h2 == nullptr) {
            return nullptr;
        }
        ListNode* a = h1, * b = h2;
        int diff = 0;
        // ������������ĳ���֮��
        while (a->next != nullptr) {
            a = a->next;
            diff++;
        }
        while (b->next != nullptr) {
            b = b->next;
            diff--;
        }
        if (a != b) {// ������������β�ڵ㲻��ͬ��˵��û�н���
            return nullptr;
        }
        // ���³�ʼ��ָ�룬���ݳ��Ȳ��ƶ��ϳ������ͷָ��
        a=diff>=0?h1:h2;//��ָ��
        b=diff>=0?h2:h1;//��ָ��
        diff = abs(diff);// diff �ľ���ֵ��Ϊ��������ĳ��Ȳ�
        while (diff-- != 0) {
            a = a->next;// ʹ�ϳ������ָ����϶������ָ�����
        }
        // ͬʱ�ƶ�����ָ�룬ֱ���ҵ�����
        while (a != b) {
            a = a->next;
            b = b->next;
        }
        return a;
    }
};

//����ÿk���ڵ�һ�鷭ת���� https://leetcode.cn/problems/reverse-nodes-in-k-group/
/*���������ͷ�ڵ� head ��ÿ k ���ڵ�һ����з�ת�����㷵���޸ĺ������
k ��һ��������������ֵС�ڻ��������ĳ��ȡ�����ڵ��������� k ������������ô�뽫���ʣ��Ľڵ㱣��ԭ��˳��
�㲻��ֻ�ǵ����ĸı�ڵ��ڲ���ֵ��������Ҫʵ�ʽ��нڵ㽻����*/
//��������ʵ��
class Solution {
private:
    // ��ת�� start �� end �������֣������� end �ڵ�
    ListNode* reverse(ListNode* start, ListNode* end) {
        ListNode* pre = nullptr;
        ListNode* cur = start;
        ListNode* next = nullptr;
        while (cur != end) {
            next = cur->next;  
            cur->next = pre;   
            pre = cur;        
            cur = next;
        }
        return pre; // ���ط�ת�����ͷ���
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k < 1) return nullptr;  // �������Ϊ�ջ� k С��1�����ؿ�ָ��
        ListNode* dummy = new ListNode(0);  // �ƽڵ㣬�򻯲���
        dummy->next = head;
        ListNode* preGroupEnd = dummy;      // ǰһ��Ľ����ڵ�
        ListNode* groupStart = head;        // ��ǰ�����ʼ�ڵ�
        // ��ѭ��������ÿһ��
        while (groupStart) {
            ListNode* groupEnd = groupStart;
            // �ҵ���ǰ��Ľ����ڵ�
            for (int i = 1; i < k; i++) {
                groupEnd = groupEnd->next;
                if (!groupEnd) {// ���ʣ��ڵ㲻��һ�飬ֱ�ӷ��ؽ��
                    return dummy->next;
                }
            }
            ListNode* nextGroupStart = groupEnd->next;  // ��һ�����ʼ�ڵ�
            groupEnd->next = nullptr;  // �Ͽ���ǰ������һ�������
            // ��ת��ǰ�鲢����µ���ͷ����ǰһ�����·�ת��������
            preGroupEnd->next = reverse(groupStart, groupEnd->next);
            // ���ӷ�ת��ĵ�ǰ�鵽��һ��
            groupStart->next = nextGroupStart;
            // ���� preGroupEnd �� groupStart��Ϊ��һ��ѭ����׼��
            preGroupEnd = groupStart;
            groupStart = nextGroupStart;
        }
        return dummy->next;
    }
};

//�������ƴ����ָ������� https://leetcode.cn/problems/copy-list-with-random-pointer/
class Node {
public:
    int val;
    Node* next;
    Node* random;
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }
        Node* cur = head;
        Node* next = nullptr;
        // 1 -> 2 -> 3 -> ... ��� : 1 -> 1' -> 2 -> 2' -> 3 -> 3' -> ...
        while (cur != nullptr) {
            next = cur->next;
            cur->next = new Node(cur->val);
            cur->next->next = next;
            cur = next;
        }

        cur = head;
        Node* copy = nullptr;
        // ����ÿһ���½ڵ�� random ָ��
        while (cur != nullptr) {
            next = cur->next->next;
            copy = cur->next;
            copy->random = (cur->random != nullptr) ? cur->random->next : nullptr;
            cur = next;
        }

        Node* ans = head->next;
        cur = head;
        // ����������� : �������������ӣ���������������
        while (cur != nullptr) {
            next = cur->next->next;
            copy = cur->next;
            cur->next = next;
            copy->next = (next != nullptr) ? next->next : nullptr;
            cur = next;
        }
        // �����������ͷ�ڵ�
        return ans;
    }
};

//����HashMap�͵ݹ飨Hash�����ظ���
class Solution {
public:
    // ��ϣ�����ڴ洢ԭ�ڵ㵽�½ڵ��ӳ��
    unordered_map<Node*, Node*> cachedNode;
    // �ݹ鸴������
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }
        // ����ڵ��Ѿ������ƹ���ֱ�ӷ����½ڵ�
        if (!cachedNode.count(head)) {
            Node* headNew = new Node(head->val);// �����µĽڵ㣬����ԭ�ڵ��ֵ
            cachedNode[head] = headNew;// �洢�½ڵ㵽��ϣ����
            // �ݹ鸴�� next �� random ָ��ָ�������ڵ�
            headNew->next = copyRandomList(head->next);
            headNew->random = copyRandomList(head->random);
        }
        // �����Ѵ��ڵĸ��ƽڵ�
        return cachedNode[head];
    }
};

//�ġ��ж������Ƿ��ǻ��Ľṹ https://leetcode.cn/problems/palindrome-linked-list/
//��ָ��һ������������ָ��һ����һ��
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return true;
        }
        // ����ָ���ҵ��е�
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        // ���� slow ���е㣬���е㿪ʼ��ת�����벿��
        ListNode* pre = slow;
        ListNode* cur = pre->next;
        ListNode* next = nullptr;
        pre->next = nullptr;//�Ͽ�����
        /*���û����һ�����ڷ�ת����Ĺ����У�ԭ������ǰ�������������ָ�뽫���ֲ��䡣
        ��ת��pre ����Ϊ�µĺ�벿�ֵ�ͷ�ڵ㣬�� cur->next ��Ȼָ��ɵ�ǰ�벿�ֵ�β�����м�ڵ㣩������ܻᵼ��һ��ѭ���ṹ��
        ���磬��������� 1 -> 2 -> 3 -> 2 -> 1����ô��ת����Ϊ 1 -> 2 < -3 < -2 < -1����ʱ 2 -> 3 ���ָ����Ȼ���ڣ��γ�һ������*/
        while (cur != nullptr) {
            next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        // ������������Ϊ�������������м�ָ
        // head -> ... -> slow <- ... <- pre
        bool ans = true;
        ListNode* left = head;
        ListNode* right = pre;
        // �Ƚ�ǰ�벿�ֺͷ�ת��ĺ�벿��
        while (left != nullptr && right != nullptr) {
            if (left->val != right->val) {
                ans = false;
                break;
            }
            left = left->next;
            right = right->next;
        }
        // �ָ�����ԭ����˳��
        cur = pre->next;
        pre->next = nullptr;
        next = nullptr;
        while (cur != nullptr) {
            next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return ans;
    }
};

//�塢��������ĵ�һ���뻷�ڵ� https://leetcode.cn/problems/linked-list-cycle-ii/
//����ָ����㷨
class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {// �������Ϊ�ջ�����ֻ��һ���ڵ�������ڵ㣬�޻�
            return nullptr; 
        }

        ListNode* slow = head->next;
        ListNode* fast = head->next->next;
        while (slow != fast) {// ����ָ��������ʾ�л�
            if (fast->next == nullptr || fast->next->next == nullptr) {// �����ָ�뵽������ĩ�ˣ�˵���޻�
                return nullptr;
            }
            // ��ָ����һ������ָ��������
            slow = slow->next;
            fast = fast->next->next;
        }
        // ����ָ������ָ��ͷ�ڵ�
        fast = head;
        // ��ָ���Ϊ��һ��������ָ�������Ľڵ㼴Ϊ������ڽڵ�
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow; // ���صڶ��������Ľڵ�
    }
};

//������������ https://leetcode.cn/problems/sort-list/
// Ҫ��ʱ�临�Ӷ�O(n*logn)������ռ临�Ӷ�O(1)����Ҫ���ȶ���
/*                 ʱ��               �ռ�              �ȶ���
SelectionSort    O(N ^ 2)             O(1)               ��
BubbleSort       O(N ^ 2)             O(1)               ��
InsertionSort    O(N ^ 2)             O(1)               ��
MergeSort        O(N* logN)           O(N)               ��         �鲢�����������Ͽ��Խ��ռ临�ӶȽ�ΪO(1)
QuickSort        O(N* logN)           O(logN)            ��
HeapSort         O(N* logN)           O(1)               ��
CountSort        O(N)                 O(M)               ��
RadixSort        O(N)                 O(M)               ��
*/                 
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;// �������Ϊ�ջ�ֻ��һ���ڵ㣬ֱ�ӷ���ԭ����
        int n = 0;//������
        ListNode* cur = head; 
        while (cur) {
            n++;
            cur = cur->next;
        }
        // ���ѭ����������ÿ��Ĳ������й鲢
        for (int step = 1; step < n; step <<= 1) {
            ListNode* l1 = head;
            ListNode* r1 = findEnd(l1, step); // �ҵ���ǰ�������Ҷ˵�
            ListNode* l2 = r1->next; // l2����һ�����ʼ��
            ListNode* r2 = findEnd(l2, step); // �ҵ���һ����Ҷ˵�
            ListNode* next = r2->next; // ��һ�����ʼ��
            // �жϵ�ǰ�������
            r1->next = nullptr;
            r2->next = nullptr;
            // ��һ��Ҫȷ��ͷ������������
            head = merge(l1, r1, l2, r2);
            lastTeamEnd = end; // ������һ��Ľ�β

            // ����ʣ�����
            while (next) {
                l1 = next;
                r1 = findEnd(l1, step); // �ҵ���ǰ�������Ҷ˵�
                l2 = r1->next; // l2����һ�����ʼ��
                if (!l2) {
                    // ���l2Ϊ�գ�˵��û�и�����飬ֱ������ʣ�ಿ��
                    lastTeamEnd->next = l1;
                    break;
                }
                r2 = findEnd(l2, step); // �ҵ���һ����Ҷ˵�
                next = r2->next; // ������һ�����ʼ��
                // �жϵ�ǰ�������
                r1->next = nullptr;
                r2->next = nullptr;
                // �ϲ���ǰ����
                lastTeamEnd->next = merge(l1, r1, l2, r2);
                lastTeamEnd = end; // ������һ��Ľ�β
            }
        }
        return head;
    }
private:
    //����ʼ�ڵ�s��ʼ��������k���ڵ㲢���أ����������k���ڵ㣬������������һ���ڵ�
    ListNode* findEnd(ListNode* s, int k) {
        while (s->next && --k) {
            s = s->next;
        }
        return s;
    }
    ListNode* start;// ȫ�ֱ������鲢��������ͷ�ڵ�
    ListNode* end;// ȫ�ֱ������鲢��������β�ڵ�
    ListNode* lastTeamEnd = nullptr;// ȫ�ֱ��������һ������Ľ�β
    // �������ϲ���������������
    // l1...r1 -> ��������󲿷�   l2...r2 -> ��������Ҳ���
    // ���غϲ�������������ͷ�ڵ�
    ListNode* merge(ListNode* l1, ListNode* r1, ListNode* l2, ListNode* r2) {
        ListNode* pre = nullptr;
        // ѡ����ʼ�ڵ�
        if (l1->val <= l2->val) {
            start = l1;
            pre = l1;
            l1 = l1->next;
        }else {
            start = l2;
            pre = l2;
            l2 = l2->next;
        }
        // �ϲ�������������
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                pre->next = l1;
                pre = l1;
                l1 = l1->next;
            }else {
                pre->next = l2;
                pre = l2;
                l2 = l2->next;
            }
        }
        if (l1) {
            pre->next = l1;
            end = r1;
        }else {
            pre->next = l2;
            end = r2;
        }
        return start;
    }
};

