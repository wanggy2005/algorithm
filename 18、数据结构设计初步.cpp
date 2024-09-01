//һ��setAll���ܵĹ�ϣ�� https://www.nowcoder.com/practice/7c4559f138e74ceb9ba57d76fd169967
/*��ϣ��������������ʱput��get��containsKey������������������ʱ�临�Ӷ�ΪO(1)��
�������һ��setAll���ܣ����ǰ����м�¼value�����ͳһ��ֵ��
����Ʋ�ʵ��������setAll���ܵĹ�ϣ������put��get��containsKey��setAll�ĸ�������ʱ�临�Ӷȶ�ΪO(1)��
����������
��һ��һ������N��ʾ��������
������N�У�ÿ�е�һ������opt�����������
��opt = 1������������������x, y��ʾ����key = x��Ӧ��value = y
��opt = 2��������һ������x����ʾ��ѯkey = x��Ӧ��value����key = x��������� - 1
��opt = 3��������һ������x����ʾ�Ѽ���������е�key��Ӧ��value������Ϊx
���������
����ÿ������2�����һ��������ʾ��*/
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
private:
    int setAllValue;
    int setAllTime;
    int cnt;
    unordered_map<int, vector<int>> set;
public:
    Solution() :setAllValue(0), setAllTime(-1), cnt(0) {}
    // setAllTime(-1) ������ʵ��ʱ�����ͻ:
    //������ cnt �� 0 ��ʼ����������κ���Ч�� setAll ��������ʹ setAllTime ���ڵ��� 0��
    // ͨ���� setAllTime ��ʼ��Ϊ - 1��ȷ�����ʼֵ�������κ���Ч�Ĳ���ʱ�����ͻ��
    void put(int a, int b) {
        if (set.find(a) != set.end()) {
            set[a][0] = b;
            set[a][1] = cnt++;
        }
        else {//����� a ��û���� set �д��ڣ�ֱ�ӷ��� set[a][0] ������������Ҫ�ȳ�ʼ�� set[a]��
            set[a] = { b,cnt++ };
        }
    }
    int get(int x) {
        if (set.find(x) != set.end()) {
            if (set[x][1] > setAllTime) {
                return set[x][0];
            }
            else {
                return setAllValue;
            }
        }
        else {
            return -1;
        }
    }
    void setAll(int x) {
        setAllValue = x;
        setAllTime = cnt++;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    Solution sol;
    int N;
    cin >> N;
    int op, x, a, b;
    for (int i = 0; i < N; i++) {
        cin >> op;
        switch (op) {
        case 1:
            cin >> a >> b;
            sol.put(a, b);
            break;
        case 2:
            cin >> x;
            cout << sol.get(x) << endl;
            break;
        case 3:
            cin >> x;
            sol.setAll(x);
            break;
        }
    }
    return 0;
}

//����LRU�ṹ https://leetcode.cn/problems/lru-cache/
/*ʹ��˫�������ԭ��
1. ����ɾ���ڵ�
��LRU�����ʵ���У��������ʹ�õĽڵ�ᱻ�Ƴ����档Ϊ��ɾ��һ���ڵ㣬��Ҫ��������ǰ���ͺ�̽ڵ㡣
˫�������У�ÿ���ڵ㶼��һ��ָ��ǰ���ڵ㣨last���ͺ�̽ڵ㣨next����ָ�롣��ˣ������ڳ���ʱ���ڣ�O(1)��ɾ��һ���ڵ㣬�����ǵ���ǰ���ͺ�̽ڵ��ָ�롣
�ڵ��������У����Ҫɾ��һ���ڵ㣬�ر��Ƿ�ͷ�ڵ㣬�����ͷ�ڵ㿪ʼ������ֱ���ҵ�Ҫɾ���ڵ��ǰһ���ڵ㡣�⵼��ɾ��������ʱ�临�Ӷ�ΪO(n)������n������ĳ��ȡ�
2. �����ƶ��ڵ㵽����β��
��LRU�����У�ÿ�η���һ���ڵ����Ҫ���ýڵ��ƶ�������β������ʾ���ʹ�ã���
˫������ʹ����������ǳ���Ч����Ϊ����ֱ��ͨ���ڵ��ǰ���ͺ��ָ����е������������������
�ڵ��������У�ͬ����Ҫ�����ҵ�ǰһ���ڵ�����������нڵ��ƶ���������Ӳ�����ʱ�临�Ӷȡ�
3. ʵ�ֶ��й���
LRU������ҪƵ���ؽ����������ʹ�ã�LRU����Ԫ�ص��Ƴ����������Ƴ�ͷ���ڵ㣬ͬʱҲ��Ҫ������Ԫ�ص�β����
˫�������ͷβ������������O(1)ʱ������ɣ��ǳ��ʺ�ʵ�ֶ��й��ܡ�*/

//˫�������ձ�ʹ�õ�˳��洢����Щ��ֵ�ԣ�����ͷ���ļ�ֵ�������ʹ�õģ�������β���ļ�ֵ�������δʹ�õġ�
//ʹ�ù�ϣ����ж�λ���ҳ���������˫�������е�λ�ã�������ƶ���˫�������ͷ���������� O(1) ��ʱ������� get ���� put ������
struct DLinkedNode {
    int key, value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value) : key(_key), value(_value), prev(nullptr), next(nullptr) {}
};
class LRUCache {
private:
    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode* head;
    DLinkedNode* tail;
    int size;
    int capacity;
public:
    LRUCache(int _capacity) : capacity(_capacity), size(0) {
        // ʹ��αͷ����αβ���ڵ�
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }
    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        // ��� key ���ڣ���ͨ����ϣ��λ�����Ƶ�ͷ��
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;
    }
    void put(int key, int value) {
        if (!cache.count(key)) {
            // ��� key �����ڣ�����һ���µĽڵ�
            DLinkedNode* node = new DLinkedNode(key, value);
            // ��ӽ���ϣ��
            cache[key] = node;
            // �����˫�������ͷ��
            addToHead(node);
            if (++size > capacity) {
                // �������������ɾ��˫�������β���ڵ�
                DLinkedNode* removed = removeTail();
                // ɾ����ϣ���ж�Ӧ����
                cache.erase(removed->key);
                // ��ֹ�ڴ�й©
                delete removed;
                size--;
            }
        }else {
            // ��� key ���ڣ���ͨ����ϣ��λ�����޸� value�����Ƶ�ͷ��
            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }

    void addToHead(DLinkedNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    void moveToHead(DLinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }
    DLinkedNode* removeTail() {
        DLinkedNode* node = tail->prev;
        removeNode(node);
        return node;
    }
};

class LRUCache {
private:
    struct doublyNodeList {
        int k;
        int val;
        doublyNodeList* last;
        doublyNodeList* next;
        doublyNodeList(int key, int value) :k(key), val(value), last(nullptr), next(nullptr) {}
        doublyNodeList() :k(0), val(0), last(nullptr), next(nullptr) {}
    };
    unordered_map<int, doublyNodeList*> NodeMap;
    int limit;
    int size = 0;
    void removeNode(doublyNodeList* node) {
        node->last->next = node->next;
        node->next->last = node->last;
    }
    void addNode(doublyNodeList* node) {
        doublyNodeList* Next = dumHead->next;
        dumHead->next = node;
        node->next = Next;
        node->last = dumHead;
        Next->last = node;
    }
    void MoveToHead(doublyNodeList* node) {
        removeNode(node);
        addNode(node);
    }
    doublyNodeList* dumHead = new doublyNodeList;
    doublyNodeList* dumTail = new doublyNodeList;
public:
    LRUCache(int capacity) {
        limit = capacity;
        dumHead->next = dumTail;
        dumTail->last = dumHead;
    }
    int get(int key) {
        if (NodeMap.count(key)) {
            MoveToHead(NodeMap[key]);
            return NodeMap[key]->val;
        }
        return -1;
    }
    void put(int key, int value) {
        if (NodeMap.count(key)) {
            MoveToHead(NodeMap[key]);
            NodeMap[key]->val = value;
        }
        else {
            if (size == limit) {
                doublyNodeList* removed_Node = dumTail->last;
                removeNode(removed_Node);
                NodeMap.erase(removed_Node->k);
                delete removed_Node;
                size--;
            }
            doublyNodeList* newNode = new doublyNodeList(key, value);
            NodeMap[key] = newNode;
            addNode(newNode);
            size++;
        }
    }
};

//�������롢ɾ���ͻ�ȡ���Ԫ��O(1)ʱ��Ľṹ https://leetcode.cn/problems/insert-delete-getrandom-o1/
/*ʵ��RandomizedSet �ࣺ
RandomizedSet() ��ʼ�� RandomizedSet ����
bool insert(int val) ��Ԫ�� val ������ʱ���򼯺��в����������� true �����򣬷��� false ��
bool remove(int val) ��Ԫ�� val ����ʱ���Ӽ������Ƴ���������� true �����򣬷��� false ��
int getRandom() ����������м����е�һ�����������֤���ô˷���ʱ���������ٴ���һ��Ԫ�أ���ÿ��Ԫ��Ӧ���� ��ͬ�ĸ��� �����ء�
�����ʵ��������к�����������ÿ�������� ƽ�� ʱ�临�Ӷ�Ϊ O(1) ��*/
class RandomizedSet {
private:
    unordered_map<int, int> numMap;
    vector<int> nums;
public:
    RandomizedSet() { srand(time(0)); }
    bool insert(int val) {
        if (!numMap.count(val)) {
            numMap[val] = nums.size();
            nums.push_back(val);
            return true;
        }
        return false;
    }
    bool remove(int val) {
        if (numMap.count(val)) {
            int index = numMap[val];
            nums[index] = nums.back();
            numMap[nums.back()] = index;
            nums.pop_back();
            numMap.erase(val);
            return true;
        }
        return false;
    }
    int getRandom() {
        return nums[rand() % nums.size()];
    }
};
//���롢ɾ���ͻ�ȡ���Ԫ��O(1)ʱ�����������ظ����ֵĽṹ https://leetcode.cn/problems/insert-delete-getrandom-o1-duplicates-allowed/
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cstdlib>
class RandomizedCollection {
private:
    unordered_map<int, unordered_set<int>> map;
    vector<int> arr;
public:
    RandomizedCollection() { srand(time(0)); }
    bool insert(int val) {
        arr.push_back(val);
        unordered_set<int>& set = map[val]; 
//��ȡ���ã�map[val] ���� unordered_map �м�Ϊ val �� unordered_set������� val �����ڣ������Զ�����һ���µ� unordered_set �����뵽 map �С�
//���ø�ֵ��valSet ��һ���� map[val] �����á�����ζ�� valSet �� map[val] ��ͬһ�����󣬶� valSet ���κ��޸Ķ���ֱ�ӷ�ӳ�� map[val] �С�
        set.insert(arr.size() - 1);
        return set.size() == 1;
    }
    bool remove(int val) {
        if (!map.count(val)) {
            return false;
        }
        unordered_set<int>& valSet = map[val];
        int valAnyIndex = *valSet.begin();
        int endValue = arr.back();
        if (val == endValue) {
            valSet.erase(arr.size() - 1);
        }else {
            unordered_set<int>& endValueSet = map[endValue];
            endValueSet.insert(valAnyIndex);
            arr[valAnyIndex] = endValue;
            endValueSet.erase(arr.size() - 1);
            valSet.erase(valAnyIndex);
        }
        arr.pop_back();
        if (valSet.empty()) {
            map.erase(val);
        }
        return true;
    }
    int getRandom() {
        return arr[rand() % arr.size()];
    }
};

//�ġ����ٻ������������λ���Ľṹ��˫�ѷ��� https://leetcode.cn/problems/find-median-from-data-stream/// 
//�������ѣ�һ������ѣ�һ��С����
//�ý�С��һ�붼������ѣ�������С��һ�������ģ����ϴ��һ�붼��С���ѣ������ϴ��һ������С�ģ�
//��ν�����ѹ����У�
//��һ������Ĭ�Ͻ�����ѣ������������ݴ��ڴ���ѶѶ������С���ѣ����С�ڵ��ڴ���ѶѶ����������ѡ�
//����������Ԫ�ظ�����Ϊ2ʱ����Ԫ�ؽ϶�ĶѵĶѶ�����������һ���ѡ�
#include <queue>
#include <vector>
class MedianFinder {
private:
    priority_queue<int> maxHeap;// ���� (�󶥶�) ���ڴ洢��С��Ԫ��
    priority_queue<int, vector<int>, greater<int>> minHeap;// ��С�� (С����) ���ڴ洢�ϴ��Ԫ��
    void balance() {
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
public:
    MedianFinder() {}
    void addNum(int num) {
        if (maxHeap.empty() || maxHeap.top() >= num) {
            maxHeap.push(num);
        }else {
            minHeap.push(num);
        }
        balance();
    }
    double findMedian() {
        if (maxHeap.size() == minHeap.size()) {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }else {
            return maxHeap.top();
        }
    }
};

//�塢���Ƶ��ջ https://leetcode.cn/problems/maximum-frequency-stack/
class FreqStack {
private:
    int topTimes; // ��ǰԪ�س��ֵ�������
    unordered_map<int, int> valueTimes; // ��¼ÿ��Ԫ�صĳ��ִ���
    unordered_map<int, vector<int>> cntValues; // ��¼ÿ�����ִ�����Ӧ��Ԫ���б�
public:
    FreqStack() : topTimes(0) {}
    void push(int val) {
        valueTimes[val]++;// ����Ԫ��val�ĳ��ִ���
        cntValues[valueTimes[val]].push_back(val);// ��Ԫ��val��ӵ����ִ���ΪvalueTimes[val]���б���
        topTimes = max(topTimes, valueTimes[val]);// ���������ִ���
    }
    int pop() {
        auto& topTimeValues = cntValues[topTimes];// ��ȡ���ִ���ΪtopTimes��Ԫ���б�
        int ans = topTimeValues.back();// ��ȡ���Ƴ��б�����һ��Ԫ�أ��������ӵ�Ԫ��
        topTimeValues.pop_back();
        // ����б�Ϊ�գ��Ƴ��ó��ִ����㲢�ݼ�topTimes
        if (topTimeValues.empty()) {
            cntValues.erase(topTimes--);
        }
        if (!--valueTimes[ans]) {// ����Ԫ��ans�ĳ��ִ���
            valueTimes.erase(ans); // ���ans�ĳ��ִ���Ϊ0�����Ƴ���
        }
        return ans; // ���ر��Ƴ���Ԫ��
    }
};

class FreqStack {
private:
    struct Bucket {
        int nums;
        stack<int> elements;
        Bucket* last;
        Bucket* next;
        Bucket(int n) :nums(n), last(nullptr), next(nullptr) {}
    };
    unordered_map<int, Bucket*> map;
    void InsertBucket(Bucket* b) {
        Bucket* cur = dummyHead;
        while (cur->next->nums < b->nums && cur->next != dummyTail) {
            cur = cur->next;
        }
        b->next = cur->next;
        b->last = cur;
        cur->next->last = b;
        cur->next = b;
    }
    void RemoveBucket(Bucket* b) {
        b->last->next = b->next;
        b->next->last = b->last;
        delete b;
    }
    Bucket* dummyHead = new Bucket(0);
    Bucket* dummyTail = new Bucket(INT_MAX);
public:
    FreqStack() {
        dummyHead->next = dummyTail;
        dummyTail->last = dummyHead;
    }
    void push(int val) {
        if (!map.count(val)) {
            if (dummyHead->next == dummyTail || dummyHead->next->nums != 1) {
                Bucket* newBucket = new Bucket(1);
                InsertBucket(newBucket);
                map[val] = newBucket;
            }else {
                map[val] = dummyHead->next;
            }
            map[val]->elements.push(val);
        }else {
            Bucket* currentBucket = map[val];
            int newFreq = currentBucket->nums + 1;
            if (currentBucket->next == dummyTail || currentBucket->next->nums != newFreq) {
                Bucket* newBucket = new Bucket(newFreq);
                InsertBucket(newBucket);
                map[val] = newBucket;
            }
            else {
                map[val] = currentBucket->next;
            }
            map[val]->elements.push(val);
        }
    }
    int pop() {
        auto& theLastBucket = dummyTail->last;
        int n = theLastBucket->nums;
        int ans = theLastBucket->elements.top();
        theLastBucket->elements.pop();
        if (n == 1) {
            map.erase(ans);
        }
        else {
            if (theLastBucket->last->nums == n - 1) {
                map[ans] = map[ans]->last;
            }
            else {
                Bucket* secondLastBucket = new Bucket(n - 1);
                InsertBucket(secondLastBucket);
                map[ans] = secondLastBucket;
            }
        }
        if (theLastBucket->elements.empty()) {
            RemoveBucket(theLastBucket);
        }
        return ans;
    }
};

//����ȫO(1)�����ݽṹ https://leetcode.cn/problems/all-oone-data-structure/
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <climits>
using namespace std;
class AllOne {
private:
    // Bucket���ʾһ��Ͱ���洢��ͬ�������ַ�������
    class Bucket {
    public:
        unordered_set<string> set; // �洢�ַ����ļ���
        int cnt;                   // ��Ͱ�ļ���
        Bucket* last;              // ָ��ǰһ��Ͱ
        Bucket* next;              // ָ����һ��Ͱ
        Bucket(const string& s, int c) : cnt(c), last(nullptr), next(nullptr) {
            set.insert(s);
        }
    };

    Bucket* head; // ����ͷ�ڵ㣬��ʾ����Ϊ0��Ͱ
    Bucket* tail; // ����β�ڵ㣬��ʾ��������Ͱ
    unordered_map<string, Bucket*> map; // �ַ�����Ͱ��ӳ��
    void insert(Bucket* cur, Bucket* pos) {// ��cur�������posͰ
        pos->next = cur->next;
        cur->next->last = pos;
        cur->next = pos;
        pos->last = cur;
    }
    void remove(Bucket* cur) {// ɾ��curͰ
        cur->last->next = cur->next;
        cur->next->last = cur->last;
        delete cur; // �ͷ��ڴ�
    }

public:
    AllOne() {// ���캯������ʼ��ͷβ�ڵ�
        head = new Bucket("", 0);
        tail = new Bucket("", INT_MAX);
        head->next = tail;
        tail->last = head;
    }
    ~AllOne() {// �����������ͷ�����Ͱ���ڴ�
        while (head) {
            Bucket* next = head->next;
            delete head;
            head = next;
        }
    }
    // �����ַ���key�ļ���
    void inc(const string& key) {
        if (map.find(key) == map.end()) { // ���key����ӳ����
            if (head->next->cnt == 1) {   // �����һ��Ͱ�ļ���Ϊ1
                map[key] = head->next;
                head->next->set.insert(key);
            }else { // ���򣬴���һ���µļ���Ϊ1��Ͱ
                Bucket* newBucket = new Bucket(key, 1);
                map[key] = newBucket;
                insert(head, newBucket);
            }
        }else { // ���key��ӳ����
            Bucket* bucket = map[key];
            if (bucket->next->cnt == bucket->cnt + 1) { // �����һ��Ͱ�ļ���Ϊ��ǰͰ����+1
                map[key] = bucket->next;
                bucket->next->set.insert(key);
            }else { // ���򣬴���һ���µ�Ͱ������Ϊ��ǰͰ����+1
                Bucket* newBucket = new Bucket(key, bucket->cnt + 1);
                map[key] = newBucket;
                insert(bucket, newBucket);
            }
            bucket->set.erase(key); // �ӵ�ǰͰ���Ƴ�key
            if (bucket->set.empty()) {
                remove(bucket); // ���ͰΪ�գ�ɾ��Ͱ
            }
        }
    }
    // �����ַ���key�ļ���
    void dec(const string& key) {
        Bucket* bucket = map[key];
        if (bucket->cnt == 1) { // �������Ϊ1��ֱ�Ӵ�ӳ����ɾ��key
            map.erase(key);
        }else {
            if (bucket->last->cnt == bucket->cnt - 1) { // �����һ��Ͱ�ļ���Ϊ��ǰͰ����-1
                map[key] = bucket->last;
                bucket->last->set.insert(key);
            }else { // ���򣬴���һ���µ�Ͱ������Ϊ��ǰͰ����-1
                Bucket* newBucket = new Bucket(key, bucket->cnt - 1);
                map[key] = newBucket;
                insert(bucket->last, newBucket);
            }
        }
        bucket->set.erase(key); // �ӵ�ǰͰ���Ƴ�key
        if (bucket->set.empty()) {
            remove(bucket); // ���ͰΪ�գ�ɾ��Ͱ
        }
    }
    string getMaxKey() const {
        if (tail->last == head) return ""; // �������Ϊ�գ����ؿ��ַ���
        return *(tail->last->set.begin()); // ���ؼ�����ߵ�Ͱ�е�����һ���ַ���
    }
    string getMinKey() const {
        if (head->next == tail) return ""; // �������Ϊ�գ����ؿ��ַ���
        return *(head->next->set.begin()); // ���ؼ�����͵�Ͱ�е�����һ���ַ���
    }
};


class AllOne {
private:
    struct Bucket {
        unordered_set<string> str;
        int cnts;
        Bucket* last;
        Bucket* next;
        Bucket(int n) :cnts(n), last(nullptr), next(nullptr) {}
    };
    unordered_map<string, Bucket*> map;
    Bucket* dummyHead = new Bucket(0);
    Bucket* dummyTail = new Bucket(INT_MAX);
    void InsertBucket(Bucket* b) {
        Bucket* cur = dummyHead;
        while (cur->next->cnts < b->cnts && cur->next != dummyTail) {
            cur = cur->next;
        }
        b->next = cur->next;
        b->last = cur;
        cur->next->last = b;
        cur->next = b;
    }
    void checkOut(Bucket* b) {
        if (b->str.empty()) {
            b->last->next = b->next;
            b->next->last = b->last;
            delete b;
        }
    }
public:
    AllOne() {
        dummyHead->next = dummyTail;
        dummyTail->last = dummyHead;
    }
    void inc(string key) {
        if (!map.count(key)) {
            if (dummyHead->next->cnts == 1) {
                dummyHead->next->str.insert(key);
            }else {
                Bucket* newBucket = new Bucket(1);
                newBucket->str.insert(key);
                InsertBucket(newBucket);
            }
            map[key] = dummyHead->next;
        }else {
            int n = map[key]->cnts;
            map[key]->str.erase(key);
            Bucket* check = map[key];
            if (map[key]->next->cnts == n + 1) {
                map[key]->next->str.insert(key);
                map[key] = map[key]->next;
            }else {
                Bucket* newBucket = new Bucket(n + 1);
                newBucket->str.insert(key);
                InsertBucket(newBucket);
                map[key] = newBucket;
            }
            checkOut(check);
        }
    }
    void dec(string key) {
        Bucket* check = map[key];
        if (map[key]->cnts == 1) {
            map[key]->str.erase(key);
            map.erase(key);
        }else {
            if (map[key]->last->cnts == map[key]->cnts - 1) {
                map[key]->str.erase(key);
                map[key] = map[key]->last;
                map[key]->str.insert(key);
            }else {
                Bucket* newBucket = new Bucket(map[key]->cnts - 1);
                newBucket->str.insert(key);
                map[key]->str.erase(key);
                InsertBucket(newBucket);
                map[key] = newBucket;
            }
        }
        checkOut(check);
    }
    string getMaxKey() {
        return dummyTail->last == dummyHead ? "" : *(dummyTail->last->str.begin());
    }
    string getMinKey() {
        return dummyHead->next == dummyTail ? "" : *(dummyHead->next->str.begin());
    }
};
