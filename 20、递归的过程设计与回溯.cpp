#include<vector>
#include<string>
#include<set>
#include<unordered_set>
#include<algorithm>
#include<stack>
#include<iostream>
using namespace std;
//һ���ַ�����ȫ�������� https://www.nowcoder.com/practice/92e6247998294f2c933906fdedbc6e6a
/*����һ���ַ���s������Ϊn����s������������
1.������: ָһ���ַ���ɾ�������ַ���Ҳ���Բ�ɾ���γɵ��ַ����������ǲ������ģ�����"abcde"�������п�����"ace", "ad"�ȵ�
2.�����е������еĽ������Ϊһ���ַ�������
3.�ַ�������������ظ��ַ������Ƿ��ص������в������ظ��������У�����"aab"��������ֻ��"", "a", "aa", "aab", "ab", "b"�����ܴ���2����ͬ��"ab"
4.�����ַ������������˳����Բ�Ψһ*/
class Solution {
public:
    vector<string> generatePermutation(string str) {
        set<string> set;// ʹ�� set ���洢Ψһ�������У��Զ�ȥ��
        string path;
        f(str, 0, path, set);
        vector<string> ans(set.begin(), set.end());
        return ans;
    }
private:
    // s[i...]��֮ǰ������·��path��Hashset�ռ����ʱȥ��
    void f(const string& s, int i, string& path, set<string>& set) {
        if (i == s.size()) {
            set.insert(path);
        }else {
            // �ӵ�·����ȥ
            path.push_back(s[i]);
            f(s, i + 1, path, set);
            // ��·�����Ƴ�
            path.pop_back();
            f(s, i + 1, path, set);
        }
    }
};

class Solution {
public:
    vector<string> generatePermutation(string str) {
        set<string> resultSet; 
        string path(str.length(), ' ');  // ��ʼ��һ������Ϊ str.length() ���ַ��������ÿո����
        f(str, 0, path, 0, resultSet); 
        vector<string> ans(resultSet.begin(), resultSet.end());
        return ans;
    }

private:
    void f(const string& s, int i, string& path, int size, set<string>& resultSet) {
        // ����������������ַ���ĩβʱ
        if (i == s.length()) {
            resultSet.insert(path.substr(0, size));  // substr ������ȡ path �д���ʼλ�õ���ǰ���� size �Ĳ���
        } else {
            // ������ǰ�ַ���·���У�Ȼ��ݹ鴦����һ���ַ�
            path[size] = s[i];
            f(s, i + 1, path, size + 1, resultSet);
            // ��������ǰ�ַ���ֱ�ӵݹ鴦����һ���ַ�
            f(s, i + 1, path, size, resultSet);
        }
    }
};


//��������һ���������� nums �����п��ܰ����ظ�Ԫ�أ����㷵�ظ��������п��ܵ���� https://leetcode.cn/problems/subsets-ii/
//�� ���� �����ظ�����ϡ����صĴ��У���Ͽ��԰� ����˳�� ����
//�������룺nums = [1,2,2]  �����[[],[1],[1,2],[1,2,2],[2],[2,2]] 
//�ص㣺���ȥ��
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ans; // ���ڴ洢�����Ӽ�
        vector<int> path(nums.size()); // ���ڴ洢��ǰ�Ӽ�·��
        sort(nums.begin(), nums.end()); // ��������������Ա��ں����ȥ��
        f(nums, 0, path, 0, ans);
        return ans;
    }
private:
    void f(vector<int>& nums, int i, vector<int>& path, int size, vector<vector<int>>& ans) {
        if (i == nums.size()) {
            vector<int> cur(path.begin(), path.begin() + size); // ����ǰ·��ת��Ϊ�Ӽ�
            ans.push_back(cur); // ���Ӽ����뵽�������
        }else {
            int j = i + 1;
            while (j < nums.size() && nums[i] == nums[j]) {
                j++; // �ҵ���ͬԪ�صĽ���λ��
            }
            // ��ǰ��x��Ҫ0��
            f(nums, j, path, size, ans);
            // ��ǰ��x��Ҫ1����Ҫ2����Ҫ3��...������
            for (; i < j; i++) {
                path[size++] = nums[i];
                f(nums, j, path, size, ans);
            }
        }
    }
};

//����û���ظ������ֵ�ȫ���� https://leetcode.cn/problems/permutations/
//ֱ����ԭ�����н��н��� ʱ�临�Ӷ�O(n*n!)
class Solution {
private:
    void f(vector<vector<int>>& ans,int i,vector<int>& nums){
        if(i==nums.size()){
            ans.push_back(nums);
        }else{
            for(int j=i;j<nums.size();++j){
                swap(nums[i],nums[j]);// ������ǰԪ��������Ԫ��
                f(ans,i+1,nums); // �ݹ�������һ��Ԫ�ص�����
                swap(nums[j],nums[i]); // �ָ�ԭ����״̬������
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

//�ġ����ظ��������ȥ��ȫ���� https://leetcode.cn/problems/permutations-ii/
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
            ans.push_back(nums); // ����ǰ���м���������
        }else {
            unordered_set<int> set; // ���ڼ���ظ�Ԫ��
            for (int j = i; j < nums.size(); ++j) {
                // nums[j]û��������iλ�ã��Ż�ȥ����
                if (!set.count(nums[j])) {
                    set.insert(nums[j]);
                    swap(nums[i], nums[j]); // ������ǰԪ��������Ԫ��
                    f(nums, i + 1, ans); // �ݹ�������һ��Ԫ�ص�����
                    swap(nums[i], nums[j]); // �ָ�ԭ����״̬������
                }
            }
        }
    }
};

//�塢�õݹ麯������ջ   ʱ�临�Ӷ�ΪO(n*n)
int bottomOut(stack<int>& stack) {
    int ans = stack.top();// ��¼��ǰջ��Ԫ��
    stack.pop();  // �Ƴ�ջ��Ԫ��
    // ���ջ�ѿգ�˵���ղ��Ƴ���Ԫ����ջ��Ԫ�أ�������
    if (stack.empty()) {
        return ans;
    }else {
        // �����ݹ飬Ѱ�Ҳ�����ջ��Ԫ��
        int last = bottomOut(stack);
        // ��ջ��Ԫ��ѹ��ջ��
        stack.push(ans);
        // ����ջ��Ԫ��
        return last;
    }
}
void reverse(stack<int>& stack) {
    // �ݹ���ֹ���������ջΪ�գ�������ݹ�
    if (stack.empty()) {
        return;
    }
    // ��¼���Ƴ�ջ��Ԫ��
    int num = bottomOut(stack);
    // �ݹ���ã���ʣ���ջԪ������
    reverse(stack);
    // ��ջ��Ԫ������ѹ��ջ��
    stack.push(num);
}
 

//�����õݹ麯������ջ   ʱ�临�Ӷ�ΪO(n*n)
class Solution {
private:
    int deep(stack<int>& s) {//�õݹ�����ȡջ�Ĵ�С
        stack<int> temp;
        int depth = 0;
        // �ƶ�ջ�е�Ԫ�ص���ʱջ�����������
        while (!s.empty()) {
            temp.push(s.top());
            s.pop();
            depth++;
        }
        // ��Ԫ���ƶ���ԭջ
        while (!temp.empty()) {
            s.push(temp.top());
            temp.pop();
        }
        return depth;
    }
    int Getmax(stack<int>& s, int depth) {//�õݹ�����ȡջ�е����Ԫ��
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
    int times(stack<int>& s, int depth, int maxVal) {//�õݹ���ͳ�����Ԫ�س��ֵĴ���
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
    void down(stack<int>& s, int depth, int maxVal, int k) {//���õݹ齫���Ԫ��ȫ���ƶ���ջ��
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


//�ߡ�Tower of Hanoi https://leetcode.cn/problems/hanota-lcci/
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
            f(n, "��", "��", "��");
        }
    }
private:
    void f(int i, string from, string to, string other) {
        if (i == 1) {
            cout << "�ƶ�Բ�� 1 �� " << from << " �� " << to << endl;
        }else {
            f(i - 1, from, other, to);
            cout << "�ƶ�Բ�� " << i << " �� " << from << " �� " << to << endl;
            f(i - 1, other, to, from);
        }
    }
};