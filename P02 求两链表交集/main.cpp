#include<iostream>
using namespace std;
#include"List.h"
#define END_OF_INPUT -1
#define MAX_INT 10000000

//�����������Ƿ���ȷ�������Ƿ����
bool IsEndOfInput(int& num) {
	//����Ƿ�������ȷ
	while (true)
	{
		cin >> num;
		if (cin.fail() || num >= MAX_INT || (num <= 0 && num != END_OF_INPUT))
		{
			cout << "�������" << "������һ��С��" << MAX_INT << "��������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	//����Ƿ�������ж�β
	if (num == END_OF_INPUT)
		return true;
	return false;
}
int main()
{
	List<int> inList1, inList2, outList;

	cout << "****************************************************" << endl;
	cout << "����˵����" << endl
		<< "1. �����2��;" << endl
		<< "2. �ֱ���ÿ�и��������ɸ����������ɵķǽ�������;" << endl
		<< "3. ��-1��ʾ���еĽ�β;" << endl
		<< "4. �����ÿո�����" << endl;

	cout << "******************���濪ʼ�������******************" << endl;
	
	int input_num;

	//�����������е�����
	while (IsEndOfInput(input_num) == false) {
		inList1.push_back(input_num);
	}
	while (IsEndOfInput(input_num) == false) {
		inList2.push_back(input_num);
	}

	LinkNode<int>* ptr1 = inList1.getHead()->link;
	LinkNode<int>* ptr2 = inList2.getHead()->link;

	//�󽻼�����
	while (ptr1 != NULL && ptr2 != NULL) {
		if (ptr1->data == ptr2->data) {
			outList.push_back(ptr1->data);
			ptr1 = ptr1->link;
			ptr2 = ptr2->link;
		}
		else if (ptr1->data < ptr2->data)
			ptr1 = ptr1->link;
		else
			ptr2 = ptr2->link;
	}

	cout << "******************���ǵĽ�������********************" << endl;
	outList.Output();
	cout << endl;
}