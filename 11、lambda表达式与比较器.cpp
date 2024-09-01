//Lambda表达式  https://blog.csdn.net/m0_60134435/article/details/136151698
/*Lambda表达式相比于普通函数和普通类，有以下几个优点：
简洁：Lambda表达式可以省略函数名和类名，直接定义和使用，使得代码更加简洁和清晰。
灵活：Lambda表达式可以捕获外部变量，可以作为函数参数，也可以作为函数返回值，使得代码更加灵活和方便。
安全：Lambda表达式可以控制外部变量的访问方式，可以避免全局变量的定义，可以避免悬空指针和无效引用的产生，使得代码更加安全和稳定。*/

//一、Lambda表达式的基本语法
//Lambda表达式是一种在被调用的位置或作为参数传递给函数的位置定义匿名函数对象（闭包）的简便方法。
[capture list](parameter list) -> return type{ function body }
[捕获列表](参数列表) -> 返回值类型{函数体}
/*其中：
①、capture list（捕获列表），用于指定 Lambda表达式可以访问的外部变量，以及是按值还是按引用的方式访问。
捕获列表可以为空，表示不访问任何外部变量，也可以使用默认捕获模式 & 或 = 来表示 按引用 或 按值 捕获所有外部变量，
还可以混合使用具体的变量名和默认捕获模式来指定不同的捕获方式。
②、parameter list（参数列表），用于表示 Lambda表达式的参数，可以为空，表示没有参数，也可以和普通函数一样指定参数的类型和名称。
③、return type（返回值类型），用于指定 Lambda表达式的返回值类型，可以省略，也可以使用->符号显式指定。
④、function body 是函数体，用于表示 Lambda表达式的具体逻辑，可以是一条语句，也可以是多条语句。*/

//二、Lambda表达式的捕获方式
//1、值捕获：在捕获列表中使用变量名，表示将该变量的值拷贝到 Lambda 表达式中，作为一个数据成员。
// 值捕获的变量在 Lambda 表达式定义时就已经确定，不会随着外部变量的变化而变化。值捕获的变量默认不能在 Lambda 表达式中修改，除非使用 mutable 关键字。
int x = 10;
auto f = [x](int y) -> int { return x + y; }; // 值捕获 x
x = 20; // 修改外部的 x
cout << f(5) << endl; // 输出 15，不受外部 x 的影响

//2、引用捕获：在捕获列表中使用 & 加变量名，表示将该变量的引用传递到 Lambda 表达式中，作为一个数据成员。
// 引用捕获的变量在 Lambda 表达式调用时才确定，会随着外部变量的变化而变化。
// 引用捕获的变量可以在 Lambda 表达式中修改，但要注意生命周期的问题，避免悬空引用的出现。
int x = 10;
auto f = [&x](int y) -> int { return x + y; }; // 引用捕获 x
x = 20; // 修改外部的 x
cout << f(5) << endl; // 输出 25，受外部 x 的影响

//3、隐式捕获：在捕获列表中使用 = 或 & ，表示按值或按引用捕获 Lambda 表达式中使用的所有外部变量。
// 这种方式可以简化捕获列表的书写，避免过长或遗漏。隐式捕获可以和显式捕获混合使用，但不能和同类型的显式捕获一起使用。
int x = 10;
int y = 20;
auto f = [=, &y](int z) -> int { return x + y + z; }; // 隐式按值捕获 x，显式按引用捕获 y
x = 30; // 修改外部的 x
y = 40; // 修改外部的 y
cout << f(5) << endl; // 输出 55，不受外部 x 的影响，受外部 y 的影响

//4、初始化捕获：在捕获列表中使用初始化表达式，从而在捕获列表中创建并初始化一个新的变量，而不是捕获一个已存在的变量。
// 这种方式可以使用 auto 关键字来推导类型，也可以显式指定类型。可以用来捕获只移动的变量，或者捕获 this 指针的值。
int x = 10;
auto f = [z = x + 5](int y) -> int { return z + y; }; // 初始化捕获 z，相当于值捕获 x + 5
x = 20; // 修改外部的 x
cout << f(5) << endl; // 输出 20，不受外部 x 的影响


//下面我们通过一些示例来展示 Lambda表达式的用法和效果。
//示例一：使用 Lambda表达式定义简单的匿名函数
// 定义一个 Lambda表达式，计算两个数的和
auto plus = [](int a, int b) -> int { return a + b; };
cout << plus(3, 4) << endl; // 调用 Lambda表达式 输出 7
// 定义一个 Lambda表达式，判断一个数是否为奇数
auto is_odd = [](int n) { return n % 2 == 1; };
// 调用 Lambda表达式
cout << is_odd(5) << endl; // 输出 1
cout << is_odd(6) << endl; // 输出 0

//示例二：使用 Lambda表达式作为函数参数
//我们可以使用 Lambda表达式作为函数的参数，这样可以方便地定义和传递一些简单的函数对象，例如自定义排序规则、自定义比较函数等。
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
    // 使用 Lambda表达式，根据 Item 中的成员 a 升序排序
    sort(vec.begin(), vec.end(), [](const Item& v1, const Item& v2) { return v1.a < v2.a; });
    // 使用 Lambda表达式，打印 vec 中的 Item 成员
    for_each(vec.begin(), vec.end(), [](const Item& item) { cout << item.a << " " << item.b << endl; });
    return 0;
}

//示例三：使用 Lambda表达式作为函数返回值
//我们可以使用 Lambda表达式作为函数的返回值，这样可以方便地定义和返回一些简单的函数对象，例如工厂函数、闭包函数等。例如：
#include <iostream>
using namespace std;
// 定义一个函数，返回一个 Lambda表达式，实现两个数的加法
auto make_adder(int x){
    return [x](int y) -> int { return x + y; };
}
int main(){
    // 调用函数，得到一个 Lambda表达式
    auto add5 = make_adder(5);
    // 调用 Lambda表达式
    cout << add5(10) << endl; // 输出 15
    return 0;
}


//三、Lambda表达式与普通函数和普通类的关系
//Lambda表达式它本质上也是一种函数对象，也就是重载了 operator() 的类的对象，每一个 Lambda表达式都对应一个唯一的匿名类。
//捕获列表实际上是匿名类的数据成员，参数列表和返回值类型实际上是匿名类的 operator() 的参数列表和返回值类型，函数体实际上是匿名类的 operator() 的函数体。
//因此Lambda表达式可以赋值给一个合适的函数指针或函数引用，也可以作为模板参数传递给一个泛型函数或类。例如：
#include <iostream>
using namespace std;
typedef int (*func_ptr) (int, int);// 定义一个函数指针类型
void apply(func_ptr f, int a, int b){// 定义一个函数，接受一个函数指针作为参数
    cout << f(a, b) << endl;
}
int main(){
    auto mul = [](int x, int y) -> int { return x * y; };
    // 将 Lambda表达式赋值给一个函数指针
    func_ptr fp = mul;
    // 调用函数，传递函数指针
    apply(fp, 3, 4); // 输出 12
    return 0;
}


//捕获 this 指针：C++17 允许在 Lambda表达式的捕获列表中使用 * this，从而实现捕获 this 指针，即可以在 Lambda表达式中访问当前对象的成员变量和成员函数。例如：
#include <iostream>
using namespace std;
class Test{
public:
    Test(int n) : num(n) {} // 构造函数，初始化 num
    void show() {// 成员函数，显示 num
        cout << num << endl;
    }
    void add(int x) {// 成员函数，增加 num
        // 定义一个 Lambda表达式，捕获 this 指针
        auto f = [*this]() { return num + x; };
        // 调用 Lambda表达式
        cout << f() << endl;
    }
private:
    int num; // 成员变量，存储一个整数
};
int main(){
    Test t(10); // 创建一个 Test 对象
    t.show(); // 调用成员函数，输出 10
    t.add(5); // 调用成员函数，输出 15
    return 0;
}

//比较器：定制比较策略
//任何比较器都默认:如果返回负数认为o1的优先级更高,如果返回正数认为o2的优先级更高,返回0二者优先级一致
//利用这个设定，可以定制优先级怎么确定，也就是怎么比较。此时不再有大小的概念，就是优先级的概念。
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
class Employee {// 员工类
public:
    int company; // 公司编号
    int age;     // 年龄
    Employee(int c, int a) : company(c), age(a) {}
    // 重载<<操作符，便于打印
    friend std::ostream& operator<<(std::ostream& os, const Employee& e) {
        os << e.company << " , " << e.age;
        return os;
    }
};
struct EmployeeComparator {// 员工比较器，根据年龄进行比较
    bool operator()(const Employee& e1, const Employee& e2) const {
        return e1.age < e2.age;
    }
};
int main() {
    Employee s1(2, 27); Employee s2(1, 60); Employee s3(4, 19);
    Employee s4(3, 23); Employee s5(1, 35); Employee s6(3, 55);
    std::vector<Employee> arr = { s1, s2, s3, s4, s5, s6 };

    // 使用EmployeeComparator按年龄排序
    std::sort(arr.begin(), arr.end(), EmployeeComparator());
    for (const Employee& e : arr) {
        std::cout << e << std::endl;
    }

    // 使用lambda函数按年龄降序排序
    std::sort(arr.begin(), arr.end(), [](const Employee& a, const Employee& b) {
        return b.age < a.age;
        });
    for (const Employee& e : arr) {
        std::cout << e << std::endl;
    }

    // 先按公司编号排序，然后按年龄排序
    std::sort(arr.begin(), arr.end(), [](const Employee& a, const Employee& b) {
        return a.company != b.company ? a.company < b.company : a.age < b.age;
        });
    for (const Employee& e : arr) {
        std::cout << e << std::endl;
    }

    // 使用std::set和EmployeeComparator进行去重
    std::set<Employee, EmployeeComparator> treeSet1(arr.begin(), arr.end());
    std::cout << treeSet1.size() << std::endl;

    // 向集合中添加一个重复的员工
    treeSet1.insert(Employee(2, 27));
    std::cout << treeSet1.size() << std::endl;

    // 使用更复杂的比较器，避免基于内存地址的去重
    auto complexComparator = [](const Employee& a, const Employee& b) {
        if (a.company != b.company) return a.company < b.company;
        if (a.age != b.age) return a.age < b.age;
        return &a < &b; // 比较内存地址
        };
    std::set<Employee, decltype(complexComparator)> treeSet2(arr.begin(), arr.end(), complexComparator);
    std::cout << treeSet2.size() << std::endl;

    // 向使用复杂比较器的集合中添加一个重复的员工
    treeSet2.insert(Employee(2, 27));
    std::cout << treeSet2.size() << std::endl;

    // PriorityQueue不会去重，不再展示
    return 0;
}
