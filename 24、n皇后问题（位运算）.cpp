#include<vector>
#include<cstdlib>
using namespace std;
//N皇后问题 https://leetcode.cn/problems/n-queens-ii/ 时间复杂度O(n!)
class Solution {
private:
    // 递归函数f，用于尝试在当前行放置皇后
    int f(int i, vector<int>& path, int n) {
        if (i == n) {
            return 1; // 如果所有行都放置了皇后，返回1表示找到一种有效方法
        }
        int ans = 0;
        // 尝试在当前行的每一列放置皇后
        for (int j = 0; j < n; j++) {
            if (check(path, i, j)) {
                path[i] = j; // 在当前行i的列j放置皇后
                ans += f(i + 1, path, n); // 递归尝试下一行
            }
        }
        return ans;
    }
    // 检查在当前行i的列j放置皇后是否有效
    bool check(const vector<int>& path, int i, int j) {
        for (int k = 0; k < i; k++) {
            // 检查是否有皇后在同一列或对角线上
            if (j == path[k] || abs(i - k) == abs(j - path[k])) {
                return false; // 如果冲突，返回false
            }
        }
        return true; // 如果没有冲突，返回true
    }
public:
    int totalNQueens(int n) {
        if (n < 1) {
            return 0;
        }
        vector<int> path(n); // path用于存储每行皇后的位置
        return f(0, path, n);
    }
};

//位运算的版本--将皇后的位置分布储存在位信息中
class Solution {
private:
    int f(int limit, int col, int left, int right) {
        if (col == limit) {
            return 1;
        }
        int ans = 0;
        //col:在纵向上不能放置皇后的位置   left：在左斜对角线方向上不能放置皇后的位置   right：在右斜对角线方向上不能放置皇后的位置
        int ban = col | left | right;//获取所有不能放置的位置
        int candidate = limit & (~ban);//对ban取反获得可以放置的位置
        int place = 0;
        while (candidate != 0) {
            place = candidate & (-candidate);  // 提取最右侧的1
            candidate ^= place;  // 移除最右侧的1，即表示在最右侧1的位置摆上皇后
            ans += f(limit, col | place, (left | place) >> 1, (right | place) << 1);//更新col、left、right
        }
        return ans;
    }
public:
    int totalNQueens(int n) {
        if (n < 1) {
            return 0;
        }
        int limit = (1 << n) - 1;//表示全为1即全部放完皇后的情况
        return f(limit, 0, 0, 0);
    }
};
