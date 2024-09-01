#include<vector>
using namespace std;
//ʱ�临�Ӷ�ΪlogN
//��������������ĳ��ֵ�Ƿ����
bool exist_num(int* arr, int n, int num) {
	if (arr == nullptr || n == 0)	return false;
	int l = 0;//���
	int r = n - 1;//�Ҷ�
	int m = 0;
	while (l <= r) {
		m = l + (r - l) >> 1;
		if (arr[m] > num)	r = m - 1;
		if (arr[m] < num)	l = m + 1;
		else	return true;
	}
	return false;
}
//������������Ѱ�Ҳ�С��num������λ��
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
//���ֲ�һ��ֻ��������������
//Ѱ�ҷ�ֵ https://leetcode.cn/problems/find-peak-element/description/?envType=problem-list-v2&envId=yD1CVJiS&
/*��ֵԪ����ָ��ֵ�ϸ������������ֵ��Ԫ�ء�
����һ���������� nums���ҵ���ֵԪ�ز�������������������ܰ��������ֵ������������£����� �κ�һ����ֵ ����λ�ü��ɡ�
����Լ��� nums[-1] = nums[n] = -�� ��
�����ʵ��ʱ�临�Ӷ�Ϊ O(log n) ���㷨����������⡣*/
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