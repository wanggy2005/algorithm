//һ������ǰ׺�Ϳ��ٵõ������ۼӺ� https://leetcode.cn/problems/range-sum-query-immutable/
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

//�������������������ۼӺ�Ϊ����ֵ��������鳤�� https://www.nowcoder.com/practice/36fb0fd3c656480c92b569258a1223d5
// ����һ����������arr, ����Ԫ�ؿ������ɸ�����0
// ����һ������aim
// ��arr�������������ۼӺ�Ϊaim��������鳤��

//��������sum-aim���ǰ׺��������ֵ�λ�ã����ڱ��������У�sum��sum-aim����i�仯
//��Hashmap������ǰ���ǰ׺�ͣ���ʱ�临�ӶȽ�ΪO(n)
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
const int MAXN = 100001; 
int arr[MAXN];
int n, aim; 
// key : ĳ��ǰ׺��
// value : ���ǰ׺��������ֵ�λ��
unordered_map<int, int> prefixMap; // ʹ�� unordered_map �洢ǰ׺�ͼ���������ֵ�λ��
int compute() {
    prefixMap.clear(); // ���ǰ׺��ӳ��
    prefixMap[0] = -1; // ��Ҫ����ǰ׺��Ϊ0ʱ���൱�������鿪ʼ֮ǰ�Ѿ����ڣ�λ��Ϊ -1
    int ans = 0; 
    int sum = 0; 
    for (int i = 0; i < n; i++) {
        sum += arr[i]; // ����ǰ׺��
        if (prefixMap.count(sum - aim)) { // ����ҵ��� sum - aim ��ǰ׺��
            ans = max(ans, i - prefixMap[sum - aim]); // ����������鳤��
        }
        if (!prefixMap.count(sum)) { // �����ǰǰ׺�͵�һ�γ���
            prefixMap[sum] = i; // ��¼����ֵ�λ��
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

//�������������������ۼӺ�Ϊ����ֵ����������� https://leetcode.cn/problems/subarray-sum-equals-k/
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
//�ġ��������������������͸���������ȵ�������鳤�� https://www.nowcoder.com/practice/545544c060804eceaed0bb84fcd992fb
// ����һ����������arr������Ԫ�ؿ������ɸ�����0
// ��arr�����������������븺��������ȵ��������ĳ���
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
        int diff = pos - neg; // �������Ĳ�ֵ
        if (prefixMap.count(diff)) {
            ans = max(ans, i - prefixMap[diff]);
        }else {
            prefixMap[diff] = i; // ��¼��һ�γ��ָò�ֵ��λ��
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
//�塢�������õ��ʱ��� https://leetcode.cn/problems/longest-well-performing-interval/
// ����һ�ݹ���ʱ��� hours�������¼��ĳһλԱ��ÿ��Ĺ���Сʱ��
// ������Ϊ��Ա��һ���еĹ���Сʱ������ 8 Сʱ��ʱ����ô��һ����� ���۵�һ��
// ��ν �������õ�ʱ��� ����ζ�����ʱ���ڣ������۵����������ϸ� ���� �����۵�����
// ���㷵�� ��������ʱ��� ����󳤶�
class Solution {
public:
    int longestWPI(vector<int>& hours) {
        unordered_map<int, int> prefixMap;
        prefixMap[0] = -1;
        int sum = 0, ans = 0;
        for (int i = 0; i < hours.size(); ++i) {
            sum += (hours[i] > 8 ? 1 : -1);
            if (sum > 0) {
                ans = i + 1; // ��ǰ������������Ч��
            }else {
                if (prefixMap.count(sum - 1)) {
                    ans = max(ans, i - prefixMap[sum - 1]);
                }
                if (!prefixMap.count(sum)) {
                    prefixMap[sum] = i; // ֻ��¼�״γ��ֵ�λ��
                }
            }
        }
        return ans;
    }
};

//����ʹ������ܱ�P���� https://leetcode.cn/problems/make-sum-divisible-by-p/
// ����һ������������ nums�������Ƴ� ��� �����飨����Ϊ �գ�
// ʹ��ʣ��Ԫ�ص� �� �ܱ� p ������ ������ ���������鶼�Ƴ���
// ���㷵������Ҫ�Ƴ������������ĳ��ȣ�����޷�������ĿҪ�󣬷��� -1 ��
// ������ ����Ϊԭ������������һ��Ԫ�ء�
class Solution {
private:
    int f(vector<int>& arr, int p, int nums_p) {
        int ans = arr.size();  // ��ʼ��Ϊ���鳤��
        unordered_map<int, int> prefixMap;
        prefixMap[0] = -1;  // �����������㿪ʼ�����
        int sum_p = 0;
        for (int i = 0; i < arr.size(); ++i) {
            sum_p = (sum_p + arr[i]) % p;
            // �����ǰ��ǰ׺�ͼ�ȥ nums_p �������� map �д��ڣ����´�
            int needed = (sum_p - nums_p + p) % p;//��ֹneedΪ����
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
            sum = (sum + num) % p;//��ֹ���
            arr.push_back(num % p);
        }
        int nums_p = sum % p;
        if (nums_p == 0) return 0;  // ����ܺ��Ѿ����Ա� p ����������Ҫɾ��������
        return f(arr, p, nums_p);
    }
};

//�ߡ�ÿ��Ԫ������ż���ε�����ַ��� https://leetcode.cn/problems/find-the-longest-substring-containing-vowels-in-even-counts/
// ����һ���ַ��� s �����㷵��������������������ַ����ĳ���
// ÿ��Ԫ����ĸ���� 'a'��'e'��'i'��'o'��'u' �����ַ����ж�ǡ�ó�����ż���Ρ�
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
        map[0] = -1; // ��ʼ״̬
        int ans = 0;
        int status = 0;
        for (int i = 0; i < n; i++) {
            int m = move(s[i]);
            if (m != -1) {
                status ^= 1 << m; // ����λ������¸���ĸ����ż״̬
            }
           /*�ʼ��status �� 0������ζ������Ԫ���ַ��ĳ��ִ�������ż����
             ÿ��Ԫ���ַ���a��e��i��o��u����ӳ�䵽 status �е�һ���ض�λ�ϡ�
             ������һ��Ԫ���ַ�ʱ��status �ж�Ӧ��λ����ת��
             status ^= 1 << m �������Ƿ�ת�� m λ��
             �����λ�� 0����ʾ���ִ�����ż��������ת���Ϊ 1����ʾ���ִ�����Ϊ��������
             �����λ�� 1����ʾ���ִ���������������ת���Ϊ 0����ʾ���ִ�����Ϊż������*/ 
            if (map[status] != -2) {
                ans = max(ans, i - map[status]);
            }else {
                map[status] = i; // ��¼״̬�״γ��ֵ�λ��
            }
        }
        return ans;
    }
};