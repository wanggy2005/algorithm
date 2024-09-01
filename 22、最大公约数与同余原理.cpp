#include<algorithm>
using namespace std;
//一、求最大公约数、最小公倍数——辗转相除法	时间复杂度为O(log a)的三次方
long gcd(long a, long b) {//求最大公约数
	return b == 0 ? a : gcd(b, a % b);
}
long lcm(long a, long b) {//求最小公倍数
	return (long)a / gcd(a, b) * b;
}

//例：第 N 个神奇数字 https://leetcode.cn/problems/nth-magical-number/
//一个正整数如果能被 a 或 b 整除，那么它是神奇的。 给定三个整数 n , a , b ，返回第 n 个神奇的数字。
// 因为答案可能很大，所以返回答案 对 10^9 + 7 取模 后的值。
//利用二分答案法和容斥原理
long gcd(long a, long b) {
    return b == 0 ? a : gcd(b, a % b);
}
long lcm(long a, long b) {
    return (a / gcd(a, b)) * b;
}
int nthMagicalNumber(int n, int a, int b) {
    long lcm_ab = lcm(a, b);
    long ans = 0;
    // 二分查找范围
    long l = min(a,b), r = (long)n * min(a, b), m = 0;
    while (l <= r) {
        m = (l + r) / 2;
        if (m / a + m / b - m / lcm_ab >= n) {//容斥原理
            ans = m;
            r = m - 1;
        }else {
            l = m + 1;
        }
    }
    return static_cast<int>(ans % 1000000007);
}

//二、同余原理        避开中间结果的溢出和常数时间运算的超时
//给定一个正整数m，如果两个整数a和b满足a - b能够被m整除，即(a - b) / m得到一个整数，那么就称整数a与b对模m同余，记作a≡b(mod m)。
/*
1.加法的同余：
所有中间结果之和 % m == 各个中间结果 % m 再相加所得的和
2.乘法的同余：
所有中间结果之积 % m == 各个中间结果 % m 再相乘所得的积
3.减法的同余：
所有中间结果之差 % m == （各个中间结果 % m 再加上m）% m     加上m防止出现负数*/