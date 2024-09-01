#include<vector>
#include<string>
#include<set>
#include<unordered_set>
#include<algorithm>
#include<stack>
#include<iostream>
using namespace std;
//一、字符串的全部子序列 https://www.nowcoder.com/practice/92e6247998294f2c933906fdedbc6e6a
/*给定一个字符串s，长度为n，求s的所有子序列
1.子序列: 指一个字符串删掉部分字符（也可以不删）形成的字符串，可以是不连续的，比如"abcde"的子序列可以有"ace", "ad"等等
2.将所有的子序列的结果返回为一个字符串数组
3.字符串里面可能有重复字符，但是返回的子序列不能有重复的子序列，比如"aab"的子序列只有"", "a", "aa", "aab", "ab", "b"，不能存在2个相同的"ab"
4.返回字符串数组里面的顺序可以不唯一*/
class Solution {
public:
    vector<string> generatePermutation(string str) {
        set<string> set;// 使用 set 来存储唯一的子序列，自动去重
        string path;
        f(str, 0, path, set);
        vector<string> ans(set.begin(), set.end());
        return ans;
    }
private:
    // s[i...]，之前决定的路径path，Hashset收集结果时去重
    void f(const string& s, int i, string& path, set<string>& set) {
        if (i == s.size()) {
            set.insert(path);
        }else {
            // 加到路径中去
            path.push_back(s[i]);
            f(s, i + 1, path, set);
            // 从路径中移除
            path.pop_back();
            f(s, i + 1, path, set);
        }
    }
};

class Solution {
public:
    vector<string> generatePermutation(string str) {
        set<string> resultSet; 
        string path(str.length(), ' ');  // 初始化一个长度为 str.length() 的字符串，并用空格填充
        f(str, 0, path, 0, resultSet); 
        vector<string> ans(resultSet.begin(), resultSet.end());
        return ans;
    }

private:
    void f(const string& s, int i, string& path, int size, set<string>& resultSet) {
        // 基础情况：当到达字符串末尾时
        if (i == s.length()) {
            resultSet.insert(path.substr(0, size));  // substr 用于提取 path 中从起始位置到当前长度 size 的部分
        } else {
            // 包含当前字符到路径中，然后递归处理下一个字符
            path[size] = s[i];
            f(s, i + 1, path, size + 1, resultSet);
            // 不包含当前字符，直接递归处理下一个字符
            f(s, i + 1, path, size, resultSet);
        }
    }
};


//二、给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的组合 https://leetcode.cn/problems/subsets-ii/
//答案 不能 包含重复的组合。返回的答案中，组合可以按 任意顺序 排列
//比如输入：nums = [1,2,2]  输出：[[],[1],[1,2],[1,2,2],[2],[2,2]] 
//重点：如何去重
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans; // 用于存储所有子集
        vector<int> path(nums.size()); // 用于存储当前子集路径
        sort(nums.begin(), nums.end()); // 对数组进行排序，以便于后面的去重
        f(nums, 0, path, 0, ans);
        return ans;
    }
private:
    void f(vector<int>& nums, int i, vector<int>& path, int size, vector<vector<int>>& ans) {
        if (i == nums.size()) {
            vector<int> cur(path.begin(), path.begin() + size); // 将当前路径转换为子集
            ans.push_back(cur); // 将子集加入到结果集中
        }else {
            int j = i + 1;
            while (j < nums.size() && nums[i] == nums[j]) {
                j++; // 找到相同元素的结束位置
            }
            // 当前数x，要0个
            f(nums, j, path, size, ans);
            // 当前数x，要1个、要2个、要3个...都尝试
            for (; i < j; i++) {
                path[size++] = nums[i];
                f(nums, j, path, size, ans);
            }
        }
    }
};

//三、没有重复项数字的全排列 https://leetcode.cn/problems/permutations/
//直接在原数据中进行交换 时间复杂度O(n*n!)
class Solution {
private:
    void f(vector<vector<int>>& ans,int i,vector<int>& nums){
        if(i==nums.size()){
            ans.push_back(nums);
        }else{
            for(int j=i;j<nums.size();++j){
                swap(nums[i],nums[j]);// 交换当前元素与后面的元素
                f(ans,i+1,nums); // 递归生成下一个元素的排列
                swap(nums[j],nums[i]); // 恢复原数组状态，回溯
            }
        }
    }
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        f(ans,0,nums);
        return ans;
    }
};

//四、有重复项数组的去重全排列 https://leetcode.cn/problems/permutations-ii/
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ans;
        f(nums, 0, ans);
        return ans;
    }
private:
    void f(vector<int>& nums, int i, vector<vector<int>>& ans) {
        if (i == nums.size()) {
            ans.push_back(nums); // 将当前排列加入结果集中
        }else {
            unordered_set<int> set; // 用于检测重复元素
            for (int j = i; j < nums.size(); ++j) {
                // nums[j]没有来到过i位置，才会去尝试
                if (!set.count(nums[j])) {
                    set.insert(nums[j]);
                    swap(nums[i], nums[j]); // 交换当前元素与后面的元素
                    f(nums, i + 1, ans); // 递归生成下一个元素的排列
                    swap(nums[i], nums[j]); // 恢复原数组状态，回溯
                }
            }
        }
    }
};

//五、用递归函数逆序栈   时间复杂度为O(n*n)
int bottomOut(stack<int>& stack) {
    int ans = stack.top();// 记录当前栈顶元素
    stack.pop();  // 移除栈顶元素
    // 如果栈已空，说明刚才移除的元素是栈底元素，返回它
    if (stack.empty()) {
        return ans;
    }else {
        // 继续递归，寻找并返回栈底元素
        int last = bottomOut(stack);
        // 将栈顶元素压回栈中
        stack.push(ans);
        // 返回栈底元素
        return last;
    }
}
void reverse(stack<int>& stack) {
    // 递归终止条件：如果栈为空，则结束递归
    if (stack.empty()) {
        return;
    }
    // 记录并移除栈底元素
    int num = bottomOut(stack);
    // 递归调用，将剩余的栈元素逆序
    reverse(stack);
    // 将栈底元素重新压入栈顶
    stack.push(num);
}
 

//六、用递归函数排序栈   时间复杂度为O(n*n)
class Solution {
private:
    int deep(stack<int>& s) {//用递归来获取栈的大小
        stack<int> temp;
        int depth = 0;
        // 移动栈中的元素到临时栈，并计算深度
        while (!s.empty()) {
            temp.push(s.top());
            s.pop();
            depth++;
        }
        // 将元素移动回原栈
        while (!temp.empty()) {
            s.push(temp.top());
            temp.pop();
        }
        return depth;
    }
    int Getmax(stack<int>& s, int depth) {//用递归来获取栈中的最大元素
        if (depth == 0) {
            return INT_MIN;
        }
        int num = s.top();
        s.pop();
        int restMax = Getmax(s, depth - 1);
        int result = max(num, restMax);
        s.push(num);
        return result;
    }
    int times(stack<int>& s, int depth, int maxVal) {//用递归来统计最大元素出现的次数
        if (depth == 0) {
            return 0;
        }
        int num = s.top();
        s.pop();
        int restTimes = times(s, depth - 1, maxVal);
        int count = restTimes + (num == maxVal ? 1 : 0);
        s.push(num);
        return count;
    }
    void down(stack<int>& s, int depth, int maxVal, int k) {//利用递归将最大元素全部移动到栈底
        if (depth == 0) {
            for (int i = 0; i < k; ++i) {
                s.push(maxVal);
            }
            return;
        }
        int num = s.top();
        s.pop();
        down(s, depth - 1, maxVal, k);
        if (num != maxVal) {
            s.push(num);
        }
    }
public:
    void sort(stack<int>& s) {
        int d = deep(s);
        while (d > 0) {
            int maxVal = Getmax(s, d);
            int k = times(s, d, maxVal);
            down(s, d, maxVal, k);
            d -= k;
        }
    }
};


//七、Tower of Hanoi https://leetcode.cn/problems/hanota-lcci/
class Solution {
private:
    void f(int i, vector<int>& A, vector<int>& B, vector<int>& C) {
        if (i == 0)    return;
        f(i - 1, A, C, B);
        C.push_back(A.back());
        A.pop_back();
        f(i - 1, B, A, C);
    }
public:
    void hanota(vector<int>& A, vector<int>& B, vector<int>& C) {
        f(A.size(), A, B, C);
    }
};

class Solution {
public:
    void hanoi(int n) {
        if (n > 0) {
            f(n, "左", "右", "中");
        }
    }
private:
    void f(int i, string from, string to, string other) {
        if (i == 1) {
            cout << "移动圆盘 1 从 " << from << " 到 " << to << endl;
        }else {
            f(i - 1, from, other, to);
            cout << "移动圆盘 " << i << " 从 " << from << " 到 " << to << endl;
            f(i - 1, other, to, from);
        }
    }
};