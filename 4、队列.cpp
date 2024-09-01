//���е�����ʵ��
class Queue {
public:
	int* queue;
	int l, r;//��β��־��
	int length;
	Queue(int n) :l(0), r(0), length(n) {
		queue = new int[n];
	}
	~Queue() {
		delete[] queue;
	}
//���еĳ��ú���ʵ��
//�ж϶����Ƿ�Ϊ��
	bool isEmpty() {
		return l == r;
	}
//���ض�����Ԫ�صĸ���
	int size() {
		return r - l;
	}
//���������е�ͷԪ��
	int pop() {
		if (!isEmpty())	return queue[l++];
	}
//���ض����е�ͷԪ�ص�������
	int head() {
		if (!isEmpty())	return queue[l];
	}
//������м���Ԫ��
	int push(int num) {
		queue[r++] = num;
	}
//���ض����е�ͷԪ�ص�������
	int tail() {
		if (!isEmpty())	return queue[r - 1];
	}
};

//ѭ������ https://leetcode.cn/problems/design-circular-queue/description/?envType=problem-list-v2&envId=QbOER4QK&
/*ѭ��������һ���������ݽṹ����������ֻ��� FIFO���Ƚ��ȳ���ԭ���Ҷ�β�������ڶ���֮�����γ�һ��ѭ������Ҳ����Ϊ�����λ���������
ѭ�����е�һ���ô������ǿ��������������֮ǰ�ù��Ŀռ䡣��һ����ͨ�����һ��һ���������ˣ����ǾͲ��ܲ�����һ��Ԫ�أ���ʹ�ڶ���ǰ�����пռ䡣
����ʹ��ѭ�����У�������ʹ����Щ�ռ�ȥ�洢�µ�ֵ��
���ʵ��Ӧ��֧�����²�����
MyCircularQueue(k): �����������ö��г���Ϊ k ��
Front: �Ӷ��׻�ȡԪ�ء��������Ϊ�գ����� -1 ��
Rear: ��ȡ��βԪ�ء��������Ϊ�գ����� -1 ��
enQueue(value): ��ѭ�����в���һ��Ԫ�ء�����ɹ������򷵻��档
deQueue(): ��ѭ��������ɾ��һ��Ԫ�ء�����ɹ�ɾ���򷵻��档
isEmpty(): ���ѭ�������Ƿ�Ϊ�ա�
isFull(): ���ѭ�������Ƿ�������*/
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

//ѭ��˫�˶��С� https://leetcode.cn/problems/design-circular-deque/description/?envType=problem-list-v2&envId=QbOER4QK&
/*ʵ�� MyCircularDeque �� :
MyCircularDeque(int k) �����캯��, ˫�˶������Ϊ k ��
boolean insertFront()����һ��Ԫ����ӵ�˫�˶���ͷ���� ��������ɹ����� true �����򷵻� false ��
boolean insertLast() ����һ��Ԫ����ӵ�˫�˶���β������������ɹ����� true �����򷵻� false ��
boolean deleteFront() ����˫�˶���ͷ��ɾ��һ��Ԫ�ء� ��������ɹ����� true �����򷵻� false ��
boolean deleteLast() ����˫�˶���β��ɾ��һ��Ԫ�ء���������ɹ����� true �����򷵻� false ��
int getFront() )����˫�˶���ͷ�����һ��Ԫ�ء����˫�˶���Ϊ�գ����� - 1 ��
int getRear() �����˫�˶��е����һ��Ԫ�ء� ���˫�˶���Ϊ�գ����� - 1 ��
boolean isEmpty() ����˫�˶���Ϊ�գ��򷵻� true �����򷵻� false  ��
boolean isFull() ����˫�˶������ˣ��򷵻� true �����򷵻� false ��*/
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
		// ע�����ﷵ�� (r - 1 + limit) % limit λ�õ�Ԫ�أ���Ϊ r ָ����һ������λ��
	}
	bool isEmpty() {
		return !size;
	}
	bool isFull() {
		return size == limit;
	}
};
