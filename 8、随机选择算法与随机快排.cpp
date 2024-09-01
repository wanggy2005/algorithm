//随机快速排序 https://leetcode.cn/problems/sort-an-array/description/?envType=problem-list-v2&envId=Y7h19rjC& O(N*log N)
#define MAXN 100001
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Solution {
private:
    void quickSort(vector<int>& nums, int l, int r) {
        if (l >= r) return;
        int x = nums[l + rand() % (r - l + 1)];
        int left = l, right = r;
        while (left <= right) {
            while (nums[left] < x) left++;
            while (nums[right] > x) right--;
            if (left <= right) {
                swap(nums[left++], nums[right--]);
            }
        }
        quickSort(nums, l, right);
        quickSort(nums, left, r);
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }
};

//利用荷兰国旗问题
class Solution {
private:
    void quickSort(vector<int>& nums, int l, int r) {
        if (l >= r) return;
        int left, right;
        partition(nums, l, r, left, right);
        quickSort(nums, l, left - 1);
        quickSort(nums, right + 1, r);
    }
    void partition(vector<int>& nums, int l, int r, int& left, int& right) {
        int x = nums[l + rand() % (r - l + 1)];
        int first = l;
        int last = r;
        int i = l;
        while (i <= last) {
            if (nums[i] == x) {
                i++;
            }else if (nums[i] < x) {
                swap(nums[first++], nums[i++]);
            }else {
                swap(nums[i], nums[last--]);
            }
        }
        left = first;
        right = last;
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }
};

//数组中的第K个最大元素 https://leetcode.cn/problems/kth-largest-element-in-an-array/description/?envType=problem-list-v2&envId=Y7h19rjC&
/*给定整数数组 nums 和整数 k，请返回数组中第 k 大的元素。
请注意，你需要找的是数组排序后的第 k 大的元素，而不是第 k 个不同的元素。
你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。*/
class Solution {
private:
    int first = 0; // 分区的起始位置
    int last = 0; // 分区的结束位置
    // 分区函数，将数组分为小于、等于和大于枢纽值的三部分
    void partition(vector<int>& nums, int l, int r, int x) {
        first = l;
        last = r;
        int i = l;
        while (i <= last) {
            if (nums[i] == x) {
                i++;
            }else if (nums[i] < x) {
                swap(nums[first++], nums[i++]);
            }else {
                swap(nums[i], nums[last--]);
            }
        }
    }
    // 随机选择算法，找到第 index 个元素（第 index 大的元素）
    int randomizedSelect(vector<int>& nums, int index) {
        int ans = 0;
        for (int l = 0, r = nums.size() - 1; l <= r;) {
            // 随机选择枢纽值进行分区
            partition(nums, l, r, nums[l + rand() % (r - l + 1)]);
            if (index < first) {
                r = first - 1; // 第 index 大的元素在左边分区
            }else if (index > last) {
                l = last + 1; // 第 index 大的元素在右边分区
            }else {
                ans = nums[index]; // 找到第 index 大的元素
                break;
            }
        }
        return ans;
    }
public:
    int findKthLargest(vector<int>& nums, int k) {
        return randomizedSelect(nums, nums.size() - k);
    }
};

class Solution {
public:
    void quickSort(vector<int>& nums, int l, int r) {
        if (l >= r) return;
        int x = nums[l + rand() % (r - l + 1)];
        int left = l, right = r;
        while (left <= right) {
            while (nums[left] < x) left++;
            while (nums[right] > x) right--;
            if (left <= right) {
                swap(nums[left++], nums[right--]);
            }
        }
        quickSort(nums, l, right);
        quickSort(nums, left, r);
    }
    int findKthLargest(vector<int>& nums, int k) {
        quickSort(nums, 0, nums.size() - 1);
        return nums[nums.size()-k];
    }
};