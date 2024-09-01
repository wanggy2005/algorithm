#include<iostream>
using namespace std;
/*��ϣ��unordered_map�� https://blog.csdn.net/Peealy/article/details/116895964
* ��ϣ����÷�����Ϊ�Ǽ��ϣ�����ֵ����key ���� �����ڴ��ַ��key��
HashSet��HashMapԭ��һ�������ް�������(value)������
��ϣ������ڹؼ��ֺʹ洢λ��֮�佨����Ӧ��ϵ�����йؼ��ֺʹ洢λ��֮����ͨ��ɢ�к���������ϵ����Ϊ:Loc(i)=Hash(key i)��
����ɾ���ġ����ʱ�临�Ӷ�ΪO(1)�����Ǵ���
���Ե�key�ķ�Χ�ǹ̶��ġ��ɿص�����£�����������ṹ�����ϣ��ṹ

������ɢ�к�����
1�����Զ�ַ����ֱ��ȡ�ؼ��ֵ�ĳ�����Ժ�����Ϊ�洢��ַ��ɢ�к���Ϊ��Hash(key) = a �� key + b
2�����������������ؼ��ֶ�ĳһС��ɢ�б��ȵ���pȡ��Ľ����Ϊ�洢��ַ��ɢ�к���Ϊ��Hash(key) = key mod p
3��ƽ��ȡ�з����Թؼ���ȡƽ����Ȼ�󽫵õ�������м伸λ��Ϊ�洢��ַ��
4���۵��������ؼ��ַָ�Ϊ�����֣�Ȼ���⼸���ֵĵ��Ӻ���Ϊ�洢��ַ��
ͨ�����Ϸ��������Ĺ�ϣ���������������ܹ�����һ���ؼ��ֶ�Ӧһ����ַ������ʵ������ǻ��г�ͻ������Ҳ����ɢ�к����Ὣ����ؼ���ӳ�䵽ͬһ����ַ�ϡ�

��ַ��ͻ���������
������̽�ⷨ����������ͻʱ����˳��鿴��һ���洢λ�ã����λ��Ϊ����״̬���ͽ��ùؼ��ִ洢�ڸ�λ���ϣ�
������Ƿ�����ͻ������������鿴�����鿴���洢�ռ��ĩβʱ�����Ҳ�����λ�ã��ͷ��ش�ͷ��ʼ�鿴��
��ƽ��̽�ⷨ����ͬ��ǰ������̽�ⷨ����˳��鿴��һ��λ���Ƿ��ܴ洢Ԫ�أ�ƽ��̽��Ĺ�������1^2, 2^2, 3^2,...��̽���µĴ洢λ���ܷ�洢Ԫ�أ�
����ɢ�з�����������ɢ�к�������ͨ����һ��ɢ�к����õ��ؼ��ֵĴ洢��ַ������ͻʱ�������õڶ���ɢ�к����������ַ������
��ַ���㷽ʽ���£�H_i = (Hash_1(key) + i * Hash_2(key)) % p
��α��������� ��������ַ��ͻʱ������һ���������Ϊ��ַ����Ѱ���µĴ洢��ַ��
��ַ���㷽ʽ���£�H_i = (Hash(key) + d_i) % p ,����d_iΪ�����
������������������ͬ�洢��ַ�Ĺؼ�������һ������m���洢��ַ����m��������Ȼ����һ�����齫m��������ı�ͷָ��洢�������γ�һ����̬�Ľṹ��
����ɢ�к���Ϊ Hash(key) = key %13���������洢�ṹΪ��https://i-blog.csdnimg.cn/blog_migrate/c08cc7f28bd9f7983c1a6691674532ad.png */

//���ʹ��STL���еĹ�ϣ��
//��1������ͷ�ļ�
#include<unordered_map>

//��2����ϣ�������
unordered_map<elemType_1, elemType_2> var_name; //����һ��û���κ�Ԫ�صĹ�ϣ������elemType_1��elemType_2��ģ�������������
unordered_map<int, int> map;//����һ����ֵ�Զ�ΪInt�Ĺ�ϣ��

//��3����ϣ��ĳ�ʼ��
//������������ϣ���ʱ��û�и�unordered_map�����κβ�������˵��õ���unordered_map��Ĭ�Ϲ��캯��������һ������������ʼ����Ҫ��һ�¼��ַ�ʽ��

//a���ڶ����ϣ���ʱ��ͨ����ʼ���б��е�Ԫ�س�ʼ�� :
unordered_map<int, int> hmap{ {{1,10},{2,12},{3,13}},3 /* 3ΪҪ�����Ĺ�ϣ���Ԫ�ظ������ɲ��� */};

//b��ͨ���±����������Ԫ��:mapName[key]=value;
//�������������Ԫ�صķ�ʽ��������ǵ�����,Ҳ���ǵ�hmap��keyΪ4�Ĵ洢λ����ֵʱ������hmap[4]=value���Ԫ�أ��Ὣԭ��ϣ����keyΪ4�洢��Ԫ�ظ���
hmap[4] = 14;
hmap[5] = 15;
cout << hmap[4];  //���Ϊ15

//c��ͨ��insert()���������Ԫ��:
//ͨ��insert()���������Ԫ�صĽ����ͨ���±������Ԫ�صĽ��һ������ͬ����insert()���Ա��⸲�����⣬insert()������ͬһ��key�в������Σ��ڶ��β����ʧ��
hmap.insert({ 5,15 });
hmap.insert({ 5,16 });
cout << hmap[5];  //���Ϊ15

//d�����ƹ��죬ͨ�������ѳ�ʼ���Ĺ�ϣ������ʼ�µı�:
unordered_map<int, int> hmap{ {1,10},{2,12},{3,13} };
unordered_map<int, int> hmap1(hmap);

//3. STL�й�ϣ��ĳ��ú���
//(1) begin()�������ú�������һ��ָ���ϣ��ʼλ�õĵ�����
//	  end()������������begin������ͬ������һ��ָ���ϣ���βλ�õ���һ��Ԫ�صĵ�����
unordered_map<int, int>::iterator iter_begin = hmap.begin(); //���������������ʼ��Ϊ��ϣ�����ʼλ��
unordered_map<int, int>::iterator iter_end = hmap.end();//���������������ʼ��Ϊ��ϣ���ĩβλ��
//��ϣ��ı�����
unordered_map<int, int> hmap{ {1,10},{2,12},{3,13} };
unordered_map<int, int>::iterator iter = hmap.begin();
for (; iter != hmap.end(); iter++) {
    cout << "key: " << iter->first << "value: " << iter->second << endl;
}

//(2) empty()�������жϹ�ϣ���Ƿ�Ϊ�գ����򷵻�true���ǿշ���false
bool isEmpty = hmap.empty();

//(3) size()���������ع�ϣ��Ĵ�С
int size = hmap.size();

//(4) erase()������ ɾ��ĳ��λ�õ�Ԫ�أ�����ɾ��ĳ��λ�ÿ�ʼ��ĳ��λ�ý�����һ��Χ�ڵ�Ԫ�أ� ���ߴ���keyֵɾ����ֵ��
unordered_map<int, int> hmap{ {1,10},{2,12},{3,13} };
unordered_map<int, int>::iterator iter_begin = hmap.begin();
unordered_map<int, int>::iterator iter_end = hmap.end();
hmap.erase(iter_begin);  //ɾ����ʼλ�õ�Ԫ��
hmap.erase(iter_begin, iter_end); //ɾ����ʼλ�úͽ���λ��֮���Ԫ��
hmap.erase(3); //ɾ��key==3�ļ�ֵ��

//(5) at()����������key���ҹ�ϣ���е�Ԫ��
unordered_map<int, int> hmap{ {1,10},{2,12},{3,13} };
int elem = hmap.at(3);

//(6) clear()��������չ�ϣ���е�Ԫ��
hmap.clear();

//(7) find()��������key��Ϊ����Ѱ�ҹ�ϣ���е�Ԫ�أ������ϣ���д��ڸ�keyֵ�򷵻ظ�λ���ϵĵ����������򷵻ع�ϣ�����һ��Ԫ����һλ���ϵĵ�����
unordered_map<int, int> hmap{ {1,10},{2,12},{3,13} };
unordered_map<int, int>::iterator iter;
iter = hmap.find(2); //����key==2�ĵ�����
if (iter != hmap.end())  cout << iter->second;//����ͨ��iter->second���ʸ�key��Ӧ��Ԫ��

//(8) count()������ ͳ��ĳ��keyֵ��Ӧ��Ԫ�ظ����� ��Ϊunordered_map�������ظ�Ԫ�أ����Է���ֵΪ0��1
int count = hmap.count(key);

//(9) bucket()��������keyѰ�ҹ�ϣ���и�Ԫ�صĴ����bucket��ţ�unordered_map��Դ���ǻ�������ʽ�Ĺ�ϣ��������ͨ��һ����bucket�洢Ԫ�أ�
int pos = hmap.bucket(key);
//    bucket_count()�������ú������ع�ϣ���д��ڵĴ洢Ͱ������һ���洢Ͱ����������Ŷ��Ԫ�أ�Ҳ���Բ����Ԫ�أ�����bucket�ĸ������ڵ���Ԫ�ظ�����
int count = hmap.bucket_count();

/*�����map��https://blog.csdn.net/m0_56494923/article/details/123239292
�������÷�����Ϊ�Ǽ��ϣ�����������֯��
TreeSet��TreeMapԭ��һ�������ް������ݵ�����
����ɾ���ġ��� + �ܶ��������صĲ���(floor��ceilling��)��ʱ��ΪO(log n)
�����Ƚ���ͬ�Ķ�����ȥ�أ��������ȥ�ؾͼ������ıȽϲ��ԣ��Ƚ������ƣ����Ѳ���ȥ�ء�
*/

#include<map>
//1��map�Ķ���
//��������һ��map :
map<typename1, typename2> mp;//���У�typename1�Ǽ������ͣ�typename2��ֵ�����͡�
//ע��������ַ��������͵�ӳ�䣬����ʹ��string��������char���飡
map<string, int> mp;//������Ϊchar������Ϊ���飬�ǲ��ܱ���Ϊ��ֵ�ġ�������������ַ�����ӳ�䣬������string��
//map�ڲ����ɺ����ʵ�ֵģ��ڽ���ӳ��Ĺ����У����Զ�ʵ�ִ�С���������ܡ�

//2��map������Ԫ�صķ���
//�١�ͨ���±���ʣ�mapName[key]=value;
map<char, int> mp;
mp['c'] = 20;
cout << mp['c'];	//�����20
//���������Ԫ�صķ�ʽҲ��������ǵ�����

//�ڡ�ͨ�����������ʣ�
//map�������Ķ��������STL��������������ķ�ʽ��ͬ��
map<typename1, typename2>::iterator it;
//map����ʹ��it->first�����ʼ���it->second������ֵ��
map<char, int> mp;
mp['a'] = 222;
mp['b'] = 333;
mp['c'] = 444;
for (map<char, int>::iterator it = mp.begin(); it != mp.end(); it++) {
	cout << it->first << " " << it->second << endl;
}

//3��map���ú���ʵ��������
//�١�find()��
//find(key)���ؼ�Ϊkeyӳ��ĵ�������ʱ�临�Ӷ�ΪO(logN)��NΪmap��ӳ��ĸ�����
map<char, int> mp;
mp['a'] = 222;
mp['b'] = 333;
mp['c'] = 444;
map<char, int>::iterator it = mp.find('b');
cout << it->first << " " << it->second;

//�ڡ�erase() :
//(a)��ɾ������Ԫ�ء�
mp.erase(it)//itΪ��Ҫɾ����Ԫ�صĵ�������ʱ�临�Ӷ�ΪO(1)
mp.erase(key)//keyΪҪɾ����ӳ��ļ���ʱ�临�Ӷ�O(logN)
//(b)��ɾ��һ�����������е�Ԫ�ء�
mp.erase(first, last)//����firstΪ��Ҫɾ�����������ʼ��������lastΪ��Ҫɾ��������ĩβ����������һ����ַ����Ϊɾ������ҿ�������[first, last)��ʱ�临�Ӷ�ΪO(last - first)��
mp.erase(mp.begin(), mp.end());

//�ۡ�size()�����map��ӳ��Ķ��������Ӷ�ΪO(1)��
mp.size();

//�ܡ�clear() :��map�е�����Ԫ�أ����Ӷ�ΪO(N)
mp.clear()

//�ݡ�count()������ ͳ��ĳ��keyֵ��Ӧ��Ԫ�ظ����� ��Ϊunordered_map�������ظ�Ԫ�أ����Է���ֵΪ0��1
int count = mp.count(key);

//�ޡ�empty()�������жϹ�ϣ���Ƿ�Ϊ�գ����򷵻�true���ǿշ���false
bool isEmpty = mp.empty();



// Integer��Long��Double��Float
// Byte��Short��Character��Boolean
// String�ȶ����������
String str1 = new String("Hello");
String str2 = new String("Hello");
// false����Ϊ��ͬ���ڴ��ַ
System.out.println(str1 == str2);
// true����Ϊ���ǵ�ֵ����ͬ��
System.out.println(str1.equals(str2));