/*��άǰ׺��	��+��-����+�Լ�
* �ݹ�+�ݳ�ԭ�� ���������ظ���������
Ŀ����Ԥ�����һ���ṹ���Ժ�ÿ�β�ѯ��ά�����κη�Χ�ϵ��ۼӺͶ���O(1)�Ĳ���
1�� ����ԭʼ״�������ɶ�άǰ׺������sum��
sum[i][j]: �������Ͻ�(0, 0)�����½�(i, j)�����Χ���ۼӺ�
sum[i][j] += sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1];
2�� ��ѯ���Ͻ�(a, b)�����½�(c, d)�����Χ���ۼӺ�
sum[c][d] - sum[c][b - 1] - sum[a - 1][d] + sum[a - 1][b - 1];
3�� ʵ�ʹ�������������0�С���0�������ٺܶ������жϡ�*/

//һ�����ö�άǰ׺����ϢѸ�ٵõ���ά����� https://leetcode.cn/problems/range-sum-query-2d-immutable/
class NumMatrix {
private:
    vector<vector<int>> sum;
    void sumMatrix(int m, int n, vector<vector<int>>& matrix) {
        sum = vector<vector<int>>(m + 1, vector<int>(n + 1, 0));
        // ����ǰ׺�;���
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

//�����߿�Ϊ1����������� https://leetcode.cn/problems/largest-1-bordered-square/
// ����һ�������� 0 �� 1 ��ɵĶ�ά���� grid
// �����ҳ��߽�ȫ���� 1 ��ɵ���� ������ ������
// �����ظ��������е�Ԫ����������������ڣ��򷵻� 0��
class Solution {
private:
    int get(const vector<vector<int>>& g, int i, int j) {
        return (i < 0 || j < 0) ? 0 : g[i][j];// ������������߽磬����0�����򷵻�ǰ׺�;����е�ֵ��
    }
    // ����ǰ׺�;���
    void build(int n, int m, vector<vector<int>>& g) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                g[i][j] += get(g, i, j - 1) + get(g, i - 1, j) - get(g, i - 1, j - 1);
            }
        }
    }
    // ����� (a, b) �� (c, d) ֮����������ǰ׺��
    int sum(const vector<vector<int>>& g, int a, int b, int c, int d) {
        // ��� a > c��˵������������Ч������ 0
        return a > c ? 0 : (g[c][d] - get(g, c, b - 1) - get(g, a - 1, d) + get(g, a - 1, b - 1));
    }
public:
    int largest1BorderedSquare(vector<vector<int>>& g) {
        int n = g.size();    // ����
        int m = g[0].size(); // ����
        build(n, m, g);// ����ǰ׺�;���
        if (sum(g, 0, 0, n - 1, m - 1) == 0) {// �������������û��1���򷵻�0
            return 0;
        }
        int ans = 1; // ��ʼ�����������α߳�Ϊ1��������һ��1��
        // ö�����п��ܵ����Ͻǵ� (a, b)
        for (int a = 0; a < n; a++) {
            for (int b = 0; b < m; b++) {
                // �ӵ�ǰ�����εĳ�ʼ�߳���ʼ���Ը���߳�
                for (int c = a + ans, d = b + ans, k = ans + 1; c < n && d < m; c++, d++, k++) {
                    // �ж��� (a, b) Ϊ���Ͻǣ�(c, d) Ϊ���½ǵ��������Ƿ��Ǳ߿�ȫΪ1��������
                    if (sum(g, a, b, c, d) - sum(g, a + 1, b + 1, c - 1, d - 1) == (k - 1) << 2) {
                        ans = k; // �������߳�
                    }
                }
            }
        }
        return ans * ans;// ������������ε����
    }
};


//��̬�滮
class Solution {
public:
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // ����������ά����left��up�����ڼ�¼����1������
        vector<vector<int>> left(m + 1, vector<int>(n + 1));// left[i][j]��ʾ��λ��(i, j)��������1������
        vector<vector<int>> up(m + 1, vector<int>(n + 1));// up[i][j]��ʾ��λ��(i, j)��������1������
        int maxBorder = 0;// ��¼���߳�
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                // �����ǰλ����1
                if (grid[i - 1][j - 1] == 1) {
                    // ���㵱ǰλ����������ϵ�����1������
                    left[i][j] = left[i][j - 1] + 1;
                    up[i][j] = up[i - 1][j] + 1;
                    // ���㵱ǰ���ܵ������ε����߳�
                    int border = min(left[i][j], up[i][j]);
                    // �������߳��Ƿ����γ�һ��������������
                    // ͨ���ж���ߺ��ϱߵ�����1����������֤
                    while (left[i - border + 1][j] < border || up[i][j - border + 1] < border) {
                        border--;
                    }
                    // �������ı߳�
                    maxBorder = max(maxBorder, border);
                }
            }
        }
        return maxBorder * maxBorder;// �����������������
    }
};

//������ά���ģ��
https://www.nowcoder.com/practice/50e1a93989df42efb0b1dec386fb4ccc

https://www.luogu.com.cn/problem/P3397

//�ġ�����Ʊ��������ͼ https://leetcode.cn/problems/stamping-the-grid/
/*����һ�� m * n �Ķ����ƾ��� grid
ÿ������ҪôΪ 0 ���գ�ҪôΪ 1 ����ռ�ݣ�
������Ʊ�ĳߴ�Ϊ stampHeight * stampWidth
�����뽫��Ʊ���������ƾ����У����������� ���� �� Ҫ�� ��
�������пո��ӣ��������κα�ռ�ݵĸ���
���Է���������Ŀ����Ʊ����Ʊ�����໥���ص�����
��Ʊ��������ת����Ʊ������ȫ�ھ�����
�������������Ҫ���ǰ���£����Է�����Ʊ���뷵�� true �����򷵻� false */

//�塢��ɢ������--����ά����������ת��Ϊ�߼����� https://leetcode.cn/problems/xepqZ5/
