#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "DataBase.h"
using namespace std;

int main()
{
	//��������������ݿ�
	RBT_DataBase sStudentSystem;
	//�������������ݿ�
	List_DataBase rStudentSystem;

	int type;

	//ѡ�����ݿ���������
	while (1)
	{
		cout << "������ѧ��ϵͳ������������(1Ϊ����2Ϊ����)" << endl;
		cin >> type;
		if ((type != 1 && type != 2) || cin.fail())
		{
			cin.clear();
			cin.ignore(65536, '\n');
			cout << "�������" << endl;
		}
		else
			break;
	}

	//�������ݿ����͵Ĳ�ͬ���ò�ͬ�Ŀ�
	type == 1 ? rStudentSystem.Initialise() : sStudentSystem.Initialise();

	char operation;
	bool quit = false;
	while (!quit)
	{
		cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������\n\n";
		cout << "��ѡ����Ҫ���еĲ�����";
		cin >> operation;
		//��Ӧ������6��ѡ��
		switch (operation)
		{
		case '0':
			quit = true;
			cout << "�����Ѿ�ȡ���������˳�������Ϊ������Ϣ���ܽ����" << endl;
			break;
		case '1':
			type == 1 ? rStudentSystem.Insert() : sStudentSystem.Insert();
			break;
		case '2':
			type == 1 ? rStudentSystem.Delete() : sStudentSystem.Delete();
			break;
		case '3':
			type == 1 ? rStudentSystem.Search() : sStudentSystem.Search();
			break;
		case '4':
			type == 1 ? rStudentSystem.Change() : sStudentSystem.Change();
			break;
		case '5':
			type == 1 ? rStudentSystem.Census() : sStudentSystem.Census();
			break;
		default:
			cin.clear();
			cin.ignore(65536, '\n');
			cout << "δ֪����,����������" << endl;
			break;
		}

		type == 1 ? rStudentSystem.PrintTable() : sStudentSystem.PrintTable();
		cout << "��ǰϵͳ�ڹ��� " << (type == 1 ? rStudentSystem.Size() : sStudentSystem.Size()) << " ������" << endl << endl;
	}

	return 0;
}