#define _CRT_SECURE_NO_WARNINGS 

#include<string.h>
#include<iostream>
#include<assert.h>

using namespace std;

/*String �ַ�����*/
#ifndef _STRING_H_
#define _STRING_H_


const int MAX_LENGTH = 128;

class String
{
private:
	int curLen;
	char* str;
	int maxLen;

public:
	String(const String& ob);
	String(const char* init);
	String();
	~String() { delete[] str; }
	int Length() const;
	char* getString() const { return str; } //����˽�г�Ա,ע��Ҫʹ��const���ڱȽ�
	int getMaxLen() const { return maxLen; }
	int KMP_Find(String& pat) const;
	void clear();//����ַ���

	//���������
	String& operator()(int pos, int len);
	int operator==(const String& ob) const { return strcmp(str, ob.getString()) == 0; }
	int operator!=(const String& ob) const { return strcmp(str, ob.getString()) != 0; }
	friend istream& operator>>(istream& in, String& instr);
	friend ostream& operator<<(ostream& out, String& outstr);
	int operator!() const { return Length() == 0; }

	String& operator=(const String& ob);
	String& operator=(char* ob);
	String operator +(char ch);
	String& operator+(const String& ob);
	String& operator+=(const char ch);
	String& operator+=(const String& ob);
	char& operator[](int i);
};
//���ƹ��캯���������д��и���
String::String(const String& ob)
{
	str = new char[MAX_LENGTH + 1];
	if (str == NULL)
	{
		cerr << "�洢�������!" << endl;
		exit(1);
	}
	curLen = ob.Length();
	maxLen = ob.getMaxLen();
	strcpy(str, ob.getString());
}
//���ƹ��캯�����������ַ������и���
String::String(const char* init)
{
	str = new char[MAX_LENGTH + 1];
	if (str == NULL || strlen(init) > MAX_LENGTH)
	{
		cerr << "�洢�������!" << endl;
		exit(1);
	}
	curLen = strlen(init);
	maxLen = MAX_LENGTH;
	strcpy(str, init); // strcpy�ǿ�����'\0'�Զ�ֹͣ��
}
//���캯��������һ�����ַ���
String::String()
{
	str = new char[MAX_LENGTH + 1];
	if (str == NULL)
	{
		cerr << "�洢�������!" << endl;
		exit(1);
	}
	str[0] = '\0';
	curLen = 0;
	maxLen = MAX_LENGTH;
}
int String::Length() const {
	int len = 0;
	while (str[len] != 0)
		++len;
	return len;
}
int String::KMP_Find(String& pat) const
{
	int posP = 0, posT = 0; // PΪ�Ӵ���TΪ����
	int lengthP = pat.Length(), lengthT = curLen;
	int f[MAX_LENGTH];
	//����ʧЧ����
	if (1)
	{
		int lP = pat.Length();
		f[0] = -1;
		for (int j = 1; j < lP; ++j)
		{
			int i = f[j - 1];
			while (*(str + j) != *(str + i + 1) && i >= 0)
				i = f[i]; //����
			if (*(str + j) == *(str + i + 1))
				f[j] = i + 1;
			else
				f[j] = -1;
		}
	}
	//�����Ӵ����ƶ�
	while (posP < lengthP && posT < lengthT)
	{
		if (pat[posP] == str[posT])
		{
			++posP;
			++posT;
		}
		else if (posP == 0)
			++posT;
		else
			posP = f[posP - 1] + 1;
	}
	if (posP < lengthP)
		return -1;
	else
		return posT - lengthP;
}
//����ַ���
void String::clear()
{
	delete[]str;
	maxLen = MAX_LENGTH;
	curLen = 0;
	str = new char[maxLen + 1];
	if (str == NULL) {
		cout << "�ڴ�������" << endl;
		exit(1);
	}
}
//��������أ���ȡ�ַ���,��pos��ʼ������ȡlen���ַ��γ��Ӵ�����
String& String::operator()(int pos, int len)
{
	if (pos < 0 || pos + len - 1 > MAX_LENGTH || len < 0)
	{
		String* temp = new String;
		return *temp;
	}
	else
	{
		if (pos + len - 1 >= curLen)
			len = curLen - 1;
		char* ttemp = new char[MAX_LENGTH + 1];
		for (int i = 0, j = pos; i < len; ++i, ++j)
			ttemp[i] = str[j];
		ttemp[len] = '\0';
		String* temp = new String(ttemp);
		return *temp;
	}
}
//��������أ����������
istream& operator>>(istream& in, String& instr)
{
	in >> instr.str;
	int len = 0;
	while (instr[len] != '\0')
		len++;
	instr.curLen = len;
	return in;
}
//��������أ���������
ostream& operator<<(ostream& out, String& outstr)
{
	out << outstr.str;
	return out;
}
//��������أ���һ���ַ��ӵ�String��
String String::operator+(char ch)
{
	String res(*this);
	int len = res.Length();
	res[len] = ch;
	res[len + 1] = '\0';
	res.curLen++;
	return res;
}
//��������أ������д�ob����
String& String::operator=(const String& ob)
{
	if (&ob != this)
	{
		delete[] str;
		str = new char[MAX_LENGTH + 1];
		if (!str)
		{
			cerr << "�ڴ治��!" << endl;
			exit(1);
		}
		curLen = ob.Length();
		strcpy(str, ob.getString());
	}
	else
		cout << "�ַ�������ֵ����!" << endl;
	return *this;
}
//��char�и�ֵ���ַ���
String& String::operator=(char* ob)
{
	delete[] str;
	str = new char[MAX_LENGTH + 1];
	if (!str || strlen(ob) > MAX_LENGTH)
	{
		cerr << "�ڴ治��!" << endl;
		exit(1);
	}
	else {
		strcpy(str, ob);
		curLen = Length();
	}
	return *this;
}
//��������أ��������ַ����ϲ��������һ���ַ���
String& String::operator+(const String& ob)
{
	curLen += ob.Length();
	char* ttemp = new char[MAX_LENGTH + 1];
	if (!ttemp)
	{
		cerr << "�ַ����±�Խ��!" << endl;
		exit(1);
	}
	strcpy(ttemp, str);
	strcpy(ttemp, ob.getString());
	String* temp = new String(ttemp);
	delete[] ttemp;
	return *temp;
}
//��������أ�������
String& String::operator+=(const String& ob)
{
	char* temp = str;
	curLen += ob.Length();
	str = new char[MAX_LENGTH + 1];
	if (!str)
	{
		cerr << "�ַ����±�Խ��!" << endl;
		exit(1);
	}
	strcpy(str, temp);
	strcpy(str, ob.getString());
	delete[] temp;
	return *this;
}
String& String::operator+=(const char ch)
{
	char* temp = str;
	curLen++;
	str = new char[MAX_LENGTH + 1];
	if (!str)
	{
		cerr << "�ַ����±�Խ��!" << endl;
		exit(1);
	}
	strcpy(str, temp);
	strcpy(str, &ch);
	delete[] temp;
	return *this;
}
//��������أ���������ȡ���е�i���ַ�
char& String::operator[](int i)
{
	if (i < 0 && i >= curLen)
	{
		cout << "�ַ����±곬��!" << endl;
		exit(1);
	}
	return str[i];
}
#endif  // ! _STRING_H_

/*List ������*/
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
	bool Insert(int i, const Type& x);					//�ڵ�i��Ԫ�غ������x
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


#endif // !_SINGLELIST_H_

/*RBTree �������*/
#ifndef _RBTREE_H_
#define _RBTREE_H_

//��ɫ
enum Color
{
	RED,
	BLACK,
};
template<class KeyType, class ValType>
struct RBTreeNode
{
	RBTreeNode<KeyType, ValType>* _left;	//��ָ��
	RBTreeNode<KeyType, ValType>* _right;	//��ָ��
	RBTreeNode<KeyType, ValType>* _parent;	//˫��ָ��
	KeyType _key;							//�ؼ��Ƚ���
	ValType _data;							//����
	Color _color;							//�����ɫ

	RBTreeNode(const KeyType key, const ValType data)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _key(key)
		, _data(data)
		, _color(RED)
	{}
};

template<class KeyType, class ValType>
class RBTree
{
	typedef RBTreeNode<KeyType, ValType> Node;
private:
	Node* _root;//������ĸ��ڵ�
public:
	int curSize;//������Ĵ�С(���н��ĸ���)

	RBTree() :_root(nullptr), curSize(0) {}				//���캯��
	~RBTree() { _Destory(_root); }						//��������

	Node* Find(const KeyType& key);						//���ҽ������λ��
	bool Insert(const KeyType key, const ValType data);	//������
	void OutPut();										//��ӡ���н�㣬�������

	bool IsRBTree();									//�ж��Ƿ���������
	bool IsEmpty() { return _root == nullptr; }			//�жϺ�����Ƿ�Ϊ��
	bool Erase(const KeyType& key);						//ɾ��ĳһ�����

private:
	void RotateL(Node* parent);							//������
	void RotateR(Node* parent);							//������
	bool _IsRBTree(Node* root, int blacknum, int count);//���ڵݹ��ж��Ƿ���������Ҫ��
	void _Destory(Node*& root);							//���ڵݹ��ͷŽ������
	void _OutPut(Node* cur);							//���ڵݹ��ӡ���н��

};

/************************************************
* ������Ĺ���
* 1. ���ֻ�к����ɫ
* 2. ���ڵ�Ϊ��ɫ
* 3. Ҷ���(NULL��)Ϊ��ɫ
* 4. ·����û���������ڵĺ�ɫ���
* 5. ÿ����㵽Ҷ��������·����������ͬ��Ŀ�ĺ�ɫ���
************************************************/
template<class KeyType, class ValType>
inline bool RBTree<KeyType, ValType>::IsRBTree()
{
	//ͷ����ǿս�㣬���Ǻ����
	if (_root == nullptr)
	{
		return true;
	}
	//����Ƿ���������2�����ڵ㲻��Ϊ��ɫ
	if (_root->_color == RED)
	{
		cout << "���ڵ�Ϊ��ɫ" << endl;
		return false;
	}

	//����Ƿ���������5��������ڵ㵽ÿһ��Ҷ���ľ�����ͬ
	int BlackNum = 0;	//·���Ϻ�ɫ������Ŀ
	Node* cur = _root;
	while (cur)
	{
		if (cur->_color == BLACK)
			BlackNum++;
		cur = cur->_left;
	}

	int count = 0;
	return _IsRBTree(_root, BlackNum, count);
}
template<class KeyType, class ValType>
inline bool RBTree<KeyType, ValType>::_IsRBTree(Node* root, int blacknum, int count)
{
	//����Ƿ���������5������������·���Ϻڽڵ���Ŀ��ͬ
	if (root == nullptr)
	{
		if (blacknum == count)
			return true;
		cout << "��·���Ϻ�ɫ�ڵ������ͬ" << endl;
		return false;
	}
	//����Ƿ���������4��·����û���������ڵĺ�ɫ���
	if (root->_color == RED && root->_parent->_color == RED)
	{
		cout << "����������ɫ�ڵ�" << endl;
		return false;
	}

	if (root->_color == BLACK)
		count++;

	//�ݹ���������α�����������������Ϊ1��Ϊtrue
	return _IsRBTree(root->_left, blacknum, count) && _IsRBTree(root->_right, blacknum, count);
}

//���ڵݹ��ͷŽ������
template<class KeyType, class ValType>
inline void RBTree<KeyType, ValType>::_Destory(Node*& root)
{
	//���ú����������ͷŽ��
	if (root == nullptr)
		return;

	_Destory(root->_left);
	_Destory(root->_right);

	delete root;
	root = nullptr;
}
//����������ʱ����ת�������������㣬ʹ�ø���㱻�Լ����Һ���ȡ�������Լ���Ϊ�Լ�������
template<class KeyType, class ValType>
inline void RBTree<KeyType, ValType>::RotateL(Node* parent)
{
	Node* subRight = parent->_right;
	Node* subRightLeft = subRight->_left;
	Node* parentP = parent->_parent;


	parent->_right = subRightLeft;
	if (subRightLeft)
		subRightLeft->_parent = parent;

	subRight->_left = parent;
	parent->_parent = subRight;

	if (parent == _root) {
		_root = subRight;
		subRight->_parent = nullptr;
	}
	else {
		subRight->_parent = parentP;
		if (parentP->_left == parent)
			parentP->_left = subRight;
		else
			parentP->_right = subRight;
	}
}
//��������˳ʱ����ת�������������㣬ʹ�ø���㱻�Լ�������ȡ�������Լ���Ϊ�Լ����Һ���
template<class KeyType, class ValType>
inline void RBTree<KeyType, ValType>::RotateR(Node* parent)
{
	Node* subLeft = parent->_left;
	Node* subLeftRight = subLeft->_right;
	Node* parentP = parent->_parent;


	parent->_left = subLeftRight;
	if (subLeftRight)
		subLeftRight->_parent = parent;

	subLeft->_right = parent;
	parent->_parent = subLeft;

	if (parent == _root) {
		_root = subLeft;
		subLeft->_parent = nullptr;
	}
	else {
		subLeft->_parent = parentP;
		if (parentP->_left == parent)
			parentP->_left = subLeft;
		else
			parentP->_right = subLeft;
	}
}
/************************************************
* ���ҽ������λ��
* ��������������߱���С���ұ߱�����
************************************************/
template<class KeyType, class ValType>
inline RBTreeNode<KeyType, ValType>* RBTree<KeyType, ValType>::Find(const KeyType& key)
{
	Node* cur = _root;
	while (cur != nullptr)
	{
		if (cur->_key > key)
			cur = cur->_left;
		else if (cur->_key < key)
			cur = cur->_right;
		else
			return cur;
	}
	return nullptr;
}

/************************************************
* �����㣺
* �������̣��ٳ�ʼΪ��ɫ �ڲ����ΪҶ�� �۵�������
* 1. �Ǹ��ڵ㣺�ɺ��ڼ���
* 2. ���ڵ��Ǻ�ɫ��ֱ�Ӳ���
* 3. ���ڵ��Ǻ�ɫ�������Ǻ�ɫ�����ڵ�������ڣ�ү����죬����ת����ү���
* 4. ���ڵ��Ǻ�ɫ�������Ǻ�ɫ���䷽��ΪLL/RR�����ڵ���ү��㣬�������ߵ���ɫ
* 5. ���ڵ��Ǻ�ɫ�������Ǻ�ɫ���䷽��ΪLR/RL������������LL/RR��ת�������4
************************************************/
template<class KeyType, class ValType>
inline bool RBTree<KeyType, ValType>::Insert(const KeyType key, const ValType data)
{
	//���1������������������Ⱦ�ɺ�ɫ����
	if (_root == nullptr)
	{
		_root = new Node(key, data);
		_root->_color = BLACK;
		curSize++;
		return true;
	}

	//����λ�ò���ڵ㣺parentΪҪ����λ�õ�˫�׽��
	Node* cur = _root, * parent = _root;
	while (cur)
	{
		if (cur->_key > key) {
			parent = cur;
			cur = cur->_left;
		}
		else if (cur->_key < key) {
			parent = cur;
			cur = cur->_right;
		}
		//�ؼ�����ͬ�򲻲���
		else
			return false;
	}

	//��cur���������ӽڵ�
	cur = new Node(key, data);
	if (parent->_key > key)
		parent->_left = cur;
	else
		parent->_right = cur;
	cur->_parent = parent;

	//���2��ֱ�Ӳ��룬�˳�
	if (parent->_color == BLACK) {
		curSize++;
		return true;
	}


	//���3/4/5�����ڵ������Ϊ�죬����Ҫ����
	while (parent && parent->_color == RED)
	{
		//��ʱ��ǰ�ڵ�һ����ү�ڵ�
		Node* granparent = parent->_parent;

		//������������Ҫ����ڵ�

		//���ڵ���ү�������
		if (parent == granparent->_left)
		{
			Node* uncle = granparent->_right;
			//���3������ڵ������Ϊ�죬ì��ת����ү���
			if (uncle && uncle->_color == RED)
			{
				//�޸���ɫ���������ϼ��
				granparent->_color = RED;
				parent->_color = uncle->_color = BLACK;

				cur = granparent;
				parent = cur->_parent;
			}
			else//���4��5������ڵ㲻���ڻ��ߴ�����Ϊ��
			{
				//���4������(�����ڵ�Ϊб��)+��ɫ
				if (cur == parent->_left) {
					RotateR(granparent);

					granparent->_color = RED;
					parent->_color = BLACK;
				}
				//���5��˫��(�����ڵ�Ϊ����)+��ɫ
				else {
					RotateL(parent);
					RotateR(granparent);
					cur->_color = BLACK;
					granparent->_color = RED;
				}
				//��ת���������ϵ�����
				break;
			}
		}

		//���ڵ���ү�����ұߣ�ʵ�ʲ�������������
		else
		{
			Node* uncle = granparent->_left;
			if (uncle && uncle->_color == RED)
			{
				parent->_color = uncle->_color = BLACK;
				granparent->_color = RED;

				cur = granparent;
				parent = cur->_parent;
			}
			else
			{
				if (cur == parent->_right) {
					RotateL(granparent);
					parent->_color = BLACK;
					granparent->_color = RED;
				}
				else {
					RotateR(parent);
					RotateL(granparent);
					cur->_color = BLACK;
					granparent->_color = RED;
				}
				break;
			}
		}
	}

	//ȷ�����ڵ�Ϊ��
	_root->_color = BLACK;
	curSize++;
	return  true;
}
/************************************************
* ɾ����㣺
* �������̣��ٿ�������� �ڿ��Լ���ɫ �ۿ��ֵ���ɫ �ܿ��ֵܺ��Ӻ�ɫ�ֲ���� �ݵ�����ɫ
* 1. ��һ�����ӣ����ӱ�ڣ�������λ
* 2. û�к��ӣ��Լ��Ǻ�ɫ��ֱ��ɾ��
* 3. û�к��ӣ��Լ��Ǻڣ��ֵ��Ǻڣ��ֵ���ͬ����/�����ӣ��ֵ���λ��������ɫ������Ⱦ�ڣ�˫�ڼ�ȥһ���
* 4. û�к��ӣ��Լ��Ǻڣ��ֵ��Ǻڣ��ֵ��з�������ӣ�������λ��������ɫ��ת�������3
* 5. û�к��ӣ��Լ��Ǻڣ��ֵ��Ǻڣ��ֵ�û���ӣ��ֵܱ�죬˫����ȥһ��ڣ����ڵ����һ��ڣ�����ת�������ڵ�
* 6. û�к��ӣ��Լ��Ǻڣ��ֵ��Ǻ죺�ֵ���λ��������ɫ���������3/4/5������һ�����
* 7. ���������ӣ��滻��ɾ�������ն������������ݹ��ҵ���ֱ�Ӻ�̣��ٴ����Ǹ���
************************************************/
template<class KeyType, class ValType>
inline bool RBTree<KeyType, ValType>::Erase(const KeyType& key)
{
	//���ڱ���������
	Node* parent = nullptr;
	Node* cur = _root;
	//���ڱ��ʵ�ʵĴ�ɾ����㼰�丸���
	Node* delParentPos = nullptr;
	Node* delPos = nullptr;

	//Ѱ�Ҵ�ɾ���Ľ��
	while (cur)
	{
		if (key < cur->_key) //����keyֵС�ڵ�ǰ����keyֵ
		{
			//���ý�����������
			parent = cur;
			cur = cur->_left;
		}
		else if (key > cur->_key) //����keyֵ���ڵ�ǰ����keyֵ
		{
			//���ý�����������
			parent = cur;
			cur = cur->_right;
		}
		else //�ҵ��˴�ɾ�����
		{
			//���1����ɾ������������Ϊ��
			if (cur->_left == nullptr)
			{
				if (cur == _root) //��ɾ������Ǹ����
				{
					_root = _root->_right; //�ø�������������Ϊ�µĸ����
					if (_root != nullptr)
					{
						_root->_parent = nullptr;
						_root->_color = BLACK; //�����Ϊ��ɫ
					}
					delete cur; //ɾ��ԭ�����
					curSize--;
					return true;
				}
				else
				{
					delParentPos = parent; //���ʵ��ɾ�����ĸ����
					delPos = cur; //���ʵ��ɾ���Ľ��
				}
				break; //���к�����ĵ����Լ�����ʵ��ɾ��
			}
			//���1����ɾ������������Ϊ��
			else if (cur->_right == nullptr)
			{
				if (cur == _root) //��ɾ������Ǹ����
				{
					_root = _root->_left; //�ø�������������Ϊ�µĸ����
					if (_root)
					{
						_root->_parent = nullptr;
						_root->_color = BLACK; //�����Ϊ��ɫ
					}
					delete cur; //ɾ��ԭ�����
					curSize--;
					return true;
				}
				else
				{
					delParentPos = parent; //���ʵ��ɾ�����ĸ����
					delPos = cur; //���ʵ��ɾ���Ľ��
				}
				break; //���к�����ĵ����Լ�����ʵ��ɾ��
			}
			//���7����ɾ��������������ӣ�ת��ì��
			else
			{
				//Ѱ�Ҵ�ɾ���������������ֱ�Ӻ��(keyֵ��С�Ľ����Ϊʵ��ɾ�����)
				Node* minParent = cur;
				Node* minRight = cur->_right;
				while (minRight->_left)
				{
					minParent = minRight;
					minRight = minRight->_left;
				}
				cur->_key = minRight->_key; //����ɾ������key��ΪminRight��key
				cur->_data = minRight->_data; //����ɾ������value��ΪminRight��value
				delParentPos = minParent; //���ʵ��ɾ�����ĸ����
				delPos = minRight; //���ʵ��ɾ���Ľ��
				break; //���к�����ĵ����Լ�����ʵ��ɾ��
			}
		}
	}

	//delPosû�б��޸Ĺ���˵��û���ҵ���ɾ�����
	if (delPos == nullptr)
		return false;

	//��¼��ɾ����㼰�丸��㣨���ں���ʵ��ɾ����
	Node* del = delPos;
	Node* delP = delParentPos;

	//���2��û�к��ӣ��Լ��Ǻ�ɫ����ֱ��ɾ��
	if (delPos->_color == RED && delPos->_left == nullptr && delPos->_right == nullptr) {
		if (del == delP->_left) //ʵ��ɾ��������丸��������
			delP->_left = nullptr;
		else //ʵ��ɾ��������丸�����Һ���
			delP->_right = nullptr;
		delete del;
		curSize--;
		return true;
	}

	//ɾ�����Ǻ�ɫ���
	if (delPos->_color == BLACK)
	{
		//���1������ɾ�������һ����ɫ�����ӣ��������Ǻ�ɫ��
		if (delPos->_left)
		{
			//�������ɫ�����ӱ�ڼ���
			delPos->_left->_color = BLACK;
		}
		//���1������ɾ�������һ����ɫ���Һ��ӣ��������Ǻ�ɫ��
		else if (delPos->_right)
		{
			delPos->_right->_color = BLACK; //�������ɫ���Һ��ӱ�ڼ���
		}
		//���3/4/5/6����ɾ���������Ҿ�Ϊ��
		else
		{
			while (delPos != _root) //����һֱ�����������
			{
				//��ɾ��������丸��������
				if (delPos == delParentPos->_left)
				{
					//�ֵܽ�����丸�����Һ���
					Node* brother = delParentPos->_right;
					//���6��brotherΪ��ɫ
					if (brother->_color == RED)
					{
						delParentPos->_color = RED;
						brother->_color = BLACK;
						RotateL(delParentPos);
						//��Ҫ��������
						brother = delParentPos->_right; //����brother�������ڱ�ѭ����ִ����������Ĵ�������
					}
					//���5��brotherΪ��ɫ���������Һ��Ӷ��Ǻ�ɫ����Ϊ��
					if (((brother->_left == nullptr) || (brother->_left->_color == BLACK))
						&& ((brother->_right == nullptr) || (brother->_right->_color == BLACK)))
					{
						brother->_color = RED;
						if (delParentPos->_color == RED)
						{
							delParentPos->_color = BLACK;
							break;
						}
						//��Ҫ��������
						delPos = delParentPos;
						delParentPos = delPos->_parent;
					}
					else
					{
						//���4��brotherΪ��ɫ�����������Ǻ�ɫ��㣬�Һ����Ǻ�ɫ����Ϊ��
						if ((brother->_right == nullptr) || (brother->_right->_color == BLACK))
						{
							brother->_left->_color = BLACK;
							brother->_color = RED;
							RotateR(brother);
							//��Ҫ��������
							brother = delParentPos->_right; //����brother������ִ����������ĵĴ�������
						}
						//���3��brotherΪ��ɫ�������Һ����Ǻ�ɫ���
						brother->_color = delParentPos->_color;
						delParentPos->_color = BLACK;
						brother->_right->_color = BLACK;
						RotateL(delParentPos);
						break; //�����ִ����Ϻ����һ������
					}
				}
				//��ɾ��������丸�����Һ���(����������)
				else
				{
					Node* brother = delParentPos->_left; //�ֵܽ�����丸��������
					//���6��brotherΪ��ɫ
					if (brother->_color == RED) //brotherΪ��ɫ
					{
						delParentPos->_color = RED;
						brother->_color = BLACK;
						RotateR(delParentPos);
						//��Ҫ��������
						brother = delParentPos->_left; //����brother�������ڱ�ѭ����ִ����������Ĵ�������
					}
					//���5��brotherΪ��ɫ���������Һ��Ӷ��Ǻ�ɫ����Ϊ��
					if (((brother->_left == nullptr) || (brother->_left->_color == BLACK))
						&& ((brother->_right == nullptr) || (brother->_right->_color == BLACK)))
					{
						brother->_color = RED;
						if (delParentPos->_color == RED)
						{
							delParentPos->_color = BLACK;
							break;
						}
						//��Ҫ��������
						delPos = delParentPos;
						delParentPos = delPos->_parent;
					}
					else
					{
						//���4��brotherΪ��ɫ�������Һ����Ǻ�ɫ��㣬�����Ǻ�ɫ����Ϊ��
						if ((brother->_left == nullptr) || (brother->_left->_color == BLACK))
						{
							brother->_right->_color = BLACK;
							brother->_color = RED;
							RotateL(brother);
							//��Ҫ��������
							brother = delParentPos->_left; //����brother������ִ����������ĵĴ�������
						}
						//���5��brotherΪ��ɫ�����������Ǻ�ɫ���
						brother->_color = delParentPos->_color;
						delParentPos->_color = BLACK;
						brother->_left->_color = BLACK;
						RotateR(delParentPos);
						break; //�����ִ����Ϻ����һ������
					}
				}
			}
		}
	}

	//����ʵ��ɾ��
	if (del->_left == nullptr) //ʵ��ɾ������������Ϊ��
	{
		//ʵ��ɾ��������丸��������
		if (del == delP->_left)
		{
			delP->_left = del->_right;
			if (del->_right)
				del->_right->_parent = delP;
		}
		//ʵ��ɾ��������丸�����Һ���
		else
		{
			delP->_right = del->_right;
			if (del->_right)
				del->_right->_parent = delP;
		}
	}
	else //ʵ��ɾ������������Ϊ��
	{
		//ʵ��ɾ��������丸��������
		if (del == delP->_left)
		{
			delP->_left = del->_left;
			if (del->_left)
				del->_left->_parent = delP;
		}
		//ʵ��ɾ��������丸�����Һ���
		else
		{
			delP->_right = del->_left;
			if (del->_left)
				del->_left->_parent = delP;
		}
	}
	delete del; //ʵ��ɾ�����
	curSize--;
	return true;
}


template<class KeyType, class ValType>
inline void RBTree<KeyType, ValType>::OutPut()
{
	_OutPut(_root);
}
template<class KeyType, class ValType>
inline void RBTree<KeyType, ValType>::_OutPut(Node* cur)
{
	if (cur == nullptr)
		return;
	_OutPut(cur->_left);
	cout << cur->_data;
	_OutPut(cur->_right);

}






#endif // !_RBTREE_H_

/*DataBase ���ݿ���*/
#ifndef _DATABASE_H_ 
#define _DATABASE_H_

#define MAX_INT 10000000

enum GENDER
{
	GENDER_MALE,
	GENDER_FEMALE
};
class Student
{
private:
	int _id;
	String _name;
	int _gender; //ʹ��ö�ٿ��Ա������
	int _age;
	String _kind;

public:
	Student() : _id(0), _name(), _gender(0), _age(0), _kind() {}
	~Student() {}
	int getID() const { return _id; }
	String getName() const { return _name; }
	int getGender() const { return _gender; }
	int getAge() const { return _age; }
	String getKind() const { return _kind; }

	void CheckInput_Int(int& num, String info);
	void CheckInput_Gender(int& gender);
	friend istream& operator>>(istream& is, Student& student);
	friend ostream& operator<<(ostream& os, const Student& student);

	friend class RBT_DataBase;
	template <class Type>
	friend class List;

	void operator=(Student& ob)
	{
		_id = ob.getID();
		_name = ob.getName();
		_gender = ob.getGender();
		_age = ob.getAge();
		_kind = ob.getKind();
	};
};
void Student::CheckInput_Int(int& num, String info)
{
	bool fail = 0;
	while (true)
	{
		cin >> num;
		if (cin.fail() || num < 0 || num >= MAX_INT)
		{
			cout << info << "�������"
				<< "������һ��С��" << MAX_INT << "��������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			fail = 1;
		}
		else if (fail == 1)
		{
			cout << "���������������Ϣ" << endl;
			break;
		}
		else
			break;
	}
}
void Student::CheckInput_Gender(int& gender)
{
	while (true)
	{
		String instr;
		cin >> instr;
		if (instr == "��")
		{
			_gender = GENDER_MALE;
			break;
		}
		else if (instr == "Ů")
		{
			_gender = GENDER_FEMALE;
			break;
		}
		cout << "�Ա���Ϣ�������,�����������л�Ů�����������������Ϣ��" << endl;
		cin.ignore(65536, '\n');
	}

}
istream& operator>>(istream& is, Student& student)
{

	student.CheckInput_Int(student._id, "����");
	is >> student._name;
	student.CheckInput_Gender(student._gender);
	student.CheckInput_Int(student._age, "����");
	is >> student._kind;
	//��ջ�������������Ϊ���������ں�����Ӱ��
	cin.ignore(65535, '\n');

	return is;
}
ostream& operator<<(ostream& os, const Student& student)
{
	//��ʽ�����
	printf("%-10d%-10s%-10s%-10d%-14s\n", student._id, student._name.getString(),
		(student.getGender() == GENDER_MALE ? "��" : "Ů"), student._age, student._kind.getString());
	return os;
}


#ifndef _RBT_DATABASE_
#define _RBT_DATABASE_
class RBT_DataBase
{
private:
	//���ǵ�����ı�ͷ
	RBTree<int, Student> table;
	int gender[2] = { 0,0 };
public:
	RBT_DataBase() {};
	~RBT_DataBase() {};

	void Initialise();//��ɶ���Ϣ��Ľ���
	void PrintTable();//��ӡ��Ϣ��

	void Insert();//����1������һ��λ�ã��ڸ�λ�ò��뿼����Ϣ
	void Delete();//����2��ɾ���ÿ��ŵ�ѧ��
	void Search();//����3�����Ҹ�����Ϣ
	void Change();//����4�����ݿ����޸Ŀ�����Ϣ
	void Census();//����5��ͳ�ƣ��������˵���Ϣ�����
	void Cancel();//����0��ȡ������

	void Wait();									//�ȴ���һ��ָʾ
	bool IsRepeated(int ID);						//�鿴�ÿ����Ƿ��ظ���
	bool IsEmpty() { return table.IsEmpty(); }//�����Ƿ����
	int	Size() { return table.curSize; }			//����ϵͳ��һ���м�������
	void CheckInput_Int(int& num);					//�������������Ƿ���Ϲ涨
};
//�������������Ƿ���Ϲ涨
void RBT_DataBase::CheckInput_Int(int& num) {
	while (true) {
		cin >> num;
		if (cin.fail() || num < 0 || num >= MAX_INT) {
			cout << "������һ��С��" << MAX_INT << "��������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
}
//��ɶ���Ϣ��Ľ���
void RBT_DataBase::Initialise()
{
	int num = 0;
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	cout << "�����뿼��������" << endl;
	//ѭ�����룬ֱ���������������
	CheckInput_Int(num);

	gender[GENDER_MALE] = gender[GENDER_FEMALE] = 0;

	cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
	for (int i = 0; i < num; ++i) {
		Student temp;
		cin >> temp;
		if (IsRepeated(temp.getID())) {
			cout << "�ÿ��Ŷ�Ӧ�Ŀ����Ѵ���,���������룡" << endl;
			i--;//���������Ԫ��
		}
		else {
			table.Insert(temp.getID(), temp);//���Ǵ�ͷ������һ���ڵ㿪ʼ
			gender[temp.getGender()]++;
		}

	}
	PrintTable();
}
//��ӡ��Ϣ��
void RBT_DataBase::PrintTable()
{
	//��ӡ���ߵ�lambda����	
	auto PrintLine = []() {
		for (int i = 0; i < 5 * 10 + 4; ++i)
			cout << "��";
		cout << endl;
	};
	if (table.IsEmpty()) { cout << "����ϵͳ���������ݣ�\n"; }
	else {
		cout << endl;
		PrintLine();
		cout << "����      ����      �Ա�      ����      �������\n";
		PrintLine();

		table.OutPut();

		PrintLine();
	}
}
//����1������һ��λ�ã��ڸ�λ�ò��뿼����Ϣ
void RBT_DataBase::Insert()
{
	while (true) {
		cout << "������ÿ������ţ��������Ա����估�������" << endl;
		Student temp;
		cin >> temp;
		if (IsRepeated(temp.getID()))
			cout << "�ÿ��Ŷ�Ӧ�Ŀ����Ѵ���,���������룡" << endl;
		else {
			table.Insert(temp.getID(), temp);
			gender[temp.getGender()]++;
			break;
		}
	}

}
//����2��ɾ���ÿ��ŵ�ѧ��
void RBT_DataBase::Delete()
{
	int ID;
	cout << "��ѡ����Ҫɾ���Ŀ����Ŀ��ţ�";
	CheckInput_Int(ID);
	if (ID == 0) { cout << "������ȡ��" << endl; return; }
	if (IsEmpty()) {
		cout << "�ñ�Ϊ�ձ�����ɾ����" << endl;
		return;
	}
	if (!IsRepeated(ID))
	{
		cout << "�Ҳ�������Ϊ " << ID << " �Ŀ���" << endl;
		return;
	}
	RBTreeNode<int, Student>* temp;
	cout << "��ɾ���Ŀ�����Ϣ�ǣ�";
	temp = table.Find(ID);
	gender[temp->_data.getGender()]--;
	cout << temp->_data;
	table.Erase(ID);
}
//����3�����Ҹ�����Ϣ
void RBT_DataBase::Search()
{
	cout << "������Ҫ���ҵĿ����Ŀ��ţ�";
	int ID;
	CheckInput_Int(ID);
	if (ID == 0) { cout << "������ȡ��" << endl; return; }
	//����
	RBTreeNode<int, Student>* temp = table.Find(ID);
	if (temp == nullptr)
		cout << "���޴���!" << endl;
	else {
		cout << "����      ����      �Ա�      ����      �������" << endl;
		cout << temp->_data;
	}
}
//����4�����ݿ����޸Ŀ�����Ϣ
void RBT_DataBase::Change()
{
	int ID;
	cout << "��ѡ����Ҫ�޸ĵĿ����Ŀ��ţ�";
	CheckInput_Int(ID);
	if (ID == 0) { cout << "������ȡ��" << endl; return; }
	//����
	RBTreeNode<int, Student>* temp = table.Find(ID);
	if (temp == nullptr)
		cout << "���޴���!" << endl;
	else {
		cout << "����      ����      �Ա�      ����      �������\n";
		cout << temp->_data;
		gender[temp->_data.getGender()]--;
		cout << "����������Ҫ�޸ĵĿ����Ŀ��ţ��������Ա����估�������" << endl;
		Student change;
		cin >> change;
		if (change.getID() != ID) {
			if (table.Find(change.getID()) != nullptr) {
				cout << "�����Ѵ��ڣ��˴��޸Ĵ���" << endl;
				return;
			}
			table.Erase(ID);
			table.Insert(change.getID(), change);
		}
		else
			temp->_data = change;
		gender[change.getGender()]++;
	}
}
//����5��ͳ�ƣ�Ŀǰ�ǰ������˵���Ϣ�����
void RBT_DataBase::Census()
{
	//PrintTable();
	auto PrintLine = []() {
		for (int i = 0; i < 5 * 10 + 4; ++i)
			cout << "-";
		cout << endl;
	};
	cout << endl;
	PrintLine();
	cout << "����������" << table.curSize << endl;
	PrintLine();
	cout << "�Ա�ͳ�ƣ�" << endl;
	cout << "����������" << gender[GENDER_MALE] << endl;
	cout << "Ů��������" << gender[GENDER_FEMALE] << endl;
	PrintLine();
}
//����0��ȡ������
void RBT_DataBase::Cancel()
{
	cout << "�ò����Ѿ�ȡ��" << endl;
	Wait();
}
//�鿴�ÿ����Ƿ��ظ���
bool RBT_DataBase::IsRepeated(int ID)
{
	return table.Find(ID) != nullptr;
}
//�ȴ���һ��ָʾ
void RBT_DataBase::Wait()
{
	cout << endl << "�س�����������" << endl;
	cin.clear();
	cin.ignore(1024, '\n');
	cin.get();
	return;
}
#endif // !_RBT_DATABASE_


#ifndef _LIST_DATABASE_
#define _LIST_DATABASE_
class List_DataBase
{
private:
	//���ǵ�����ı�ͷ
	List<Student> table;
	int gender[2] = { 0,0 };

public:
	List_DataBase() {};
	~List_DataBase() {};

	void Initialise(); //��ɶ���Ϣ��Ľ���
	void PrintTable(); //��ӡ��Ϣ��

	void Insert(); //����1������һ��λ�ã��ڸ�λ�ò��뿼����Ϣ
	void Delete(); //����2��ɾ���ÿ��ŵ�ѧ��
	void Search(); //����3�����Ҹ�����Ϣ
	void Change(); //����4�����ݿ����޸Ŀ�����Ϣ
	void Census(); //����5��ͳ�ƣ��������˵���Ϣ�����
	void Cancel(); //����0��ȡ������

	void Wait();										   //�ȴ���һ��ָʾ
	bool IsRepeated(int ID);							   //�鿴�ÿ����Ƿ��ظ���
	bool IsEmpty() { return (this->table.Length() == 0); } //�����Ƿ����
	int Size() { return table.Length(); }				   //����ϵͳ��һ���м�������
	int FindLocation(int ID);							   //����ID�ҵ���Ӧ���ŵ�����λ��
	void CheckInput_Int(int& num);						   //�������������Ƿ���Ϲ涨
};
//��ɶ���Ϣ��Ľ���
void List_DataBase::Initialise()
{
	int num = 0;
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	cout << "�����뿼��������" << endl;
	//ѭ�����룬ֱ���������������
	CheckInput_Int(num);

	gender[0] = gender[1] = 0;

	cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
	for (int i = 0; i < num; ++i)
	{
		Student temp;
		cin >> temp;
		if (IsRepeated(temp.getID()))
		{
			cout << "�ÿ��Ŷ�Ӧ�Ŀ����Ѵ���,���������룡" << endl;
			i--; //���������Ԫ��
		}
		else {
			table.Insert(i, temp); //���Ǵ�ͷ������һ���ڵ㿪ʼ
			gender[temp.getGender()]++;
		}
	}
	PrintTable();
}
//��ӡ��Ϣ��
void List_DataBase::PrintTable()
{
	//��ӡ���ߵ�lambda����
	auto PrintLine = []()
	{
		for (int i = 0; i < 5 * 10 + 4; ++i)
			cout << "��";
		cout << endl;
	};

	if (table.IsEmpty())
	{
		cout << "����ϵͳ���������ݣ�\n";
	}
	else
	{
		cout << endl;
		PrintLine();
		cout << "����      ����      �Ա�      ����      �������\n";
		PrintLine();
		int num = Size();
		//һ��ʼ��ͷ���
		for (int i = 0; i < num; ++i)
		{
			cout << *table.getData(i + 1);
		}
		PrintLine();
	}
}
//����1������һ��λ�ã��ڸ�λ�ò��뿼����Ϣ
void List_DataBase::Insert()
{
	cout << "������Ҫ����Ŀ�����λ�ã�";
	int pos;
	int maxPos = Size();
	//���봦������Խ�磬����ȡ������
	while (true)
	{
		CheckInput_Int(pos);
		if (pos == 0)
		{
			cout << "������ȡ��" << endl;
			return;
		}
		else if (pos <= 0 || pos > maxPos + 1)
		{
			cout << "��λ��Խ�磬�����λ��Ӧ��Ϊ������" << maxPos << "�������������������룡" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
			break;
	}
	while (true)
	{
		cout << "������ÿ������ţ��������Ա����估�������" << endl;
		Student temp;
		cin >> temp;
		if (IsRepeated(temp.getID()))
			cout << "�ÿ��Ŷ�Ӧ�Ŀ����Ѵ���,���������룡" << endl;
		else
		{
			table.Insert(pos - 1, temp); //�ǲ���pos-1��Ԫ�صĺ���
			gender[temp.getGender()]++;
			break;
		}
	}
}
//����2��ɾ���ÿ��ŵ�ѧ��
void List_DataBase::Delete()
{
	int ID;
	cout << "��ѡ����Ҫɾ���Ŀ����Ŀ��ţ�";
	CheckInput_Int(ID);
	if (ID == 0)
	{
		cout << "������ȡ��" << endl;
		return;
	}
	if (IsEmpty())
	{
		cout << "�ñ�Ϊ�ձ�����ɾ����" << endl;
		return;
	}
	if (!IsRepeated(ID))
	{
		cout << "�Ҳ�������Ϊ " << ID << " �Ŀ���" << endl;
		return;
	}
	int loc = FindLocation(ID);
	Student temp;
	table.Remove(loc, temp);
	gender[temp.getGender()]--;
	cout << "��ɾ���Ŀ�����Ϣ�ǣ�";
	cout << temp;
}
//����3�����Ҹ�����Ϣ
void List_DataBase::Search()
{
	cout << "������Ҫ���ҵĿ����Ŀ��ţ�";
	int ID;
	CheckInput_Int(ID);
	if (ID == 0)
	{
		cout << "������ȡ��" << endl;
		return;
	}
	//����
	LinkNode<Student>* ptr = table.getHead();
	while (ptr != NULL)
	{
		if (ptr->data.getID() == ID)
		{
			cout << "����      ����      �Ա�      ����      �������" << endl;
			cout << ptr->data;
			return;
		}
		ptr = ptr->link;
	}
	cout << "���޴���!" << endl;
}
//����4�����ݿ����޸Ŀ�����Ϣ
void List_DataBase::Change()
{
	int ID;
	cout << "��ѡ����Ҫ�޸ĵĿ����Ŀ��ţ�";
	CheckInput_Int(ID);
	if (ID == 0)
	{
		cout << "������ȡ��" << endl;
		return;
	}
	int pos = FindLocation(ID);
	if (pos == 0)
	{
		cout << "�Ҳ�������Ϊ " << ID << " �Ŀ���" << endl;
		return;
	}
	cout << "����������Ҫ�޸ĵĿ����Ŀ��ţ��������Ա����估�������" << endl;
	gender[table.getData(pos)->getGender()]--;
	Student temp;
	cin >> temp;
	if (FindLocation(temp.getID()) != 0) {
		cout << "�����Ѵ��ڣ��˴��޸Ĵ���" << endl;
		gender[temp.getGender()]++;
		return;
	}
	gender[temp.getGender()]++;
	table.setData(pos, temp);
}
//����5��ͳ�ƣ�Ŀǰ�ǰ������˵���Ϣ�����
void List_DataBase::Census()
{
	//PrintTable();
	auto PrintLine = []() {
		for (int i = 0; i < 5 * 10 + 4; ++i)
			cout << "-";
		cout << endl;
	};
	cout << endl;
	PrintLine();
	cout << "����������" << table.Length() << endl;
	PrintLine();
	cout << "�Ա�ͳ�ƣ�" << endl;
	cout << "����������" << gender[GENDER_MALE] << endl;
	cout << "Ů��������" << gender[GENDER_FEMALE] << endl;
	PrintLine();
}
//����0��ȡ������
void List_DataBase::Cancel()
{
	cout << "�ò����Ѿ�ȡ��" << endl;
	Wait();
}
//�鿴�ÿ����Ƿ��ظ���
bool List_DataBase::IsRepeated(int ID)
{
	LinkNode<Student>* ptr = table.getHead();
	while (ptr != NULL)
	{
		if (ptr->data.getID() == ID)
			return true;
		ptr = ptr->link;
	}
	return false;
}
//���Ҹ�Ԫ�س��ֵ�λ�ã����Ҳ����򷵻�0
int List_DataBase::FindLocation(int ID)
{
	if (IsRepeated(ID) == 0)
	{
		return 0;
	}
	LinkNode<Student>* cur = table.getHead();
	int pos = 0;
	while (cur != NULL)
	{
		if (cur->data.getID() == ID)
		{
			return pos;
		}
		pos++;
		cur = cur->link; //������һ�䣬������ѭ��
	}
	return 0;
}
//�ȴ���һ��ָʾ
void List_DataBase::Wait()
{
	cout << endl
		<< "�س�����������" << endl;
	cin.clear();
	cin.ignore(1024, '\n');
	cin.get();
	return;
}
//�������������Ƿ���Ϲ涨
void List_DataBase::CheckInput_Int(int& num)
{
	while (true)
	{
		cin >> num;
		if (cin.fail() || num < 0 || num >= MAX_INT)
		{
			cout << "������һ��С��" << MAX_INT << "��������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
}
#endif // !_LIST_DATABASE_

#endif // !_DATABASE_H_