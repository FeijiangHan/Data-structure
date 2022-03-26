#pragma once
#include"Sort.h"

template<class T>
class HeapSort : public Sort<T>
{
private:
	int heapSize;

protected:

	void sort_()
	{
		//cout << "heap" << endl;
		this->heapSize = Sort<T>::arraySize;

		for (int index = (this->heapSize >> 1) - 1; index >= 0; index--)
		{
			siftDown(index);
		}


		while(heapSize > 1)
		{
			Sort<T>::swap_(0, --heapSize);
			siftDown(0);
		}
	}



	void siftDown(int index)
	{

		T element = (* (this->arr))[index];

		int half = heapSize >> 1;
		while (index < half) { // index�����Ƿ�Ҷ�ӽڵ�
			// Ĭ������߸����ڵ��
			int childIndex = (index << 1) + 1;
			T child = (*(this->arr))[childIndex];

			int rightIndex = childIndex + 1;
			// ���ӽڵ�����ӽڵ��
			if (rightIndex < heapSize &&
				this->cmp_val((*(this->arr))[rightIndex], child) > 0) {
				child = (*(this->arr))[childIndex = rightIndex];
			}

			// ���ڵ����ӽڵ�
			if (this->cmp_val(element, child) >= 0) break;

			(*(this->arr))[index] = child;
			index = childIndex;
		}
		(*(this->arr))[index] = element;
	}


	//void siftDown(int index)
	//{

	//	// ���������ƽڵ����ֵ
	//	T e = (*(this->arr))[index];
	//	// ��Ҷ�ӽڵ���������Ʋ���
	//	int no_leaf_number = (heapSize >> 1); // ��Ҷ�ӽڵ����

	//	while (index < no_leaf_number)
	//	{

	//		int left = index << 1 + 1;
	//		int right = index << 1 + 2;
	//		T leftValue = (*(this->arr))[left];
	//		T rightValue = (*(this->arr))[right];

	//		bool cmpVal = this->cmp_val(rightValue, leftValue);

	//		// �õ�����ӽڵ�λ�ú���ֵ
	//		int nextIndex = cmpVal ? left : right;
	//		T maxNextVal = cmpVal ? leftValue : rightValue;

	//		if (this->cmp_val(maxNextVal, e)) break;
	//		// ����������������ֵ
	//		(*(this->arr))[index] = (*(this->arr))[nextIndex];
	//		index = nextIndex;

	//	}

	//	(*(this->arr))[index] = e;
	//}


};