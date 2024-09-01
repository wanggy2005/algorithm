//队列的数组实现
class Queue {
public:
	int* queue;
	int l, r;//首尾标志点
	int length;
	Queue(int n) :l(0), r(0), length(n) {
		queue = new int[n];
	}
	~Queue() {
		delete[] queue;
	}
//队列的常用函数实现
//判断队列是否为空
	bool isEmpty() {
		return l == r;
	}
//返回队列中元素的个数
	int size() {
		return r - l;
	}
//弹出队列中的头元素
	int pop() {
		if (!isEmpty())	return queue[l++];
	}
//返回队列中的头元素但不弹出
	int head() {
		if (!isEmpty())	return queue[l];
	}
//向队列中加入元素
	int push(int num) {
		queue[r++] = num;
	}
//返回队列中的头元素但不弹出
	int tail() {
		if (!isEmpty())	return queue[r - 1];
	}
};

//循环队列 https://leetcode.cn/problems/design-circular-queue/description/?envType=problem-list-v2&envId=QbOER4QK&
/*循环队列是一种线性数据结构，其操作表现基于 FIFO（先进先出）原则并且队尾被连接在队首之后以形成一个循环。它也被称为“环形缓冲器”。
循环队列的一个好处是我们可以利用这个队列之前用过的空间。在一个普通队列里，一旦一个队列满了，我们就不能插入下一个元素，即使在队列前面仍有空间。
但是使用循环队列，我们能使用这些空间去存储新的值。
你的实现应该支持如下操作：
MyCircularQueue(k): 构造器，设置队列长度为 k 。
Front: 从队首获取元素。如果队列为空，返回 -1 。
Rear: 获取队尾元素。如果队列为空，返回 -1 。
enQueue(value): 向循环队列插入一个元素。如果成功插入则返回真。
deQueue(): 从循环队列中删除一个元素。如果成功删除则返回真。
isEmpty(): 检查循环队列是否为空。
isFull(): 检查循环队列是否已满。*/
class MyCircularQueue {
public:
	int* circularqueue = nullptr;
	int l = 0, r = 0, limit = 0, size = 0;
	MyCircularQueue(int k) {
		circularqueue = new int[k];
		limit = k;
	}
	bool enQueue(int value) {
		if (isFull())	return false;
		circularqueue[r] = value;
		r = r < limit - 1 ? r + 1 : 0;
		size++;
		return true;
	}
	bool deQueue() {
		if (isEmpty())	return false;
		l = l < limit - 1 ? l + 1 : 0;
		size--;
		return true;
	}
	int Front() {
		if (isEmpty())	return -1;
		return circularqueue[l];
	}
	int Rear() {
		if (isEmpty())	return -1;
		int last = (r - 1 + limit) % limit;
//		int last = r == 0 ? limit - 1 : r - 1;
		return circularqueue[last];
	}
	bool isEmpty() {
		return !size;
	}
	bool isFull() {
		return size == limit;
	}
};

//循环双端队列。 https://leetcode.cn/problems/design-circular-deque/description/?envType=problem-list-v2&envId=QbOER4QK&
/*实现 MyCircularDeque 类 :
MyCircularDeque(int k) ：构造函数, 双端队列最大为 k 。
boolean insertFront()：将一个元素添加到双端队列头部。 如果操作成功返回 true ，否则返回 false 。
boolean insertLast() ：将一个元素添加到双端队列尾部。如果操作成功返回 true ，否则返回 false 。
boolean deleteFront() ：从双端队列头部删除一个元素。 如果操作成功返回 true ，否则返回 false 。
boolean deleteLast() ：从双端队列尾部删除一个元素。如果操作成功返回 true ，否则返回 false 。
int getFront() )：从双端队列头部获得一个元素。如果双端队列为空，返回 - 1 。
int getRear() ：获得双端队列的最后一个元素。 如果双端队列为空，返回 - 1 。
boolean isEmpty() ：若双端队列为空，则返回 true ，否则返回 false  。
boolean isFull() ：若双端队列满了，则返回 true ，否则返回 false 。*/
class MyCircularDeque {
public:
	int* circulardeque;
	int l = 0, r = 0, limit = 0, size = 0;
	MyCircularDeque(int k) {
		circulardeque = new int[k];
		limit = k;
	}
	~MyCircularDeque() {
		delete[] circulardeque;
	}
	bool insertFront(int value) {
		if (isFull())	return false;
		l = (l - 1 + limit) % limit;//
		circulardeque[l] = value;
		size++;
		return true;
	}
	bool insertLast(int value) {
		if (isFull())	return false;
		circulardeque[r] = value;//
		r = (r + 1) % limit;//
		size++;
		return true;
	}
	bool deleteFront() {
		if (isEmpty())	return false;
		l = (l + 1) % limit;
		size--;
		return true;
	}
	bool deleteLast() {
		if (isEmpty())	return false;
		r = (r - 1 + limit) % limit;
		size--;
		return true;
	}
	int getFront() {
		if (isEmpty())	return -1;
		return circulardeque[l];
	}
	int getRear() {
		if (isEmpty())	return -1;
		return circulardeque[(r - 1 + limit) % limit];
		// 注意这里返回 (r - 1 + limit) % limit 位置的元素，因为 r 指向下一个可用位置
	}
	bool isEmpty() {
		return !size;
	}
	bool isFull() {
		return size == limit;
	}
};
