/*�ѣ����ȶ��У�https://www.bilibili.com/video/BV1AF411G7cA?vd_source=f8aeedc23d987bfb0dea78b38581fa28
1���ѱ�����һ����ȫ��������
��ȫ������ֻ�������һ�в�Ϊ���������һ�б����޼���ش�����������
2��������У�ÿ�����ڵ��Ԫ�ر���������ӽڵ��е�Ԫ�أ�
С�����У�ÿ�����ڵ��Ԫ�ر���С���丸�ڵ��е�Ԫ�ء�
3����i���ڵ�ĸ��ڵ㣺��i-1)/2
��i���ڵ�����ӽڵ㣺2i+1	��i���ڵ�����ӽڵ㣺2i+2
*/
//1���Ӷ���׽��� O��N*log N��
//�������������ѵĶ������ٶ���������ϵ���
//2���ӵ��򶥽��� O (N)
//�Ƚ�����ȫ��ѹ����У��ٶ�ÿ�����ڵ�������µ���

//������ https://leetcode.cn/problems/sort-an-array/?envType=problem-list-v2&envId=QiPupvND&
//�ӵ��򶥽���
#include <vector>
#include <algorithm>
class Solution {
private:
    void heapify(vector<int>& arr, int i, int size) {// ��Ԫ�����ˣ�ά���ѵ�����
        int l = 2 * i + 1; // ���ӽڵ�
        while (l < size) {
            // ����ڵ����ҽڵ����ҳ��ϴ���ӽڵ�
            int best = (l + 1 < size && arr[l + 1] > arr[l]) ? l + 1 : l;
            // �ڽϴ���ӽڵ�͸��ڵ����ҳ����Ľڵ�
            best = (arr[best] > arr[i]) ? best : i;
            if (best == i) {
                break; // ������ڵ�����������µ���
            }
            swap(arr[best], arr[i]);// ���򽻻����ڵ�ͽϴ���ӽڵ�
            i = best; // ���µ�ǰ�ڵ�λ��Ϊ�ϴ��ӽڵ�λ��
            l = 2 * i + 1; // �������ӽڵ�λ��
        }
    }
    void heapSort(vector<int>& arr) {// ��������
        int n = arr.size();
        // �Ե����Ͻ����󶥶ѣ��󶥶�������Ϊ����
        for (int i = (n - 1) / 2; i >= 0; i--) {
            heapify(arr, i, n);
        }
        // �����Ԫ���ƶ�������ĩβ����С�ѵķ�Χ������������
        while (n > 1) {
            swap(arr[0], arr[--n]); // �����Ѷ�Ԫ��
            heapify(arr, 0, n); // �����Ѷ�Ԫ�أ�ά���ѵ�����
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