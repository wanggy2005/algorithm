/*二维前缀和	左+上-左上+自己
* 递归+容斥原理 左上区域重复加了两次
目的是预处理出一个结构，以后每次查询二维数组任何范围上的累加和都是O(1)的操作
1、 根据原始状况，生成二维前缀和数组sum，
sum[i][j]: 代表左上角(0, 0)到右下角(i, j)这个范围的累加和
sum[i][j] += sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1];
2、 查询左上角(a, b)到右下角(c, d)这个范围的累加和
sum[c][d] - sum[c][b - 1] - sum[a - 1][d] + sum[a - 1][b - 1];
3、 实际过程中往往补第0行、第0列来减少很多条件判断。*/

//一、利用二维前缀和信息迅速得到二维区域和 https://leetcode.cn/problems/range-sum-query-2d-immutable/
class NumMatrix {
private:
    vector<vector<int>> sum;
    void sumMatrix(int m, int n, vector<vector<int>>& matrix) {
        sum = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
        // 构建前缀和矩阵
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                sum[i][j] = matrix[i - 1][j - 1] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
            }
        }
    }
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        sumMatrix(m, n, matrix);
    }
    int sumRegion(int row1, int col1, int row2, int col2) {
        return sum[row2 + 1][col2 + 1] - sum[row1][col2 + 1] - sum[row2 + 1][col1] + sum[row1][col1];
    }
};

//二、边框为1的最大正方形 https://leetcode.cn/problems/largest-1-bordered-square/
// 给你一个由若干 0 和 1 组成的二维网格 grid
// 请你找出边界全部由 1 组成的最大 正方形 子网格
// 并返回该子网格中的元素数量。如果不存在，则返回 0。
class Solution {
private:
    int get(const vector<vector<int>>& g, int i, int j) {
        return (i < 0 || j < 0) ? 0 : g[i][j];// 如果索引超出边界，返回0；否则返回前缀和矩阵中的值。
    }
    // 构建前缀和矩阵
    void build(int n, int m, vector<vector<int>>& g) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                g[i][j] += get(g, i, j - 1) + get(g, i - 1, j) - get(g, i - 1, j - 1);
            }
        }
    }
    // 计算从 (a, b) 到 (c, d) 之间矩形区域的前缀和
    int sum(const vector<vector<int>>& g, int a, int b, int c, int d) {
        // 如果 a > c，说明矩形区域无效，返回 0
        return a > c ? 0 : (g[c][d] - get(g, c, b - 1) - get(g, a - 1, d) + get(g, a - 1, b - 1));
    }
public:
    int largest1BorderedSquare(vector<vector<int>>& g) {
        int n = g.size();    // 行数
        int m = g[0].size(); // 列数
        build(n, m, g);// 构建前缀和矩阵
        if (sum(g, 0, 0, n - 1, m - 1) == 0) {// 如果整个矩阵中没有1，则返回0
            return 0;
        }
        int ans = 1; // 初始化最大的正方形边长为1（至少有一个1）
        // 枚举所有可能的左上角点 (a, b)
        for (int a = 0; a < n; a++) {
            for (int b = 0; b < m; b++) {
                // 从当前正方形的初始边长开始尝试更大边长
                for (int c = a + ans, d = b + ans, k = ans + 1; c < n && d < m; c++, d++, k++) {
                    // 判断以 (a, b) 为左上角，(c, d) 为右下角的正方形是否是边框全为1的正方形
                    if (sum(g, a, b, c, d) - sum(g, a + 1, b + 1, c - 1, d - 1) == (k - 1) << 2) {
                        ans = k; // 更新最大边长
                    }
                }
            }
        }
        return ans * ans;// 返回最大正方形的面积
    }
};


//动态规划
class Solution {
public:
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // 创建两个二维数组left和up，用于记录连续1的数量
        vector<vector<int>> left(m + 1, vector<int>(n + 1));// left[i][j]表示从位置(i, j)向左连续1的数量
        vector<vector<int>> up(m + 1, vector<int>(n + 1));// up[i][j]表示从位置(i, j)向上连续1的数量
        int maxBorder = 0;// 记录最大边长
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                // 如果当前位置是1
                if (grid[i - 1][j - 1] == 1) {
                    // 计算当前位置向左和向上的连续1的数量
                    left[i][j] = left[i][j - 1] + 1;
                    up[i][j] = up[i - 1][j] + 1;
                    // 计算当前可能的正方形的最大边长
                    int border = min(left[i][j], up[i][j]);
                    // 检查这个边长是否能形成一个完整的正方形
                    // 通过判断左边和上边的连续1的数量来验证
                    while (left[i - border + 1][j] < border || up[i][j - border + 1] < border) {
                        border--;
                    }
                    // 更新最大的边长
                    maxBorder = max(maxBorder, border);
                }
            }
        }
        return maxBorder * maxBorder;// 返回最大的正方形面积
    }
};

//三、二维差分模版
https://www.nowcoder.com/practice/50e1a93989df42efb0b1dec386fb4ccc

https://www.luogu.com.cn/problem/P3397

//四、用邮票贴满网格图 https://leetcode.cn/problems/stamping-the-grid/
/*给你一个 m * n 的二进制矩阵 grid
每个格子要么为 0 （空）要么为 1 （被占据）
给你邮票的尺寸为 stampHeight * stampWidth
我们想将邮票贴进二进制矩阵中，且满足以下 限制 和 要求 ：
覆盖所有空格子，不覆盖任何被占据的格子
可以放入任意数目的邮票，邮票可以相互有重叠部分
邮票不允许旋转，邮票必须完全在矩阵内
如果在满足上述要求的前提下，可以放入邮票，请返回 true ，否则返回 false */

//五、离散化方法--将二维的物理坐标转化为逻辑坐标 https://leetcode.cn/problems/xepqZ5/
