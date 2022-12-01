#include<iostream>
#include"PriorityQueue.h"
using namespace std;

#define MAX_PIECES_NUM 10000
#define MAX_NUM 100000

/***************************************
* 1.����һ��Ҫ�гɵĿ���
* 2.����ÿһ���Ӧ�Ļ���
* 3.�����С����
****************************************/
int main()
{
	int pieces;
	//����ľ������
	while (1) {
		cin >> pieces;
		if (pieces<=0 || pieces>MAX_PIECES_NUM || cin.fail()) {
			cout << "������һ��������" << MAX_PIECES_NUM << "��������" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else break;
	}
	//�������ȶ���
	PriorityQueue<int> PQueue(pieces);
	//��ֻ��Ҫһ��ľͷ����Ҫ�پ���
	bool noCut = (pieces == 1);
	//���ÿ��ľ��ĳ���
	while (pieces--) {
		int num;
		cin >> num;
		if (num<0 || num>MAX_NUM || cin.fail()) {
			cout << "������󣬳����˳���" << endl;
			return -1;
		}
		//���������
		PQueue.push(num);
	}

	////һ��ľͷ����Ҫ��
	//if (noCut) {
	//	cout << "ľͷ����Ҫ�⣬����Ϊ0" << endl;
	//	return 0;
	//}
		
	//���ж��д���ȡ��������С�ģ�������ͺ��
	int cost = 0;
	if (PQueue.size() == 1)	PQueue.pop(cost);
	while (PQueue.size() > 1) {
		int num1, num2, sum;
		PQueue.pop(num1);
		PQueue.pop(num2);
		sum = num1 + num2;
		PQueue.push(sum);
		cost += sum;
		//PQueue.Print();
	}
	cout << cost << endl;
}