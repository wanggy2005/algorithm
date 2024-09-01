#include<algorithm>
using namespace std;
//һ�������Լ������С����������շת�����	ʱ�临�Ӷ�ΪO(log a)�����η�
long gcd(long a, long b) {//�����Լ��
	return b == 0 ? a : gcd(b, a % b);
}
long lcm(long a, long b) {//����С������
	return (long)a / gcd(a, b) * b;
}

//������ N ���������� https://leetcode.cn/problems/nth-magical-number/
//һ������������ܱ� a �� b ��������ô��������ġ� ������������ n , a , b �����ص� n ����������֡�
// ��Ϊ�𰸿��ܴܺ����Է��ش� �� 10^9 + 7 ȡģ ���ֵ��
//���ö��ִ𰸷����ݳ�ԭ��
long gcd(long a, long b) {
    return b == 0 ? a : gcd(b, a % b);
}
long lcm(long a, long b) {
    return (a / gcd(a, b)) * b;
}
int nthMagicalNumber(int n, int a, int b) {
    long lcm_ab = lcm(a, b);
    long ans = 0;
    // ���ֲ��ҷ�Χ
    long l = min(a,b), r = (long)n * min(a, b), m = 0;
    while (l <= r) {
        m = (l + r) / 2;
        if (m / a + m / b - m / lcm_ab >= n) {//�ݳ�ԭ��
            ans = m;
            r = m - 1;
        }else {
            l = m + 1;
        }
    }
    return static_cast<int>(ans % 1000000007);
}

//����ͬ��ԭ��        �ܿ��м���������ͳ���ʱ������ĳ�ʱ
//����һ��������m�������������a��b����a - b�ܹ���m��������(a - b) / m�õ�һ����������ô�ͳ�����a��b��ģmͬ�࣬����a��b(mod m)��
/*
1.�ӷ���ͬ�ࣺ
�����м���֮�� % m == �����м��� % m ��������õĺ�
2.�˷���ͬ�ࣺ
�����м���֮�� % m == �����м��� % m ��������õĻ�
3.������ͬ�ࣺ
�����м���֮�� % m == �������м��� % m �ټ���m��% m     ����m��ֹ���ָ���*/