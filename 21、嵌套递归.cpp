#include<vector>
#include<string>
#include<set>
#include<unordered_set>
#include<algorithm>
#include<stack>
#include<iostream>
#include<map>
using namespace std;
/*嵌套类问题的解题套路
大概过程: 
定义全局变量 int where
递归函数f(i) : s[i..]，从i位置出发开始解析，遇到 字符串终止 或 嵌套条件终止 就返回
返回值是f(i)负责这一段的结果
f(i)在返回前更新全局变量where，让上级函数通过where知道解析到了什么位置，进而继续

执行细节:
如果f(i)遇到 嵌套条件开始，就调用下级递归去处理嵌套，下级会负责嵌套部分的计算结果
f(i)下级处理完成后，f(i)可以根据下级更新的全局变量where，知道该从什么位置继续解析*/

//一、含有嵌套的表达式求值 https://leetcode.cn/problems/basic-calculator-iii/
/*实现一个基本的计算器来计算简单的表达式字符串。表达式字符串只包含非负整数， + ， - ， * ， / 操作符，左括号(，右括号)和空格。整数除法需要向下截断。
你可以假定给定的字符串总是有效的。所有的中间结果的范围为[-2147483648，2147483647]*/
class Solution {
private:
    int where;
    // s[i....] 开始计算，遇到字符串终止或者遇到 ')' 停止
    // 返回: 自己负责的这一段，计算的结果
    // 返回之前，更新成员变量 where，为了上游函数知道从哪继续！
    int f(const string& s, int i) {
        int cur = 0;
        vector<int> numbers;//数字栈
        vector<char> ops;//运算符栈
        while (i < s.length() && s[i] != ')') {
            if (isdigit(s[i])) {  // 如果当前字符是数字
                cur = cur * 10 + (s[i++] - '0');
            }else if (s[i] != '(') {  // 如果当前字符是运算符 (+, -, *, /)
                push(numbers, ops, cur, s[i++]);
                cur = 0;
            }else {  // 如果遇到了左括号 '('
                cur = f(s, i + 1);  // 递归处理括号内的表达式
                i = where + 1;  // 更新索引，跳过 ')'
            }
        }
        push(numbers, ops, cur, '+');  // 将最后一个数字压入栈
        where = i;  // 更新位置索引
        return compute(numbers, ops);  // 计算并返回结果
    }
    // 将当前数字和操作符压入栈中，处理优先级操作符（*，/）
    void push(vector<int>& numbers, vector<char>& ops, int cur, char op) {
        int n = numbers.size();
        if (n == 0 || ops[n - 1] == '+' || ops[n - 1] == '-') {
            numbers.push_back(cur);
            ops.push_back(op);
        }else {  // 处理优先级操作符（*，/）
            int topNumber = numbers[n - 1];
            char topOp = ops[n - 1];
            if (topOp == '*') {
                numbers[n - 1] = topNumber * cur;
            }else {
                numbers[n - 1] = topNumber / cur;
            }
            ops[n - 1] = op;  // 更新操作符
        }
    }
    // 计算结果，根据栈中的数字和操作符
    int compute(const vector<int>& numbers, const vector<char>& ops) {
        int n = numbers.size();
        int ans = numbers[0];
        for (int i = 1; i < n; i++) {
            if (ops[i - 1] == '+') {
                ans += numbers[i];
            }else {
                ans -= numbers[i];
            }
        }
        return ans;
    }
public:
    int calculate(const string& str) {
        where = 0;  // 初始化 where 变量
        return f(str, 0);  // 从字符串的第一个字符开始计算
    }
};

//二、含有嵌套的字符串解码 https://leetcode.cn/problems/decode-string/
/*给定一个经过编码的字符串，返回它解码后的字符串。
编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。
你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。
此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。*/
class Solution {
private:
    string decode(const string& s, int& i) {//i按引用传递，这样省去了全局变量
        string result;
        while (i < s.length() && s[i] != ']') {
            if (isalpha(s[i])) {//s[i]如果是字母，直接加到答案里
                result += s[i++];
            }else if (isdigit(s[i])) {//s[i]如果是数字
                int cnt = 0;
                while (isdigit(s[i])) {
                    cnt = cnt * 10 + (s[i++] - '0');
                }//先获取重复的次数
                i++; // 跳过 '['
                string parsedStr = decode(s, i);
                i++; // 跳过 ']'
                while (cnt--) {
                    result += parsedStr;
                }
            }
        }
        return result;
    }
public:
    string decodeString(string s) {
        int i = 0;
        return decode(s, i);
    }
};

class Solution {
private:
    string f(const string& s, int i) {
        string path;
        int cnt = 0;
        while (i < s.length() && s[i] != ']') {
            if (isalpha(s[i])) {  // 如果是字母，直接添加到结果字符串
                path += s[i++];
            }else if (isdigit(s[i])) {  // 如果是数字，计算重复次数
                cnt = cnt * 10 + s[i++] - '0';
            }else {
                // 遇到 '[' 时递归处理
                path += get(cnt, f(s, i + 1));
                i = where + 1;  // 更新当前位置
            }
        }
        where = i;  // 更新全局变量，指向当前处理到的位置
        return path;
    }
    // 将字符串str重复cnt次
    string get(int& cnt, const string& str) {
        string result;
        for (; cnt > 0; cnt--) {
            result += str;
        }
        return result;
    }
public:
    int where;  // 全局变量，用于记录解析过程中的当前位置
    string decodeString(const string& str) {
        where = 0;
        return f(str, 0);
    }
};

//三、含有嵌套的分子式求原子数量 https://leetcode.cn/problems/number-of-atoms/description/
class Solution {
private:
    int where = 0;  // 全局变量，跟踪解析的位置
    // 递归函数：解析字符串中的元素及括号，返回元素计数的有序表
    map<string, int> f(const string& s, int i) {
        map<string, int> ans;  // 存储当前解析的元素及其计数
        string name;  // 当前元素的名称
        map<string, int> pre;  // 存储括号内解析的元素及其计数
        int cnt = 0;  // 当前元素的计数
        // 遍历字符串
        while (i < s.length() && s[i] != ')') {
            if (isupper(s[i]) || s[i] == '(') {
                // 遇到大写字母或 '('
                fill(ans, name, pre, cnt);  // 更新 ans
                name.clear();  // 重置元素名称
                pre.clear();  // 重置括号内的元素计数
                cnt = 0;  // 重置计数
                if (isupper(s[i])) {
                    // 遇到大写字母，表示元素名称的开始
                    name += s[i++];
                }else {
                    // 遇到 '('，递归解析括号内的部分
                    pre = f(s, i + 1);
                    i = where + 1;  // 更新当前位置
                }
            }else if (islower(s[i])) {
                name += s[i++];// 遇到小写字母，继续添加元素名称
            }else {
                // 遇到数字，计算当前元素的计数
                cnt = cnt * 10 + s[i++] - '0';
            }
        }
        // 更新 ans
        fill(ans, name, pre, cnt);
        where = i;  // 更新全局变量，指向当前处理到的位置
        return ans;
    }
    // 将元素及其计数填充到 ans 中
    void fill(map<string, int>& ans, const string& name, const map<string, int>& pre, int cnt) {
        if (!name.empty() || !pre.empty()) {
            cnt = (cnt == 0) ? 1 : cnt;  // 如果最后括号外的计数为 0，则设置为 1
            if (!name.empty()) {
                // 如果最后有没跟数字的元素，将其计数更新到 ans 中
                ans[name] += cnt;
            }else {
                // 如果没有没跟数字的元素，处理括号内的元素
                for (const auto& [key, value] : pre) {
                    ans[key] += value * cnt;  // 更新元素计数
                }
            }
        }
    }
public:
    string countOfAtoms(const string& str) {
        auto map = f(str, 0);  
        string ans;
        for (const auto& [key, cnt] : map) {
            ans += key;  // 添加元素名称
            if (cnt > 1) {  // 如果计数大于 1，添加计数值
                ans += to_string(cnt);
            }
        }
        return ans;
    }
};