#ifndef _BANK_H_
#define _BANK_H_

#include<iostream>
#include<assert.h>
using namespace std;

/*List������*/
#ifndef _SINGLELIST_H_
#define _SINGLELIST_H_
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
class SingleList {
protected:
	LinkNode<Type>* first;								//�����ͷָ��
public:
	SingleList() { first = new LinkNode<Type>; }
	SingleList(const Type& x) { first = new LinkNode<Type>(x); }
	SingleList(SingleList<Type>& L);					//���ƹ��캯��
	~SingleList() { makeEmpty(); }						//��������
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
	SingleList<Type>& operator=(SingleList<Type>& L);	//���غ���:��ֵ
};

//���ƹ��캯��
template<class Type>SingleList<Type>::SingleList(SingleList<Type>& L)
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
template<class Type>void SingleList<Type>::makeEmpty()
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
template<class Type>int SingleList<Type>::Length()
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
template<class Type>LinkNode<Type>* SingleList<Type>::Search(Type x)
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
template<class Type>LinkNode<Type>* SingleList<Type>::Locate(int i)
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
template<class Type>Type* SingleList<Type>::getData(int i)
{
	if (i < 0)return NULL;
	LinkNode<Type>* cur = Locate(i);
	if (cur == NULL)return NULL;
	else
		return &cur->data;
}
//��x�޸ĵ�i��Ԫ�ص�ֵ
template<class Type>void SingleList<Type>::setData(int i, Type& x)
{
	if (i <= 0)return;//iֵ̫С
	LinkNode<Type>* cur = Locate(i);
	if (cur == NULL)return;//iֵ̫��
	else
		cur->data = x;
}
//�ڵ�i��Ԫ�غ������x
template<class Type>bool SingleList<Type>::Insert(int i, Type& x)
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
template<class Type>bool SingleList<Type>::Remove(int i, Type& x)
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
template<class Type>void SingleList<Type>::Input(int num)
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
template<class Type>void SingleList<Type>::Output()
{
	LinkNode<Type>* cur = first->link;
	while (cur != NULL) {
		cout << cur.data << endl;//ע������Ҫ�������<<����
		cur = cur->link;
	}
}
//���غ���:��ֵ
template<class Type>SingleList<Type>& SingleList<Type>::operator=(SingleList<Type>& L)
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

/*Queue������*/
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

#endif // !_BANK_H_
