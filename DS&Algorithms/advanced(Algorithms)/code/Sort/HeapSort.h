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
		while (index < half) { // index必须是非叶子节点
			// 默认是左边跟父节点比
			int childIndex = (index << 1) + 1;
			T child = (*(this->arr))[childIndex];

			int rightIndex = childIndex + 1;
			// 右子节点比左子节点大
			if (rightIndex < heapSize &&
				this->cmp_val((*(this->arr))[rightIndex], child) > 0) {
				child = (*(this->arr))[childIndex = rightIndex];
			}

			// 大于等于子节点
			if (this->cmp_val(element, child) >= 0) break;

			(*(this->arr))[index] = child;
			index = childIndex;
		}
		(*(this->arr))[index] = element;
	}


	//void siftDown(int index)
	//{

	//	// 保留待下移节点的数值
	//	T e = (*(this->arr))[index];
	//	// 有叶子节点则进行下移操作
	//	int no_leaf_number = (heapSize >> 1); // 非叶子节点个数

	//	while (index < no_leaf_number)
	//	{

	//		int left = index << 1 + 1;
	//		int right = index << 1 + 2;
	//		T leftValue = (*(this->arr))[left];
	//		T rightValue = (*(this->arr))[right];

	//		bool cmpVal = this->cmp_val(rightValue, leftValue);

	//		// 得到最大子节点位置和数值
	//		int nextIndex = cmpVal ? left : right;
	//		T maxNextVal = cmpVal ? leftValue : rightValue;

	//		if (this->cmp_val(maxNextVal, e)) break;
	//		// 更新索引，覆盖数值
	//		(*(this->arr))[index] = (*(this->arr))[nextIndex];
	//		index = nextIndex;

	//	}

	//	(*(this->arr))[index] = e;
	//}


};