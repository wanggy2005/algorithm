//Lambda���ʽ  https://blog.csdn.net/m0_60134435/article/details/136151698
/*Lambda���ʽ�������ͨ��������ͨ�࣬�����¼����ŵ㣺
��ࣺLambda���ʽ����ʡ�Ժ�������������ֱ�Ӷ����ʹ�ã�ʹ�ô�����Ӽ���������
��Lambda���ʽ���Բ����ⲿ������������Ϊ����������Ҳ������Ϊ��������ֵ��ʹ�ô���������ͷ��㡣
��ȫ��Lambda���ʽ���Կ����ⲿ�����ķ��ʷ�ʽ�����Ա���ȫ�ֱ����Ķ��壬���Ա�������ָ�����Ч���õĲ�����ʹ�ô�����Ӱ�ȫ���ȶ���*/

//һ��Lambda���ʽ�Ļ����﷨
//Lambda���ʽ��һ���ڱ����õ�λ�û���Ϊ�������ݸ�������λ�ö��������������󣨱հ����ļ�㷽����
[capture list](parameter list) -> return type{ function body }
[�����б�](�����б�) -> ����ֵ����{������}
/*���У�
�١�capture list�������б�������ָ�� Lambda���ʽ���Է��ʵ��ⲿ�������Լ��ǰ�ֵ���ǰ����õķ�ʽ���ʡ�
�����б����Ϊ�գ���ʾ�������κ��ⲿ������Ҳ����ʹ��Ĭ�ϲ���ģʽ & �� = ����ʾ ������ �� ��ֵ ���������ⲿ������
�����Ի��ʹ�þ���ı�������Ĭ�ϲ���ģʽ��ָ����ͬ�Ĳ���ʽ��
�ڡ�parameter list�������б������ڱ�ʾ Lambda���ʽ�Ĳ���������Ϊ�գ���ʾû�в�����Ҳ���Ժ���ͨ����һ��ָ�����������ͺ����ơ�
�ۡ�return type������ֵ���ͣ�������ָ�� Lambda���ʽ�ķ���ֵ���ͣ�����ʡ�ԣ�Ҳ����ʹ��->������ʽָ����
�ܡ�function body �Ǻ����壬���ڱ�ʾ Lambda���ʽ�ľ����߼���������һ����䣬Ҳ�����Ƕ�����䡣*/

//����Lambda���ʽ�Ĳ���ʽ
//1��ֵ�����ڲ����б���ʹ�ñ���������ʾ���ñ�����ֵ������ Lambda ���ʽ�У���Ϊһ�����ݳ�Ա��
// ֵ����ı����� Lambda ���ʽ����ʱ���Ѿ�ȷ�������������ⲿ�����ı仯���仯��ֵ����ı���Ĭ�ϲ����� Lambda ���ʽ���޸ģ�����ʹ�� mutable �ؼ��֡�
int x = 10;
auto f = [x](int y) -> int { return x + y; }; // ֵ���� x
x = 20; // �޸��ⲿ�� x
cout << f(5) << endl; // ��� 15�������ⲿ x ��Ӱ��

//2�����ò����ڲ����б���ʹ�� & �ӱ���������ʾ���ñ��������ô��ݵ� Lambda ���ʽ�У���Ϊһ�����ݳ�Ա��
// ���ò���ı����� Lambda ���ʽ����ʱ��ȷ�����������ⲿ�����ı仯���仯��
// ���ò���ı��������� Lambda ���ʽ���޸ģ���Ҫע���������ڵ����⣬�����������õĳ��֡�
int x = 10;
auto f = [&x](int y) -> int { return x + y; }; // ���ò��� x
x = 20; // �޸��ⲿ�� x
cout << f(5) << endl; // ��� 25�����ⲿ x ��Ӱ��

//3����ʽ�����ڲ����б���ʹ�� = �� & ����ʾ��ֵ�����ò��� Lambda ���ʽ��ʹ�õ������ⲿ������
// ���ַ�ʽ���Լ򻯲����б����д�������������©����ʽ������Ժ���ʽ������ʹ�ã������ܺ�ͬ���͵���ʽ����һ��ʹ�á�
int x = 10;
int y = 20;
auto f = [=, &y](int z) -> int { return x + y + z; }; // ��ʽ��ֵ���� x����ʽ�����ò��� y
x = 30; // �޸��ⲿ�� x
y = 40; // �޸��ⲿ�� y
cout << f(5) << endl; // ��� 55�������ⲿ x ��Ӱ�죬���ⲿ y ��Ӱ��

//4����ʼ�������ڲ����б���ʹ�ó�ʼ�����ʽ���Ӷ��ڲ����б��д�������ʼ��һ���µı����������ǲ���һ���Ѵ��ڵı�����
// ���ַ�ʽ����ʹ�� auto �ؼ������Ƶ����ͣ�Ҳ������ʽָ�����͡�������������ֻ�ƶ��ı��������߲��� this ָ���ֵ��
int x = 10;
auto f = [z = x + 5](int y) -> int { return z + y; }; // ��ʼ������ z���൱��ֵ���� x + 5
x = 20; // �޸��ⲿ�� x
cout << f(5) << endl; // ��� 20�������ⲿ x ��Ӱ��


//��������ͨ��һЩʾ����չʾ Lambda���ʽ���÷���Ч����
//ʾ��һ��ʹ�� Lambda���ʽ����򵥵���������
// ����һ�� Lambda���ʽ�������������ĺ�
auto plus = [](int a, int b) -> int { return a + b; };
cout << plus(3, 4) << endl; // ���� Lambda���ʽ ��� 7
// ����һ�� Lambda���ʽ���ж�һ�����Ƿ�Ϊ����
auto is_odd = [](int n) { return n % 2 == 1; };
// ���� Lambda���ʽ
cout << is_odd(5) << endl; // ��� 1
cout << is_odd(6) << endl; // ��� 0

//ʾ������ʹ�� Lambda���ʽ��Ϊ��������
//���ǿ���ʹ�� Lambda���ʽ��Ϊ�����Ĳ������������Է���ض���ʹ���һЩ�򵥵ĺ������������Զ�����������Զ���ȽϺ����ȡ�
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct Item{
    Item(int aa, int bb) : a(aa), b(bb) {}
    int a;
    int b;
};
int main(){
    vector<Item> vec;
    vec.push_back(Item(1, 19));
    vec.push_back(Item(10, 3));
    vec.push_back(Item(3, 7));
    vec.push_back(Item(8, 12));
    // ʹ�� Lambda���ʽ������ Item �еĳ�Ա a ��������
    sort(vec.begin(), vec.end(), [](const Item& v1, const Item& v2) { return v1.a < v2.a; });
    // ʹ�� Lambda���ʽ����ӡ vec �е� Item ��Ա
    for_each(vec.begin(), vec.end(), [](const Item& item) { cout << item.a << " " << item.b << endl; });
    return 0;
}

//ʾ������ʹ�� Lambda���ʽ��Ϊ��������ֵ
//���ǿ���ʹ�� Lambda���ʽ��Ϊ�����ķ���ֵ���������Է���ض���ͷ���һЩ�򵥵ĺ����������繤���������հ������ȡ����磺
#include <iostream>
using namespace std;
// ����һ������������һ�� Lambda���ʽ��ʵ���������ļӷ�
auto make_adder(int x){
    return [x](int y) -> int { return x + y; };
}
int main(){
    // ���ú������õ�һ�� Lambda���ʽ
    auto add5 = make_adder(5);
    // ���� Lambda���ʽ
    cout << add5(10) << endl; // ��� 15
    return 0;
}


//����Lambda���ʽ����ͨ��������ͨ��Ĺ�ϵ
//Lambda���ʽ��������Ҳ��һ�ֺ�������Ҳ���������� operator() ����Ķ���ÿһ�� Lambda���ʽ����Ӧһ��Ψһ�������ࡣ
//�����б�ʵ����������������ݳ�Ա�������б�ͷ���ֵ����ʵ������������� operator() �Ĳ����б�ͷ���ֵ���ͣ�������ʵ������������� operator() �ĺ����塣
//���Lambda���ʽ���Ը�ֵ��һ�����ʵĺ���ָ��������ã�Ҳ������Ϊģ��������ݸ�һ�����ͺ������ࡣ���磺
#include <iostream>
using namespace std;
typedef int (*func_ptr) (int, int);// ����һ������ָ������
void apply(func_ptr f, int a, int b){// ����һ������������һ������ָ����Ϊ����
    cout << f(a, b) << endl;
}
int main(){
    auto mul = [](int x, int y) -> int { return x * y; };
    // �� Lambda���ʽ��ֵ��һ������ָ��
    func_ptr fp = mul;
    // ���ú��������ݺ���ָ��
    apply(fp, 3, 4); // ��� 12
    return 0;
}


//���� this ָ�룺C++17 ������ Lambda���ʽ�Ĳ����б���ʹ�� * this���Ӷ�ʵ�ֲ��� this ָ�룬�������� Lambda���ʽ�з��ʵ�ǰ����ĳ�Ա�����ͳ�Ա���������磺
#include <iostream>
using namespace std;
class Test{
public:
    Test(int n) : num(n) {} // ���캯������ʼ�� num
    void show() {// ��Ա��������ʾ num
        cout << num << endl;
    }
    void add(int x) {// ��Ա���������� num
        // ����һ�� Lambda���ʽ������ this ָ��
        auto f = [*this]() { return num + x; };
        // ���� Lambda���ʽ
        cout << f() << endl;
    }
private:
    int num; // ��Ա�������洢һ������
};
int main(){
    Test t(10); // ����һ�� Test ����
    t.show(); // ���ó�Ա��������� 10
    t.add(5); // ���ó�Ա��������� 15
    return 0;
}

//�Ƚ��������ƱȽϲ���
//�καȽ�����Ĭ��:������ظ�����Ϊo1�����ȼ�����,�������������Ϊo2�����ȼ�����,����0�������ȼ�һ��
//��������趨�����Զ������ȼ���ôȷ����Ҳ������ô�Ƚϡ���ʱ�����д�С�ĸ���������ȼ��ĸ��
#include<iostream>
#include<set>
using namespace std;
class employee {
public:
    int age;
    int company;
    employee(int c,int a):company(c),age(a){}
};
struct employeeComparator {
    bool operator()(const employee& o1, const employee& o2)const {
        return o1.age - o2.age;
    }
};
int main() {
    set<employee
}


#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
class Employee {// Ա����
public:
    int company; // ��˾���
    int age;     // ����
    Employee(int c, int a) : company(c), age(a) {}
    // ����<<�����������ڴ�ӡ
    friend std::ostream& operator<<(std::ostream& os, const Employee& e) {
        os << e.company << " , " << e.age;
        return os;
    }
};
struct EmployeeComparator {// Ա���Ƚ���������������бȽ�
    bool operator()(const Employee& e1, const Employee& e2) const {
        return e1.age < e2.age;
    }
};
int main() {
    Employee s1(2, 27); Employee s2(1, 60); Employee s3(4, 19);
    Employee s4(3, 23); Employee s5(1, 35); Employee s6(3, 55);
    std::vector<Employee> arr = { s1, s2, s3, s4, s5, s6 };

    // ʹ��EmployeeComparator����������
    std::sort(arr.begin(), arr.end(), EmployeeComparator());
    for (const Employee& e : arr) {
        std::cout << e << std::endl;
    }

    // ʹ��lambda���������併������
    std::sort(arr.begin(), arr.end(), [](const Employee& a, const Employee& b) {
        return b.age < a.age;
        });
    for (const Employee& e : arr) {
        std::cout << e << std::endl;
    }

    // �Ȱ���˾�������Ȼ����������
    std::sort(arr.begin(), arr.end(), [](const Employee& a, const Employee& b) {
        return a.company != b.company ? a.company < b.company : a.age < b.age;
        });
    for (const Employee& e : arr) {
        std::cout << e << std::endl;
    }

    // ʹ��std::set��EmployeeComparator����ȥ��
    std::set<Employee, EmployeeComparator> treeSet1(arr.begin(), arr.end());
    std::cout << treeSet1.size() << std::endl;

    // �򼯺������һ���ظ���Ա��
    treeSet1.insert(Employee(2, 27));
    std::cout << treeSet1.size() << std::endl;

    // ʹ�ø����ӵıȽ�������������ڴ��ַ��ȥ��
    auto complexComparator = [](const Employee& a, const Employee& b) {
        if (a.company != b.company) return a.company < b.company;
        if (a.age != b.age) return a.age < b.age;
        return &a < &b; // �Ƚ��ڴ��ַ
        };
    std::set<Employee, decltype(complexComparator)> treeSet2(arr.begin(), arr.end(), complexComparator);
    std::cout << treeSet2.size() << std::endl;

    // ��ʹ�ø��ӱȽ����ļ��������һ���ظ���Ա��
    treeSet2.insert(Employee(2, 27));
    std::cout << treeSet2.size() << std::endl;

    // PriorityQueue����ȥ�أ�����չʾ
    return 0;
}
