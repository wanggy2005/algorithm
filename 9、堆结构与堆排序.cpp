/*堆（优先队列）https://www.bilibili.com/video/BV1AF411G7cA?vd_source=f8aeedc23d987bfb0dea78b38581fa28
1、堆必须是一个完全二叉树。
完全二叉树只允许最后一行不为满，且最后一行必须无间隔地从左向右排序。
2、大根堆中，每个父节点的元素必须大于其子节点中的元素；
小根堆中，每个父节点的元素必须小于其父节点中的元素。
3、第i个节点的父节点：（i-1)/2
第i个节点的左子节点：2i+1	第i个节点的右子节点：2i+2
*/
//1、从顶向底建堆 O（N*log N）
//将数据逐个插入堆的顶部，再对其进行向上调整
//2、从底向顶建堆 O (N)
//先将数据全部压入堆中，再对每个父节点进行向下调整

//堆排序 https://leetcode.cn/problems/sort-an-array/?envType=problem-list-v2&envId=QiPupvND&
//从底向顶建堆
#include <vector>
#include <algorithm>
class Solution {
private:
    void heapify(vector<int>& arr, int i, int size) {// 将元素下滤，维护堆的性质
        int l = 2 * i + 1; // 左子节点
        while (l < size) {
            // 在左节点与右节点中找出较大的子节点
            int best = (l + 1 < size && arr[l + 1] > arr[l]) ? l + 1 : l;
            // 在较大的子节点和父节点中找出最大的节点
            best = (arr[best] > arr[i]) ? best : i;
            if (best == i) {
                break; // 如果父节点最大，则不需向下调整
            }
            swap(arr[best], arr[i]);// 否则交换父节点和较大的子节点
            i = best; // 更新当前节点位置为较大子节点位置
            l = 2 * i + 1; // 更新左子节点位置
        }
    }
    void heapSort(vector<int>& arr) {// 堆排序函数
        int n = arr.size();
        // 自底向上建立大顶堆（大顶堆排序完为正序）
        for (int i = (n - 1) / 2; i >= 0; i--) {
            heapify(arr, i, n);
        }
        // 将最大元素移动到数组末尾，缩小堆的范围，继续调整堆
        while (n > 1) {
            swap(arr[0], arr[--n]); // 弹出堆顶元素
            heapify(arr, 0, n); // 调整堆顶元素，维护堆的性质
        }
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        if (nums.size() > 1)    heapSort(nums);
        return nums;
    }
};

#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
void heapify(vector<int>& nums, int i, int n) {
	int l = 2 * i + 1;
	while (l < n) {
		int largest = (l + 1 < n && nums[l] < nums[l + 1]) ? l + 1 : l;
		largest = nums[largest] > nums[i] ? largest : i;
		if (largest == i) { break; }
		swap(nums[i], nums[largest]);
		i = largest;
		l = 2 * i + 1;
	}
}
void heapSort(vector<int>& nums, int n) {
	if (n <= 1) { return; }
	for (int i = (n - 1) / 2; i >= 0; i--) {
		heapify(nums, i, n);
	}
	int size = n;
	while (size > 1) {
		swap(nums[0], nums[--size]);
		heapify(nums, 0, size);
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n = 0;
	cin >> n;
	vector<int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}
	heapSort(nums, n);
	for (int i = 0; i < n; i++) {
		cout << nums[i] << " ";
		if (i == n - 1) { cout << endl; }
	}
	return 0;
}