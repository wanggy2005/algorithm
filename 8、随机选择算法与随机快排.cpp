//����������� https://leetcode.cn/problems/sort-an-array/description/?envType=problem-list-v2&envId=Y7h19rjC& O(N*log N)
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

//���ú�����������
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

//�����еĵ�K�����Ԫ�� https://leetcode.cn/problems/kth-largest-element-in-an-array/description/?envType=problem-list-v2&envId=Y7h19rjC&
/*������������ nums ������ k���뷵�������е� k ���Ԫ�ء�
��ע�⣬����Ҫ�ҵ������������ĵ� k ���Ԫ�أ������ǵ� k ����ͬ��Ԫ�ء�
�������Ʋ�ʵ��ʱ�临�Ӷ�Ϊ O(n) ���㷨��������⡣*/
class Solution {
private:
    int first = 0; // ��������ʼλ��
    int last = 0; // �����Ľ���λ��
    // �����������������ΪС�ڡ����ںʹ�����Ŧֵ��������
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
    // ���ѡ���㷨���ҵ��� index ��Ԫ�أ��� index ���Ԫ�أ�
    int randomizedSelect(vector<int>& nums, int index) {
        int ans = 0;
        for (int l = 0, r = nums.size() - 1; l <= r;) {
            // ���ѡ����Ŧֵ���з���
            partition(nums, l, r, nums[l + rand() % (r - l + 1)]);
            if (index < first) {
                r = first - 1; // �� index ���Ԫ������߷���
            }else if (index > last) {
                l = last + 1; // �� index ���Ԫ�����ұ߷���
            }else {
                ans = nums[index]; // �ҵ��� index ���Ԫ��
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