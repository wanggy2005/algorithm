//位图 https://www.bilibili.com/video/BV1yr4y1Z7jb?vd_source=f8aeedc23d987bfb0dea78b38581fa28
//其实就是用bit组成的数组来存放值，用bit状态1、0代表存在、不存在，取值和存值操作都用位运算
//限制是必须为连续范围且不能过大。好处是极大的节省空间，因为1个数字只占用1个bit的空间。
//set数组的第几个数字：num/32	该数字的第几个bit：num%32

/*位图的实现
Bitset(int n)：初始化位图的大小，只支持0~n - 1所有数字的增删改查
void add(int num)：把num加入到位图
void remove(int num)：把num从位图中删除
void reverse(int num)：如果位图里没有num，就加入；如果位图里有num，就删除
boolean contains(int num)：查询num是否在位图中
*/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
using namespace std;
class Bitset {
public:
    vector<int> set;
    Bitset(int n) {
        set.resize((n + 31) / 32);// 位图的大小为 (n + 31) / 32，确保能容纳n个bit
    }
    void add(int num) {// 添加操作，将数字num添加到集合中
        set[num / 32] |= 1 << (num % 32);// 利用 | 将第num个bit位置为1
    }
    void remove(int num) {// 删除操作，将数字num从集合中移除
        set[num / 32] &= ~(1 << (num % 32));// 将第num个bit位置为0
    }
    void reverse(int num) {// 反转操作，反转数字num的存在状态
        set[num / 32] ^= 1 << (num % 32);// 将第num个bit取反
    }
    bool contains(int num) {// 包含检查，检查数字num是否存在于集合中
        // 检查第num个bit是否为1，如果是则返回true，否则返回false
        return set[num / 32] >> (num % 32);
    }
};
//利用对数器验证
int main() {
    int n = 1000;
    int testTimes = 10000;
    cout << "测试开始" << endl;
    Bitset bitSet(n);
    unordered_set<int> hashSet;//直接用HashSet做对比测试
    cout << "调用阶段开始" << endl;
    srand(time(0)); // 使用当前时间作为随机种子
    for (int i = 0; i < testTimes; i++) {
        double decide = (double)rand() / RAND_MAX;
        int number = rand() % n;//0~n-1间的随机数
        //等概率地调用各种操作
        if (decide < 0.333) {
            bitSet.add(number);
            hashSet.insert(number);
        }
        else if (decide < 0.666) {
            bitSet.remove(number);
            hashSet.erase(number);
        }
        else {
            bitSet.reverse(number);
            if (hashSet.find(number) != hashSet.end()) {
                hashSet.erase(number);
            }
            else {
                hashSet.insert(number);
            }
        }
    }
    cout << "调用阶段结束" << endl;
    cout << "验证阶段开始" << endl;
    for (int i = 0; i < n; ++i) {
        if (bitSet.contains(i) != (hashSet.find(i) != hashSet.end())) {
            cout << "出错了!" << endl;
        }
    }
    cout << "验证阶段结束" << endl;
    cout << "测试结束" << endl;
    return 0;
}

/*在线测试 https://leetcode-cn.com/problems/design-bitset/
Bitset(int size) 用 size 个位初始化 Bitset ，所有位都是 0 。
void fix(int idx) 将下标为 idx 的位上的值更新为 1 。如果值已经是 1 ，则不会发生任何改变。
void unfix(int idx) 将下标为 idx 的位上的值更新为 0 。如果值已经是 0 ，则不会发生任何改变。
void flip() 翻转 Bitset 中每一位上的值。换句话说，所有值为 0 的位将会变成 1 ，反之亦然。
boolean all() 检查 Bitset 中 每一位 的值是否都是 1 。如果满足此条件，返回 true ；否则，返回 false 。
boolean one() 检查 Bitset 中 是否 至少一位 的值是 1 。如果满足此条件，返回 true ；否则，返回 false 。
int count() 返回 Bitset 中值为 1 的位的 总数 。
String toString() 返回 Bitset 的当前组成情况。注意，在结果字符串中，第 i 个下标处的字符应该与 Bitset 中的第 i 位一致。
*/
#include <vector>
#include <string>
#include <sstream>
using namespace std;
class Bitset {
private:
    vector<int> set;
    int size;
    int zeros;
    int ones;
    bool reverse;
public:
    // 构造函数，初始化位图
    Bitset(int n) : size(n), zeros(n), ones(0), reverse(false) {
        set.resize((n + 31) / 32);
    }
    // 将数字i加入位图
    void fix(int i) {
        int index = i / 32;
        int bit = i % 32;
        if (!reverse) {
            // 位图未翻转状态
            if ((set[index] & (1 << bit)) == 0) {//注意 & 的运算优先级低于 == 和 !=
                zeros--;
                ones++;
                set[index] |= (1 << bit);
            }
        }
        else {
            // 位图翻转状态
            if ((set[index] & (1 << bit)) != 0) {
                zeros--;
                ones++;
                set[index] ^= (1 << bit);
            }
        }
    }
    // 将数字i从位图中移除
    void unfix(int i) {
        int index = i / 32;
        int bit = i % 32;
        if (!reverse) {
            if ((set[index] & (1 << bit)) != 0) {
                ones--;
                zeros++;
                set[index] ^= (1 << bit);
            }
        }
        else {
            if ((set[index] & (1 << bit)) == 0) {
                ones--;
                zeros++;
                set[index] |= (1 << bit);
            }
        }
    }
    // 翻转整个位图
    void flip() {
        reverse = !reverse;
        swap(zeros, ones);
    }
    // 检查所有位是否为1
    bool all() {
        return ones == size;
    }
    // 检查是否至少有一个位为1
    bool one() {
        return ones > 0;
    }
    // 计算位图中为1的位的数量
    int count() {
        return ones;
    }
    // 返回位图的字符串表示
    string toString() {
        ostringstream builder;
        for (int i = 0, k = 0; i < size; k++) {
            //i 是全局的位索引，通过这个变量可以知道当前处理的是第几位。
            int number = set[k]; //number 是当前的32位整数，表示32个位的信息。
            for (int j = 0; j < 32 && i < size; j++, i++) {
                int status = (number >> j) & 1;
                status ^= reverse ? 1 : 0;
                builder << status;
            }
        }
        return builder.str();
    }
};
