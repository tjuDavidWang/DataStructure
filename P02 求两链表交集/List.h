#ifndef _SINGLELIST_H_
#define _SINGLELIST_H_

#include<iostream>
using namespace std;

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
	List(List<Type>& L);								//���ƹ��캯��
	~List() { makeEmpty(); }							//��������
	void makeEmpty();									//���������ó�Ϊ�ձ�
	int Length();										//��������ĳ���
	LinkNode<Type>* getHead()const { return first; }	//����ͷָ��ĵ�ַ
	void setHead(LinkNode<Type>* ptr) { first = ptr; };	//����ͷ���ĵ�ַ
	LinkNode<Type>* Search(Type x);						//����������x��Ԫ��
	LinkNode<Type>* Locate(int i);						//��������i��Ԫ�صĵ�ַ
	Type* getData(int i);								//�õ���i��Ԫ�ص�ֵ
	void setData(int i, Type& x);						//��x�޸ĵ�i��Ԫ�ص�ֵ
	bool Insert(int i, Type& x);						//�ڵ�i��Ԫ�غ������x
	bool Remove(int i, Type & x);						//ɾ����i��Ԫ��,x������ֵ
	bool IsEmpty()const									//�жϱ��Ƿ�Ϊ��
	{
		return first->link == NULL ? true : false;
	}
	bool IsFull()const { return false; }				//�ж������Ƿ�����,ֱ�ӷ���false
	void Input(int num);								//һ������
	void push_back(Type input);					//�������
	void Output();										//���
	List<Type>& operator=(List<Type>& L);				//���غ���:��ֵ
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
//�������
template<class Type>void List<Type>::push_back(Type input)
{
	LinkNode<Type>* newNode, * last;
	//�õ������Ľ��λ��
	for (last = first; last->link != NULL; last = last->link);

	newNode = new LinkNode<Type>(input);
	if (newNode == NULL) {
		cerr << "�洢�������!" << endl;
		exit(1);
	}
	last->link = newNode;
	last = newNode;
}

//���
template<class Type>void List<Type>::Output()
{
	LinkNode<Type>* cur = first->link;
	if (cur == NULL) {
		cout << "NULL" << endl;
		return;
	}
	while (cur != NULL) {
		cout << cur->data << " ";//ע������Ҫ�������<<����
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


#endif