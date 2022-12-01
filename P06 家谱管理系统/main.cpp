#define _CRT_SECURE_NO_WARNINGS 
#include"FamilyTree.h"
using namespace std;

int main()
{
	cout << "==================================================" << endl;
	cout << "**                 ���׹���ϵͳ                 **" << endl;
	cout << "==================================================" << endl;
	cout << "**\t\t��ѡ��Ҫִ�еĲ�����\t\t**" << endl;
	cout << "**\t\tA --- ���Ƽ���\t\t\t**" << endl;
	cout << "**\t\tB --- ��Ӽ�ͥ��Ա\t\t**" << endl;
	cout << "**\t\tC --- ��ɢ�ֲ���ͥ\t\t**" << endl;
	cout << "**\t\tD --- ���ļ�ͥ��Ա����\t\t**" << endl;
	cout << "**\t\tE --- �˳�����\t\t\t**" << endl;
	cout << "==================================================" << endl;

	char operation;
	bool exitFlag = false;	//�����ж��Ƿ��˳�
	FamilyTree tree;		
	tree.InitializeTree();
	while (!exitFlag)
	{
		int faultFlag = false;//�����ж��Ƿ��������
		cout << endl << "��ѡ��Ҫִ�еĲ�����";
		cin >> operation;
		switch (operation)
		{
		case 'A':
		case 'a':
			tree.BuildFamily();
			break;
		case 'B':
		case 'b':
			tree.AddFamilyMember();
			break;
		case 'C':
		case 'c':
			tree.DelFamily();
			break;
		case 'D':
		case 'd':
			tree.RenameFamilyMember();
			break;
		case 'E':
		case 'e':
			exitFlag = true;
			break;
		default:
			faultFlag = true;
			cin.clear();
			cin.ignore(65536, '\n');
			cout << "������Ϸ���ִ�в�����" << endl;
		}
		if (!faultFlag) {
			cout << endl;
			tree.Show();
		}
			
		if (exitFlag)
			cout << "�����Ѿ��˳�..." << endl;
	}

	return 0;
}
