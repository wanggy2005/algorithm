#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
//�鲢���� https://www.luogu.com.cn/problem/P1177 O(n*log n)
/*�������n������С��������������*/
const int MAXN = 100001; // �����������󳤶�
int arr[MAXN]; // ԭ����
int help[MAXN]; // ��������
int n; // ���鳤��
void merge(int l, int m, int r) {// �鲢���������ںϲ������������������
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
void mergesort(int l, int r) {// �鲢���������ݹ�ؽ����黮��Ϊ�����鲢����
	if (l == r)	return;
	int m = l + (r - l) / 2;
	mergesort(l, m);
	mergesort(m + 1, r);
	merge(l, m, r);
}
int main() {
	ios::sync_with_stdio(false); // ����ͬ��������������Ч��
	cin.tie(nullptr); // ���cin��cout�İ�
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

/*�鲢����
1.һ������Ĵ��Ƿ���Լ�Ϊ����+��+����ҡ�
2.���������ʱ���������Ҳ��־������Ƿ��ܲ��������ԣ����������ص㣩
*/
//��һ������С�� https://www.nowcoder.com/questionTerminal/edfe05a1d45c4ea89101d936cac32469
/*��һ�������У�ÿһ������߱ȵ�ǰ��С�����ۼ�������������������С�͡���һ�������С�͡�
����[1, 3, 4, 2, 5]
1��߱�1С������û��
3��߱�3С������1
4��߱�4С������1, 3
2��߱�2С������1
5��߱�5С������1, 3, 4, 2
����С��Ϊ1 + 1 + 3 + 1 + 1 + 3 + 4 + 2 = 16
����һ������s��ʵ�ֺ�������s��С��
*/
const int MAXN = 100001;
int n;
int arr[MAXN];
int help[MAXN];
long long Merge(int l, int m, int r) {// �鲢���������ںϲ�����������������鲢�����ۼӺ�
	long long ans = 0;
	for (int i = l, j = m + 1, sum = 0; j <= r; j++) {// �����ۼӺ�
		while (i <= m && arr[i] <= arr[j]) {
			sum += arr[i++]; // �ۻ���벿��С�ڵ����Ұ벿�ֵ�Ԫ�غ�
		}
		ans += sum; // ���ۻ��ͼӵ����մ���
	}
	int a = l, b = m + 1, i = l;// �鲢����
	while (a <= m && b <= r) {
		help[i++] = arr[a] <= arr[b] ? arr[a++] : arr[b++];
	}
	while (a <= m) {
		help[i++] = arr[a++];
	}
	while (b <= r) {
		help[i++] = arr[b++];
	}
	for (int i = l; i <= r; i++) {// �����������е�Ԫ�ظ��ƻ�ԭ����
		arr[i] = help[i];
	}
	return ans; // �����ۼӺ�
}
long long mergecalculate(int l, int r) {
	if (l == r)	return 0;
	int m = l + (r - l) / 2;
	return mergecalculate(l, m) + mergecalculate(m + 1, r) + Merge(l, m, r);// �ݹ�ؼ������������֣����ϲ����
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

//��������ת�� https://leetcode.cn/problems/reverse-pairs/
/*����һ������ nums ����� i < j �� nums[i] > 2*nums[j] ���Ǿͽ� (i, j) ����һ����Ҫ��ת�ԡ�
����Ҫ���ظ��������е���Ҫ��ת�Ե�������*/
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
//���ڲ��whileѭ���У��ҵ���������nums[i]>2*nums[j]����������Ԫ�أ�����j�����ƶ���
// ��jֹͣ�ƶ�ʱ��˵����j��r������Ԫ�ض�����nums[i]>2*nums[j]����ˣ�����ÿ��i����������������������� j - (m + 1)
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