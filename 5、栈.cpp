//ջ������ʵ��
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
//ջ�ĳ��ú���ʵ��
//�ж�ջ�Ƿ�Ϊ��
	bool isEmpty() {
		return !size;
	}
//��ջ��ѹ��һ��Ԫ��
	void push(int num) {
		stack[size++] = num;
	}
//��ջ�е���һ��Ԫ�ز����ظ�Ԫ��
	int pop() {
		return stack[--size];
	}
//����ջ�е�Ԫ�ظ���
	int getSize() {
		return size;
	}
};

//�ö���ʵ��ջ https://leetcode.cn/problems/implement-stack-using-queues/description/?envType=problem-list-v2&envId=QbOER4QK&
/*����ʹ�ö���ʵ��һ�������ȳ���ջ����֧����ͨջ��ȫ�����ֲ�����push��top��pop �� empty��
ʵ�� MyStack �ࣺ
void push(int x) ��Ԫ�� x ѹ��ջ����
int pop() �Ƴ�������ջ��Ԫ�ء�
int top() ����ջ��Ԫ�ء�
boolean empty() ���ջ�ǿյģ����� true �����򣬷��� false ��*/
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

//��ջʵ�ֶ��� https://leetcode.cn/problems/implement-queue-using-stacks/description/?envType=problem-list-v2&envId=QbOER4QK&
/*�����ʹ������ջʵ�������ȳ����С�����Ӧ��֧��һ�����֧�ֵ����в�����push��pop��peek��empty����
ʵ�� MyQueue �ࣺ
void push(int x) ��Ԫ�� x �Ƶ����е�ĩβ
int pop() �Ӷ��еĿ�ͷ�Ƴ�������Ԫ��
int peek() ���ض��п�ͷ��Ԫ��
boolean empty() �������Ϊ�գ����� true �����򣬷��� false*/
#include <stack>
using namespace std;
class MyQueue {
private:
	stack<int> in;
	stack<int> out;//outջ���˲��ܴ�inջ�е������� ���Ҫ�������ݣ�inջ�е����ݱ��뵹��
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

//��Сջ https://leetcode.cn/problems/bao-han-minhan-shu-de-zhan-lcof/description/?envType=problem-list-v2&envId=QbOER4QK&
/*�������һ�� ��Сջ �����ṩ push ��pop ��top �����������ڳ���ʱ���ڼ�������СԪ�ص�ջ��
ʵ�� MinStack ��:
MinStack() ��ʼ����ջ����
void push(int val) ��Ԫ��val�����ջ��
void pop() ɾ����ջ������Ԫ�ء�
int top() ��ȡ��ջ������Ԫ�ء�
int getMin() ��ȡ��ջ�е���СԪ�ء�*/
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
