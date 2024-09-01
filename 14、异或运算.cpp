/*异或运算性质
1）异或运算就是没有进位的二进制加法
2）异或运算满足交换律和结合律。也就是同一批数字，不管异或顺序是什么，最终的结果都是一个
3）0 ^ n = n，n ^ n = 0
4）整体异或和如果是x，整体中某个部分的异或和如果是y，那么剩下部分的异或和是x ^ y
其中第4）相关的题目最多，利用区间上异或和的性质
Nim博弈也是和异或运算相关的算法*/

#include<iostream>
using namespace std;
//一、交换两个数
// 当i!=j，没问题，会完成交换功能
// 当i==j，会出错
// 所以知道这种写法即可，并不推荐
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
    swap(arr, 0, 0);  // 这个操作是无效的，会导致错误
    cout << arr[0] << endl;
    return 0;
}

//二、不用任何判断语句和比较操作，返回两个数的最大值（作差） https://www.nowcoder.com/practice/d2707eaf98124f1e8f1d9c18ad487f76
#include <iostream>
#include <climits>
// 必须保证n一定是0或者1
int flip(int n) { // 0变1，1变0
    return n ^ 1;
}
int sign(int n) { // 非负数返回1, 负数返回0
    return flip(n >> 31 & 1);
}
// 有溢出风险的实现
int getMax1(int a, int b) {
    int c = a - b;//c可能溢出
    // c非负，returnA -> 1
    // c非负，returnB -> 0
    // c负数，returnA -> 0
    // c负数，returnB -> 1
    int returnA = sign(c);
    int returnB = flip(returnA);
    return a * returnA + b * returnB;
}

// 没有任何问题的实现
//这种方法的核心在于避免了直接的减法运算(实际差值 c 的使用)，而是通过符号的判断来决定返回哪个值。不会出现由于大数减小数而导致的溢出问题。
int getMax2(int a, int b) {
    int c = a - b;
    int sa = sign(a);// a的符号
    int sb = sign(b);// b的符号
    int sc = sign(c);// c的符号
    // 判断A和B，符号是不是不一样，如果不一样diffAB=1，如果一样diffAB=0
    int diffAB = sa ^ sb;
    // 判断A和B，符号是不是一样，如果一样sameA B=1，如果不一样sameAB=0
    int sameAB = flip(diffAB);
    int returnA = diffAB * sa + sameAB * sc;
    //return a的条件：
    //1.a、b符号不一样（此时c的值可能溢出）且a是非负的  2.a、b符号一样（此时c的值不可能溢出）且c为非负的
    int returnB = flip(returnA);
    return a * returnA + b * returnB;
}
int main() {
    int a = INT_MIN;
    int b = INT_MAX;
    // getMax1方法会错误，因为溢出
    cout << getMax1(a, b) << endl;
    // getMax2方法永远正确
    cout << getMax2(a, b) << endl;
    return 0;
}

//三、找到缺失的数字 https://leetcode.cn/problems/missing-number/
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

//四、出现了奇数次的数 https://leetcode.cn/problems/single-number/
//给你一个 非空 整数数组 nums ，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
//你必须设计并实现线性时间复杂度的算法来解决此问题，且该算法只使用常量额外空间。
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

//五、Brian Kernighan算法 - 提取出某数二进制状态中最右侧的1
//将该数与其补码 做 与运算&     n = n & (-n)
//例题：只出现一次的数字 III https://leetcode.cn/problems/single-number-iii/
// 数组中有2种数出现了奇数次，其他的数都出现了偶数次,返回这2种出现了奇数次的数
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
        // 直接将 eor1 转换为无符号整数
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
/*在计算 rightOne 时，如果 eor1 等于 INT_MIN（即 - 2147483648），我们使用 eor1 本身作为无符号整数的形式。否则，我们将 eor1 取负并转换为无符号整数。
eor1 == numeric_limits<int>::min() 检查 eor1 是否为 INT_MIN。numeric_limits<int>::min() 是 C++ 中定义的用于获取 int 类型最小值的函数。
通过检查 eor1 是否为最小值，我们避免了对 INT_MIN 取负数的操作，从而避免了运行时错误。
这种改动确保了 rightOne 的计算在所有情况下都能正确进行，尤其是避免了 INT_MIN 的特殊情况。这是一种避免负数溢出的方法。*/

//六、只出现一次的数字 II https://leetcode.cn/problems/single-number-ii/
// 数组中只有1种数出现次数少于m次，其他数都出现了m次，返回出现次数小于m次的那种数
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
        vector<int> cnts(32, 0); // cnts[i] : i 位上有多少个 1
        // 统计每一位上 1 的出现次数
        for (int num : arr) {
            for (int i = 0; i < 32; ++i) {
                cnts[i] += (num >> i) & 1;
            }
        }
        int ans = 0; 
        // 根据每一位的 1 的出现次数确定结果
        for (int i = 0; i < 32; i++) {
            // 如果当前位上 1 的出现次数不能被 m 整除，说明这个位属于出现次数少于 m 次的那个数
            if (cnts[i] % m != 0) {
                ans |= (1 << i); // 更新结果，设置对应位的值为 1
            }
        }
        return ans; 
    }
};