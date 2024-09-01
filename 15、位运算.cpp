//һ���ж�һ�������ǲ���2���� https://leetcode.cn/problems/power-of-two/
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && n == (n & (-n));//����Brian Kernighan�㷨
    }
};

//�����ж�һ�������ǲ���3���� https://leetcode.cn/problems/power-of-three/
class Solution {
public:
    // ���һ��������3��ĳ���ݣ���ô�����һ��ֻ����3�����������
	// 1162261467��int�ͷ�Χ�ڣ�����3���ݣ�����3��19�η�
	// ���1162261467ֻ����3����������ӣ����nҲ��ֻ����3����������ӣ���ô
	// 1162261467 % n == 0
	// ��֮���1162261467 % n != 0 ˵��nһ��������������
    bool isPowerOfThree(int n) {
        return n > 0 && 1162261467 % n == 0;
    }
};

class Solution {
public:
    bool isPowerOfThree(int n) {
        if (n <= 0) return false;
        while (n % 3 == 0) {
            n /= 3;
        }
        return n == 1;
    }
};

//������֪n�ǷǸ��������ش��ڵ���n����С��2ĳ�η������int��Χ�ڲ�������������������������Сֵ
#include <iostream>
using namespace std;
class Code03_Near2power {
public:
    int near2power(int n) {
        // ��� n С�ڵ��� 0������ 1����Ϊ 2 �� 0 �η��� 1
        if (n <= 0) {return 1;}
        // �� n �� 1���Ա����
        n--;
        // ʹ��λ�������ҵ����ڵ��� n ����С 2 ����
        n |= n >> 1;   // �� n �ĸ� 1 λ��չ���� 1 λ
        n |= n >> 2;   // �������һ����չ
        n |= n >> 4;   // ������չ
        n |= n >> 8;   // ������չ
        n |= n >> 16;  // ������չ��32 λ�����Ĵ���16 λ����չ�� 31 λ��
        // ���ս���� 1���õ����ڵ��� n ����С 2 ����
        return n + 1;
    }
};

//�ġ����ַ�Χ��λ�� https://leetcode.cn/problems/bitwise-and-of-numbers-range/
// ������������ left �� right ����ʾ���� [left, right],���ش��������������� & �Ľ��(���� left ��right �˵�)
class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        while (left < right) {
            right -= right & (-right);
        }
        return right;
    }
};

//�塢��������Ƶ�״̬ https://leetcode.cn/problems/reverse-bits/
//���㷨����031���ر���λ�����ɧ������https://www.bilibili.com/video/BV1ch4y1Q7vd?vd_source=f8aeedc23d987bfb0dea78b38581fa28 ��Ŀ5
#include <iostream>
using namespace std;
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        // �Ƚ������ڵ�λ
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
        // �������ڵ� 2 λ
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
        // �������ڵ� 4 λ
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
        // �������ڵ� 8 λ
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
        // �������ڵ� 16 λ
        n = (n >> 16) | (n << 16);
        return n;
    }
};
/*
0xaaaaaaaa�����룬��ʾ��������ʽ�� 10101010...��������ѡȡ n ������ż��λ�õ�λ�����ҵ��󣩣���Щλ���� 1��
0x55555555�����룬��ʾ��������ʽ�� 01010101...��������ѡȡ n ����������λ�õ�λ����Щλ���� 1��
0xcccccccc�����룬��ʾ��������ʽ�� 11001100...�����ڻ�ȡÿ�ĸ�λ�е�ǰ��������λ��
0x33333333�����룬��ʾ��������ʽ�� 00110011...�����ڻ�ȡÿ�ĸ�λ�еĺ���������λ��
0xf0f0f0f0�����룬��ʾ��������ʽ�� 1111000011110000...�����ڻ�ȡÿ�˸�λ�е�ǰ�ĸ�λ��
0x0f0f0f0f�����룬��ʾ��������ʽ�� 0000111100001111...�����ڻ�ȡÿ�˸�λ�еĺ��ĸ�λ��
0xff00ff00�����룬��ʾ��������ʽ�� 11111111000000001111111100000000�����ڻ�ȡÿ 16 λ�е�ǰ��λ��
0x00ff00ff�����룬��ʾ��������ʽ�� 00000000111111110000000011111111�����ڻ�ȡÿ 16 λ�еĺ��λ��
n >> 16���� n ���� 16 λ�������� 16 λ�ı���λ���Ƶ��� 16 λ��λ�á�
n << 16���� n ���� 16 λ�������� 16 λ�ı���λ���Ƶ��� 16 λ��λ�á�
*/

//��������n�Ķ��������м���1 https://leetcode.cn/problems/hamming-distance/
// ��������֮��ġ��������롱ָ�������������ֶ�Ӧ������λ��ͬ��λ�õ���Ŀ�������������� x �� y�����㲢��������֮��ĺ�������
#include <iostream>
using namespace std;
class Solution {
public:
    int hammingDistance(int x, int y) {
        return cntOnes(x ^ y);
    }
    int cntOnes(int n) {
        // ����ÿ�����ڵ�λ������ÿ��λ�е� 1 �ĸ���
        n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
        // ����ÿ 4 λ�е�ÿ��λ������ÿ��λ�е� 1 �ĸ���
        n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
        // ����ÿ 8 λ�е�ÿ 4 λ������ÿ 4 λ�е� 1 �ĸ���
        n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
        // ����ÿ 16 λ�е�ÿ 8 λ������ÿ 8 λ�е� 1 �ĸ���
        n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff00ff);
        // ����ÿ 32 λ�е�ÿ 16 λ������ÿ 16 λ�е� 1 �ĸ���
        n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
        // ���ض����Ʊ�ʾ�� 1 ������
        return n;
    }
};
/*
0x55555555����������ʽΪ 01010101 01010101 01010101 01010101��
�������ѡ����ÿ�����ڵı���λ�еĵ�λ���֣�����λ����
0x33333333����������ʽΪ 00110011 00110011 00110011 00110011��
�������ѡ����ÿ 4 λ�е�ǰ��λ���֣��� 2 λ����
0x0f0f0f0f����������ʽΪ 00001111 00001111 00001111 00001111��
�������ѡ����ÿ 8 λ�е�ǰ 4 λ���֣��� 4 λ����
0x00ff00ff����������ʽΪ 00000000 11111111 00000000 11111111��
�������ѡ����ÿ 16 λ�е�ǰ 8 λ���֣��� 8 λ����
0x0000ffff����������ʽΪ 00000000 00000000 11111111 11111111��
�������ѡ����ÿ 32 λ�е�ǰ 16 λ���֣��� 16 λ����
*/


//λ����ʵ�ּӼ��˳��������в��ܳ������������ 
//һ��λ����ʵ�ּӷ�������ÿһλ�޽�λ��ӵĽ��+��λ�Ľ�����ϼ��㣬ֱ����λ��ʧ
int add(int a, int b) {
    int ans = a;
    while (b != 0) {
        // ans : a��b�޽�λ��ӵĽ��
        ans = a ^ b;
        // b : a��b���ʱ�Ľ�λ��Ϣ
        b = (a & b) << 1;
        a = ans;
    }
    return ans;
}
//����λ����ʵ�ּ��������üӷ���һ������x�෴�������䲹�� (~x)+1
int neg(int n) {
    return add(~n, 1);
}
int minus(int a, int b) {
    return add(a, neg(b));
}
//����λ����ʵ�ֳ˷���ģ����ʽ�˷��Ĺ���
int multiply(int a, int b) {
    int ans = 0;
    while (b != 0) {
        if ((b & 1) != 0) {
            // ���b��ǰ�����λΪ1������a
            ans = add(ans, a);
        }
        a <<= 1;
        b >>= 1;
    }
    return ans;
}
//�ġ�λ����ʵ�ֳ���  https://leetcode.cn/problems/divide-two-integers/
#include <climits>
#include <iostream>
const int MIN = INT_MIN;
// ���뱣֤a��b������������Сֵ����Ϊת���෴��ʱ�������
int div(int a, int b) {
    int x = a < 0 ? neg(a) : a;
    int y = b < 0 ? neg(b) : b;
    int ans = 0;
    for (int i = 30; i >= 0; i = minus(i, 1)) {
        // ��� (x >> i) �Ƿ���ڵ��� y
        if ((x >> i) >= y) {
            ans |= (1 << i); // �ڽ���ĵ� i λ���� 1
            x = minus(x, y << i); // ��ȥ y << i��������һ��λ�ļ��
        }
    }
    return (a < 0) ^ (b < 0) ? neg(ans) : ans;// ��� a �� b ��ţ����Ϊ����
}
int divide(int a, int b) {
    if (a == MIN && b == MIN) {// a �� b ������Сֵ�����Ϊ 1
        return 1;
    }
    if (a != MIN && b != MIN) {// a �� b ��������Сֵ����������
        return div(a, b);
    }
    if (b == MIN) {// a ������Сֵ��b ����Сֵ�����Ϊ 0
        return 0;
    }
    if (b == neg(1)) {// a ����Сֵ��b �� -1��������ĿҪ�󷵻����ֵ
        return INT_MAX;
    }
    // a ����Сֵ��b ������Сֵ�Ҳ��� -1
    // �������㣨a+b��/ b�����b<0,����㣨a-b��/ b�����𰸼Ӽ�һ����
    a = add(a, b > 0 ? b : neg(b));
    int ans = div(a, b);
    int offset = b > 0 ? neg(1) : 1;
    return add(ans, offset);
}