#define _CRT_SECURE_NO_WARNINGS 
#include<string.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

/*String�ַ�����*/
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
	int f[MAX_LENGTH] = {};
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
#endif // !_STRING_H_

/*Vector������*/
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
	if (data == ob.data)
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

/*Graphͼ��*/
#ifndef _GRAPH_H_
#define _GRAPH_H_
#define INF 100000
#define UNFOUND -1
//MST���õĽ���Լ�adjacentList����ı�
struct Edge {
	int leftVertex;
	int rightVertex;	//����Ľ��
	int weight;		//�ߵ�Ȩ��
	Edge(int from = -1, int to = -1, int val = 0) :leftVertex(from), rightVertex(to), weight(val) {};
};
//����ͼ�������ȶ�������
#ifndef _GRAPH_
#define _GRAPH_
class Graph
{
private:
	//����
	Vector<String> Vertex;
	//���ܣ����ڽӾ���������ߣ��ڽӱ�֮����index����String���еײ����
	Vector<Vector<int>> Matrix;
	//Prim�㷨����С������
	Vector<Edge> MSTree;
public:
	Graph() {};
	void CreateVertex();//������������  --A
	void AddEdge();		//��ӵ����ı�  --B
	void BuildMST();	//������С������--C
	void PrintMST();	//��ʾ��С������--D
private:
	int findVertex(const String& vetex);//�鿴�Ƿ��ظ������ظ��򷵻�
	void clear();//�������ͼ����������
	void Prim(int index);//�ҵ���Vertex�е�����
	void NotConnectedCase(Vector<bool>visited);//û����ȫ��ͨ�����������Ѿ���ͨ��δ��ͨ�����
	String& getName(int index) { return Vertex[index]; }
};
int Graph::findVertex(const String& vetex) {
	if (Vertex.IsEmpty())
		return UNFOUND;
	else {
		for (int i = 0; i != Vertex.size(); ++i) {
			if (Vertex[i] == vetex)
				return i;
		}
		return UNFOUND;
	}
}
void Graph::CreateVertex() {
	clear();
	int numVertex;
	cout << "�����붥��ĸ�����";
	while (1) {
		cin >> numVertex;
		if (numVertex <= 0 || numVertex > INF || cin.fail()) {
			cin.clear();
			cin.ignore(65536, '\n');
			cout << "�������Ӧ��Ϊ������" << INF << "�������������������룡" << endl;
		}
		else
			break;
	}
	cout << "�������������������ƣ�" << endl;
	for (int i = 0; i < numVertex; ++i)
	{
		String vertexName;
		cin >> vertexName;
		//�ж��Ƿ��Ѵ���
		if (findVertex(vertexName) != UNFOUND) {
			cout << "����" << vertexName << "�Ѵ��ڣ�" << endl;
			i--;//��������ýڵ�
		}
		else
			Vertex.push_back(vertexName);
	}
	Matrix = Vector<Vector<int>>(numVertex, Vector<int>(numVertex, INF));

}
void Graph::AddEdge() {
	String vertexA, vertexB;
	int edgeLength;
	while (true)
	{
		cout << "�������������㼰�ߣ�";
		cin >> vertexA >> vertexB >> edgeLength;
		int indexA = findVertex(vertexA);
		int indexB = findVertex(vertexB);

		//ֹͣ��ȡ����
		if (edgeLength <= 0 || vertexA == "?" || vertexB == "?")
			break;

		if (indexA == -1) {
			cout << "���� " << vertexA << " ������" << endl;
			continue;
		}
		if (indexB == -1) {
			cout << "���� " << vertexB << " ������" << endl;
			continue;
		}
		if (edgeLength >= INF||edgeLength<=0) {
			cout << "�ߵ�Ȩ��Ӧ����һ��С��" << INF << "��������" << endl;
			continue;
		}
		if (edgeLength < Matrix[indexA][indexB]) {
			Matrix[indexA][indexB] = edgeLength;
			Matrix[indexB][indexA] = edgeLength;
		}

	}
}
void Graph::BuildMST()
{
	MSTree.clear();
	if (Vertex.size() == 1) {
		cout << "ֻ��һ�����㣬����������С����" << endl;
		return;
	}
	String startVertex;
	cout << "��������ʼ���㣺";
	cin >> startVertex;
	int index = findVertex(startVertex);
	if (index == -1) {
		cout << "���� " << startVertex << " ������" << endl;
		return;
	}
	//��ʼ������С��
	cout << endl;
	cout << "����Prim��С��..." << endl;
	Prim(index);
}
void Graph::PrintMST()
{
	if (MSTree.size() != Vertex.size() - 1 || Vertex.size() == 1)
	{
		cout << "��ͼ����ͨ������������С������" << endl;
		return;
	}
	else
	{
		cout << "��С�������Ķ��㼰��Ϊ��" << endl << endl;
		for (int i = 0; i < MSTree.size(); ++i)
			cout << getName(MSTree[i].leftVertex) << "-<" << MSTree[i].weight << ">->" << getName(MSTree[i].rightVertex) << '\t';
		cout << endl;
	}
}
void Graph::Prim(int index)
{
	int vertexNum = Vertex.size();
	Vector<bool>visited(vertexNum, false);
	Vector<int>distance(vertexNum, INF);
	Vector<int>nearVertex(vertexNum, index);

	distance[index] = 0;
	for (int i = 0; i < vertexNum; ++i) {
		//һ��ʼ�����ڱ�λ��
		int minIndex = index, minCost = INF;
		//�ҵ�����������ĵ��λ��
		for (int j = 0; j < vertexNum; j++) {
			if (visited[j] == false && distance[j] < minCost)
			{
				minIndex = j;
				minCost = distance[j];
			}

		}
		//����Ϊ�ѷ��ʣ����뼯����
		visited[minIndex] = true;
		if (distance[minIndex] != 0 && distance[minIndex] != INF)
			MSTree.push_back({ nearVertex[minIndex],minIndex,distance[minIndex] });
		//�������е㵽���ϵľ���
		for (int i = 0; i < vertexNum; ++i) {
			int curVertex = i;
			int curWeight = Matrix[minIndex][i];
			if (distance[curVertex] > curWeight) {
				distance[curVertex] = curWeight;
				nearVertex[curVertex] = minIndex;
			}
		}
		if (distance[minIndex] == INF)
			break;

	}
	if (MSTree.size() != vertexNum - 1) {
		NotConnectedCase(visited);
	}
	else {
		cout << "������ɣ�" << endl << endl;
	}

}
void Graph::NotConnectedCase(Vector<bool>visitedList)
{
	cout << "��ͼ����ͨ��" << endl;
	cout << "��Щ����Ѿ���ͨ��";
	for (int i = 0; i < visitedList.size(); ++i) {
		if (visitedList[i] == true)
			cout << getName(i) << " ";
	}
	cout << endl;
	cout << "��Щ�����δ��ͨ��";
	for (int i = 0; i < visitedList.size(); ++i) {
		if (visitedList[i] == false)
			cout << getName(i) << " ";
	}
	cout << endl;
}
void Graph::clear() {
	Vertex.clear();
	Matrix.clear();
	MSTree.clear();
}
#endif // !_GRAPH_
#endif // !_GRAPH_H_