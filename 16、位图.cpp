//λͼ https://www.bilibili.com/video/BV1yr4y1Z7jb?vd_source=f8aeedc23d987bfb0dea78b38581fa28
//��ʵ������bit��ɵ����������ֵ����bit״̬1��0������ڡ������ڣ�ȡֵ�ʹ�ֵ��������λ����
//�����Ǳ���Ϊ������Χ�Ҳ��ܹ��󡣺ô��Ǽ���Ľ�ʡ�ռ䣬��Ϊ1������ֻռ��1��bit�Ŀռ䡣
//set����ĵڼ������֣�num/32	�����ֵĵڼ���bit��num%32

/*λͼ��ʵ��
Bitset(int n)����ʼ��λͼ�Ĵ�С��ֻ֧��0~n - 1�������ֵ���ɾ�Ĳ�
void add(int num)����num���뵽λͼ
void remove(int num)����num��λͼ��ɾ��
void reverse(int num)�����λͼ��û��num���ͼ��룻���λͼ����num����ɾ��
boolean contains(int num)����ѯnum�Ƿ���λͼ��
*/
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
using namespace std;
class Bitset {
public:
    vector<int> set;
    Bitset(int n) {
        set.resize((n + 31) / 32);// λͼ�Ĵ�СΪ (n + 31) / 32��ȷ��������n��bit
    }
    void add(int num) {// ��Ӳ�����������num��ӵ�������
        set[num / 32] |= 1 << (num % 32);// ���� | ����num��bitλ��Ϊ1
    }
    void remove(int num) {// ɾ��������������num�Ӽ������Ƴ�
        set[num / 32] &= ~(1 << (num % 32));// ����num��bitλ��Ϊ0
    }
    void reverse(int num) {// ��ת��������ת����num�Ĵ���״̬
        set[num / 32] ^= 1 << (num % 32);// ����num��bitȡ��
    }
    bool contains(int num) {// ������飬�������num�Ƿ�����ڼ�����
        // ����num��bit�Ƿ�Ϊ1��������򷵻�true�����򷵻�false
        return set[num / 32] >> (num % 32);
    }
};
//���ö�������֤
int main() {
    int n = 1000;
    int testTimes = 10000;
    cout << "���Կ�ʼ" << endl;
    Bitset bitSet(n);
    unordered_set<int> hashSet;//ֱ����HashSet���ԱȲ���
    cout << "���ý׶ο�ʼ" << endl;
    srand(time(0)); // ʹ�õ�ǰʱ����Ϊ�������
    for (int i = 0; i < testTimes; i++) {
        double decide = (double)rand() / RAND_MAX;
        int number = rand() % n;//0~n-1��������
        //�ȸ��ʵص��ø��ֲ���
        if (decide < 0.333) {
            bitSet.add(number);
            hashSet.insert(number);
        }
        else if (decide < 0.666) {
            bitSet.remove(number);
            hashSet.erase(number);
        }
        else {
            bitSet.reverse(number);
            if (hashSet.find(number) != hashSet.end()) {
                hashSet.erase(number);
            }
            else {
                hashSet.insert(number);
            }
        }
    }
    cout << "���ý׶ν���" << endl;
    cout << "��֤�׶ο�ʼ" << endl;
    for (int i = 0; i < n; ++i) {
        if (bitSet.contains(i) != (hashSet.find(i) != hashSet.end())) {
            cout << "������!" << endl;
        }
    }
    cout << "��֤�׶ν���" << endl;
    cout << "���Խ���" << endl;
    return 0;
}

/*���߲��� https://leetcode-cn.com/problems/design-bitset/
Bitset(int size) �� size ��λ��ʼ�� Bitset ������λ���� 0 ��
void fix(int idx) ���±�Ϊ idx ��λ�ϵ�ֵ����Ϊ 1 �����ֵ�Ѿ��� 1 ���򲻻ᷢ���κθı䡣
void unfix(int idx) ���±�Ϊ idx ��λ�ϵ�ֵ����Ϊ 0 �����ֵ�Ѿ��� 0 ���򲻻ᷢ���κθı䡣
void flip() ��ת Bitset ��ÿһλ�ϵ�ֵ�����仰˵������ֵΪ 0 ��λ������ 1 ����֮��Ȼ��
boolean all() ��� Bitset �� ÿһλ ��ֵ�Ƿ��� 1 �������������������� true �����򣬷��� false ��
boolean one() ��� Bitset �� �Ƿ� ����һλ ��ֵ�� 1 �������������������� true �����򣬷��� false ��
int count() ���� Bitset ��ֵΪ 1 ��λ�� ���� ��
String toString() ���� Bitset �ĵ�ǰ��������ע�⣬�ڽ���ַ����У��� i ���±괦���ַ�Ӧ���� Bitset �еĵ� i λһ�¡�
*/
#include <vector>
#include <string>
#include <sstream>
using namespace std;
class Bitset {
private:
    vector<int> set;
    int size;
    int zeros;
    int ones;
    bool reverse;
public:
    // ���캯������ʼ��λͼ
    Bitset(int n) : size(n), zeros(n), ones(0), reverse(false) {
        set.resize((n + 31) / 32);
    }
    // ������i����λͼ
    void fix(int i) {
        int index = i / 32;
        int bit = i % 32;
        if (!reverse) {
            // λͼδ��ת״̬
            if ((set[index] & (1 << bit)) == 0) {//ע�� & ���������ȼ����� == �� !=
                zeros--;
                ones++;
                set[index] |= (1 << bit);
            }
        }
        else {
            // λͼ��ת״̬
            if ((set[index] & (1 << bit)) != 0) {
                zeros--;
                ones++;
                set[index] ^= (1 << bit);
            }
        }
    }
    // ������i��λͼ���Ƴ�
    void unfix(int i) {
        int index = i / 32;
        int bit = i % 32;
        if (!reverse) {
            if ((set[index] & (1 << bit)) != 0) {
                ones--;
                zeros++;
                set[index] ^= (1 << bit);
            }
        }
        else {
            if ((set[index] & (1 << bit)) == 0) {
                ones--;
                zeros++;
                set[index] |= (1 << bit);
            }
        }
    }
    // ��ת����λͼ
    void flip() {
        reverse = !reverse;
        swap(zeros, ones);
    }
    // �������λ�Ƿ�Ϊ1
    bool all() {
        return ones == size;
    }
    // ����Ƿ�������һ��λΪ1
    bool one() {
        return ones > 0;
    }
    // ����λͼ��Ϊ1��λ������
    int count() {
        return ones;
    }
    // ����λͼ���ַ�����ʾ
    string toString() {
        ostringstream builder;
        for (int i = 0, k = 0; i < size; k++) {
            //i ��ȫ�ֵ�λ������ͨ�������������֪����ǰ������ǵڼ�λ��
            int number = set[k]; //number �ǵ�ǰ��32λ��������ʾ32��λ����Ϣ��
            for (int j = 0; j < 32 && i < size; j++, i++) {
                int status = (number >> j) & 1;
                status ^= reverse ? 1 : 0;
                builder << status;
            }
        }
        return builder.str();
    }
};
