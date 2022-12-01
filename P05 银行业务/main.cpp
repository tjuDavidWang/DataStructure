#include"Bank.h"
using namespace std;

#define MAX_N 1000

#define SPEED_A 2
#define SPEED_B 1


/**************************************************
* 1. ���봦��
* 2. ������������ķŵ�A��ż���ķŵ�B������֮��ո�ָ�
* 3. �Ƚ��ȳ������ö��н��д�������
**************************************************/

int main() {

	cout << "������һ������������һ������Ϊ�˿�������֮���ΪNλ�ͻ��ı��" << endl;

	int N, num;
	LinkedQueue<int>queueA, queueB;
	//����N������
	while (1) {
		cout << "���룺";
		cin >> N;
		if (N <= 0 || N > MAX_N || cin.fail()) {
			cout << "NΪһ��������" << MAX_N << "��������������������!" << endl;
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else
			break;
	}
	//���num������
	for (int i = 0; i < N; ++i) {
		while (1) {
			cin >> num;
			if (num <= 0 || cin.fail()) {
				cout << "numΪһ�����������������������б��!" << endl;
				cin.clear();
				cin.ignore(100000, '\n');
			}
			else
				break;
		}
		//�����Ӧ������
		if (num % 2 == 1)
			queueA.EnQueue(num);
		else
			queueB.EnQueue(num);
	}
	/*���������
	* 1.ÿ�γ�2��A���ͽ�1��B,ʹ������flag���б��
	* 2.��AΪ����ֱ�ӳ���B
	* 3.��BΪ����ֱ�ӳ���A
	*/
	int flagA = 0, flagB = 0;
	cout << "�����";
	for (int i = 0; i < N; ++i)
	{
		if (i != 0)cout << ' ';//���һ����Ų������пո�
		if (queueA.IsEmpty()) {//A����Ϊ��
			cout << queueB.DeQueue();
			continue;
		}
		if (queueB.IsEmpty()) {//B����Ϊ��
			cout << queueA.DeQueue();
			continue;
		}
		if (flagA < SPEED_A) {//A����δ�����2��
			cout << queueA.DeQueue();
			flagA++;
		}
		else if (flagA == SPEED_A) {
			if (flagB != SPEED_B) {
				cout << queueB.DeQueue();
				flagB++;
			}
			else {//��flagB==SPEED_B
				flagB = flagA = 0;		//������㣬��ʼ��һ��
				--i;
				cout << '\b';//����û��������
			}
		}
	}
	cout << endl;

}