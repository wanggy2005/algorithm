/*�����������
1������������û�н�λ�Ķ����Ƽӷ�
2������������㽻���ɺͽ���ɡ�Ҳ����ͬһ�����֣��������˳����ʲô�����յĽ������һ��
3��0 ^ n = n��n ^ n = 0
4���������������x��������ĳ�����ֵ����������y����ôʣ�²��ֵ�������x ^ y
���е�4����ص���Ŀ��࣬�������������͵�����
Nim����Ҳ�Ǻ����������ص��㷨*/

#include<iostream>
using namespace std;
//һ������������
// ��i!=j��û���⣬����ɽ�������
// ��i==j�������
// ����֪������д�����ɣ������Ƽ�
void swap(int arr[], int i, int j) {
    arr[i] = arr[i] ^ arr[j];
    arr[j] = arr[i] ^ arr[j];
    arr[i] = arr[i] ^ arr[j];
}
int main() {
    int a = -2323;
    int b = 10;
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    cout << a << endl;
    cout << b << endl;
    
    int arr[] = { 3, 5 };
    swap(arr, 0, 1);
    cout << arr[0] << endl;
    cout << arr[1] << endl;
    swap(arr, 0, 0);  // �����������Ч�ģ��ᵼ�´���
    cout << arr[0] << endl;
    return 0;
}

//���������κ��ж����ͱȽϲ��������������������ֵ����� https://www.nowcoder.com/practice/d2707eaf98124f1e8f1d9c18ad487f76
#include <iostream>
#include <climits>
// ���뱣֤nһ����0����1
int flip(int n) { // 0��1��1��0
    return n ^ 1;
}
int sign(int n) { // �Ǹ�������1, ��������0
    return flip(n >> 31 & 1);
}
// ��������յ�ʵ��
int getMax1(int a, int b) {
    int c = a - b;//c�������
    // c�Ǹ���returnA -> 1
    // c�Ǹ���returnB -> 0
    // c������returnA -> 0
    // c������returnB -> 1
    int returnA = sign(c);
    int returnB = flip(returnA);
    return a * returnA + b * returnB;
}

// û���κ������ʵ��
//���ַ����ĺ������ڱ�����ֱ�ӵļ�������(ʵ�ʲ�ֵ c ��ʹ��)������ͨ�����ŵ��ж������������ĸ�ֵ������������ڴ�����С�������µ�������⡣
int getMax2(int a, int b) {
    int c = a - b;
    int sa = sign(a);// a�ķ���
    int sb = sign(b);// b�ķ���
    int sc = sign(c);// c�ķ���
    // �ж�A��B�������ǲ��ǲ�һ���������һ��diffAB=1�����һ��diffAB=0
    int diffAB = sa ^ sb;
    // �ж�A��B�������ǲ���һ�������һ��sameA B=1�������һ��sameAB=0
    int sameAB = flip(diffAB);
    int returnA = diffAB * sa + sameAB * sc;
    //return a��������
    //1.a��b���Ų�һ������ʱc��ֵ�����������a�ǷǸ���  2.a��b����һ������ʱc��ֵ�������������cΪ�Ǹ���
    int returnB = flip(returnA);
    return a * returnA + b * returnB;
}
int main() {
    int a = INT_MIN;
    int b = INT_MAX;
    // getMax1�����������Ϊ���
    cout << getMax1(a, b) << endl;
    // getMax2������Զ��ȷ
    cout << getMax2(a, b) << endl;
    return 0;
}

//�����ҵ�ȱʧ������ https://leetcode.cn/problems/missing-number/
#include <iostream>
#include <vector>
class MissingNumber {
public:
    int missingNumber(vector<int>& nums) {
        int xorAll = 0, xorHas = 0;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            xorAll ^= i;
            xorHas ^= nums[i];
        }
        xorAll ^= n;
        return xorAll ^ xorHas;
    }
};

//�ġ������������ε��� https://leetcode.cn/problems/single-number/
//����һ�� �ǿ� �������� nums ������ĳ��Ԫ��ֻ����һ�����⣬����ÿ��Ԫ�ؾ��������Ρ��ҳ��Ǹ�ֻ������һ�ε�Ԫ�ء�
//�������Ʋ�ʵ������ʱ�临�Ӷȵ��㷨����������⣬�Ҹ��㷨ֻʹ�ó�������ռ䡣
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int xorNUM = 0;
        for (int num:nums) {
            xorNUM ^= num;
        }
        return xorNUM;
    }
};

//�塢Brian Kernighan�㷨 - ��ȡ��ĳ��������״̬�����Ҳ��1
//���������䲹�� �� ������&     n = n & (-n)
//���⣺ֻ����һ�ε����� III https://leetcode.cn/problems/single-number-iii/
// ��������2���������������Σ�����������������ż����,������2�ֳ����������ε���
#include <vector>
#include <limits>
using namespace std;
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int eor1 = 0;
        for (int num : nums) {
            eor1 ^= num;
        }
        // eor1 : a ^ b
        // ֱ�ӽ� eor1 ת��Ϊ�޷�������
        unsigned int rightOne = eor1 & static_cast<unsigned int>(eor1 == numeric_limits<int>::min() ? eor1 : -eor1);
        int eor2 = 0;
        for (int num : nums) {
            if ((num & rightOne) == 0) {
                eor2 ^= num;
            }
        }
        return { eor2, eor1 ^ eor2 };
    }
};
/*�ڼ��� rightOne ʱ����� eor1 ���� INT_MIN���� - 2147483648��������ʹ�� eor1 ������Ϊ�޷�����������ʽ���������ǽ� eor1 ȡ����ת��Ϊ�޷���������
eor1 == numeric_limits<int>::min() ��� eor1 �Ƿ�Ϊ INT_MIN��numeric_limits<int>::min() �� C++ �ж�������ڻ�ȡ int ������Сֵ�ĺ�����
ͨ����� eor1 �Ƿ�Ϊ��Сֵ�����Ǳ����˶� INT_MIN ȡ�����Ĳ������Ӷ�����������ʱ����
���ָĶ�ȷ���� rightOne �ļ�������������¶�����ȷ���У������Ǳ����� INT_MIN ���������������һ�ֱ��⸺������ķ�����*/

//����ֻ����һ�ε����� II https://leetcode.cn/problems/single-number-ii/
// ������ֻ��1�������ִ�������m�Σ���������������m�Σ����س��ִ���С��m�ε�������
#include <vector>
using namespace std;
#include <vector>
using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        return find(nums, 3); 
    }
    int find(vector<int>& arr, int m) {
        vector<int> cnts(32, 0); // cnts[i] : i λ���ж��ٸ� 1
        // ͳ��ÿһλ�� 1 �ĳ��ִ���
        for (int num : arr) {
            for (int i = 0; i < 32; ++i) {
                cnts[i] += (num >> i) & 1;
            }
        }
        int ans = 0; 
        // ����ÿһλ�� 1 �ĳ��ִ���ȷ�����
        for (int i = 0; i < 32; i++) {
            // �����ǰλ�� 1 �ĳ��ִ������ܱ� m ������˵�����λ���ڳ��ִ������� m �ε��Ǹ���
            if (cnts[i] % m != 0) {
                ans |= (1 << i); // ���½�������ö�Ӧλ��ֵΪ 1
            }
        }
        return ans; 
    }
};