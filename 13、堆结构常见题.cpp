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
//1���ϲ�k���������� https://www.nowcoder.com/practice/65cfde9e5b9b4cf2b6bafa5f3ef33fa6
/*�ϲ� k ������������������Ϊһ���������������ͷ�ڵ㡣
���ݷ�Χ���ڵ���������0��n��5000��ÿ���ڵ��val����Oval�O <= 1000 Ҫ��ʱ�临�Ӷ�O(nlogn)
ʾ��1���룺[{1, 2, 3}, { 4,5,6,7 }]
����ֵ��{ 1,2,3,4,5,6,7 }
ʾ��2���룺[{1, 2}, { 1,4,5 }, { 6 }]
����ֵ��{ 1,1,2,4,5,6 } */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // С����
        auto cmp = [](ListNode* a, ListNode* b) { return a->val > b->val; };//�Զ���Ƚ���
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> heap(cmp); 
        //decltype(cmp) ���ڻ�ȡ cmp ��� lambda ���ʽ������
        //����Ƚ������� true�����ʾ��һ��Ԫ�ص����ȼ����ڵڶ���Ԫ�أ������ȶ����е�һ��Ԫ�ػᱻ���ڵڶ���Ԫ��֮��
        //����Ƚ������� false�����ʾ��һ��Ԫ�ص����ȼ����ڻ���ڵڶ���Ԫ�ء�
        // �����������ͷ�ڵ�������
        for (ListNode* h : lists) {
            if (h != nullptr) {
                heap.push(h);
            }
        }
        if (heap.empty())   return nullptr;
        // �ȵ���һ���ڵ㣬��Ϊ��ͷ��
        ListNode* head = heap.top();
        heap.pop();
        ListNode* pre = head;
        // ���ͷ�ڵ����һ���ڵ㲻Ϊ�գ��������
        if (pre->next != nullptr) {
            heap.push(pre->next);
        }
        // ����������еĽڵ㣬���ؽ�����
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

//2���߶�����غ�����  https://www.nowcoder.com/practice/1ae8d0b6bb4e4bcdbf64ec491f63fc37
/*ÿһ���߶ζ���start��end�����������ʾ�����߶���X���ϴ�startλ�ÿ�ʼ��endλ�ý�����
����һ���߶Σ��������غ�����������غ��˼����߶Σ���β��ӵ��߶β����غϡ�
���磺�߶�[1, 2]���߶�[2.3]���غϡ��߶�[1, 3]���߶�[2, 3]�غϡ�
������������һ��һ����N����ʾ��N���߶Ρ�������N��ÿ��2��������ʾ�߶���ʼ����ֹλ��
������������һ��������ʾͬһ��λ������غ϶������߶�*/
int minMeetingRooms(vector<vector<int>>& meetings) {
    int n = meetings.size();
    // �Ի���Ŀ�ʼʱ���������
    sort(meetings.begin(), meetings.end(), [](const vector<int>& a, const vector<int>& b) {return a[0] < b[0]; });//�� sort �У�true ��ʾ���������ȼ������������ȶ����У�true ���ʾ���������ȼ�����
    // С���ѣ��洢����Ľ���ʱ��
    priority_queue<int, vector<int>, greater<int>> heap;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        // �Ƴ��ѽ����Ļ���
        while (!heap.empty() && heap.top() <= meetings[i][0]) {
            heap.pop();
        }
        // ���뵱ǰ����Ľ���ʱ��
        heap.push(meetings[i][1]);
        // ��¼��Ҫ�Ļ���������
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
    vector<vector<int>> seg(n, vector<int>(2));//ע���ʼ���Ĺ淶
    for(int i=0;i<n;i++){
        cin>>seg[i][0]>>seg[i][1];
    }
    cout<<coincideNums(seg);
    return 0;
}
//3��������ͼ�������ٲ������� https://leetcode.cn/problems/minimum-operations-to-halve-array-sum/description/
/*����һ������������ nums ��ÿһ�β����У�����Դ� nums ��ѡ�� ���� һ������������С�� ǡ�� һ�롣��ע�⣬�ں�������������ԶԼ������������ִ�в�����
���㷵�ؽ� nums ����� ���� ����һ��� ���� ��������
���룺nums = [5, 19, 8, 1]
�����3
���ͣ���ʼ nums �ĺ�Ϊ 5 + 19 + 8 + 1 = 33 ��
�����ǽ�����ͼ�������һ���һ�ַ�����
ѡ������ 19 ����СΪ 9.5 ��
ѡ������ 9.5 ����СΪ 4.75 ��
ѡ������ 8 ����СΪ 4 ��
��������Ϊ[5, 4.75, 4, 1] ����Ϊ 5 + 4.75 + 4 + 1 = 14.75 ��
nums �ĺͼ�С�� 33 - 14.75 = 18.25 ����С�Ĳ��ֳ����˳�ʼ����͵�һ�룬18.25 >= 33 / 2 = 16.5 ��
������Ҫ 3 ������ʵ����ĿҪ�����Է��� 3 ��
����֤�����޷�ͨ������ 3 ������ʹ����ͼ�������һ�롣*/\
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
