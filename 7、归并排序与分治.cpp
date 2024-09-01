#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
//归并排序 https://www.luogu.com.cn/problem/P1177 O(n*log n)
/*将读入的n个数从小到大排序后输出。*/
const int MAXN = 100001; // 定义数组的最大长度
int arr[MAXN]; // 原数组
int help[MAXN]; // 辅助数组
int n; // 数组长度
void merge(int l, int m, int r) {// 归并函数，用于合并两个已排序的子数组
	int i = l;
	int a = l;
	int b = m + 1;
	while (a <= m && b <= r) {
		help[i++] = arr[a] <= arr[b] ? arr[a++] : arr[b++];
	}
	while (a <= m) {
		help[i++] = arr[a++];
	}
	while (b <= r) {
		help[i++] = arr[b++];
	}
	for (i = l; i <= r; i++) {
		arr[i] = help[i];
	}
}
void mergesort(int l, int r) {// 归并排序函数，递归地将数组划分为子数组并排序
	if (l == r)	return;
	int m = l + (r - l) / 2;
	mergesort(l, m);
	mergesort(m + 1, r);
	merge(l, m, r);
}
int main() {
	ios::sync_with_stdio(false); // 禁用同步，提高输入输出效率
	cin.tie(nullptr); // 解除cin和cout的绑定
	cout.tie(nullptr);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	mergesort(0, n - 1);
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
		if (i == n)	cout << "\n";
	}
	return 0;
}

/*归并分治
1.一个问题的答案是否可以简化为“左+右+左跨右”
2.计算左跨右时，若在左、右部分均有序，是否能产生便利性（有序性是重点）
*/
//例一、计算小和 https://www.nowcoder.com/questionTerminal/edfe05a1d45c4ea89101d936cac32469
/*在一个数组中，每一个数左边比当前数小的数累加起来，叫做这个数组的小和。求一个数组的小和。
例子[1, 3, 4, 2, 5]
1左边比1小的数：没有
3左边比3小的数：1
4左边比4小的数：1, 3
2左边比2小的数：1
5左边比5小的数：1, 3, 4, 2
所以小和为1 + 1 + 3 + 1 + 1 + 3 + 4 + 2 = 16
给定一个数组s，实现函数返回s的小和
*/
const int MAXN = 100001;
int n;
int arr[MAXN];
int help[MAXN];
long long Merge(int l, int m, int r) {// 归并函数，用于合并两个已排序的子数组并计算累加和
	long long ans = 0;
	for (int i = l, j = m + 1, sum = 0; j <= r; j++) {// 计算累加和
		while (i <= m && arr[i] <= arr[j]) {
			sum += arr[i++]; // 累积左半部分小于等于右半部分的元素和
		}
		ans += sum; // 将累积和加到最终答案中
	}
	int a = l, b = m + 1, i = l;// 归并过程
	while (a <= m && b <= r) {
		help[i++] = arr[a] <= arr[b] ? arr[a++] : arr[b++];
	}
	while (a <= m) {
		help[i++] = arr[a++];
	}
	while (b <= r) {
		help[i++] = arr[b++];
	}
	for (int i = l; i <= r; i++) {// 将辅助数组中的元素复制回原数组
		arr[i] = help[i];
	}
	return ans; // 返回累加和
}
long long mergecalculate(int l, int r) {
	if (l == r)	return 0;
	int m = l + (r - l) / 2;
	return mergecalculate(l, m) + mergecalculate(m + 1, r) + Merge(l, m, r);// 递归地计算左右两部分，并合并结果
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cout << mergecalculate(0, n - 1);
	return 0;
}

//例二、反转对 https://leetcode.cn/problems/reverse-pairs/
/*给定一个数组 nums ，如果 i < j 且 nums[i] > 2*nums[j] 我们就将 (i, j) 称作一个重要翻转对。
你需要返回给定数组中的重要翻转对的数量。*/
const int MAXN = 50001;
int help[MAXN];
class Solution {
public:
	int merge(int l, int m, int r, vector<int>& nums) {
		int ans = 0;
		for (int i = l, j = m + 1; i <= m; i++) {
			while (j <= r && (long)nums[i] > 2 * (long)nums[j]) {
				j++;
			}
			ans += j - (m + 1);
//在内层的while循环中，找到所有满足nums[i]>2*nums[j]的右子数组元素，并将j向右移动。
// 当j停止移动时，说明从j到r的所有元素都满足nums[i]>2*nums[j]。因此，对于每个i，满足条件的逆序对数量是 j - (m + 1)
		}
		int a = l, i = l, b = m + 1;
		while (a <= m && b <= r) {
			help[i++] = nums[a] <= nums[b] ? nums[a++] : nums[b++];
		}
		while (a <= m) {
			help[i++] = nums[a++];
		}
		while (b <= r) {
			help[i++] = nums[b++];
		}
		for (int i = l; i <= r; i++) {
			nums[i] = help[i];
		}
		return ans;
	}
	int mergecount(int l, int r, vector<int>& nums) {
		if (l >= r) return 0; 
		int m = l + (r - l) / 2;
		return mergecount(l, m, nums) + mergecount(m + 1, r, nums) + merge(l, m, r, nums);
	}
	int reversePairs(vector<int>& nums) {
		int n = nums.size();
		return mergecount(0, n - 1, nums);
	}
};