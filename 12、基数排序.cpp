#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
/*基数排序：不基于比较的排序  https://leetcode.cn/problems/sort-an-array/
和比较无关的排序，对于对象的数据特征有要求，并不通用
基数排序的实现细节
关键点：前缀数量分区的技巧、数字提取某一位的技巧
时间复杂度O(n)，额外空间复杂度O(m)，需要辅助空间做类似桶的作用，来不停的装入、弹出数字

一般来讲，基数排序要求，样本是10进制的非负整数
如果不是就需要转化，代码里做了转化，并且代码里可以设置任何进制来进行排序
一旦比较的对象不再是常规数字，那么改写代价的增加是显而易见的，所以不基于比较的排序并不通用
*/
class Solution {
private:
    int BASE = 10; // 基数排序的基数，默认是10进制
    int MAXN = 50001; 
    int* help = new int[MAXN]; // 辅助数组，用于排序过程中存放数据
    int* cnts = new int[BASE]; // 计数数组，用于记录每个基数位置上的数字出现次数
    // 计算一个数字在指定基数下的位数
    int bits(int number) {
        int ans = 0;
        while (number > 0) {
            ans++;
            number /= BASE;
        }
        return ans;
    }
    void radixSort(vector<int>& nums, int n, int bits) {
        for (int offset = 1; bits > 0; offset *= BASE, bits--) {
            // 重置计数数组
            memset(cnts, 0, BASE * sizeof(int));
            // 统计每个基数位置上的数字出现次数
            for (int i = 0; i < n; i++) {
                cnts[(nums[i] / offset) % BASE]++;
            }
            // 将计数数组转化为前缀和数组，方便定位每个数字在辅助数组中的位置
            for (int i = 1; i < BASE; i++) {
                cnts[i] = cnts[i] + cnts[i - 1];
            }
            // 从后往前遍历原数组，将数字放置到辅助数组中的正确位置
            for (int i = n - 1; i >= 0; i--) {
                help[--cnts[(nums[i] / offset) % BASE]] = nums[i];
            }
            // 将辅助数组中的内容复制回原数组
            for (int i = 0; i < n; i++) {
                nums[i] = help[i];
            }
        }
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        int n = nums.size();
        int min = *min_element(nums.begin(), nums.end());// 找到数组中的最小值
        // 将数组中的每个元素都减去最小值，转化为非负数组
        for (int i = 0; i < n; i++) {
            nums[i] -= min;
        }
        int max = *max_element(nums.begin(), nums.end());// 找到数组中的最大值
        // 计算最大值的位数，决定基数排序的轮数
        radixSort(nums, n, bits(max));
        // 将数组中的每个元素都加回最小值，恢复原来的值
        for (int i = 0; i < n; i++) {
            nums[i] += min;
        }
        return nums;
    }
};


static const int BASE = 10;
int bits(int number) {
    if (number == 0) return 1;
    int ans = 0;
    while (number > 0) {
        ans++;
        number /= BASE;
    }
    return ans;
}
void radixSort(vector<int>& nums, int n, int bits, vector<int>& cnt, vector<int>& help) {
    fill(cnt.begin(), cnt.end(), 0);
    for (int offset = 1; bits > 0; offset *= BASE, bits--) {
        for (int i = 0; i < n; i++) {
            int digit = (nums[i] / offset) % BASE;
            if (digit < 0) digit += BASE;
            cnt[digit]++;
        }
        for (int i = 1; i < BASE; i++) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            int digit = (nums[i] / offset) % BASE;
            if (digit < 0) digit += BASE;
            help[--cnt[digit]] = nums[i];
        }
        for (int i = 0; i < n; i++) {
            nums[i] = help[i];
        }
        fill(cnt.begin(), cnt.end(), 0);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> nums(n);
    vector<int> help(n);
    vector<int> cnt(BASE);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    int maxval = *max_element(nums.begin(), nums.end());
    int bit = bits(maxval);
    radixSort(nums, n, bit, cnt, help);
    for (int i = 0; i < n; i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
    return 0;
}
