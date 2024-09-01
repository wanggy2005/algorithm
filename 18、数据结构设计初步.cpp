//一、setAll功能的哈希表 https://www.nowcoder.com/practice/7c4559f138e74ceb9ba57d76fd169967
/*哈希表常见的三个操作时put、get和containsKey，而且这三个操作的时间复杂度为O(1)。
现在想加一个setAll功能，就是把所有记录value都设成统一的值。
请设计并实现这种有setAll功能的哈希表，并且put、get、containsKey和setAll四个操作的时间复杂度都为O(1)。
输入描述：
第一行一个整数N表示操作数。
接下来N行，每行第一个数字opt代表操作类型
若opt = 1，接下来有两个整数x, y表示设置key = x对应的value = y
若opt = 2，接下来一个整数x，表示查询key = x对应的value，若key = x不存在输出 - 1
若opt = 3，接下来一个整数x，表示把加入过的所有的key对应的value都设置为x
输出描述：
对于每个操作2，输出一个整数表示答案*/
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
    // setAllTime(-1) 避免与实际时间戳冲突:
    //计数器 cnt 从 0 开始递增，因此任何有效的 setAll 操作都会使 setAllTime 大于等于 0。
    // 通过将 setAllTime 初始化为 - 1，确保其初始值不会与任何有效的操作时间戳冲突。
    void put(int a, int b) {
        if (set.find(a) != set.end()) {
            set[a][0] = b;
            set[a][1] = cnt++;
        }
        else {//如果键 a 还没有在 set 中存在，直接访问 set[a][0] 会引发错误。需要先初始化 set[a]。
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

//二、LRU结构 https://leetcode.cn/problems/lru-cache/
/*使用双向链表的原因
1. 快速删除节点
在LRU缓存的实现中，最近最少使用的节点会被移出缓存。为了删除一个节点，需要访问它的前驱和后继节点。
双向链表中，每个节点都有一个指向前驱节点（last）和后继节点（next）的指针。因此，可以在常数时间内（O(1)）删除一个节点，方法是调整前驱和后继节点的指针。
在单向链表中，如果要删除一个节点，特别是非头节点，必须从头节点开始遍历，直到找到要删除节点的前一个节点。这导致删除操作的时间复杂度为O(n)，其中n是链表的长度。
2. 快速移动节点到链表尾部
在LRU缓存中，每次访问一个节点后，需要将该节点移动到链表尾部（表示最近使用）。
双向链表使得这个操作非常高效，因为可以直接通过节点的前驱和后继指针进行调整，而无需遍历链表。
在单向链表中，同样需要遍历找到前一个节点的引用来进行节点移动，这会增加操作的时间复杂度。
3. 实现队列功能
LRU缓存需要频繁地进行最近最少使用（LRU）的元素的移除操作，即移除头部节点，同时也需要插入新元素到尾部。
双向链表的头尾操作都可以在O(1)时间内完成，非常适合实现队列功能。*/

//双向链表按照被使用的顺序存储了这些键值对，靠近头部的键值对是最近使用的，而靠近尾部的键值对是最久未使用的。
//使用哈希表进行定位，找出缓存项在双向链表中的位置，随后将其移动到双向链表的头部，即可在 O(1) 的时间内完成 get 或者 put 操作。
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
        // 使用伪头部和伪尾部节点
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }
    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        // 如果 key 存在，先通过哈希表定位，再移到头部
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;
    }
    void put(int key, int value) {
        if (!cache.count(key)) {
            // 如果 key 不存在，创建一个新的节点
            DLinkedNode* node = new DLinkedNode(key, value);
            // 添加进哈希表
            cache[key] = node;
            // 添加至双向链表的头部
            addToHead(node);
            if (++size > capacity) {
                // 如果超出容量，删除双向链表的尾部节点
                DLinkedNode* removed = removeTail();
                // 删除哈希表中对应的项
                cache.erase(removed->key);
                // 防止内存泄漏
                delete removed;
                size--;
            }
        }else {
            // 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
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

//三、插入、删除和获取随机元素O(1)时间的结构 https://leetcode.cn/problems/insert-delete-getrandom-o1/
/*实现RandomizedSet 类：
RandomizedSet() 初始化 RandomizedSet 对象
bool insert(int val) 当元素 val 不存在时，向集合中插入该项，并返回 true ；否则，返回 false 。
bool remove(int val) 当元素 val 存在时，从集合中移除该项，并返回 true ；否则，返回 false 。
int getRandom() 随机返回现有集合中的一项（测试用例保证调用此方法时集合中至少存在一个元素）。每个元素应该有 相同的概率 被返回。
你必须实现类的所有函数，并满足每个函数的 平均 时间复杂度为 O(1) 。*/
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
//插入、删除和获取随机元素O(1)时间且允许有重复数字的结构 https://leetcode.cn/problems/insert-delete-getrandom-o1-duplicates-allowed/
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
//获取引用：map[val] 访问 unordered_map 中键为 val 的 unordered_set。如果键 val 不存在，它会自动创建一个新的 unordered_set 并插入到 map 中。
//引用赋值：valSet 是一个对 map[val] 的引用。这意味着 valSet 和 map[val] 是同一个对象，对 valSet 的任何修改都会直接反映到 map[val] 中。
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

//四、快速获得数据流的中位数的结构（双堆法） https://leetcode.cn/problems/find-median-from-data-stream/// 
//建两个堆：一个大根堆，一个小根堆
//让较小的一半都进大根堆（弹出较小的一半中最大的），较大的一半都进小根堆（弹出较大的一半中最小的）
//如何将数据压入堆中？
//第一个数据默认进大根堆，如果后面的数据大于大根堆堆顶，则进小根堆；如果小于等于大根堆堆顶，则进大根堆。
//当两个堆中元素个数差为2时，将元素较多的堆的堆顶弹出。进另一个堆。
#include <queue>
#include <vector>
class MedianFinder {
private:
    priority_queue<int> maxHeap;// 最大堆 (大顶堆) 用于存储较小的元素
    priority_queue<int, vector<int>, greater<int>> minHeap;// 最小堆 (小顶堆) 用于存储较大的元素
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

//五、最大频率栈 https://leetcode.cn/problems/maximum-frequency-stack/
class FreqStack {
private:
    int topTimes; // 当前元素出现的最大次数
    unordered_map<int, int> valueTimes; // 记录每个元素的出现次数
    unordered_map<int, vector<int>> cntValues; // 记录每个出现次数对应的元素列表
public:
    FreqStack() : topTimes(0) {}
    void push(int val) {
        valueTimes[val]++;// 增加元素val的出现次数
        cntValues[valueTimes[val]].push_back(val);// 将元素val添加到出现次数为valueTimes[val]的列表中
        topTimes = max(topTimes, valueTimes[val]);// 更新最大出现次数
    }
    int pop() {
        auto& topTimeValues = cntValues[topTimes];// 获取出现次数为topTimes的元素列表
        int ans = topTimeValues.back();// 获取并移除列表的最后一个元素，即最近添加的元素
        topTimeValues.pop_back();
        // 如果列表为空，移除该出现次数层并递减topTimes
        if (topTimeValues.empty()) {
            cntValues.erase(topTimes--);
        }
        if (!--valueTimes[ans]) {// 减少元素ans的出现次数
            valueTimes.erase(ans); // 如果ans的出现次数为0，则移除它
        }
        return ans; // 返回被移除的元素
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

//六、全O(1)的数据结构 https://leetcode.cn/problems/all-oone-data-structure/
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <climits>
using namespace std;
class AllOne {
private:
    // Bucket类表示一个桶，存储相同计数的字符串集合
    class Bucket {
    public:
        unordered_set<string> set; // 存储字符串的集合
        int cnt;                   // 该桶的计数
        Bucket* last;              // 指向前一个桶
        Bucket* next;              // 指向下一个桶
        Bucket(const string& s, int c) : cnt(c), last(nullptr), next(nullptr) {
            set.insert(s);
        }
    };

    Bucket* head; // 虚拟头节点，表示计数为0的桶
    Bucket* tail; // 虚拟尾节点，表示最大计数的桶
    unordered_map<string, Bucket*> map; // 字符串到桶的映射
    void insert(Bucket* cur, Bucket* pos) {// 在cur后面插入pos桶
        pos->next = cur->next;
        cur->next->last = pos;
        cur->next = pos;
        pos->last = cur;
    }
    void remove(Bucket* cur) {// 删除cur桶
        cur->last->next = cur->next;
        cur->next->last = cur->last;
        delete cur; // 释放内存
    }

public:
    AllOne() {// 构造函数，初始化头尾节点
        head = new Bucket("", 0);
        tail = new Bucket("", INT_MAX);
        head->next = tail;
        tail->last = head;
    }
    ~AllOne() {// 析构函数，释放所有桶的内存
        while (head) {
            Bucket* next = head->next;
            delete head;
            head = next;
        }
    }
    // 增加字符串key的计数
    void inc(const string& key) {
        if (map.find(key) == map.end()) { // 如果key不在映射中
            if (head->next->cnt == 1) {   // 如果下一个桶的计数为1
                map[key] = head->next;
                head->next->set.insert(key);
            }else { // 否则，创建一个新的计数为1的桶
                Bucket* newBucket = new Bucket(key, 1);
                map[key] = newBucket;
                insert(head, newBucket);
            }
        }else { // 如果key在映射中
            Bucket* bucket = map[key];
            if (bucket->next->cnt == bucket->cnt + 1) { // 如果下一个桶的计数为当前桶计数+1
                map[key] = bucket->next;
                bucket->next->set.insert(key);
            }else { // 否则，创建一个新的桶，计数为当前桶计数+1
                Bucket* newBucket = new Bucket(key, bucket->cnt + 1);
                map[key] = newBucket;
                insert(bucket, newBucket);
            }
            bucket->set.erase(key); // 从当前桶中移除key
            if (bucket->set.empty()) {
                remove(bucket); // 如果桶为空，删除桶
            }
        }
    }
    // 减少字符串key的计数
    void dec(const string& key) {
        Bucket* bucket = map[key];
        if (bucket->cnt == 1) { // 如果计数为1，直接从映射中删除key
            map.erase(key);
        }else {
            if (bucket->last->cnt == bucket->cnt - 1) { // 如果上一个桶的计数为当前桶计数-1
                map[key] = bucket->last;
                bucket->last->set.insert(key);
            }else { // 否则，创建一个新的桶，计数为当前桶计数-1
                Bucket* newBucket = new Bucket(key, bucket->cnt - 1);
                map[key] = newBucket;
                insert(bucket->last, newBucket);
            }
        }
        bucket->set.erase(key); // 从当前桶中移除key
        if (bucket->set.empty()) {
            remove(bucket); // 如果桶为空，删除桶
        }
    }
    string getMaxKey() const {
        if (tail->last == head) return ""; // 如果链表为空，返回空字符串
        return *(tail->last->set.begin()); // 返回计数最高的桶中的任意一个字符串
    }
    string getMinKey() const {
        if (head->next == tail) return ""; // 如果链表为空，返回空字符串
        return *(head->next->set.begin()); // 返回计数最低的桶中的任意一个字符串
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
