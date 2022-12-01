#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<chrono>
#include"Sort.h"
using namespace std;

#define MAX_NUM 100000000
#define MAX_SORT_NUM 10000

//Ĭ��������Ϊ�ǵݼ�����������
/**************************************
* 1.����������������
* 2.����������飺����˳������
* 3.���в�ͬ�����򷽷�����������
**************************************/

void Sort(int* arr, int num, const char* funcName, void(*sort)(int*, int, SortData&)) {

	//��arr�е�Ԫ�ظ��Ƹ�temp
	int* temp = new int[num];
	memcpy(temp, arr, num * sizeof(int));

	SortData data;

	printf("%-15s", funcName);

	//����ʵ������г��ÿ�<chrono>�������ʱ
	auto start = chrono::steady_clock::now();

	sort(temp, num, data);

	auto end = chrono::steady_clock::now();
	chrono::duration<double, std::milli>elapsed = end - start;

	printf("\t%10.0lfms", elapsed.count());
	printf("\t%15lld", data.compareTimes);
	printf("\t%15lld\n", data.moveTimes);

	delete[]temp;


}
void SortProcess(int* arr, int num, const char* name) {
	cout << endl;
	cout << "===============================================================" << endl;
	cout << "**                         " << name << "                         **" << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "�㷨����                ʱ��           �Ƚϴ���        �ƶ�����" << endl;
	if (num > MAX_SORT_NUM) {
		cout << "ð������              ������" << endl;
		cout << "ѡ������              ������" << endl;
		cout << "ֱ�Ӳ�������          ������" << endl;
		cout << "�۰��������          ������" << endl;
	}
	else {
		Sort(arr, num, "ð������", BubbleSort);
		Sort(arr, num, "ѡ������", SelectSort);
		Sort(arr, num, "ֱ�Ӳ�������", straightInsertSort);
		Sort(arr, num, "�۰��������", binaryInsertSort);
	}
	Sort(arr, num, "ϣ������", ShellSort);
	Sort(arr, num, "��������", QuickSort);
	Sort(arr, num, "������", HeapSort);
	Sort(arr, num, "�鲢����", MergeSort);
	Sort(arr, num, "��������", CountSort);
	Sort(arr, num, "MSD��������", MSDRadixSort);
	Sort(arr, num, "LSD��������", LSDRadixSort);
	cout << "===============================================================" << endl;


}

int main()
{
	//չʾ����
	cout << "====================================================" << endl;
	cout << "**                  �����㷨�Ƚ�                  **" << endl;
	cout << "====================================================" << endl;
	cout << "**                  1.ð������                    **" << endl;
	cout << "**                  2.ѡ������                    **" << endl;
	cout << "**                  3.ֱ�Ӳ�������                **" << endl;
	cout << "**                  4.�۰��������                **" << endl;
	cout << "**                  5.ϣ������                    **" << endl;
	cout << "**                  6.��������                    **" << endl;
	cout << "**                  7.������                      **" << endl;
	cout << "**                  8.�鲢����                    **" << endl;
	cout << "**                  9.��������                    **" << endl;
	cout << "**                  10.MSD��������                **" << endl;
	cout << "**                  11.LSD��������                **" << endl;
	cout << "====================================================" << endl;
	cout << endl;
	cout << "������Ҫ����������ĸ�����";
	int num;
	while (1) {
		cin >> num;
		if (cin.fail() || num < 0 || num > MAX_NUM) {
			cout << "������һ��������" << MAX_NUM << "��������" << endl;
			cin.clear();
			cin.ignore(65536, '\n');
		}
		else break;
	}

	int* arr = new int[num];
	GetArray _array;

	_array.randomArray(arr, num);
	cout << "��" << num << "��Ԫ�ص��������������" << endl;

	SortProcess(arr, num, "�������");

	_array.ascendArray(arr, num);
	SortProcess(arr, num, "��������");

	_array.descendArray(arr, num);
	SortProcess(arr, num, "��������");



}
