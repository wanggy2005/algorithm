#include<vector>
using namespace std;
//һ���������� https://leetcode.cn/problems/number-of-islands/
// ����һ���� '1'��½�أ��� '0'��ˮ����ɵĵĶ�ά����������������е��������
// �������Ǳ�ˮ��Χ������ÿ������ֻ����ˮƽ�����/����ֱ���������ڵ�½�������γ�
// ���⣬����Լ��������������߾���ˮ��Χ
class Solution {
private:
    void dfs(vector<vector<char>>& board, int n, int m, int i, int j) {
        if (i < 0 || i >= n || j < 0 || j >= m || board[i][j] != '1') {//����±�Խ����߸õ��ѱ���Ⱦ��ֱ�ӷ���
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

//������Χ�Ƶ����� https://leetcode.cn/problems/surrounded-regions/
// ����һ�� m x n �ľ��� board ���������ַ� 'X' �� 'O' ���ҵ����б� 'X' Χ�Ƶ�����
// ������Щ���������е� 'O' �� 'X' ��䡣
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

//����// ����˹��� https://leetcode.cn/problems/making-a-large-island/
// ����һ����СΪ n * n �����ƾ��� grid ����� ֻ�ܽ�һ�� 0 ��� 1 ��
// ����ִ�д˲�����grid �����ĵ�������Ƕ��٣�
// ���� ��һ���ϡ��¡������ĸ����������� 1 �γ�
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
        // ��������grid���ҵ����еĵ��첢�ò�ͬ��id���
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    dfs(grid, n, m, i, j, id++);
                }
            }
        }
        vector<int> sizes(id);
        int ans = 0;
        // �������е���������С
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] > 1) {
                    ans = max(ans, ++sizes[grid[i][j]]);
                }
            }
        }
        // ���۽�0���1���ܴ�������󵺵����
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

//�ġ���ש�� https://leetcode.cn/problems/bricks-falling-when-hit/
// ��һ�� m * n �Ķ�Ԫ���� grid ������ 1 ��ʾש�飬0 ��ʾ�հ�
// ש�� �ȶ���������䣩��ǰ���ǣ�
// һ��שֱ�����ӵ�����Ķ���������
// ������һ�����ڣ�4 ������֮һ��ש�� �ȶ� �������ʱ
// ����һ������ hits ��������Ҫ��������ש���λ��
// ÿ������ hits[i] = (rowi, coli) λ���ϵ�ש��ʱ����Ӧλ�õ�ש�飨�����ڣ�����ʧ
// Ȼ��������ש�������Ϊ��һ���������� ����
// һ��ש����䣬���� ���� ������ grid ����ʧ���������������������ȶ���ש���ϣ�
// ����һ������ result ������ result[i] ��ʾ�� i ������������Ӧ�����ש����Ŀ��
// ע�⣬��������ָ����û��ש��Ŀհ�λ�ã�������������������û��ש����䡣