#include<unordered_set>
#include<unordered_map>
using namespace std;
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
//一、返回两个无环链表相交的第一个节点 https://leetcode.cn/problems/intersection-of-two-linked-lists/
/*给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 null 。
题目数据 保证 整个链式结构中不存在环。
注意，函数返回结果后，链表必须 保持其原始结构 。*/

//利用HashSet
//时间复杂度：O(m+n)，其中 m 和 n 是分别是链表 headA 和 headB 的长度。需要遍历两个链表各一次。
//空间复杂度：O(m)，其中 m 是链表 headA 的长度。需要使用哈希集合存储链表 headA 中的全部节点。
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
//更好的解法：
class Solution {
    ListNode* getIntersectionNode(ListNode* h1, ListNode* h2) {
        if (h1 == nullptr || h2 == nullptr) {
            return nullptr;
        }
        ListNode* a = h1, * b = h2;
        int diff = 0;
        // 计算两个链表的长度之差
        while (a->next != nullptr) {
            a = a->next;
            diff++;
        }
        while (b->next != nullptr) {
            b = b->next;
            diff--;
        }
        if (a != b) {// 如果两个链表的尾节点不相同，说明没有交点
            return nullptr;
        }
        // 重新初始化指针，根据长度差移动较长链表的头指针
        a=diff>=0?h1:h2;//长指针
        b=diff>=0?h2:h1;//短指针
        diff = abs(diff);// diff 的绝对值即为两个链表的长度差
        while (diff-- != 0) {
            a = a->next;// 使较长链表的指针与较短链表的指针对齐
        }
        // 同时移动两个指针，直到找到交点
        while (a != b) {
            a = a->next;
            b = b->next;
        }
        return a;
    }
};

//二、每k个节点一组翻转链表 https://leetcode.cn/problems/reverse-nodes-in-k-group/
/*给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。
k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。*/
//利用容器实现
class Solution {
private:
    // 反转从 start 到 end 的链表部分，不包括 end 节点
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
        return pre; // 返回反转后的新头结点
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k < 1) return nullptr;  // 如果链表为空或 k 小于1，返回空指针
        ListNode* dummy = new ListNode(0);  // 哑节点，简化操作
        dummy->next = head;
        ListNode* preGroupEnd = dummy;      // 前一组的结束节点
        ListNode* groupStart = head;        // 当前组的起始节点
        // 主循环，处理每一组
        while (groupStart) {
            ListNode* groupEnd = groupStart;
            // 找到当前组的结束节点
            for (int i = 1; i < k; i++) {
                groupEnd = groupEnd->next;
                if (!groupEnd) {// 如果剩余节点不够一组，直接返回结果
                    return dummy->next;
                }
            }
            ListNode* nextGroupStart = groupEnd->next;  // 下一组的起始节点
            groupEnd->next = nullptr;  // 断开当前组与下一组的连接
            // 反转当前组并获得新的组头。将前一组与新反转的组连接
            preGroupEnd->next = reverse(groupStart, groupEnd->next);
            // 连接反转后的当前组到下一组
            groupStart->next = nextGroupStart;
            // 更新 preGroupEnd 和 groupStart，为下一次循环做准备
            preGroupEnd = groupStart;
            groupStart = nextGroupStart;
        }
        return dummy->next;
    }
};

//三、复制带随机指针的链表 https://leetcode.cn/problems/copy-list-with-random-pointer/
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
        // 1 -> 2 -> 3 -> ... 变成 : 1 -> 1' -> 2 -> 2' -> 3 -> 3' -> ...
        while (cur != nullptr) {
            next = cur->next;
            cur->next = new Node(cur->val);
            cur->next->next = next;
            cur = next;
        }

        cur = head;
        Node* copy = nullptr;
        // 设置每一个新节点的 random 指针
        while (cur != nullptr) {
            next = cur->next->next;
            copy = cur->next;
            copy->random = (cur->random != nullptr) ? cur->random->next : nullptr;
            cur = next;
        }

        Node* ans = head->next;
        cur = head;
        // 新老链表分离 : 老链表重新连接，新链表重新连接
        while (cur != nullptr) {
            next = cur->next->next;
            copy = cur->next;
            cur->next = next;
            copy->next = (next != nullptr) ? next->next : nullptr;
            cur = next;
        }
        // 返回新链表的头节点
        return ans;
    }
};

//利用HashMap和递归（Hash不会重复）
class Solution {
public:
    // 哈希表用于存储原节点到新节点的映射
    unordered_map<Node*, Node*> cachedNode;
    // 递归复制链表
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }
        // 如果节点已经被复制过，直接返回新节点
        if (!cachedNode.count(head)) {
            Node* headNew = new Node(head->val);// 创建新的节点，复制原节点的值
            cachedNode[head] = headNew;// 存储新节点到哈希表中
            // 递归复制 next 和 random 指针指向的链表节点
            headNew->next = copyRandomList(head->next);
            headNew->random = copyRandomList(head->random);
        }
        // 返回已存在的复制节点
        return cachedNode[head];
    }
};

//四、判断链表是否是回文结构 https://leetcode.cn/problems/palindrome-linked-list/
//快指针一次跳两步，慢指针一次跳一步
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return true;
        }
        // 快慢指针找到中点
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        // 现在 slow 是中点，从中点开始反转链表后半部分
        ListNode* pre = slow;
        ListNode* cur = pre->next;
        ListNode* next = nullptr;
        pre->next = nullptr;//断开链接
        /*如果没有这一步，在反转链表的过程中，原本连接前后两部分链表的指针将保持不变。
        反转后，pre 将成为新的后半部分的头节点，而 cur->next 仍然指向旧的前半部分的尾部（中间节点），这可能会导致一个循环结构。
        例如，如果链表是 1 -> 2 -> 3 -> 2 -> 1，那么反转后会成为 1 -> 2 < -3 < -2 < -1，此时 2 -> 3 这个指针仍然存在，形成一个环。*/
        while (cur != nullptr) {
            next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        // 现在链表被调整为从左右两侧往中间指
        // head -> ... -> slow <- ... <- pre
        bool ans = true;
        ListNode* left = head;
        ListNode* right = pre;
        // 比较前半部分和反转后的后半部分
        while (left != nullptr && right != nullptr) {
            if (left->val != right->val) {
                ans = false;
                break;
            }
            left = left->next;
            right = right->next;
        }
        // 恢复链表原来的顺序
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

//五、返回链表的第一个入环节点 https://leetcode.cn/problems/linked-list-cycle-ii/
//快慢指针的算法
class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        if (head == nullptr || head->next == nullptr || head->next->next == nullptr) {// 如果链表为空或链表只有一个节点或两个节点，无环
            return nullptr; 
        }

        ListNode* slow = head->next;
        ListNode* fast = head->next->next;
        while (slow != fast) {// 快慢指针相遇表示有环
            if (fast->next == nullptr || fast->next->next == nullptr) {// 如果快指针到达链表末端，说明无环
                return nullptr;
            }
            // 慢指针走一步，快指针走两步
            slow = slow->next;
            fast = fast->next->next;
        }
        // 将快指针重新指向头节点
        fast = head;
        // 快指针变为走一步，快慢指针相遇的节点即为环的入口节点
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow; // 返回第二次相遇的节点
    }
};

//六、排序链表 https://leetcode.cn/problems/sort-list/
// 要求时间复杂度O(n*logn)，额外空间复杂度O(1)，还要求稳定性
/*                 时间               空间              稳定性
SelectionSort    O(N ^ 2)             O(1)               无
BubbleSort       O(N ^ 2)             O(1)               有
InsertionSort    O(N ^ 2)             O(1)               有
MergeSort        O(N* logN)           O(N)               有         归并排序在链表上可以将空间复杂度降为O(1)
QuickSort        O(N* logN)           O(logN)            无
HeapSort         O(N* logN)           O(1)               无
CountSort        O(N)                 O(M)               有
RadixSort        O(N)                 O(M)               有
*/                 
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) return head;// 如果链表为空或只有一个节点，直接返回原链表
        int n = 0;//链表长度
        ListNode* cur = head; 
        while (cur) {
            n++;
            cur = cur->next;
        }
        // 外层循环：逐步扩大每组的步长进行归并
        for (int step = 1; step < n; step <<= 1) {
            ListNode* l1 = head;
            ListNode* r1 = findEnd(l1, step); // 找到当前步长的右端点
            ListNode* l2 = r1->next; // l2是下一组的起始点
            ListNode* r2 = findEnd(l2, step); // 找到下一组的右端点
            ListNode* next = r2->next; // 下一组的起始点
            // 切断当前组的链表
            r1->next = nullptr;
            r2->next = nullptr;
            // 第一组要确定头部，单独处理
            head = merge(l1, r1, l2, r2);
            lastTeamEnd = end; // 更新上一组的结尾

            // 处理剩余的组
            while (next) {
                l1 = next;
                r1 = findEnd(l1, step); // 找到当前步长的右端点
                l2 = r1->next; // l2是下一组的起始点
                if (!l2) {
                    // 如果l2为空，说明没有更多的组，直接连接剩余部分
                    lastTeamEnd->next = l1;
                    break;
                }
                r2 = findEnd(l2, step); // 找到下一组的右端点
                next = r2->next; // 更新下一组的起始点
                // 切断当前组的链表
                r1->next = nullptr;
                r2->next = nullptr;
                // 合并当前两组
                lastTeamEnd->next = merge(l1, r1, l2, r2);
                lastTeamEnd = end; // 更新上一组的结尾
            }
        }
        return head;
    }
private:
    //从起始节点s开始，向下数k个节点并返回，如果链表不足k个节点，返回链表的最后一个节点
    ListNode* findEnd(ListNode* s, int k) {
        while (s->next && --k) {
            s = s->next;
        }
        return s;
    }
    ListNode* start;// 全局变量：归并后的链表的头节点
    ListNode* end;// 全局变量：归并后的链表的尾节点
    ListNode* lastTeamEnd = nullptr;// 全局变量：最后一组链表的结尾
    // 函数：合并两个有序链表部分
    // l1...r1 -> 已排序的左部分   l2...r2 -> 已排序的右部分
    // 返回合并后的有序链表的头节点
    ListNode* merge(ListNode* l1, ListNode* r1, ListNode* l2, ListNode* r2) {
        ListNode* pre = nullptr;
        // 选择起始节点
        if (l1->val <= l2->val) {
            start = l1;
            pre = l1;
            l1 = l1->next;
        }else {
            start = l2;
            pre = l2;
            l2 = l2->next;
        }
        // 合并两个有序链表
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

