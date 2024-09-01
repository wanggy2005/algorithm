//栈的数列实现
class Stack {
	int* stack;
	int size;
	int capacity;
	Stack(int n) :capacity(n), size(0) {
		stack = new int[n];
	}
	~Stack() {
		delete[] stack;
	}
//栈的常用函数实现
//判断栈是否为空
	bool isEmpty() {
		return !size;
	}
//向栈中压入一个元素
	void push(int num) {
		stack[size++] = num;
	}
//从栈中弹出一个元素并返回该元素
	int pop() {
		return stack[--size];
	}
//返回栈中的元素个数
	int getSize() {
		return size;
	}
};

//用队列实现栈 https://leetcode.cn/problems/implement-stack-using-queues/description/?envType=problem-list-v2&envId=QbOER4QK&
/*请你使用队列实现一个后入先出的栈，并支持普通栈的全部四种操作（push、top、pop 和 empty）
实现 MyStack 类：
void push(int x) 将元素 x 压入栈顶。
int pop() 移除并返回栈顶元素。
int top() 返回栈顶元素。
boolean empty() 如果栈是空的，返回 true ；否则，返回 false 。*/
#include <queue>
class MyStack {
private:
	queue<int> queue;
public:
	MyStack() {}
	void push(int x) {
		int n = queue.size();
		queue.push(x);
		for (int i = 0; i < n; i++) {
			queue.push(queue.front());
			queue.pop();
		}
	}
	int pop() {
		int val = queue.front();
		queue.pop();
		return val;
	}
	int top() {
		return queue.front();
	}
	bool empty() {
		return queue.empty();
	}
};

//用栈实现队列 https://leetcode.cn/problems/implement-queue-using-stacks/description/?envType=problem-list-v2&envId=QbOER4QK&
/*请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：
实现 MyQueue 类：
void push(int x) 将元素 x 推到队列的末尾
int pop() 从队列的开头移除并返回元素
int peek() 返回队列开头的元素
boolean empty() 如果队列为空，返回 true ；否则，返回 false*/
#include <stack>
using namespace std;
class MyQueue {
private:
	stack<int> in;
	stack<int> out;//out栈空了才能从in栈中导出数据 如果要导出数据，in栈中的数据必须倒完
	void inToOut() {
		if (out.empty()) {
			while (!in.empty()) {
				out.push(in.top());
				in.pop();
			}
		}
	}
public:
	MyQueue() {}
	void push(int x) {
		in.push(x);
		inToOut();
	}
	int pop() {
		inToOut();
		int val = out.top();
		out.pop();
		return val;
	}
	int peek() {
		inToOut();
		return out.top();
	}
	bool empty() {
		return in.empty() && out.empty();
	}
};

//最小栈 https://leetcode.cn/problems/bao-han-minhan-shu-de-zhan-lcof/description/?envType=problem-list-v2&envId=QbOER4QK&
/*请你设计一个 最小栈 。它提供 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
实现 MinStack 类:
MinStack() 初始化堆栈对象。
void push(int val) 将元素val推入堆栈。
void pop() 删除堆栈顶部的元素。
int top() 获取堆栈顶部的元素。
int getMin() 获取堆栈中的最小元素。*/
class MinStack {
private:
	int* data;
	int* min;
	int size;
public:
	static const int MAXN = 8001;
	MinStack():size(0) {
		data = new int[MAXN];
		min = new int[MAXN];
	}
	~MinStack() {
		delete[] data;
		delete[] min;
	}
	void push(int x) {
		data[size] = x;
		if (size == 0 || x < min[size - 1]) {
			min[size] = x;
		}else {
			min[size] = min[size - 1];
		}
		size++;
	}
	void pop() {
		size--;
	}
	int top() {
		return data[size - 1];
	}
	int getMin() {
		return min[size - 1];
	}
};
