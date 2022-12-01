#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include<iostream>
#include<assert.h>
using namespace std;

#define DefaultPQSize  10
namespace myCompare {
	template<class Type>bool Compare_Max(Type a, Type b) {
		return a > b;
	}
	template<class Type>bool Compare_Min(Type a, Type b) {
		return a < b;
	}
	//���庯��ָ��Ϊcomp��������������Լ�������ʽ
	typedef bool(*comp)(int, int);

}
namespace Heap {
	//���϶��µĵ���
	template<class Type>void FilterDown(int start, int curSize, Type* heap, myCompare::comp Comp)
	{

		int cur = start;
		int child = 2 * cur + 1;//j��i������
		Type temp = heap[cur];
		//��֤��С���ѣ�ÿһ������Ҳ��
		while (child < curSize)
		{
			//child����ָ�����һ�����,����Ů��ѡС��
			if (child < curSize - 1 && Comp(heap[child + 1], heap[child])) 
				child++;
			if (Comp(temp, heap[child]))//head��ֵ��posС
				break;
			else //head��ֵ��pos��
			{
				heap[cur] = heap[child];
				cur = child;

				child = 2 * child + 1;//posת������������
			}
		}
		heap[cur] = temp;
	}
	//���¶��ϵĵ���
	template<class Type>void FilterUp(int start, Type* heap, myCompare::comp Comp) 
	{
		int cur = start, parent = (cur - 1) / 2;
		while (cur > 0) {
			if (Comp(heap[parent], heap[cur]))//parent<heap
				break;
			else {
				Type temp = heap[cur];
				heap[cur] = heap[parent];
				heap[parent] = temp;

				cur = parent;
				parent = (parent - 1) / 2;

			}
		}
	}
	//����в���Ԫ��
	template<class Type>bool Insert(const Type& x, int& curSize, Type* heap, myCompare::comp Comp) 
	{
		heap[curSize] = x;
		FilterUp(curSize, heap, Comp);
		curSize++;
		return true;
	}
	//ɾ������Ԫ��
	template<class Type>bool Remove(Type& x, int& curSize, Type* heap, myCompare::comp Comp) 
	{
		if (curSize == 0) {
			cout << "���ѿ�" << endl;
			return false;
		}
		x = heap[0];
		heap[0] = heap[--curSize];//ȡ���һ�����ͷ��
		FilterDown(0, curSize, heap, Comp);//���϶��µ���
		return true;
	}
}



template<class Type>
class PriorityQueue {
protected:
	Type* data;
	int curSize;
	int maxSize;
	myCompare::comp Compare;	//���ú���ָ��ָʾ�ȽϷ�ʽ��Ĭ����Min
public:
	PriorityQueue(int size = DefaultPQSize, bool (*Compare)(Type, Type) = myCompare::Compare_Min);
	~PriorityQueue() { delete[]data; }
	bool push(const Type& x);
	bool pop(Type& x);
	int size()const { return curSize; }

	bool getFront(Type& x)const;

	void makeEmpty() { curSize = 0; }
	bool IsEmpty() { return curSize == 0; }
	bool IsFull() { return curSize == maxSize; }
	void Print() {
		for (int i = 0; i < curSize; ++i)
			cout << data[i] << " ";
		cout << endl;
	}
};
template<class Type>PriorityQueue<Type>::PriorityQueue(int size, bool (*compare)(Type, Type))
	:maxSize(size), curSize(0), Compare(compare) {
	data = new Type[maxSize];
	assert(data != NULL);
}
template<class Type> bool PriorityQueue<Type>::push(const Type& x)
{
	if (IsFull())return false;
	Heap::Insert(x, curSize, data, Compare);
	return true;
}
template<class Type>bool PriorityQueue<Type>::pop(Type& x)
{
	if (IsEmpty())return false;
	Heap::Remove(x, curSize, data, Compare);
	return true;
}
template<class Type>bool PriorityQueue<Type>::getFront(Type& x) const
{
	if (IsEmpty())return false;
	x = data[0];
	return true;
}



#endif // !_PRIORITY_QUEUE_H_
