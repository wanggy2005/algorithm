//一、利用前缀和快速得到区域累加和 https://leetcode.cn/problems/range-sum-query-immutable/
class NumArray {
private:
    vector<int> sum;
public:
    NumArray(vector<int>& nums) {
        sum.resize(nums.size() + 1, 0);
        for (int i = 1; i <= nums.size(); i++) {
            sum[i] = sum[i - 1] + nums[i - 1];
        }
    }
    int sumRange(int left, int right) {
        return sum[right + 1] - sum[left];
    }
};

//二、返回无序数组中累加和为给定值的最长子数组长度 https://www.nowcoder.com/practice/36fb0fd3c656480c92b569258a1223d5
// 给定一个无序数组arr, 其中元素可正、可负、可0
// 给定一个整数aim
// 求arr所有子数组中累加和为aim的最长子数组长度

//本质是求sum-aim这个前缀和最早出现的位置，而在遍历过程中，sum和sum-aim都随i变化
//用Hashmap来保存前面的前缀和，将时间复杂度降为O(n)
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
const int MAXN = 100001; 
int arr[MAXN];
int n, aim; 
// key : 某个前缀和
// value : 这个前缀和最早出现的位置
unordered_map<int, int> prefixMap; // 使用 unordered_map 存储前缀和及其最早出现的位置
int compute() {
    prefixMap.clear(); // 清空前缀和映射
    prefixMap[0] = -1; // 重要：当前缀和为0时，相当于在数组开始之前已经存在，位置为 -1
    int ans = 0; 
    int sum = 0; 
    for (int i = 0; i < n; i++) {
        sum += arr[i]; // 计算前缀和
        if (prefixMap.count(sum - aim)) { // 如果找到了 sum - aim 的前缀和
            ans = max(ans, i - prefixMap[sum - aim]); // 更新最长子数组长度
        }
        if (!prefixMap.count(sum)) { // 如果当前前缀和第一次出现
            prefixMap[sum] = i; // 记录其出现的位置
        }
    }
    return ans; 
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL); 
    while (cin >> n >> aim) {
        for (int i = 0; i < n; i++) {
            cin >> arr[i]; 
        }
        cout << compute() << endl;
    }
    return 0;
}

//三、返回无序数组中累加和为给定值的子数组个数 https://leetcode.cn/problems/subarray-sum-equals-k/
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> prefixMap;
        int ans = 0;
        int sum = 0;
        prefixMap[0] = 1;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            if (prefixMap.count(sum - k)) {
                ans += prefixMap[sum - k];
            }
            prefixMap[sum]++;
        }
        return ans;
    }
};
//四、返回无序数组中正数和负数个数相等的最长子数组长度 https://www.nowcoder.com/practice/545544c060804eceaed0bb84fcd992fb
// 给定一个无序数组arr，其中元素可正、可负、可0
// 求arr所有子数组中正数与负数个数相等的最长子数组的长度
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
int f(vector<int>& nums, int n) {
    unordered_map<int, int> prefixMap;
    prefixMap[0] = -1;
    int ans = 0;
    int pos = 0, neg = 0;
    for (int i = 0; i < n; i++) {
        if (nums[i] > 0) {
            pos++;
        }else if (nums[i] < 0) {
            neg++;
        }
        int diff = pos - neg; // 正负数的差值
        if (prefixMap.count(diff)) {
            ans = max(ans, i - prefixMap[diff]);
        }else {
            prefixMap[diff] = i; // 记录第一次出现该差值的位置
        }
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    int x;
    vector<int> nums;
    for (int i = 0; i < n; i++) {
        cin >> x;
        nums.push_back(x);
    }
    cout << f(nums, n);
}
//五、表现良好的最长时间段 https://leetcode.cn/problems/longest-well-performing-interval/
// 给你一份工作时间表 hours，上面记录着某一位员工每天的工作小时数
// 我们认为当员工一天中的工作小时数大于 8 小时的时候，那么这一天就是 劳累的一天
// 所谓 表现良好的时间段 ，意味在这段时间内，「劳累的天数」是严格 大于 不劳累的天数
// 请你返回 表现良好时间段 的最大长度
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        unordered_map<int, int> prefixMap;
        prefixMap[0] = -1;
        int sum = 0, ans = 0;
        for (int i = 0; i < hours.size(); ++i) {
            sum += (hours[i] > 8 ? 1 : -1);
            if (sum > 0) {
                ans = i + 1; // 当前整个数组是有效的
            }else {
                if (prefixMap.count(sum - 1)) {
                    ans = max(ans, i - prefixMap[sum - 1]);
                }
                if (!prefixMap.count(sum)) {
                    prefixMap[sum] = i; // 只记录首次出现的位置
                }
            }
        }
        return ans;
    }
};

//六、使数组和能被P整除 https://leetcode.cn/problems/make-sum-divisible-by-p/
// 给你一个正整数数组 nums，请你移除 最短 子数组（可以为 空）
// 使得剩余元素的 和 能被 p 整除。 不允许 将整个数组都移除。
// 请你返回你需要移除的最短子数组的长度，如果无法满足题目要求，返回 -1 。
// 子数组 定义为原数组中连续的一组元素。
class Solution {
private:
    int f(vector<int>& arr, int p, int nums_p) {
        int ans = arr.size();  // 初始化为数组长度
        unordered_map<int, int> prefixMap;
        prefixMap[0] = -1;  // 处理从数组起点开始的情况
        int sum_p = 0;
        for (int i = 0; i < arr.size(); ++i) {
            sum_p = (sum_p + arr[i]) % p;
            // 如果当前的前缀和减去 nums_p 的余数在 map 中存在，更新答案
            int needed = (sum_p - nums_p + p) % p;//防止need为负数
            if (prefixMap.count(needed)) {
                ans = min(ans, i - prefixMap[needed]);
            }
            prefixMap[sum_p] = i;
        }
        return ans == arr.size() ? -1 : ans;
    }
public:
    int minSubarray(vector<int>& nums, int p) {
        int sum = 0;
        vector<int> arr;
        for (int num : nums) {
            sum = (sum + num) % p;//防止溢出
            arr.push_back(num % p);
        }
        int nums_p = sum % p;
        if (nums_p == 0) return 0;  // 如果总和已经可以被 p 整除，不需要删除子数组
        return f(arr, p, nums_p);
    }
};

//七、每个元音包含偶数次的最长子字符串 https://leetcode.cn/problems/find-the-longest-substring-containing-vowels-in-even-counts/
// 给你一个字符串 s ，请你返回满足以下条件的最长子字符串的长度
// 每个元音字母，即 'a'，'e'，'i'，'o'，'u' 在子字符串中都恰好出现了偶数次。
class Solution {
private:
    int move(char cha) {
        switch (cha) {
        case 'a': return 0;
        case 'e': return 1;
        case 'i': return 2;
        case 'o': return 3;
        case 'u': return 4;
        default: return -1;
        }
    }
public:
    int findTheLongestSubstring(const string& s) {
        int n = s.length();
        vector<int> map(32, -2); // map[0...31] = -2
        map[0] = -1; // 初始状态
        int ans = 0;
        int status = 0;
        for (int i = 0; i < n; i++) {
            int m = move(s[i]);
            if (m != -1) {
                status ^= 1 << m; // 巧用位运算更新各字母的奇偶状态
            }
           /*最开始，status 是 0，这意味着所有元音字符的出现次数都是偶数。
             每个元音字符（a、e、i、o、u）都映射到 status 中的一个特定位上。
             当遇到一个元音字符时，status 中对应的位被翻转。
             status ^= 1 << m 的作用是翻转第 m 位：
             如果这位是 0（表示出现次数是偶数），翻转后变为 1（表示出现次数变为奇数）。
             如果这位是 1（表示出现次数是奇数），翻转后变为 0（表示出现次数变为偶数）。*/ 
            if (map[status] != -2) {
                ans = max(ans, i - map[status]);
            }else {
                map[status] = i; // 记录状态首次出现的位置
            }
        }
        return ans;
    }
};