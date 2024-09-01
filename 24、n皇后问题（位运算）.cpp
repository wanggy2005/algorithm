#include<vector>
#include<cstdlib>
using namespace std;
//N�ʺ����� https://leetcode.cn/problems/n-queens-ii/ ʱ�临�Ӷ�O(n!)
class Solution {
private:
    // �ݹ麯��f�����ڳ����ڵ�ǰ�з��ûʺ�
    int f(int i, vector<int>& path, int n) {
        if (i == n) {
            return 1; // ��������ж������˻ʺ󣬷���1��ʾ�ҵ�һ����Ч����
        }
        int ans = 0;
        // �����ڵ�ǰ�е�ÿһ�з��ûʺ�
        for (int j = 0; j < n; j++) {
            if (check(path, i, j)) {
                path[i] = j; // �ڵ�ǰ��i����j���ûʺ�
                ans += f(i + 1, path, n); // �ݹ鳢����һ��
            }
        }
        return ans;
    }
    // ����ڵ�ǰ��i����j���ûʺ��Ƿ���Ч
    bool check(const vector<int>& path, int i, int j) {
        for (int k = 0; k < i; k++) {
            // ����Ƿ��лʺ���ͬһ�л�Խ�����
            if (j == path[k] || abs(i - k) == abs(j - path[k])) {
                return false; // �����ͻ������false
            }
        }
        return true; // ���û�г�ͻ������true
    }
public:
    int totalNQueens(int n) {
        if (n < 1) {
            return 0;
        }
        vector<int> path(n); // path���ڴ洢ÿ�лʺ��λ��
        return f(0, path, n);
    }
};

//λ����İ汾--���ʺ��λ�÷ֲ�������λ��Ϣ��
class Solution {
private:
    int f(int limit, int col, int left, int right) {
        if (col == limit) {
            return 1;
        }
        int ans = 0;
        //col:�������ϲ��ܷ��ûʺ��λ��   left������б�Խ��߷����ϲ��ܷ��ûʺ��λ��   right������б�Խ��߷����ϲ��ܷ��ûʺ��λ��
        int ban = col | left | right;//��ȡ���в��ܷ��õ�λ��
        int candidate = limit & (~ban);//��banȡ����ÿ��Է��õ�λ��
        int place = 0;
        while (candidate != 0) {
            place = candidate & (-candidate);  // ��ȡ���Ҳ��1
            candidate ^= place;  // �Ƴ����Ҳ��1������ʾ�����Ҳ�1��λ�ð��ϻʺ�
            ans += f(limit, col | place, (left | place) >> 1, (right | place) << 1);//����col��left��right
        }
        return ans;
    }
public:
    int totalNQueens(int n) {
        if (n < 1) {
            return 0;
        }
        int limit = (1 << n) - 1;//��ʾȫΪ1��ȫ������ʺ�����
        return f(limit, 0, 0, 0);
    }
};
