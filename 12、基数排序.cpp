#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
/*�������򣺲����ڱȽϵ�����  https://leetcode.cn/problems/sort-an-array/
�ͱȽ��޹ص����򣬶��ڶ��������������Ҫ�󣬲���ͨ��
���������ʵ��ϸ��
�ؼ��㣺ǰ׺���������ļ��ɡ�������ȡĳһλ�ļ���
ʱ�临�Ӷ�O(n)������ռ临�Ӷ�O(m)����Ҫ�����ռ�������Ͱ�����ã�����ͣ��װ�롢��������

һ����������������Ҫ��������10���ƵķǸ�����
������Ǿ���Ҫת��������������ת�������Ҵ�������������κν�������������
һ���ȽϵĶ������ǳ������֣���ô��д���۵��������Զ��׼��ģ����Բ����ڱȽϵ����򲢲�ͨ��
*/
class Solution {
private:
    int BASE = 10; // ��������Ļ�����Ĭ����10����
    int MAXN = 50001; 
    int* help = new int[MAXN]; // �������飬������������д������
    int* cnts = new int[BASE]; // �������飬���ڼ�¼ÿ������λ���ϵ����ֳ��ִ���
    // ����һ��������ָ�������µ�λ��
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
            // ���ü�������
            memset(cnts, 0, BASE * sizeof(int));
            // ͳ��ÿ������λ���ϵ����ֳ��ִ���
            for (int i = 0; i < n; i++) {
                cnts[(nums[i] / offset) % BASE]++;
            }
            // ����������ת��Ϊǰ׺�����飬���㶨λÿ�������ڸ��������е�λ��
            for (int i = 1; i < BASE; i++) {
                cnts[i] = cnts[i] + cnts[i - 1];
            }
            // �Ӻ���ǰ����ԭ���飬�����ַ��õ����������е���ȷλ��
            for (int i = n - 1; i >= 0; i--) {
                help[--cnts[(nums[i] / offset) % BASE]] = nums[i];
            }
            // �����������е����ݸ��ƻ�ԭ����
            for (int i = 0; i < n; i++) {
                nums[i] = help[i];
            }
        }
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        int n = nums.size();
        int min = *min_element(nums.begin(), nums.end());// �ҵ������е���Сֵ
        // �������е�ÿ��Ԫ�ض���ȥ��Сֵ��ת��Ϊ�Ǹ�����
        for (int i = 0; i < n; i++) {
            nums[i] -= min;
        }
        int max = *max_element(nums.begin(), nums.end());// �ҵ������е����ֵ
        // �������ֵ��λ���������������������
        radixSort(nums, n, bits(max));
        // �������е�ÿ��Ԫ�ض��ӻ���Сֵ���ָ�ԭ����ֵ
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
