#ifndef _SORT_H_
#define _SORT_H_

#include <cstdlib>
#include <cstring>
#include <time.h>

namespace Opearation
{
	template <typename T>
	void swap(T& t1, T& t2)
	{
		T tmp = t1;
		t1 = t2;
		t2 = tmp;
	}
}

struct SortData
{
	long long moveTimes = 0;
	long long compareTimes = 0;
};

namespace Sequence
{

	//�����������
	void randomArray(int* arr, int num, int seed = 0)
	{

		srand(seed != 0 ? seed : time(NULL));
		for (int i = 0; i < num; i++)
		{
			arr[i] = rand() % num;
		}
	}
	//������������
	void ascendArray(int* arr, int num)
	{
		for (int i = 0; i < num; ++i)
			arr[i] = i;
	}
	//������������
	void descendArray(int* arr, int num)
	{
		for (int i = 0; i < num; ++i)
			arr[i] = num - i;
	}
	//����ͬ������
	void equalArray(int* arr, int num)
	{
		for (int i = 0; i < num; ++i)
			arr[i] = 0;
	}

};
/**********************
 * ð������
 ***********************/
void BubbleSort(int* arr, int num, SortData& data)
{
	bool disorderFlag = true; //���false��δ�����������˴�����������ľ�ֱ������������
	for (int i = 0; i < num && disorderFlag; ++i)
	{
		// i��ǰ����j�Ӻ���ǰ�������ʶflag���鿴�Ƿ��Ѿ�����
		disorderFlag = false;
		for (int j = num - 1; j > i; --j)
		{
			if (arr[j - 1] > arr[j])
			{
				Opearation::swap(arr[j - 1], arr[j]);
				data.moveTimes += 3;
				disorderFlag = true;
			}
			++data.compareTimes;
		}
	}
}
/**********************
 * ��������
 ***********************/
void quickSort(int* arr, int left, int right, SortData& data)
{
	if (left < right)
	{

		//������·ȡ�ж��㷨�����Ż�
		int ptrLeft = left, ptrRight = right;
		int mid = (left + right) / 2, smallestOfThree = left;
		if (arr[mid] < arr[smallestOfThree])
			smallestOfThree = mid;
		if (arr[right] < arr[smallestOfThree])
			smallestOfThree = right;
		if (smallestOfThree != right)
			Opearation::swap(arr[smallestOfThree], arr[right]); //������Сֵ�ŵ����Ҷ�
		if (arr[mid] < arr[left])
			Opearation::swap(arr[mid], arr[left]); //��Сֵ�������

		//�ҵ�pivotӦ�÷��õ�λ��
		int pivot = arr[left]; // leftλ��Ϊ��ȱ,ֱ�ӿ��Ը�ֵ
		while (ptrLeft < ptrRight)
		{

			while (ptrLeft < ptrRight && arr[ptrRight] >= pivot)
			{
				--ptrRight;
				++data.compareTimes;
			}
			arr[ptrLeft] = arr[ptrRight];
			++data.moveTimes;

			while (ptrLeft < ptrRight && arr[ptrLeft] <= pivot)
			{
				++ptrLeft;
				++data.compareTimes;
			}
			arr[ptrRight] = arr[ptrLeft];
			++data.moveTimes;

			data.compareTimes += 2;
		}
		arr[ptrLeft] = pivot;
		++data.moveTimes;

		// pivot���ҷ���
		quickSort(arr, left, ptrLeft - 1, data);
		quickSort(arr, ptrLeft + 1, right, data);
	}
}
void QuickSort(int* arr, int num, SortData& data)
{
	quickSort(arr, 0, num - 1, data);
}
/**********************
 * ֱ�Ӳ�������
 ***********************/
void straightInsertSort(int* arr, int num, SortData& data)
{
	for (int i = 1; i < num; ++i)
	{
		if (arr[i] < arr[i - 1])
		{ //�൱����Ҫ�����ı��
			int temp = arr[i];
			++data.moveTimes;

			int j = i - 1;
			for (; j >= 0 && arr[j] > temp; --j)
			{ // j>=0Ҫ����ǰ�棬����ֱ������
				//���Ųλ��
				arr[j + 1] = arr[j];
				++data.compareTimes;
			}
			++data.compareTimes;

			//���Ƶ�����λ��
			arr[j + 1] = temp;
			++data.moveTimes;
		}
	}
}
/**********************
 * �۰��������
 ***********************/
void binaryInsertSort(int* arr, int num, SortData& data)
{
	int mid, left, right;

	// i����ָʾ�����Ԫ��ԭ����λ��
	for (int i = 1; i < num; ++i)
	{
		int temp = arr[i];
		++data.moveTimes;

		//���ֲ��ҹ��̣����Ӧ�ò���right+1��λ��
		left = 0;
		right = i - 1;
		while (left <= right)
		{
			mid = (left + right) / 2;
			if (arr[mid] > temp)
				right = mid - 1;
			else
				left = mid + 1;
			++data.compareTimes;
		}

		for (int j = i - 1; j >= left; --j)
		{
			arr[j + 1] = arr[j];
			++data.moveTimes;
		}

		arr[left] = temp;
		++data.moveTimes;
	}
}
/**********************
 * ϣ������
 ***********************/
void ShellSort(int* arr, int num, SortData& data)
{
	//�ı�ÿһ�η���Ĵ�С
	for (int gap = num / 2; gap >= 1; gap /= 2)
	{
		for (int i = gap; i < num; ++i)
		{
			if (arr[i] < arr[i - gap])
			{
				int temp = arr[i];
				++data.moveTimes;

				int j = i - gap;
				for (; j >= 0 && arr[j] > temp; j -= gap)
				{
					++data.compareTimes;
					arr[j + gap] = arr[j];
					++data.moveTimes;
				}

				arr[j + gap] = temp;
				++data.moveTimes;
			} // if
		}	  // for (int i = step; i < num; ++i)
	}		  // for (int step = num / 2; step >= 1; step /= 2)
}
/**********************
 * ѡ������
 ***********************/
void SelectSort(int* arr, int num, SortData& data)
{
	for (int i = 0; i < num - 1; ++i)
	{ //���һ�ο��Բ����ٱȽ�
		int minIndex = i;
		for (int j = i + 1; j < num; ++j)
		{
			if (arr[j] < arr[minIndex])
				minIndex = j;
			++data.compareTimes;
		}
		if (minIndex != i)
		{
			Opearation::swap(arr[i], arr[minIndex]);
			data.moveTimes += 3;
		}
	}
}
/**********************
 * ������
 ***********************/
template <class Type>
bool Compare_Max(Type a, Type b)
{
	return a > b;
}
typedef bool (*comp)(int, int);
static void FilterDown(int* heap, int end, int parent, SortData& data)
{ //�ѵ���(����)
	comp Comp = Compare_Max;
	int child = 2 * parent + 1;
	while (child < end)
	{
		if (child + 1 < end)
		{
			++data.compareTimes;
			if (Comp(heap[child + 1], heap[child]))
				child++; // �ҽϴ���ӽڵ�
		}
		++data.compareTimes;
		if (Comp(heap[parent], heap[child]))
			break;
		Opearation::swap(heap[parent], heap[child]);
		data.moveTimes += 3;
		parent = child;
		child = 2 * parent + 1;
	}
}
void HeapSort(int* heap, int num, SortData& data)
{
	//��ʼ����,�ӵ����ڶ���(����)��ʼ�޸�
	for (int i = (num - 2) / 2; i >= 0; i--)
		FilterDown(heap, num, i, data);

	for (int i = num - 1; i > 0; i--)
	{

		Opearation::swap(heap[i], heap[0]); //�����������Ľ���λ��
		data.moveTimes += 3;
		FilterDown(heap, i, 0, data); //����ʣ�µĶ�
	}
}
/**********************
 * �鲢����
 ***********************/
void merge(int* temp, int* arr, int left, int mid, int right, SortData& data)
{
	for (int i = left; i <= right; ++i)
	{
		temp[i] = arr[i];
		++data.moveTimes;
	}
	int ptrLeft = left, ptrRight = mid + 1;
	int ptrRes = left;
	while (ptrLeft <= mid && ptrRight <= right)
	{
		++data.moveTimes;
		++data.compareTimes;
		if (temp[ptrLeft] <= temp[ptrRight])
			arr[ptrRes++] = temp[ptrLeft++];
		else
			arr[ptrRes++] = temp[ptrRight++];
	}
	while (ptrLeft <= mid)
	{
		arr[ptrRes++] = temp[ptrLeft++];
		++data.moveTimes;
	}
	while (ptrRight <= right)
	{
		arr[ptrRes++] = temp[ptrRight++];
		++data.moveTimes;
	}
}
void mergeSort(int* temp, int* arr, int left, int right, SortData& data)
{
	if (left < right)
	{
		int mid = (left + right) / 2;
		mergeSort(temp, arr, left, mid, data);
		mergeSort(temp, arr, mid + 1, right, data);
		merge(temp, arr, left, mid, right, data);
	}
	return;
}
void MergeSort(int* arr, int num, SortData& data)
{
	int* temp = new int[num];
	mergeSort(temp, arr, 0, num - 1, data);
	delete[] temp;
}
/**********************
 * ��������
 ***********************/
void CountSort(int* arr, int num, SortData& data)
{

	int max = arr[0], min = arr[0];
	for (int i = 1; i < num; ++i)
	{
		if (arr[i] > max)
			max = arr[i];
		if (arr[i] < min)
			min = arr[i];
		data.compareTimes += 2;
	}

	int* temp = new int[max - min + 1];
	memset(temp, 0, (max - min + 1) * sizeof(int)); //����:ͷ�ļ�<cstring>

	for (int i = 0; i < num; ++i)
	{
		++temp[arr[i] - min];
		++data.moveTimes;
	}

	int pos = 0;
	for (int i = 0; i < max - min + 1; ++i)
	{
		while (temp[i])
		{
			arr[pos++] = i + min;
			--temp[i];
			++data.moveTimes;
		}
	}
}
/**********************
 * LSD��������[10����]
 ***********************/
void LSDRadixSort(int* arr, int num, SortData& data)
{

	//�����λ��
	int maxDigit = 0, curMaxNum = arr[0];
	for (int i = 1; i < num; ++i)
	{
		if (arr[i] > curMaxNum)
			curMaxNum = arr[i];
	}
	while (curMaxNum)
	{
		curMaxNum /= 10;
		++maxDigit;
	}

	int radix = 1;
	int* count = new int[10];
	int* temp = new int[num];

	for (int i = 1; i <= maxDigit; ++i)
	{
		//����ǰ���ÿ��������
		memset(count, 0, 10 * sizeof(int));
		//ͳ��ÿ��Ͱ�еļ�¼��
		for (int j = 0; j < num; ++j)
		{
			int k = (arr[j] / radix) % 10;
			++count[k];
		}
		//����temp�е�λ��(���ұ�)
		count[0] = count[0];
		for (int j = 1; j < 10; ++j)
			count[j] = count[j - 1] + count[j];
		//��Ԫ�طŵ���Ӧ�ķ�����
		for (int j = num - 1; j >= 0; --j)
		{
			int k = (arr[j] / radix) % 10;
			temp[--count[k]] = arr[j];
			++data.moveTimes;
		}
		//��temp�е�Ԫ�ظ�ֵ��arr׼����һ�ֵıȽ�
		for (int j = 0; j < num; ++j)
		{
			arr[j] = temp[j];
			++data.moveTimes;
		}

		radix *= 10;
	}
}
/**********************
 * MSD��������[16����]
 ***********************/
static int getDigitBase16(int x, int Digit)
{
	// Digit��ʾλ��-1
	// y=Digit<<2   Digit*4,��ʾxҪ�ƶ���λ��
	// z=x>>y       ��ʾx/(pow(2,y))
	// z&0xF        ��ʾ�Գ���Ľ��ȡģ���������

	return x >> (Digit << 2) & 0xF;
}
static void msdRadixSort(int* arr, int begin, int end, int maxDigit, const int radix, SortData& data)
{
	const int n = end - begin;

	//�����Ͱ�������1������/��Ͱ�����λ��<0��������ݹ�
	if (n <= 1 || maxDigit < 0)
		return;

	int* temp = new int[n];
	memset(temp, -1, n * sizeof(int));

	int* count = new int[radix]; //��Ӧ0-0xf������
	memset(count, 0, radix * sizeof(int));

	for (int i = begin; i < end; i++)
		++count[getDigitBase16(arr[i], maxDigit)];

	//����temp�е�λ��(���ұ�)
	for (int i = 1; i < radix; i++)
		count[i] += count[i - 1];

	for (int i = begin; i < end; i++)
	{
		temp[--count[getDigitBase16(arr[i], maxDigit)]] = arr[i];
		++data.moveTimes;
	}

	//��temp��ֵ��arr[begin]���Ժ��λ��
	memcpy(arr + begin, temp, n * sizeof(int));
	data.moveTimes += 2 * n;

	for (int i = 0; i < radix; i++)
	{
		int add = (i == radix - 1 ? n : count[i + 1]); //�ж�i�Ƿ������һ��Ͱ,��ȷ����ĩβ��λ��
		//�ݹ�
		msdRadixSort(arr, begin + count[i], begin + add, maxDigit - 1, radix, data);
	}
	delete[] count;
	delete[] temp;
}

void MSDRadixSort(int* arr, int n, SortData& data)
{
	int curMaxNum = arr[0]; //���������ֵ
	int maxDigit = -1;		//���λ��-1

	//������ֵ
	for (int i = 1; i < n; i++)
		if (arr[i] > curMaxNum)
			curMaxNum = arr[i];

	//������ֵ16���Ƶ�λ��
	while (curMaxNum)
	{
		curMaxNum >>= 4;
		maxDigit++;
	}

	msdRadixSort(arr, 0, n, maxDigit, 16, data);
}
#endif // !_SORT_H_
