#include<vector>
using namespace std;
//一、岛屿数量 https://leetcode.cn/problems/number-of-islands/
// 给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量
// 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成
// 此外，你可以假设该网格的四条边均被水包围
class Solution {
private:
    void dfs(vector<vector<char>>& board, int n, int m, int i, int j) {
        if (i < 0 || i >= n || j < 0 || j >= m || board[i][j] != '1') {//如果下标越界或者该点已被感染，直接返回
            return;
        }
        board[i][j] = '0';
        dfs(board, n, m, i - 1, j);
        dfs(board, n, m, i + 1, j);
        dfs(board, n, m, i, j - 1);
        dfs(board, n, m, i, j + 1);
    }
public:
    int numIslands(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();
        int islands = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == '1') {
                    islands++;
                    dfs(board, n, m, i, j);
                }
            }
        }
        return islands;
    }
};

//二、被围绕的区域 https://leetcode.cn/problems/surrounded-regions/
// 给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' ，找到所有被 'X' 围绕的区域
// 并将这些区域里所有的 'O' 用 'X' 填充。
class Solution {
private:
    void flood(vector<vector<char>>& board, int i, int j, int m, int n) {
        if (i < 0 || j < 0 || i >= n || j >= m || board[i][j] == 'X' || board[i][j] == 'F') {
            return;
        }
        board[i][j] = 'F';
        flood(board, i + 1, j, m, n);
        flood(board, i - 1, j, m, n);
        flood(board, i, j + 1, m, n);
        flood(board, i, j - 1, m, n);
    }
    void fill(vector<vector<char>>& board, int m, int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
                if (board[i][j] == 'F') {
                    board[i][j] = 'O';
                }
            }
        }
    }
public:
    void solve(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();
        for (int i = 0; i < n; i++) {
            flood(board, i, 0, m, n);
            flood(board, i, m - 1, m, n);
        }
        for (int j = 1; j < m - 1; j++) {
            flood(board, 0, j, m, n);
            flood(board, n - 1, j, m, n);
        }
        fill(board, m, n);
    }
};

//三、// 最大人工岛 https://leetcode.cn/problems/making-a-large-island/
// 给你一个大小为 n * n 二进制矩阵 grid 。最多 只能将一格 0 变成 1 。
// 返回执行此操作后，grid 中最大的岛屿面积是多少？
// 岛屿 由一组上、下、左、右四个方向相连的 1 形成
class Solution {
private:
    void dfs(vector<vector<int>>& grid, int n, int m, int i, int j, int id) {
        if (i < 0 || i == n || j < 0 || j == m || grid[i][j] != 1) {
            return;
        }
        grid[i][j] = id;
        dfs(grid, n, m, i - 1, j, id);
        dfs(grid, n, m, i + 1, j, id);
        dfs(grid, n, m, i, j - 1, id);
        dfs(grid, n, m, i, j + 1, id);
    }
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int id = 2;
        // 遍历整个grid，找到所有的岛屿并用不同的id标记
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    dfs(grid, n, m, i, j, id++);
                }
            }
        }
        vector<int> sizes(id);
        int ans = 0;
        // 计算所有岛屿的面积大小
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] > 1) {
                    ans = max(ans, ++sizes[grid[i][j]]);
                }
            }
        }
        // 讨论将0变成1所能带来的最大岛的面积
        vector<bool> visited(id, false);
        int up, down, left, right, merge;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 0) {
                    up = i > 0 ? grid[i - 1][j] : 0;
                    down = i + 1 < n ? grid[i + 1][j] : 0;
                    left = j > 0 ? grid[i][j - 1] : 0;
                    right = j + 1 < m ? grid[i][j + 1] : 0;
                    visited[up] = true;
                    merge = 1 + sizes[up];
                    if (!visited[down]) {
                        merge += sizes[down];
                        visited[down] = true;
                    }
                    if (!visited[left]) {
                        merge += sizes[left];
                        visited[left] = true;
                    }
                    if (!visited[right]) {
                        merge += sizes[right];
                        visited[right] = true;
                    }
                    ans = max(ans, merge);
                    visited[up] = false;
                    visited[down] = false;
                    visited[left] = false;
                    visited[right] = false;
                }
            }
        }
        return ans;
    }
};

//四、打砖块 https://leetcode.cn/problems/bricks-falling-when-hit/
// 有一个 m * n 的二元网格 grid ，其中 1 表示砖块，0 表示空白
// 砖块 稳定（不会掉落）的前提是：
// 一块砖直接连接到网格的顶部，或者
// 至少有一块相邻（4 个方向之一）砖块 稳定 不会掉落时
// 给你一个数组 hits ，这是需要依次消除砖块的位置
// 每当消除 hits[i] = (rowi, coli) 位置上的砖块时，对应位置的砖块（若存在）会消失
// 然后其他的砖块可能因为这一消除操作而 掉落
// 一旦砖块掉落，它会 立即 从网格 grid 中消失（即，它不会落在其他稳定的砖块上）
// 返回一个数组 result ，其中 result[i] 表示第 i 次消除操作对应掉落的砖块数目。
// 注意，消除可能指向是没有砖块的空白位置，如果发生这种情况，则没有砖块掉落。