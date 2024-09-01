#include<vector>
#include<string>
#include<set>
#include<unordered_set>
#include<algorithm>
#include<stack>
#include<iostream>
#include<map>
using namespace std;
/*Ƕ��������Ľ�����·
��Ź���: 
����ȫ�ֱ��� int where
�ݹ麯��f(i) : s[i..]����iλ�ó�����ʼ���������� �ַ�����ֹ �� Ƕ��������ֹ �ͷ���
����ֵ��f(i)������һ�εĽ��
f(i)�ڷ���ǰ����ȫ�ֱ���where�����ϼ�����ͨ��where֪����������ʲôλ�ã���������

ִ��ϸ��:
���f(i)���� Ƕ��������ʼ���͵����¼��ݹ�ȥ����Ƕ�ף��¼��Ḻ��Ƕ�ײ��ֵļ�����
f(i)�¼�������ɺ�f(i)���Ը����¼����µ�ȫ�ֱ���where��֪���ô�ʲôλ�ü�������*/

//һ������Ƕ�׵ı��ʽ��ֵ https://leetcode.cn/problems/basic-calculator-iii/
/*ʵ��һ�������ļ�����������򵥵ı��ʽ�ַ��������ʽ�ַ���ֻ�����Ǹ������� + �� - �� * �� / ��������������(��������)�Ϳո�����������Ҫ���½ضϡ�
����Լٶ��������ַ���������Ч�ġ����е��м����ķ�ΧΪ[-2147483648��2147483647]*/
class Solution {
private:
    int where;
    // s[i....] ��ʼ���㣬�����ַ�����ֹ�������� ')' ֹͣ
    // ����: �Լ��������һ�Σ�����Ľ��
    // ����֮ǰ�����³�Ա���� where��Ϊ�����κ���֪�����ļ�����
    int f(const string& s, int i) {
        int cur = 0;
        vector<int> numbers;//����ջ
        vector<char> ops;//�����ջ
        while (i < s.length() && s[i] != ')') {
            if (isdigit(s[i])) {  // �����ǰ�ַ�������
                cur = cur * 10 + (s[i++] - '0');
            }else if (s[i] != '(') {  // �����ǰ�ַ�������� (+, -, *, /)
                push(numbers, ops, cur, s[i++]);
                cur = 0;
            }else {  // ��������������� '('
                cur = f(s, i + 1);  // �ݹ鴦�������ڵı��ʽ
                i = where + 1;  // �������������� ')'
            }
        }
        push(numbers, ops, cur, '+');  // �����һ������ѹ��ջ
        where = i;  // ����λ������
        return compute(numbers, ops);  // ���㲢���ؽ��
    }
    // ����ǰ���ֺͲ�����ѹ��ջ�У��������ȼ���������*��/��
    void push(vector<int>& numbers, vector<char>& ops, int cur, char op) {
        int n = numbers.size();
        if (n == 0 || ops[n - 1] == '+' || ops[n - 1] == '-') {
            numbers.push_back(cur);
            ops.push_back(op);
        }else {  // �������ȼ���������*��/��
            int topNumber = numbers[n - 1];
            char topOp = ops[n - 1];
            if (topOp == '*') {
                numbers[n - 1] = topNumber * cur;
            }else {
                numbers[n - 1] = topNumber / cur;
            }
            ops[n - 1] = op;  // ���²�����
        }
    }
    // ������������ջ�е����ֺͲ�����
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
        where = 0;  // ��ʼ�� where ����
        return f(str, 0);  // ���ַ����ĵ�һ���ַ���ʼ����
    }
};

//��������Ƕ�׵��ַ������� https://leetcode.cn/problems/decode-string/
/*����һ������������ַ������������������ַ�����
�������Ϊ: k[encoded_string]����ʾ���з������ڲ��� encoded_string �����ظ� k �Ρ�ע�� k ��֤Ϊ��������
�������Ϊ�����ַ���������Ч�ģ������ַ�����û�ж���Ŀո�������ķ��������Ƿ��ϸ�ʽҪ��ġ�
���⣬�������Ϊԭʼ���ݲ��������֣����е�����ֻ��ʾ�ظ��Ĵ��� k �����粻������� 3a �� 2[4] �����롣*/
class Solution {
private:
    string decode(const string& s, int& i) {//i�����ô��ݣ�����ʡȥ��ȫ�ֱ���
        string result;
        while (i < s.length() && s[i] != ']') {
            if (isalpha(s[i])) {//s[i]�������ĸ��ֱ�Ӽӵ�����
                result += s[i++];
            }else if (isdigit(s[i])) {//s[i]���������
                int cnt = 0;
                while (isdigit(s[i])) {
                    cnt = cnt * 10 + (s[i++] - '0');
                }//�Ȼ�ȡ�ظ��Ĵ���
                i++; // ���� '['
                string parsedStr = decode(s, i);
                i++; // ���� ']'
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
            if (isalpha(s[i])) {  // �������ĸ��ֱ����ӵ�����ַ���
                path += s[i++];
            }else if (isdigit(s[i])) {  // ��������֣������ظ�����
                cnt = cnt * 10 + s[i++] - '0';
            }else {
                // ���� '[' ʱ�ݹ鴦��
                path += get(cnt, f(s, i + 1));
                i = where + 1;  // ���µ�ǰλ��
            }
        }
        where = i;  // ����ȫ�ֱ�����ָ��ǰ������λ��
        return path;
    }
    // ���ַ���str�ظ�cnt��
    string get(int& cnt, const string& str) {
        string result;
        for (; cnt > 0; cnt--) {
            result += str;
        }
        return result;
    }
public:
    int where;  // ȫ�ֱ��������ڼ�¼���������еĵ�ǰλ��
    string decodeString(const string& str) {
        where = 0;
        return f(str, 0);
    }
};

//��������Ƕ�׵ķ���ʽ��ԭ������ https://leetcode.cn/problems/number-of-atoms/description/
class Solution {
private:
    int where = 0;  // ȫ�ֱ��������ٽ�����λ��
    // �ݹ麯���������ַ����е�Ԫ�ؼ����ţ�����Ԫ�ؼ����������
    map<string, int> f(const string& s, int i) {
        map<string, int> ans;  // �洢��ǰ������Ԫ�ؼ������
        string name;  // ��ǰԪ�ص�����
        map<string, int> pre;  // �洢�����ڽ�����Ԫ�ؼ������
        int cnt = 0;  // ��ǰԪ�صļ���
        // �����ַ���
        while (i < s.length() && s[i] != ')') {
            if (isupper(s[i]) || s[i] == '(') {
                // ������д��ĸ�� '('
                fill(ans, name, pre, cnt);  // ���� ans
                name.clear();  // ����Ԫ������
                pre.clear();  // ���������ڵ�Ԫ�ؼ���
                cnt = 0;  // ���ü���
                if (isupper(s[i])) {
                    // ������д��ĸ����ʾԪ�����ƵĿ�ʼ
                    name += s[i++];
                }else {
                    // ���� '('���ݹ���������ڵĲ���
                    pre = f(s, i + 1);
                    i = where + 1;  // ���µ�ǰλ��
                }
            }else if (islower(s[i])) {
                name += s[i++];// ����Сд��ĸ���������Ԫ������
            }else {
                // �������֣����㵱ǰԪ�صļ���
                cnt = cnt * 10 + s[i++] - '0';
            }
        }
        // ���� ans
        fill(ans, name, pre, cnt);
        where = i;  // ����ȫ�ֱ�����ָ��ǰ������λ��
        return ans;
    }
    // ��Ԫ�ؼ��������䵽 ans ��
    void fill(map<string, int>& ans, const string& name, const map<string, int>& pre, int cnt) {
        if (!name.empty() || !pre.empty()) {
            cnt = (cnt == 0) ? 1 : cnt;  // ������������ļ���Ϊ 0��������Ϊ 1
            if (!name.empty()) {
                // ��������û�����ֵ�Ԫ�أ�����������µ� ans ��
                ans[name] += cnt;
            }else {
                // ���û��û�����ֵ�Ԫ�أ����������ڵ�Ԫ��
                for (const auto& [key, value] : pre) {
                    ans[key] += value * cnt;  // ����Ԫ�ؼ���
                }
            }
        }
    }
public:
    string countOfAtoms(const string& str) {
        auto map = f(str, 0);  
        string ans;
        for (const auto& [key, cnt] : map) {
            ans += key;  // ���Ԫ������
            if (cnt > 1) {  // ����������� 1����Ӽ���ֵ
                ans += to_string(cnt);
            }
        }
        return ans;
    }
};