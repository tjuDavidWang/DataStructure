#include<iostream>
#include<assert.h>

using namespace std;

#pragma once
#ifndef _SINGLELIST_H_
#define _SINGLELIST_H_

#include<iostream>
using namespace std;
//������ͷ���ĵ�������

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
	LinkNode<Type>* first;								//�����ͷָ��,�п�ͷ���
public:
	List() { first = new LinkNode<Type>; }
	List(const Type& x) { first = new LinkNode<Type>(x); }
	List(const List<Type>& L);				//���ƹ��캯��
	~List() { makeEmpty(); }						//��������
	void makeEmpty();									//���������ó�Ϊ�ձ�
	int Length();										//��������ĳ���
	LinkNode<Type>* getHead()const { return first; }	//����ͷָ��ĵ�ַ
	void setHead(LinkNode<Type>* ptr) { first = ptr; };	//����ͷ���ĵ�ַ
	LinkNode<Type>* Search(Type x);						//����������x��Ԫ��
	LinkNode<Type>* Locate(int i);						//��������i��Ԫ�صĵ�ַ
	Type* getData(int i);								//�õ���i��Ԫ�ص�ֵ
	void setData(int i, Type& x);						//��x�޸ĵ�i��Ԫ�ص�ֵ
	bool Insert(int i, const Type& x);						//�ڵ�i��Ԫ�غ������x
	bool Remove(int i, Type& x);						//ɾ����i��Ԫ��,x������ֵ
	bool IsEmpty()const									//�жϱ��Ƿ�Ϊ��
	{
		return first->link == NULL ? true : false;
	}
	bool IsFull()const { return false; }				//�ж������Ƿ�����,ֱ�ӷ���false
	void Input(int num);								//����
	void Output();										//���
	List<Type>& operator=(const List<Type>& L);	//���غ���:��ֵ

	void push_back(const Type& x) {
		Insert(Length(), x);
	}
	void pop_back(Type& x) {
		Remove(Length(), x);
	}
};

//���ƹ��캯��
template<class Type>List<Type>::List(const List<Type>& L)
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
template<class Type>bool List<Type>::Insert(int i, const Type& x)
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
template<class Type>List<Type>& List<Type>::operator=(const List<Type>& L)
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


#endif

/*Queue ������*/
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

#endif // !_QUEUE_H_

/*Vector ������*/
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
			return i.data - j.data;
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

/*Activities �ؼ����*/
#ifndef _AOE_NET_H_
#define _AOE_NET_H_
#define MAX_N 100
#define ERROR_EXIT_OUTPUT 0 

struct Edge {
	int fromVertex;
	int toVertex;	//����Ľ��
	int weight;		//�ߵ�Ȩ��
	bool isKey;
	Edge(int from = -1, int to = -1, int val = 0,bool iskey=false)
		:fromVertex(from), toVertex(to), weight(val),isKey(iskey) {};
};
class AOE_Net {
private:
	int vertexNum, edgeNum;				//�������ͱ����������Ŵ�1��ʼ��
	int minTime ;						//���ʱ��
	Vector<List<Edge>> adjacentList;	//�ڽӱ�
	Vector<List<Edge>> InadjacentList;	//���ڽӱ�
	Vector<int>inDegrees;				//������е�����
	Vector<int>TopoSequence;			//����ز�����

public:
	void Initialize();	//��ʼ��AOE����
	void GetTopoSequence();	//��û���ز�����
	void CalculateTime();	//����ʱ��
	void OutputResult();	//������

};
//��ʼ��AOE����
void  AOE_Net::Initialize()
{

	//��������ͱ���
	while (1) {
		cout << "����������������" << MAX_N << "����������";
		cin >> vertexNum >> edgeNum;
		if (cin.fail() || vertexNum > MAX_N || edgeNum > MAX_N || edgeNum <= 0 || vertexNum <= 0||vertexNum==1) {
			if (vertexNum == 1)
			{
				cout << "��ͼӦ���������޻�ͼ" << endl;
				exit(1);
			}
			cout << "�������" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else
			break;
	}


	inDegrees = Vector<int>(vertexNum + 1, 0);
	for (int i = 0; i <= vertexNum; ++i) {
		inDegrees[i] = 0;
		adjacentList.push_back(List<Edge>());
		InadjacentList.push_back(List<Edge>());
	}

	//�����
	cout << "������" << edgeNum << "���ߣ����ӵ㰴��1~" << vertexNum << "��ţ���Ŀʱ��ΪС��" << MAX_N << "��������" << endl;
	int pos = 1, fromVertex, toVertex, value;
	while (pos <= edgeNum) {
		printf("��%3d���ߣ�", pos);
		cin >> fromVertex >> toVertex >> value;
		if (fromVertex > vertexNum || fromVertex <= 0 || toVertex > vertexNum || toVertex <= 0 
			|| value <= 0 || value >= MAX_N||fromVertex==toVertex)
		{
			cin.clear();
			cin.ignore(65536, '\n');
			cout << "�ñ������������������" << endl;
			pos--;
		}
		else {
			inDegrees[toVertex]++;
			//���ñ߷����ڽӱ���
			adjacentList[fromVertex].Insert(0, Edge(fromVertex, toVertex, value));
			InadjacentList[toVertex].Insert(0, Edge(toVertex, fromVertex, value));
		}
		pos++;
	}

}
//��û���ز���������
void AOE_Net::GetTopoSequence()
{
	//����ز�����
	LinkedQueue<int>TopoQueue;
	int count = 0;//�����ж��Ƿ�ɻ�
	//�Ƚ�����Ѿ�Ϊ0�ķ������
	for (int i = 1; i <= vertexNum; ++i) {
		if (inDegrees[i] == 0) {
			TopoQueue.EnQueue(i);
			TopoSequence.push_back(i);
			count++;
		}
	}
	//������ֱ�����е㶼���ز�������
	while (!TopoQueue.IsEmpty()) {
		int top = TopoQueue.DeQueue();
		for (int i = 1; i <= adjacentList[top].Length(); i++) {
			int to = adjacentList[top].getData(i)->toVertex;
			if (to == -1)
				break;
			inDegrees[to]--;
			if (inDegrees[to] == 0) {
				TopoQueue.EnQueue(to);
				TopoSequence.push_back(to);
				count++;
			}
		}
	}	
	//����������д��ڻ�
	if (count != vertexNum) {
		cout << endl;
		cout << ERROR_EXIT_OUTPUT << endl;
		exit(1);
	}

}
//����ʱ��
void AOE_Net::CalculateTime()
{
	minTime = 0;
	//��¼ÿ���¼���ʱ�䣺��ά��,�ֱ���ve/vl
	Vector<Vector<int>>VertexTime(1, Vector<int>(vertexNum + 1, 0));

	//����ve:ÿ���¼����翪ʼʱ��
	for (int i = 0; i < vertexNum; ++i) {
		int fromVertex = TopoSequence[i];
		for (int j = 1; j <= adjacentList[fromVertex].Length(); ++j) {
			int toVertex = adjacentList[fromVertex].getData(j)->toVertex;
			int value = adjacentList[fromVertex].getData(j)->weight;
			int temp = VertexTime[0][fromVertex] + value;
			if (temp > VertexTime[0][toVertex]) {
				VertexTime[0][toVertex] = temp;
			}
		}
	}

	//������������Ҫ��ʱ��
	for (int i = 1; i <= vertexNum; ++i)
		minTime = minTime > VertexTime[0][i] ? minTime : VertexTime[0][i];

	VertexTime.push_back(Vector<int>(vertexNum + 1, minTime));

	//����vl��ÿ���¼�����ʼʱ��
	for (int i = vertexNum-1; i >=0; --i) {
		int fromVertex = TopoSequence[i];
		for (int j = 1; j <= InadjacentList[fromVertex].Length(); ++j) {
			int toVertex = InadjacentList[fromVertex].getData(j)->toVertex;
			int value = InadjacentList[fromVertex].getData(j)->weight;
			int temp = VertexTime[1][fromVertex] - value;
			if (temp < VertexTime[1][toVertex]) {
				VertexTime[1][toVertex] = temp;
			}
		}
	}

	//���������翪ʼʱ��������ʼʱ��
	for (int i = 1; i < vertexNum; i++)
	{
		//ʵ��ͬһ�������˳��Ϊ������˳��
		for (int j = 1; j <= adjacentList[i].Length(); ++j)
		{
			Edge* temp = adjacentList[i].getData(j);
			int earlytime= VertexTime[0][temp->fromVertex];
			int latetime = VertexTime[1][temp->toVertex] - temp->weight;
			if (earlytime == latetime)
				adjacentList[i].getData(j)->isKey = true;
		}
	}

}
//������
void AOE_Net::OutputResult()
{
	//���
	cout << endl;
	cout << minTime << endl;
	//������Ŀ���Ҫ��
	for (int i = 1; i <= vertexNum; i++)
	{
		//ʵ��ͬһ�������˳��Ϊ������˳��
		for (int j =1;j<= adjacentList[i].Length(); ++j)
		{
			Edge* temp = adjacentList[i].getData(j);
			if(temp->isKey==true)
			cout <<temp->fromVertex << "->" << temp->toVertex << endl;
		}
	}

}
#endif // !_AOE_NET_H_
