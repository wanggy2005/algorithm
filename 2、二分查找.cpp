#include<vector>
using namespace std;
//时间复杂度为logN
//查找有序数组中某个值是否存在
bool exist_num(int* arr, int n, int num) {
	if (arr == nullptr || n == 0)	return false;
	int l = 0;//左端
	int r = n - 1;//右端
	int m = 0;
	while (l <= r) {
		m = l + (r - l) >> 1;
		if (arr[m] > num)	r = m - 1;
		if (arr[m] < num)	l = m + 1;
		else	return true;
	}
	return false;
}
//在有序数组中寻找不小于num的最左位置
int find_left(int* arr, int n, int num) {
	int ans = -1;
	if (arr == nullptr || n == 0)	return -1;
	int l = 0, r = n - 1, m = 0;;
	while (l <= r) {
		m = l + (r - l) >> 1;
		if (arr[m] < num){
			l = m + 1;
		}else {
			ans = m;
			r = m - 1;
		}
	}
	return ans;
}
//二分不一定只局限于有序数组
//寻找峰值 https://leetcode.cn/problems/find-peak-element/description/?envType=problem-list-v2&envId=yD1CVJiS&
/*峰值元素是指其值严格大于左右相邻值的元素。
给你一个整数数组 nums，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回 任何一个峰值 所在位置即可。
你可以假设 nums[-1] = nums[n] = -∞ 。
你必须实现时间复杂度为 O(log n) 的算法来解决此问题。*/
class Solution {
public:
	int findPeakElement(vector<int>& nums) {
		int n = nums.size();
		if (n == 1 || nums[0] > nums[1])	return 0;
		int l = 0, r = n - 1, m = 0;
		while (r > l) {
			m = l + (r - l) / 2;
			if (nums[m] > nums[m + 1])	r = m;
			else	l = m + 1;
		}
		return l;
	}
};