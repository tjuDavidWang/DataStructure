#include<iostream>
#include<assert.h>
using namespace std;

//������
#ifndef _LIST_H_
#define _LIST_H_

//��������Ķ���
template <class Type>
struct LinkNode {
	Type data;				//������
	LinkNode<Type>* link;	//��ָ����
	//���ֹ��캯�������Ƿ������ݶ�����г�ʼ��
	LinkNode(LinkNode<Type>* ptr = NULL) :link(ptr) {}
	LinkNode(const Type& item, LinkNode<Type>* ptr = NULL) :data(item), link(ptr) {}
};
//�Ե�����Ķ���
template <class Type>
class List {
protected:
	LinkNode<Type>* first;								//�����ͷָ��
public:
	List() { first = new LinkNode<Type>; }
	List(const Type& x) { first = new LinkNode<Type>(x); }
	List(List<Type>& L);					//���ƹ��캯��
	~List() { makeEmpty(); }						//��������
	void makeEmpty();									//���������ó�Ϊ�ձ�
	int Length();										//��������ĳ���
	LinkNode<Type>* getHead()const { return first; }	//����ͷָ��ĵ�ַ
	void setHead(LinkNode<Type>* ptr) { first = ptr; };	//����ͷ���ĵ�ַ
	LinkNode<Type>* Search(Type x);						//����������x��Ԫ��
	LinkNode<Type>* Locate(int i);						//��������i��Ԫ�صĵ�ַ
	Type* getData(int i);								//�õ���i��Ԫ�ص�ֵ
	void setData(int i, Type& x);						//��x�޸ĵ�i��Ԫ�ص�ֵ
	bool Insert(int i, Type& x);						//�ڵ�i��Ԫ�غ������x
	bool Remove(int i, Type& x);						//ɾ����i��Ԫ��,x������ֵ
	bool IsEmpty()const									//�жϱ��Ƿ�Ϊ��
	{
		return first->link == NULL ? true : false;
	}
	bool IsFull()const { return false; }				//�ж������Ƿ�����,ֱ�ӷ���false
	void Input(int num);								//����
	void Output();										//���
	List<Type>& operator=(List<Type>& L);	//���غ���:��ֵ
};

//���ƹ��캯��
template<class Type>List<Type>::List(List<Type>& L)
{
	Type value;
	LinkNode<Type>* from_ptr = L.getHead();
	LinkNode<Type>* to_ptr = first = new LinkNode<Type>;
	while (from_ptr->link != NULL) {
		value = from_ptr->link->data;
		to_ptr->link = new LinkNode<Type>(value);
		to_ptr = to_ptr->link;
		from_ptr = from_ptr->link;
	}
	to_ptr->link = NULL;
}
//���������ó�Ϊ�ձ�
template<class Type>void List<Type>::makeEmpty()
{
	LinkNode<Type>* q;
	while (first->link != NULL)
	{
		q = first->link;
		first->link = first->link->link;
		delete q;
	}
	delete first;
}
//��������ĳ���
template<class Type>int List<Type>::Length()
{
	int count = 0;
	LinkNode<Type>* ptr = first->link;
	while (ptr != NULL) {
		ptr = ptr->link;
		++count;
	}
	return count;
}
//����������x��Ԫ��
template<class Type>LinkNode<Type>* List<Type>::Search(Type x)
{
	LinkNode<Type>* cur = first->link;
	while (cur != NULL) {
		if (cur->data == x)
			break;
		else
			cur = cur->link;
	}
	return cur;
}
//��������i��Ԫ�صĵ�ַ(>=0),�Ҳ����򷵻�NULL
template<class Type>LinkNode<Type>* List<Type>::Locate(int i)
{
	if (i < 0 || i>Length())return NULL;
	LinkNode<Type>* cur = first;
	int k = 0;
	while (cur != NULL && k < i) {
		cur = cur->link;
		++k;
	}
	return cur;
}
//�õ���i��Ԫ�ص�ֵ,����ָ�룬���������Ƿ��и�Ԫ��
template<class Type>Type* List<Type>::getData(int i)
{
	if (i < 0)return NULL;
	LinkNode<Type>* cur = Locate(i);
	if (cur == NULL)return NULL;
	else
		return &cur->data;
}
//��x�޸ĵ�i��Ԫ�ص�ֵ
template<class Type>void List<Type>::setData(int i, Type& x)
{
	if (i <= 0)return;//iֵ̫С
	LinkNode<Type>* cur = Locate(i);
	if (cur == NULL)return;//iֵ̫��
	else
		cur->data = x;
}
//�ڵ�i��Ԫ�غ������x
template<class Type>bool List<Type>::Insert(int i, Type& x)
{
	LinkNode<Type>* cur = Locate(i);
	if (cur == NULL)return false;
	LinkNode<Type>* newNode = new LinkNode<Type>(x);
	if (newNode == NULL) {
		cerr << "�ڴ�������!" << endl;
		exit(1);
	}
	newNode->link = cur->link;
	cur->link = newNode;
	return true;
}
//ɾ����i��Ԫ��,x������ֵ
template<class Type>bool List<Type>::Remove(int i, Type& x)
{
	LinkNode<Type>* cur = Locate(i - 1);//ע���Ǵӵ�i-1��ȥ��
	if (cur == NULL || cur->link == NULL)
		return false;
	LinkNode<Type>* del = cur->link;
	cur->link = del->link;
	x = del->data;
	delete del;
	return true;
}
//����:���ú�巨������һ����������н�㼯�ɵ�������
template<class Type>void List<Type>::Input(int num)
{
	//��Ҫ��endTag/num������һ�ε�����
	LinkNode<Type>* newNode, * last;
	Type val;
	first = new LinkNode<Type>;//���ÿ�ͷ���
	if (first == NULL || num < 0) {
		cerr << "�洢�������!" << endl;
		exit(1);
	}
	if (num == 0) {
		first->link = NULL;
		return;
	}
	last = first;
	while (num--) {
		cin >> val;//�ǵö�Type���ͽ���>>���������
		newNode = new LinkNode<Type>(val);
		if (newNode == NULL) {
			cerr << "�洢�������!" << endl;
			exit(1);
		}
		last->link = newNode;
		last = newNode;
	}
}
//���
template<class Type>void List<Type>::Output()
{
	LinkNode<Type>* cur = first->link;
	while (cur != NULL) {
		cout << cur.data << endl;//ע������Ҫ�������<<����
		cur = cur->link;
	}
}
//���غ���:��ֵ
template<class Type>List<Type>& List<Type>::operator=(List<Type>& L)
{
	Type value;
	LinkNode<Type>* srcptr = L.getHead();
	LinkNode<Type>* destptr = first = new LinkNode<Type>;
	while (srcptr->link != NULL) {
		value = srcptr->link->data;//ע��Ҫ��data��=�������������
		destptr->link = new LinkNode<Type>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = NULL;//���һ��Ҫָ��NULL
	return *this;//���ز��������ַ
}


#endif // !_LIST_H_

//ջ��
#ifndef _STACK_H_
#define _STACK_H_


//��ʽջ�Ķ���:ʹ��֮ǰ������ĵ�����
template<class Type>
class Stack
{
private:
	LinkNode<Type>* top;			//ջ��ָ��
public:
	Stack() :top(NULL) {}				//���캯��
	~Stack() { makeEmpty(); }		//��������
	bool IsEmpty()const;			//���ջ�Ƿ�Ϊ��
	void makeEmpty();				//��ջ���
	Type getTop()const;		//�õ�ջ��Ԫ��

	void Push(const Type& x);		//��Ԫ��ѹ��ջ��
	Type Pop();				//��ջ��Ԫ�ص���
	bool Pop(Type& x);				//��ջ��Ԫ�ص���
	int size()const;				//���ջ��Ԫ�صĶ���

	friend ostream& operator<<<Type>(ostream& os, const Stack<Type>& stack);//���ջ�е�Ԫ��
};
//���ջ�Ƿ�Ϊ��
template<class Type>bool Stack<Type>::IsEmpty()const {
	if (top == NULL)return true;
	else return false;
}
//���ջ��Ԫ�صĶ���
template<class Type>int Stack<Type>::size() const {
	LinkNode<Type>* ptr = top;
	int cnt = 0;
	while (top != NULL) {
		top = top->link;
		cnt++;
	}
	return cnt;
}
//��ջ���
template<class Type>void Stack<Type>::makeEmpty() {
	LinkNode<Type>* del;
	while (top != NULL) {
		del = top;
		top = top->link;
		delete del;
	}
}
//��Ԫ��ѹ��ջ��
template<class Type>void Stack<Type>::Push(const Type& x) {
	top = new LinkNode<Type>(x, top);//���½�����linkָ��top
	if (top == NULL) {
		cout << "�洢�������" << endl;
		exit(1);
	}
}
//��ջ��Ԫ�ص���
template<class Type>Type Stack<Type>::Pop() {
	if (IsEmpty() == true)
		exit(1);
	LinkNode<Type>* del = top;
	Type x = top->data;
	top = top->link;
	delete del;
	return x;
}
template<class Type>bool Stack<Type>::Pop(Type& x) {
	if (IsEmpty() == true)return false;
	LinkNode<Type>* del = top;
	top = top->link;
	x = del->data;
	delete del;
	return true;
}
//�õ�ջ��Ԫ��
template<class Type>Type Stack<Type>::getTop() const {
	if (IsEmpty() == true)
		exit(1);
	return top->data;
}
//���ջ�е�Ԫ��
template<class Type>ostream& operator<<(ostream& os, const Stack<Type>& stack) {
	os << "ջ��Ԫ�صĸ��� = " << stack.size() << endl;
	LinkNode<Type>* ptr = stack.top;
	int i = 0;
	while (ptr != NULL)
		os << ++i << ":" << ptr->data << endl;
	return os;
}

#endif // !_STACK_H_

//������
#ifndef _VECTOR_H_
#define _VECTOR_H_

#define VECTOR_DEFAULT_SIZE 1

template<class Type>
class Vector
{
private:
	int curSize;		//���ݴ�С
	int maxSize;		//��ǰ����
	Type* data;			//����
public:
	//������
	class Iterator
	{
	private:
		Type* data;			//һ��ָ�룬ָ����������
	public:
		//Ĭ�Ϲ��캯��
		Iterator() :data(nullptr) {};
		//���캯��
		Iterator(Type* init_data) :data(init_data) {};

		//���������
		//�����ݲ���
		Type& operator*() { return *data; }
		//�Ƚ������
		bool operator==(const Iterator& comp)const { return data == comp.data; }
		bool operator<(const Iterator& comp)const { return data < comp.data; }
		bool operator>(const Iterator& comp)const { return data > comp.data; }
		bool operator>=(const Iterator& comp)const { return data >= comp.data; }
		bool operator<=(const Iterator& comp)const { return data <= comp.data; }
		bool operator!=(const Iterator& comp)const { return data != comp.data; }
		//���������:ǰ�úͺ���
		Vector<Type>::Iterator& operator++() { data++; return (*this); }
		Vector<Type>::Iterator operator++(int)
		{
			Vector<Type>::Iterator old = (*this);
			++(*this);
			return old;
		}
		//�Լ������:ǰ�úͺ���
		Vector<Type>::Iterator& operator--() { data--; return (*this); }
		Vector<Type>::Iterator operator--(int) {
			Vector<Type>::Iterator old = (*this);
			--(*this);
			return old;
		}
		//�����һ����
		Vector<Type>::Iterator operator+(int index)
		{
			Vector<Type>::Iterator old = (*this);
			for (int i = 0; i < index; ++i)
				++old;
			return old;
		}
		//ǰ����һ����,��Ҫʹ��typename�����ñ�����֪��Vector<Type>�Ǹ�����
		friend typename Vector<Type>::Iterator operator+(int index, typename Vector<Type>::Iterator data)
		{
			typename Vector<Type>::Iterator old = data;
			for (int i = 0; i < index; ++i)
				++old;
			return old;
		}
		//���ȥһ����
		Vector<Type>::Iterator operator-(int index)
		{
			Vector<Type>::Iterator old = (*this);
			for (int i = 0; i < index; ++i)
				--old;
			return old;
		}
		//�Լ�
		Vector<Type>::Iterator& operator+=(int index)
		{
			for (int i = 0; i < index; ++i)
				++(*this);
			return (*this);
		}
		//�Լ�
		Vector<Type>::Iterator& operator-=(int index)
		{
			for (int i = 0; i < index; ++i)
				--(*this);
			return (*this);
		}
		friend int operator-(const Vector<Type>::Iterator& i, const Vector<Type>::Iterator& j)
		{
			return int(i.data - j.data);
		}
	};
	Vector();
	Vector(int init_size);
	Vector(const Vector& ob);
	Vector(int init_size, Type indata);
	~Vector() { delete[]data; }

	int size()const { return curSize; }
	void push_back(const Type& element);				//β����������
	Type pop_back();								//ɾ��β������
	Type getLast() { return data[curSize - 1]; }
	bool insert(const Iterator place, Type item);	//��ָ��������λ�ò�������
	bool erase(const Iterator place);				//ɾ��ָ��������������
	bool clear();									//�������
	bool IsEmpty() { return curSize == 0; }

	void fillAll(const Type x);						//��Ԫ��ͳһ��ֵ
	bool Enlarge();									//����Ԫ������

	void Print();

	Type& operator[](int i);
	Vector<Type>& operator=(const Vector<Type>& ob);

	//��������Ÿ��õ�ָʾ����λ��
	Iterator begin();
	Iterator end();
	const Vector<Type>::Iterator begin()const;
	const Vector<Type>::Iterator end()const;
};
//���캯��
template<class Type> Vector<Type>::Vector()
	:curSize(0), maxSize(VECTOR_DEFAULT_SIZE)
{
	data = new Type[maxSize];
	if (data == NULL) {
		cout << "�ڴ�������" << endl;
		exit(1);
	}
}
template<class Type> Vector<Type>::Vector(int init_size)
{
	curSize = init_size;
	maxSize = (init_size / VECTOR_DEFAULT_SIZE + 1) * VECTOR_DEFAULT_SIZE;
	data = new Type[maxSize];
	if (data == NULL) {
		cout << "�ڴ�������" << endl;
		exit(1);
	}
}
template<class Type> Vector<Type>::Vector(const Vector& ob)
{
	curSize = ob.curSize;
	maxSize = ob.maxSize;
	data = new Type[maxSize];
	if (data == NULL) {
		cout << "�ڴ�������" << endl;
		exit(1);
	}
	for (int i = 0; i < curSize; ++i)
		data[i] = ob.data[i];
}
template<class Type> Vector<Type>::Vector(int init_size, Type init_data)
{
	curSize = init_size;
	maxSize = (init_size / VECTOR_DEFAULT_SIZE + 1) * VECTOR_DEFAULT_SIZE;
	data = new Type[maxSize];
	if (data == NULL) {
		cout << "�ڴ�������" << endl;
		exit(1);
	}
	for (int i = 0; i < curSize; ++i)
		data[i] = init_data;
}
//β����������
template<class Type>void Vector<Type>::push_back(const Type& element) {
	if (curSize == maxSize)
		Enlarge();
	data[curSize++] = element;//ע�������curSize����������++
}
//ɾ��β������
template<class Type>Type Vector<Type>::pop_back() {
	if (curSize == 0) {
		cout << "Vector��û��Ԫ���ˣ�" << endl;
		exit(1);
	}
	return data[--curSize];//ע����������--curSize�ٷ���
}
//��ָ��������λ�ò�������
template<class Type> bool Vector<Type>::insert(const Iterator place, Type item)
{
	//�ȼ�¼�����λ�ã�֮��Enlarge�ᵼ�����ַ�仯
	int pos = place - begin();
	if (curSize == maxSize)
		if (Enlarge() == false)return false;
	int i = 0;
	//��Ԫ�ض�����ƶ�һλ
	for (i = curSize - 1; i >= pos; --i)
		data[i + 1] = data[i];
	data[pos] = item;
	curSize++;
	return true;
}
//ɾ��ָ��������������
template<class Type>bool Vector<Type>::erase(const Iterator place)
{
	int pos = place - begin();
	if (pos < 0 || pos >= curSize)
		return false;
	while (pos < curSize - 1) {
		data[pos] = data[pos + 1];
		++pos;
	}
	curSize--;
	return true;
}
//�������
template<class Type>bool Vector<Type>::clear() {
	delete[]data;
	curSize = 0;
	maxSize = VECTOR_DEFAULT_SIZE;
	data = new Type[maxSize];
	if (data == NULL)
		return false;
	return true;
}
//ͳһ��ֵ(�����Ѿ��й�ֵ�Ĳ���)
template<class Type>void Vector<Type>::fillAll(const Type x)
{
	for (int i = 0; i < curSize; i++)
		data[i] = x;
}
//����Ԫ������
template<class Type>bool Vector<Type>::Enlarge()
{
	maxSize += VECTOR_DEFAULT_SIZE;
	Type* del = data;
	Type* newData = new Type[maxSize];
	if (newData == NULL)return false;
	for (int i = 0; i < curSize; ++i)
		newData[i] = data[i];
	data = newData;
	delete[]del;
	return true;
}
template<class Type> void Vector<Type>::Print()
{
	for (int i = 0; i < curSize; ++i)
		cout << data[i] << " ";
}
//�����±������
template<class Type>Type& Vector<Type>::operator[](int i)
{
	if (i < 0 || i >= curSize) {
		cout << "��ַ���ʴ���" << endl;
		exit(1);
	}
	return data[i];
}
//���صȺ������
template<class Type>Vector<Type>& Vector<Type>::operator=(const Vector<Type>& ob)
{
	//�����ߵĵ�ַ��ͬ��ֱ�ӷ���
	if (data == ob.data)//������==����Ŀ���
		return *this;
	this->clear();
	for (auto i = ob.begin(); i != ob.end(); ++i)
		this->push_back(*i);
	return *this;
}
template<class Type>typename Vector<Type>::Iterator Vector<Type>::begin() {
	return curSize > 0 ? typename Vector<Type>::Iterator(&data[0]) :
		typename Vector<Type>::Iterator();
}
template<class Type>inline const typename Vector<Type>::Iterator Vector<Type>::begin()const
{
	return curSize > 0 ? typename Vector<Type>::Iterator(&data[0]) :
		typename Vector<Type>::Iterator();
}

template<class Type>typename Vector<Type>::Iterator Vector<Type>::end()
{
	return curSize > 0 ? ++(typename Vector<Type>::Iterator(&data[curSize - 1])) :
		typename Vector<Type>::Iterator();
}
template<class Type>
inline const typename Vector<Type>::Iterator Vector<Type>::end()const
{
	return curSize > 0 ? ++(typename Vector<Type>::Iterator(&data[curSize - 1])) :
		typename Vector<Type>::Iterator();
}
#endif // !_VECTOR_H_

//������
#ifndef _QUEUE_H_
#define _QUEUE_H_

//����-����
const int maxSize = 50;
template<class Type>
class Queue {
public:
	Queue() {};
	~Queue() {};
	virtual bool EnQueue(const Type& x) = 0;	//��Ԫ��x�������
	virtual bool DeQueue(Type& x) = 0;			//��ͷԪ�س�����
	virtual bool getFront(Type& x)const = 0;	//��ȡ��ͷԪ�ص�ֵ
	virtual bool IsEmpty()const = 0;			//�ж϶��пշ�
	//virtual bool IsFull()const = 0;			//�ж϶�������
	virtual int getSize()const = 0;				//�����Ԫ�ظ���
};
//���е���ʽ����
template<class Type>
class LinkedQueue :public Queue<Type> {
protected:
	LinkNode<Type>* front, * rear;
public:
	LinkedQueue() :front(NULL), rear(NULL) {}
	~LinkedQueue() { makeEmpty(); }

	bool IsEmpty()const;
	void makeEmpty();
	int getSize()const;
	bool getFront(Type& x)const;

	bool EnQueue(const Type& x);
	bool DeQueue(Type& x);
	Type DeQueue();

};
//�ж϶��пշ�
template<class Type> bool LinkedQueue<Type>::IsEmpty()const
{
	return (front == NULL) ? true : false;
}
//�ÿն��У��ͷ����������н��
template<class Type> void LinkedQueue<Type>::makeEmpty()
{
	LinkNode<Type>* del;
	while (front != NULL) {
		del = front;
		front = front->link;
		delete del;
	}
}
//�����Ԫ�ظ���
template<class Type>int LinkedQueue<Type>::getSize() const
{
	LinkNode<Type>* ptr = front;
	int cnt = 0;
	while (ptr != NULL) {
		ptr = ptr->link;
		cnt++;
	}
	return cnt;
}
//��ȡ��ͷԪ�ص�ֵ
template<class Type>bool LinkedQueue<Type>::getFront(Type& x) const
{
	if (IsEmpty())return false;
	x = front->data;
	return true;
}
//��Ԫ��x�������
template<class Type>bool LinkedQueue<Type>::EnQueue(const Type& x)
{
	if (front == NULL) {
		front = rear = new LinkNode<Type>(x);//һ��ʼָ��ͬһ��ط�
		if (front == NULL) return false;
	}
	else {
		rear->link = new LinkNode<Type>(x);
		if (rear == NULL)return false;
		rear = rear->link;
	}
	return true;

}
//��ͷԪ�س�����
template<class Type>bool LinkedQueue<Type>::DeQueue(Type& x)
{
	//if (IsEmpty())return false;
	LinkNode<Type>* del = front;
	x = front->data;
	front = front->link;
	delete del;
	return true;
}
template<class Type> Type LinkedQueue<Type>::DeQueue()
{

	LinkNode<Type>* del = front;
	Type x = front->data;
	front = front->link;
	delete del;
	return x;
}

//�������Ԫ��
template<class Type>ostream& operator<<(ostream& os, const LinkedQueue<Type>& queue)
{
	os << "�����е�Ԫ�ظ�����" << queue.getSize() << endl;
	LinkNode<Type>* ptr = queue.front;
	int i = 0;
	while (ptr != NULL) {
		os << ++i << ":" << ptr->data << endl;
		ptr = ptr->link;
	}
	return os;
}

#endif // !_QUEUE_H_

//���ȶ�����
#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

template<class Type>bool Compare_Max(Type a, Type b) {
	return a > b;
}
template<class Type>bool Compare_Min(Type a, Type b) {
	return a < b;
}

template<class Type>void FilterDown(int start, int curSize, Type* heap, bool(*Comp)(Type, Type))
{
	int curPos = start;
	while (curPos >= 0) {
		int cur = curPos;
		int child = 2 * curPos + 1;//j��i������
		Type temp = heap[cur];

		//��֤��С���ѣ�ÿһ������Ҳ��
		while (child < curSize)
		{
			if (child < curSize - 1 && Comp(heap[child + 1], heap[child])) //j����ָ�����һ�����,����Ů��ѡС��
				child++;
			if (Comp(heap[cur], heap[child]))//head��ֵ��posС
				break;
			else //head��ֵ��pos��
			{
				heap[cur] = heap[child];
				cur = child;

				child = 2 * child + 1;//posת������������
			}
		}
		heap[cur] = temp;

		curPos--;
	}

}
template<class Type>void FilterUp(int start, Type* heap, bool(*Comp)(Type, Type)) {
	int cur = start, parent = (cur - 1) / 2;
	Type temp = heap[cur];
	while (cur > 0) {
		if (Comp(heap[parent], heap[cur]))//parent<heap
			break;
		else {
			heap[cur] = heap[parent];
			cur = parent;
			parent = (parent - 1) / 2;
		}
		heap[cur] = temp;
	}
}
template<class Type>int Insert(const Type& x, int& curSize, Type* heap, bool(*Comp)(Type, Type)) {
	//if (curSize == maxSize) {
	//	cout << "������" << endl;
	//	return 0;
	//}
	heap[curSize] = x;
	FilterUp(curSize, heap, Comp);
	curSize++;
	return 1;
}
template<class Type>int Remove(Type& x, int& curSize, Type* heap, bool(*Comp)(Type, Type)) {
	if (curSize == 0) {
		cout << "���ѿ�" << endl;
	}
	x = heap[0];
	heap[0] = heap[--curSize];//ȡ���һ�����ͷ��
	FilterDown(0, curSize, heap, Comp);//���϶��µ���
	return 1;
}


template<class Type>
class PriorityQueue {
protected:
	Type* data;
	int maxSize;
	int curSize;
	bool(*Compare)(Type, Type);	//���ú���ָ��ָʾ�ȽϷ�ʽ��Ĭ����Min
	enum { DefaultPQSize = 100 };
public:
	PriorityQueue(bool (*compare)(Type, Type) = Compare_Min, int size = DefaultPQSize);
	~PriorityQueue() { delete[]data; }
	bool push(const Type& x);
	bool pop(Type& x);
	int size()const { return curSize; }

	bool getFront(Type& x);

	void makeEmpty() { curSize = 0; }
	bool IsEmpty() { return curSize == 0; }
	bool IsFull() { return curSize == maxSize; }
	void Print() {
		for (int i = 0; i < curSize; ++i)
			cout << data[i] << " ";
		cout << endl;
	}
};

template<class Type>PriorityQueue<Type>::PriorityQueue(bool (*compare)(Type, Type), int size)
	:maxSize(size), curSize(0), Compare(compare) {
	data = new Type[maxSize];
	assert(data != NULL);
}
template<class Type> bool PriorityQueue<Type>::push(const Type& x)
{
	if (IsFull())return false;
	Insert(x, curSize, data, Compare);
	return true;
}
template<class Type>bool PriorityQueue<Type>::pop(Type& x)
{
	if (IsEmpty())return false;
	Remove(x, curSize, data, Compare);
	return true;
}
template<class Type>bool PriorityQueue<Type>::getFront(Type& x)
{
	if (IsEmpty())return false;
	x = data[0];
	return true;
}


#endif // !_PRIORITY_QUEUE_H_

//�Թ�������
#ifndef _MAZE_H_
#define _MAZE_H_
enum Direction { NONE = -1, UP, DOWN, LEFT, RIGHT };

#define Static_Rows 15
#define Static_Cols 15

#define Wall_Patten '#'
#define Passage_Patten '0'
#define ShowWay '1'
#define MAX_INT 1000

#define WALL "# "//"�� "
#define WAY "O "// "��"
#define PATH "  "

struct Position {
	int X, Y;
	int dir;
	int predictCost = 0;
	Position() :X(-1), Y(-1), dir(NONE), predictCost(0) {};
	Position(int x, int y) :X(x), Y(y), dir(NONE), predictCost(0) {};
	Position(int x, int y, Position dst) :X(x), Y(y), dir(NONE) {
		//���������پ��룬���ж�Ԥ�ڵıȽ�
		predictCost = (X > dst.X) ? X - dst.X : dst.X - X;
		predictCost += (Y > dst.Y) ? Y - dst.Y : dst.Y - Y;
	};
	Position(int x, int y, Direction tdir) :X(x), Y(y), dir(tdir) {};
	Position& operator =(Position pos) {
		X = pos.X;
		Y = pos.Y;
		dir = pos.dir;//push_back()�����漰����ֵ
		predictCost = pos.predictCost;
		return *this;
	}
	bool operator ==(Position& ob) {
		if (ob.X == X && ob.Y == Y)
			return true;
		else return false;
	}
	bool operator !=(Position& ob) {
		if (ob.X == X && ob.Y == Y)
			return false;
		else return true;
	}
	friend ostream& operator <<(ostream& out, const Position pos) {
		out << '<' << pos.X << ',' << pos.Y << '>' << ' ';
		return out;
	}
};


//���䴫��PrioityQueue�У�ȷ�������е����ȼ�
bool PositionCompare(Position a, Position b) {
	int distance_A, distance_B;
	distance_A = a.predictCost;
	distance_B = b.predictCost;
	bool res = distance_A < distance_B;
	return res;
}

class MazeProblem {
private:
	char** maze = {};
	int rows = 0;
	int cols = 0;
	int move[4][2] = { {1,0},{0,1},{-1,0},{0,-1} };//��������
	Vector<Position> res;//���ڴ���·�����
private:
	//��ӡ�Թ���·��
	void printMaze()
	{
		cout << endl;
		if (cols + rows >= 300) {
			cout << "�Թ�������̫�࣬�˴�������ӡ" << endl;
			return;
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (maze[i][j] == '#')
					cout << WALL;//��
				else if (maze[i][j] == ShowWay)
					cout << WAY;
				else
					cout << PATH;
			}
			cout << endl;
		}
	}
	//��������ʽ-0��ӡ�Թ�·��
	void printPath() {

		cout << endl << "�Թ�·����" << endl;
		//�Ѿ���Postion�������<<����
		for (int i = res.size() - 1; i > 0; i--) {
			cout << res[i] << " ---> ";
		}
		cout << res[0] << endl;
	}

	//DFSѰ·�㷨
	void DFS_SeekPath(Position src, Position dst) {
		printMaze();
		Vector<Position> stack;
		stack.clear();
		bool notFind = false;

		Vector<Vector<bool>> visited(rows, Vector<bool>(cols, false));
		stack.push_back(src);
		visited[src.X][src.Y] = true;

		//����ջ�Ľṹ�������
		while (stack.getLast() != dst) {
			if (stack.IsEmpty())
				notFind = 1;

			Position cur = stack[stack.size() - 1];
			Position pre;
			if (stack.size() >= 2)
				pre = stack[stack.size() - 2];

			//�������ĸ�����
			int dir = cur.dir + 1;
			while (dir < 4)
			{
				int x1 = cur.X + move[dir][0];
				int y1 = cur.Y + move[dir][1];
				Position newPos(x1, y1);
				if (maze[x1][y1] == Wall_Patten || visited[x1][y1] == true)//�õ���ǽ�����߸õ��Ѿ����ʹ���
					dir++;
				else {
					stack[stack.size() - 1].dir = dir;
					stack.push_back(newPos);
					visited[newPos.X][newPos.Y] = true;
					break;
				}
			}
			if (dir == 4)//�ĸ������ҹ���û�У�����·,����pop����
			{
				Position temp = stack.pop_back();
				visited[temp.X][temp.Y] = false;
			}
		}


		if (notFind) {
			cout << "û��·���ɽ�����ͨ��" << endl;
			exit(1);
		}
		else {
			while (stack.IsEmpty() == false) {
				Position temp = stack.pop_back();
				res.push_back(temp);
				maze[temp.X][temp.Y] = ShowWay;
			}

		}

	}
	//BFSѰ·�㷨
	void BFS_SeekPath(Position src, Position dst) {
		Vector<Vector<int>>mazePoint(rows, Vector<int>(cols, 0));//���ڼ�¼����
		Position cur = src;
		LinkedQueue<Position>queue;
		bool find = 0;

		mazePoint[src.X][src.Y] = 1;
		queue.EnQueue(cur);

		while (queue.IsEmpty() == false) {
			queue.DeQueue(cur);
			int dir = 0;
			while (dir < 4) {
				Position temp(cur.X + move[dir][0], cur.Y + move[dir][1]);
				if (temp.X == dst.X && temp.Y == dst.Y) {//���ҵ��յ���
					find = 1;
					mazePoint[temp.X][temp.Y] = mazePoint[cur.X][cur.Y] + 1;
					break;
				}
				if (mazePoint[temp.X][temp.Y] == 0 && maze[temp.X][temp.Y] != Wall_Patten) {
					mazePoint[temp.X][temp.Y] = mazePoint[cur.X][cur.Y] + 1;
					queue.EnQueue(temp);
				}
				else
					dir++;//�����������һ������
			}
			if (find == 1) {
				queue.makeEmpty();
				res.push_back(Position(dst));
				break;
			}
		}

		if (find == 0) {
			cout << "û��·���ɽ�����ͨ��" << endl;
			exit(1);
		}
		//����·��
		else {
			int x = dst.X, y = dst.Y;
			int cnt = mazePoint[x][y];
			maze[x][y] = ShowWay;
			for (; cnt > 1; cnt--) {
				Position tmp(x, y);
				int dir = 0;
				while (dir < 4) {
					int x1 = x + move[dir][0];
					int y1 = y + move[dir][1];
					if (mazePoint[x1][y1] == cnt - 1) {
						x = x1; y = y1;
						res.push_back(Position(x, y));
						maze[x][y] = ShowWay;
						break;
					}
					dir++;
				}
			}
		}
	}
	//A*�㷨Ѱ·���Ѿ����
	void AStar_SeekPath(Position src, Position dst) {
		//��ʼ������
		Vector<Vector<int>>mazePoint(rows, Vector<int>(cols, 0));
		PriorityQueue<Position>Pqueue(PositionCompare, rows);
		bool find = 0;

		mazePoint[src.X][src.Y] = 1;
		Pqueue.push(Position(src.X, src.Y, dst));

		while (Pqueue.IsEmpty() == false) {
			Position cur, top;
			Pqueue.pop(cur);
			Pqueue.getFront(top);

			int dir = 0;
			while (dir < 4) {
				Position temp(cur.X + move[dir][0], cur.Y + move[dir][1], dst);
				if (temp.X == dst.X && temp.Y == dst.Y) {//���ҵ��յ���
					find = 1;
					mazePoint[temp.X][temp.Y] = mazePoint[cur.X][cur.Y] + 1;
					break;
				}
				if (mazePoint[temp.X][temp.Y] == 0 && maze[temp.X][temp.Y] != Wall_Patten) {
					mazePoint[temp.X][temp.Y] = mazePoint[cur.X][cur.Y] + 1;
					//GotoXY(temp.Y*2, temp.X );
					//cout<< "��";
					Pqueue.push(temp);
				}
				else
					dir++;//�����������һ������
			}

			if (find == 1) {
				res.push_back(Position(dst));
				break;
			}
		}
		//GotoXY(cols * 2, rows);
		if (find == 0) {
			cout << "û��·���ɽ�����ͨ��" << endl;
			exit(1);
		}
		//����·��
		else {
			int x = dst.X, y = dst.Y;
			int cnt = mazePoint[x][y];
			maze[x][y] = ShowWay;
			for (; cnt > 1; cnt--) {
				Position tmp(x, y);
				int dir = 0;
				while (dir < 4) {
					int x1 = x + move[dir][0];
					int y1 = y + move[dir][1];
					if (mazePoint[x1][y1] == cnt - 1) {
						x = x1; y = y1;
						res.push_back(Position(x, y));
						maze[x][y] = ShowWay;
						break;
					}
					dir++;
				}
			}
		}
	}

	//�ҳ��뵱ǰλ�����ڵ�ǽ������Prim�㷨��������Թ�
	void FindBlock(int pos_X, int pos_Y, Vector<Position>& myblock) {
		if (pos_X + 1 < rows - 1 && maze[pos_X + 1][pos_Y] == Wall_Patten) {//down
			myblock.push_back(Position(pos_X + 1, pos_Y, DOWN));
		}
		if (pos_Y + 1 < cols - 1 && maze[pos_X][pos_Y + 1] == Wall_Patten) {//right
			myblock.push_back(Position(pos_X, pos_Y + 1, RIGHT));
		}
		if (pos_X - 1 > 1 && maze[pos_X - 1][pos_Y] == Wall_Patten) {//up
			myblock.push_back(Position(pos_X - 1, pos_Y, UP));
		}
		if (pos_Y - 1 > 1 && maze[pos_X][pos_Y - 1] == Wall_Patten) {//left
			myblock.push_back(Position(pos_X, pos_Y - 1, LEFT));
		}
	}
public:
	//��������Ƿ�Խ��
	void getNum(int& num)
	{
		while (true)
		{
			cin >> num;
			if (cin.fail() || num < 3 || num >= MAX_INT)
			{
				cout << "�������,��������[3," << MAX_INT << "]֮���������, ���������룺";
				cin.clear();
				cin.ignore(65535, '\n');
			}
			else
				break;
		}
	}
	//��������Թ�
	void getRandomMaze() {
		cout << "�������ͼ��������";
		getNum(rows);
		cout << "�������ͼ��������";
		getNum(cols);

		///////////////////////////////////////////Prim�Թ������㷨/////////////////////////////////////////////////

		//�ȴ���ʾ�����������̫���û���֪���ڸ�ʲô������
		cout << endl << "�Թ�������......" << endl;

		//�ѵ�ͼ���ಿ��ȫ������Ϊǽ
		maze = new char* [rows];
		for (int i = 0; i < rows; ++i) {
			maze[i] = new char[cols + 1];
			for (int j = 0; j <= cols; ++j)
				maze[i][j] = Wall_Patten;
			maze[i][cols] = '\0';
		}

		maze[1][1] = Passage_Patten;
		Vector<Position>myblock;

		//srand(1);//���������
		srand((unsigned int)(time(0)));
		int pos_X = 1, pos_Y = 1;
		FindBlock(pos_X, pos_Y, myblock);
		//��һ��ѹ������ǽ������ұߺ�������棩����ѭ��
		while (myblock.size()) {
			int BlockSize = myblock.size();
			//���ѡ��һ��ǽ������0 ~ BlockSize-1֮����������ͬʱҲ��vector��ǽ���±꣩
			int randnum = rand() % BlockSize;

			Position SelectBlock = myblock[randnum];

			//���������ǡ�ѡ���ǽ������
			pos_X = SelectBlock.X;
			pos_Y = SelectBlock.Y;
			//���ݵ�ǰѡ���ǽ�ķ�����к�������
			//��ʱ����ʼ�� ѡ���ǽ Ŀ��� ����������ͬһֱ����
			//�����ÿ󹤴ӡ�ѡ���ǽ������ǰ������Ŀ��顱
			switch (SelectBlock.dir) {
			case DOWN:
				pos_X++;
				break;
			case RIGHT:
				pos_Y++;
				break;
			case LEFT:
				pos_Y--;
				break;
			case UP:
				pos_X--;
				break;
			}
			//Ŀ��������ǽ
			if (maze[pos_X][pos_Y] == Wall_Patten) {
				//��ͨǽ��Ŀ���
				if ((pos_X > 0 && pos_X < rows - 1 && pos_Y>0 && pos_Y < cols - 1)) {
					maze[pos_X][pos_Y] = Passage_Patten;
					//�ٴ��ҳ���󹤵�ǰλ�����ڵ�ǽ
					FindBlock(pos_X, pos_Y, myblock);
				}

				if ((SelectBlock.X > 0 && SelectBlock.X < rows - 1 && SelectBlock.Y>0 && SelectBlock.Y < cols - 1))
					maze[SelectBlock.X][SelectBlock.Y] = Passage_Patten;
				/*maze[pos_X][pos_Y] = Passage_Patten;
				maze[SelectBlock.X][SelectBlock.Y] = Passage_Patten;*/

			}
			else {}//relax

			//ɾ�����ǽ(���ò��˵�ǽɾ�ˣ�������Щ�Ѿ�ʩ�����˲�����ʩ���ˣ�ͬʱҲ��ȷ������������ѭ��)
			myblock.erase(myblock.begin() + randnum);
		}
		/*if (rows % 2 == 0) {
			maze[rows - 3][cols - 3] = maze[rows - 2][cols - 2] = Passage_Patten;
			maze[rows - 2][cols - 3] = maze[rows - 3][cols - 2] = Passage_Patten;
		}*/
		maze[rows - 2][cols - 3] = Wall_Patten;
		maze[rows - 2][cols - 2] = Passage_Patten;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		cout << "���������ͼ���£�" << endl;
		printMaze();

	}
	//ʹ�ù̶��Թ�
	void getStaticMaze()
	{
		//��ʼ���̶��Թ�
		rows = Static_Rows;
		cols = Static_Cols;
		maze = new char* [rows];
		for (int i = 0; i < rows; ++i) {
			maze[i] = new char[cols + 1];
			for (int j = 0; j <= cols; ++j)
				maze[i][j] = Wall_Patten;
		}

		for (int i = 0; i < 15; ++i)
			for (int j = 0; j < 15; ++j)
				maze[i][j] = fixed_maze[i][j];
		cout << "�̶��Թ����£�" << endl;
		printMaze();
	}
	//�������㷨��ѡ��һ��Ѱ��·��
	void FindPath()
	{
		char ch;
		cout << endl << "������next�����»س�����Ѱ��·������" << endl;
		cin >> ch;
		cin.clear();
		cin.ignore(65536, '\n');

		Position src(1, 1), dst(rows - 2, cols - 2);

		cout << "****************************************" << endl;
		cout << "�Թ�Ѱ·�㷨��" << endl
			<< "1.DFS�㷨���Թ�·��" << endl
			<< "2.BFS�㷨���Թ�·��" << endl
			<< "3.A*�㷨���Թ�·��" << endl;
		cout << "****************************************" << endl;
		cout << "��ѡ���Թ�Ѱ·��ʽ�ı��(Ĭ��ΪA*�㷨)��";
		int algorithm;
		cin >> algorithm;

		switch (algorithm)
		{
		case 1:
			DFS_SeekPath(src, dst);
			break;
		case 2:
			BFS_SeekPath(src, dst);
			break;
		case 3:
			AStar_SeekPath(src, dst);
			break;
		default:
			AStar_SeekPath(src, dst);
			break;
		}
		cout << "Ĭ�����Ϊ" << src << "���յ�Ϊ" << dst << endl << endl;
		cout << "����Ϊ�Թ�·��չʾ��" << endl;
		printMaze();

		printPath();
	}
protected:
	char fixed_maze[15][15] = { //ˮƽ����Ϊy������ֱ����ΪX��
	{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
	{'#','0','0','0','#','0','#','#','#','#','#','0','0','0','#'},
	{'#','0','#','0','#','0','0','0','0','0','0','0','#','0','#'},
	{'#','0','#','0','0','0','#','#','0','#','0','#','0','0','#'},
	{'#','#','#','0','#','#','0','0','0','#','0','#','#','0','#'},
	{'#','0','0','0','#','#','#','#','0','0','0','0','0','0','#'},
	{'#','#','0','#','#','0','0','0','#','#','#','0','#','#','#'},
	{'#','0','0','0','0','0','#','#','#','#','0','0','#','0','#'},
	{'#','#','#','0','#','#','#','0','#','0','0','#','#','0','#'},
	{'#','0','#','0','#','#','#','0','0','#','0','0','0','0','#'},
	{'#','0','0','0','#','#','0','#','#','#','#','0','#','0','#'},
	{'#','#','#','0','0','#','0','#','#','0','#','#','#','0','#'},
	{'#','0','#','#','0','0','0','0','#','0','#','0','0','0','#'},
	{'#','0','0','#','0','0','0','#','#','0','0','0','#','0','#'},
	{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
	};
};



#endif // !_MAZE_H_


