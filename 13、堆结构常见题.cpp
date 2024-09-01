#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};
//1、合并k个有序链表 https://www.nowcoder.com/practice/65cfde9e5b9b4cf2b6bafa5f3ef33fa6
/*合并 k 个升序的链表并将结果作为一个升序的链表返回其头节点。
数据范围：节点总数满足0≤n≤5000，每个节点的val满足∣val∣ <= 1000 要求：时间复杂度O(nlogn)
示例1输入：[{1, 2, 3}, { 4,5,6,7 }]
返回值：{ 1,2,3,4,5,6,7 }
示例2输入：[{1, 2}, { 1,4,5 }, { 6 }]
返回值：{ 1,1,2,4,5,6 } */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 小根堆
        auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };//自定义比较器
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> heap(cmp); 
        //decltype(cmp) 用于获取 cmp 这个 lambda 表达式的类型
        //如果比较器返回 true，则表示第一个元素的优先级低于第二个元素，在优先队列中第一个元素会被放在第二个元素之后。
        //如果比较器返回 false，则表示第一个元素的优先级高于或等于第二个元素。
        // 将所有链表的头节点加入堆中
        for (ListNode* h : lists) {
            if (h != nullptr) {
                heap.push(h);
            }
        }
        if (heap.empty())   return nullptr;
        // 先弹出一个节点，作为总头部
        ListNode* head = heap.top();
        heap.pop();
        ListNode* pre = head;
        // 如果头节点的下一个节点不为空，加入堆中
        if (pre->next != nullptr) {
            heap.push(pre->next);
        }
        // 逐个弹出堆中的节点，并重建链表
        while (!heap.empty()) {
            ListNode* cur = heap.top();
            heap.pop();
            pre->next = cur;
            pre = pre->next;
            if (cur->next != nullptr) {
                heap.push(cur->next);
            }
        }
        return head;
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> heap(cmp); 
        for (ListNode* h : lists) {
            if (h != nullptr) {
                heap.push(h);
            }
        }
        if (heap.empty())   return nullptr;
        ListNode* head = heap.top();
        heap.pop();
        ListNode* pre = head;
        if (pre->next != nullptr) {
            heap.push(pre->next);
        }
        while (!heap.empty()) {
            ListNode* cur = heap.top();
            heap.pop();
            pre->next = cur;
            pre = pre->next;
            if (cur->next != nullptr) {
                heap.push(cur->next);
            }
        }
        return head;
    }
};

//2、线段最多重合问题  https://www.nowcoder.com/practice/1ae8d0b6bb4e4bcdbf64ec491f63fc37
/*每一个线段都有start和end两个数据项，表示这条线段在X轴上从start位置开始到end位置结束。
给定一批线段，求所有重合区域中最多重合了几个线段，首尾相接的线段不算重合。
例如：线段[1, 2]和线段[2.3]不重合。线段[1, 3]和线段[2, 3]重合。
输入描述：第一行一个数N，表示有N条线段。接下来N行每行2个数，表示线段起始和终止位置
输出描述：输出一个数，表示同一个位置最多重合多少条线段*/
int minMeetingRooms(vector<vector<int>>& meetings) {
    int n = meetings.size();
    // 对会议的开始时间进行排序
    sort(meetings.begin(), meetings.end(), [](const vector<int>& a, const vector<int>& b) {return a[0] < b[0]; });//在 sort 中，true 表示“更高优先级”；而在优先队列中，true 则表示“更低优先级”。
    // 小根堆，存储会议的结束时间
    priority_queue<int, vector<int>, greater<int>> heap;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        // 移除已结束的会议
        while (!heap.empty() && heap.top() <= meetings[i][0]) {
            heap.pop();
        }
        // 加入当前会议的结束时间
        heap.push(meetings[i][1]);
        // 记录需要的会议室数量
        ans = max(ans, (int)heap.size());
    }
    return ans;
}

int coincideNums(vector<vector<int>>& seg){
    sort(seg.begin(),seg.end(),[](vector<int>& a,vector<int>& b){return a[0]<b[0];});
    priority_queue<int, vector<int>, greater<int>> end;
    int ans=0;
    for(int i=0;i<seg.size();i++){
        int startTime=seg[i][0];
        int endTime=seg[i][1];
        while (!end.empty() && end.top() <= startTime) {
            end.pop();
        }
        end.push(endTime);
        ans=max(ans,(int)end.size());
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    vector<vector<int>> seg(n, vector<int>(2));//注意初始化的规范
    for(int i=0;i<n;i++){
        cin>>seg[i][0]>>seg[i][1];
    }
    cout<<coincideNums(seg);
    return 0;
}
//3、将数组和减半的最少操作次数 https://leetcode.cn/problems/minimum-operations-to-halve-array-sum/description/
/*给你一个正整数数组 nums 。每一次操作中，你可以从 nums 中选择 任意 一个数并将它减小到 恰好 一半。（注意，在后续操作中你可以对减半过的数继续执行操作）
请你返回将 nums 数组和 至少 减少一半的 最少 操作数。
输入：nums = [5, 19, 8, 1]
输出：3
解释：初始 nums 的和为 5 + 19 + 8 + 1 = 33 。
以下是将数组和减少至少一半的一种方法：
选择数字 19 并减小为 9.5 。
选择数字 9.5 并减小为 4.75 。
选择数字 8 并减小为 4 。
最终数组为[5, 4.75, 4, 1] ，和为 5 + 4.75 + 4 + 1 = 14.75 。
nums 的和减小了 33 - 14.75 = 18.25 ，减小的部分超过了初始数组和的一半，18.25 >= 33 / 2 = 16.5 。
我们需要 3 个操作实现题目要求，所以返回 3 。
可以证明，无法通过少于 3 个操作使数组和减少至少一半。*/\
class Solution {
public:
    int halveArray(vector<int>& nums) {
        int cnt=0;
        double sum=0;
        priority_queue<double> num;
        for(int n:nums){
            sum+=n;
            num.push(static_cast<double>(n));
        }
        while(sum>0){
            double maxnum=num.top();
            num.pop();            
            num.push(maxnum/2.0);
            sum-=maxnum;
            cnt++;
        }
        return cnt;
    }
};

const int MAXN = 100001;
long heap[MAXN];
class Solution {
public:
    int halveArray(vector<int>& nums) {
        int n = nums.size();
        long long sum = 0;
        for (int i = n - 1; i >= 0; i--) {
            heap[i] = static_cast<long long>(nums[i]) << 20;
            sum += heap[i];
            heapify(i,n);
        }
        sum /= 2;
        int ans = 0;
        for (long long minus = 0; minus < sum; ans++) {
            heap[0] /= 2;
            minus += heap[0];
            heapify(0,n);
        }
        return ans;
    }
private:
    void heapify(int i, int n) {
        int l = i * 2 + 1;
        while (l < n) {
            int best = l + 1 < n && heap[l + 1] > heap[l] ? l + 1 : l;
            best = heap[best] > heap[i] ? best : i;
            if (best == i) {
                break;
            }
            swap(heap[best], heap[i]);
            i = best;
            l = i * 2 + 1;
        }
    }
};
