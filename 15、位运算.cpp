//一、判断一个整数是不是2的幂 https://leetcode.cn/problems/power-of-two/
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && n == (n & (-n));//利用Brian Kernighan算法
    }
};

//二、判断一个整数是不是3的幂 https://leetcode.cn/problems/power-of-three/
class Solution {
public:
    // 如果一个数字是3的某次幂，那么这个数一定只含有3这个质数因子
	// 1162261467是int型范围内，最大的3的幂，它是3的19次方
	// 这个1162261467只含有3这个质数因子，如果n也是只含有3这个质数因子，那么
	// 1162261467 % n == 0
	// 反之如果1162261467 % n != 0 说明n一定含有其他因子
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

//三、已知n是非负数，返回大于等于n的最小的2某次方，如果int范围内不存在这样的数，返回整数最小值
#include <iostream>
using namespace std;
class Code03_Near2power {
public:
    int near2power(int n) {
        // 如果 n 小于等于 0，返回 1，因为 2 的 0 次方是 1
        if (n <= 0) {return 1;}
        // 将 n 减 1，以便计算
        n--;
        // 使用位操作来找到大于等于 n 的最小 2 的幂
        n |= n >> 1;   // 将 n 的高 1 位扩展到低 1 位
        n |= n >> 2;   // 将结果进一步扩展
        n |= n >> 4;   // 继续扩展
        n |= n >> 8;   // 继续扩展
        n |= n >> 16;  // 继续扩展（32 位整数的处理，16 位后扩展到 31 位）
        // 最终结果加 1，得到大于等于 n 的最小 2 的幂
        return n + 1;
    }
};

//四、数字范围按位与 https://leetcode.cn/problems/bitwise-and-of-numbers-range/
// 给你两个整数 left 和 right ，表示区间 [left, right],返回此区间内所有数字 & 的结果(包含 left 、right 端点)
class Solution {
public:
    int rangeBitwiseAnd(int left, int right) {
        while (left < right) {
            right -= right & (-right);
        }
        return right;
    }
};

//五、逆序二进制的状态 https://leetcode.cn/problems/reverse-bits/
//【算法讲解031【必备】位运算的骚操作】https://www.bilibili.com/video/BV1ch4y1Q7vd?vd_source=f8aeedc23d987bfb0dea78b38581fa28 题目5
#include <iostream>
using namespace std;
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        // 先交换相邻的位
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
        // 交换相邻的 2 位
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
        // 交换相邻的 4 位
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
        // 交换相邻的 8 位
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
        // 交换相邻的 16 位
        n = (n >> 16) | (n << 16);
        return n;
    }
};
/*
0xaaaaaaaa：掩码，表示二进制形式的 10101010...。它用来选取 n 的所有偶数位置的位（从右到左），这些位都是 1。
0x55555555：掩码，表示二进制形式的 01010101...。它用来选取 n 的所有奇数位置的位，这些位都是 1。
0xcccccccc：掩码，表示二进制形式的 11001100...，用于获取每四个位中的前两个比特位。
0x33333333：掩码，表示二进制形式的 00110011...，用于获取每四个位中的后两个比特位。
0xf0f0f0f0：掩码，表示二进制形式的 1111000011110000...，用于获取每八个位中的前四个位。
0x0f0f0f0f：掩码，表示二进制形式的 0000111100001111...，用于获取每八个位中的后四个位。
0xff00ff00：掩码，表示二进制形式的 11111111000000001111111100000000，用于获取每 16 位中的前八位。
0x00ff00ff：掩码，表示二进制形式的 00000000111111110000000011111111，用于获取每 16 位中的后八位。
n >> 16：将 n 右移 16 位，这样高 16 位的比特位将移到低 16 位的位置。
n << 16：将 n 左移 16 位，这样低 16 位的比特位将移到高 16 位的位置。
*/

//六、返回n的二进制中有几个1 https://leetcode.cn/problems/hamming-distance/
// 两个整数之间的“汉明距离”指的是这两个数字对应二进制位不同的位置的数目。给你两个整数 x 和 y，计算并返回它们之间的汉明距离
#include <iostream>
using namespace std;
class Solution {
public:
    int hammingDistance(int x, int y) {
        return cntOnes(x ^ y);
    }
    int cntOnes(int n) {
        // 处理每对相邻的位，计算每对位中的 1 的个数
        n = (n & 0x55555555) + ((n >> 1) & 0x55555555);
        // 处理每 4 位中的每对位，计算每对位中的 1 的个数
        n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
        // 处理每 8 位中的每 4 位，计算每 4 位中的 1 的个数
        n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
        // 处理每 16 位中的每 8 位，计算每 8 位中的 1 的个数
        n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff00ff);
        // 处理每 32 位中的每 16 位，计算每 16 位中的 1 的个数
        n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
        // 返回二进制表示中 1 的总数
        return n;
    }
};
/*
0x55555555：二进制形式为 01010101 01010101 01010101 01010101。
这个掩码选择了每对相邻的比特位中的低位部分（奇数位）。
0x33333333：二进制形式为 00110011 00110011 00110011 00110011。
这个掩码选择了每 4 位中的前两位部分（低 2 位）。
0x0f0f0f0f：二进制形式为 00001111 00001111 00001111 00001111。
这个掩码选择了每 8 位中的前 4 位部分（低 4 位）。
0x00ff00ff：二进制形式为 00000000 11111111 00000000 11111111。
这个掩码选择了每 16 位中的前 8 位部分（低 8 位）。
0x0000ffff：二进制形式为 00000000 00000000 11111111 11111111。
这个掩码选择了每 32 位中的前 16 位部分（低 16 位）。
*/


//位运算实现加减乘除，过程中不能出现算术运算符 
//一、位运算实现加法：利用每一位无进位相加的结果+进位的结果不断计算，直到进位消失
int add(int a, int b) {
    int ans = a;
    while (b != 0) {
        // ans : a和b无进位相加的结果
        ans = a ^ b;
        // b : a和b相加时的进位信息
        b = (a & b) << 1;
        a = ans;
    }
    return ans;
}
//二、位运算实现减法：利用加法，一个数字x相反数就是其补码 (~x)+1
int neg(int n) {
    return add(~n, 1);
}
int minus(int a, int b) {
    return add(a, neg(b));
}
//三、位运算实现乘法：模拟竖式乘法的过程
int multiply(int a, int b) {
    int ans = 0;
    while (b != 0) {
        if ((b & 1) != 0) {
            // 如果b当前的最低位为1，加上a
            ans = add(ans, a);
        }
        a <<= 1;
        b >>= 1;
    }
    return ans;
}
//四、位运算实现除法  https://leetcode.cn/problems/divide-two-integers/
#include <climits>
#include <iostream>
const int MIN = INT_MIN;
// 必须保证a和b都不是整数最小值（因为转成相反数时会溢出）
int div(int a, int b) {
    int x = a < 0 ? neg(a) : a;
    int y = b < 0 ? neg(b) : b;
    int ans = 0;
    for (int i = 30; i >= 0; i = minus(i, 1)) {
        // 检查 (x >> i) 是否大于等于 y
        if ((x >> i) >= y) {
            ans |= (1 << i); // 在结果的第 i 位设置 1
            x = minus(x, y << i); // 减去 y << i，继续下一个位的检查
        }
    }
    return (a < 0) ^ (b < 0) ? neg(ans) : ans;// 如果 a 和 b 异号，结果为负数
}
int divide(int a, int b) {
    if (a == MIN && b == MIN) {// a 和 b 都是最小值，结果为 1
        return 1;
    }
    if (a != MIN && b != MIN) {// a 和 b 都不是最小值，正常除法
        return div(a, b);
    }
    if (b == MIN) {// a 不是最小值，b 是最小值，结果为 0
        return 0;
    }
    if (b == neg(1)) {// a 是最小值，b 是 -1，根据题目要求返回最大值
        return INT_MAX;
    }
    // a 是最小值，b 不是最小值且不是 -1
    // 处理：计算（a+b）/ b，如果b<0,则计算（a-b）/ b。最后答案加减一即可
    a = add(a, b > 0 ? b : neg(b));
    int ans = div(a, b);
    int offset = b > 0 ? neg(1) : 1;
    return add(ans, offset);
}