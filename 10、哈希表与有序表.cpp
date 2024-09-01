#include<iostream>
using namespace std;
/*哈希表（unordered_map） https://blog.csdn.net/Peealy/article/details/116895964
* 哈希表的用法（认为是集合，根据值来做key 或者 根据内存地址做key）
HashSet和HashMap原理一样，有无伴随数据(value)的区别
哈希表就是在关键字和存储位置之间建立对应关系，其中关键字和存储位置之间是通过散列函数建立关系，记为:Loc(i)=Hash(key i)。
增、删、改、查的时间复杂度为O(1)，但是大常数
所以当key的范围是固定的、可控的情况下，可以用数组结构替代哈希表结构

常见的散列函数：
1）线性定址法：直接取关键字的某个线性函数作为存储地址，散列函数为：Hash(key) = a × key + b
2）除留余数法：将关键字对某一小于散列表长度的数p取余的结果作为存储地址，散列函数为：Hash(key) = key mod p
3）平方取中法：对关键字取平方，然后将得到结果的中间几位作为存储地址；
4）折叠法：将关键字分割为几部分，然后将这几部分的叠加和作为存储地址。
通过以上方法构建的哈希表在理想的情况下能够做到一个关键字对应一个地址，但是实际情况是会有冲突发生，也就是散列函数会将多个关键字映射到同一个地址上。

地址冲突解决方法：
①线性探测法：当发生冲突时，就顺序查看下一个存储位置，如果位置为空闲状态，就将该关键字存储在该位置上，
如果还是发生冲突，就依次往后查看，当查看到存储空间的末尾时还是找不到空位置，就返回从头开始查看；
②平方探测法：不同于前面线性探测法依次顺序查看下一个位置是否能存储元素，平方探测的规则是以1^2, 2^2, 3^2,...，探测新的存储位置能否存储元素；
③再散列法：利用两个散列函数，当通过第一个散列函数得到关键字的存储地址发生冲突时，再利用第二个散列函数计算出地址增量，
地址计算方式如下：H_i = (Hash_1(key) + i * Hash_2(key)) % p
④伪随机数法： 当发生地址冲突时，加入一个随机数作为地址增量寻找新的存储地址，
地址计算方式如下：H_i = (Hash(key) + d_i) % p ,其中d_i为随机数
⑤拉链法：将具有相同存储地址的关键字链成一单链表，m个存储地址就设m个单链表，然后用一个数组将m个单链表的表头指针存储起来，形成一个动态的结构，
假设散列函数为 Hash(key) = key %13，其拉链存储结构为：https://i-blog.csdnimg.cn/blog_migrate/c08cc7f28bd9f7983c1a6691674532ad.png */

//如何使用STL库中的哈希表
//（1）导入头文件
#include<unordered_map>

//（2）哈希表的声明
unordered_map<elemType_1, elemType_2> var_name; //声明一个没有任何元素的哈希表，其中elemType_1和elemType_2是模板允许定义的类型
unordered_map<int, int> map;//定义一个键值对都为Int的哈希表

//（3）哈希表的初始化
//以上在声明哈希表的时候并没有给unordered_map传递任何参数，因此调用的是unordered_map的默认构造函数，生成一个空容器。初始化主要有一下几种方式：

//a）在定义哈希表的时候通过初始化列表中的元素初始化 :
unordered_map<int, int> hmap{ {{1,10},{2,12},{3,13}},3 /* 3为要创建的哈希表的元素个数，可不带 */};

//b）通过下标运算来添加元素:mapName[key]=value;
//但是这样的添加元素的方式会产生覆盖的问题,也就是当hmap中key为4的存储位置有值时，再用hmap[4]=value添加元素，会将原哈希表中key为4存储的元素覆盖
hmap[4] = 14;
hmap[5] = 15;
cout << hmap[4];  //结果为15

//c）通过insert()函数来添加元素:
//通过insert()函数来添加元素的结果和通过下标来添加元素的结果一样，不同的是insert()可以避免覆盖问题，insert()函数在同一个key中插入两次，第二次插入会失败
hmap.insert({ 5,15 });
hmap.insert({ 5,16 });
cout << hmap[5];  //结果为15

//d）复制构造，通过其他已初始化的哈希表来初始新的表:
unordered_map<int, int> hmap{ {1,10},{2,12},{3,13} };
unordered_map<int, int> hmap1(hmap);

//3. STL中哈希表的常用函数
//(1) begin()函数：该函数返回一个指向哈希表开始位置的迭代器
//	  end()函数：作用于begin函数相同，返回一个指向哈希表结尾位置的下一个元素的迭代器
unordered_map<int, int>::iterator iter_begin = hmap.begin(); //申请迭代器，并初始化为哈希表的起始位置
unordered_map<int, int>::iterator iter_end = hmap.end();//申请迭代器，并初始化为哈希表的末尾位置
//哈希表的遍历：
unordered_map<int, int> hmap{ {1,10},{2,12},{3,13} };
unordered_map<int, int>::iterator iter = hmap.begin();
for (; iter != hmap.end(); iter++) {
    cout << "key: " << iter->first << "value: " << iter->second << endl;
}

//(2) empty()函数：判断哈希表是否为空，空则返回true，非空返回false
bool isEmpty = hmap.empty();

//(3) size()函数：返回哈希表的大小
int size = hmap.size();

//(4) erase()函数： 删除某个位置的元素，或者删除某个位置开始到某个位置结束这一范围内的元素， 或者传入key值删除键值对
unordered_map<int, int> hmap{ {1,10},{2,12},{3,13} };
unordered_map<int, int>::iterator iter_begin = hmap.begin();
unordered_map<int, int>::iterator iter_end = hmap.end();
hmap.erase(iter_begin);  //删除开始位置的元素
hmap.erase(iter_begin, iter_end); //删除开始位置和结束位置之间的元素
hmap.erase(3); //删除key==3的键值对

//(5) at()函数：根据key查找哈希表中的元素
unordered_map<int, int> hmap{ {1,10},{2,12},{3,13} };
int elem = hmap.at(3);

//(6) clear()函数：清空哈希表中的元素
hmap.clear();

//(7) find()函数：以key作为参数寻找哈希表中的元素，如果哈希表中存在该key值则返回该位置上的迭代器，否则返回哈希表最后一个元素下一位置上的迭代器
unordered_map<int, int> hmap{ {1,10},{2,12},{3,13} };
unordered_map<int, int>::iterator iter;
iter = hmap.find(2); //返回key==2的迭代器
if (iter != hmap.end())  cout << iter->second;//可以通过iter->second访问该key对应的元素

//(8) count()函数： 统计某个key值对应的元素个数， 因为unordered_map不允许重复元素，所以返回值为0或1
int count = hmap.count(key);

//(9) bucket()函数：以key寻找哈希表中该元素的储存的bucket编号（unordered_map的源码是基于拉链式的哈希表，所以是通过一个个bucket存储元素）
int pos = hmap.bucket(key);
//    bucket_count()函数：该函数返回哈希表中存在的存储桶总数（一个存储桶可以用来存放多个元素，也可以不存放元素，并且bucket的个数大于等于元素个数）
int count = hmap.bucket_count();

/*有序表（map）https://blog.csdn.net/m0_56494923/article/details/123239292
有序表的用法（认为是集合，但是有序组织）
TreeSet和TreeMap原理一样，有无伴随数据的区别
增、删、改、查 + 很多和有序相关的操作(floor、ceilling等)，时间为O(log n)
有序表比较相同的东西会去重，如果不想去重就加入更多的比较策略（比较器定制）。堆不会去重。
*/

#include<map>
//1、map的定义
//单独定义一个map :
map<typename1, typename2> mp;//其中，typename1是键的类型，typename2是值的类型。
//注：如果是字符串到整型的映射，必须使用string而不能用char数组！
map<string, int> mp;//这是因为char数组作为数组，是不能被作为键值的。所以如果想用字符串做映射，必须用string。
//map内部是由红黑树实现的，在建立映射的过程中，会自动实现从小到大排序功能。

//2、map容器内元素的访问
//①、通过下标访问：mapName[key]=value;
map<char, int> mp;
mp['c'] = 20;
cout << mp['c'];	//答案输出20
//这样的添加元素的方式也会产生覆盖的问题

//②、通过迭代器访问：
//map迭代器的定义和其他STL容器迭代器定义的方式相同：
map<typename1, typename2>::iterator it;
//map可以使用it->first来访问键，it->second来访问值：
map<char, int> mp;
mp['a'] = 222;
mp['b'] = 333;
mp['c'] = 444;
for (map<char, int>::iterator it = mp.begin(); it != mp.end(); it++) {
	cout << it->first << " " << it->second << endl;
}

//3、map常用函数实例解析：
//①、find()：
//find(key)返回键为key映射的迭代器，时间复杂度为O(logN)，N为map中映射的个数：
map<char, int> mp;
mp['a'] = 222;
mp['b'] = 333;
mp['c'] = 444;
map<char, int>::iterator it = mp.find('b');
cout << it->first << " " << it->second;

//②、erase() :
//(a)、删除单个元素。
mp.erase(it)//it为需要删除的元素的迭代器。时间复杂度为O(1)
mp.erase(key)//key为要删除的映射的键。时间复杂度O(logN)
//(b)、删除一个区间内所有的元素。
mp.erase(first, last)//其中first为需要删除的区间的起始迭代器，last为需要删除的区间末尾迭代器的下一个地址，即为删除左闭右开的区间[first, last)。时间复杂度为O(last - first)：
mp.erase(mp.begin(), mp.end());

//③、size()：获得map中映射的对数，复杂度为O(1)。
mp.size();

//④、clear() :空map中的所有元素，复杂度为O(N)
mp.clear()

//⑤、count()函数： 统计某个key值对应的元素个数， 因为unordered_map不允许重复元素，所以返回值为0或1
int count = mp.count(key);

//⑥、empty()函数：判断哈希表是否为空，空则返回true，非空返回false
bool isEmpty = mp.empty();



// Integer、Long、Double、Float
// Byte、Short、Character、Boolean
// String等都有这个特征
String str1 = new String("Hello");
String str2 = new String("Hello");
// false，因为不同的内存地址
System.out.println(str1 == str2);
// true，因为它们的值是相同的
System.out.println(str1.equals(str2));