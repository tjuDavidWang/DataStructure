#define _CRT_SECURE_NO_WARNINGS 
#include<iostream>
#include<string.h>
using namespace std;

/*String�ַ�����*/
#ifndef _STRING_H_
#define _STRING_H_

using namespace std;
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
#endif

/*Stackջ��*/
#ifndef _STACK_H_
#define _STACK_H_

//��������Ķ���
template <class Type>
struct LinkNode {
	Type data;				//������
	LinkNode<Type>* link;	//��ָ����
	//���ֹ��캯�������Ƿ������ݶ�����г�ʼ��
	LinkNode(LinkNode<Type>* ptr = NULL) :link(ptr) {}
	LinkNode(const Type& item, LinkNode<Type>* ptr = NULL) :data(item), link(ptr) {}
};

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

#endif // !_STACK_H_