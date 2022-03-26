#pragma once
#include"Sort.h"

template<class T>
class InsertionSort2 : public Sort<T>
{
public:
	// 类似打牌，把后面小的牌插到前面
	void sort_()
	{
		for (int begin = 1; begin < this->arraySize; begin++)
		{
			int index = GetInsertIndex(begin); // 计算出begin处的元素应该插入在哪个位置
			MovingEle(begin, index); // 把begin处的数值移动到index处
		}
	}


	void MovingEle(int source,int dest)
	{
		T val = (*this->arr)[source]; // 后面会覆盖，提前保留数值

		for (int i = source; i > dest; i--)
		{
			(*this->arr)[i] = (*this->arr)[i - 1];
		}

		(*this->arr)[dest] = val;
	}


	// 找到val应该插入在之前已经排好序的序列的哪个位置、
	// 和普通二分查找不同，这里找到相同元素不返回，而是二分至后半段，保证了稳定性
	int GetInsertIndex(int val_index)
	{
		int low = 0;
		int high = val_index; // begin之前都排好了

		while (low < high)
		{
			int mid = (low + high) >> 1;
			if (this->cmp_(val_index, mid) < 0)
			{
				high = mid;
			}
			else // 相等和大于的情况都去右边找，保证了稳定性
			{
				low = mid + 1;
			}
		}
		return low; // 最后low=high，代表的就是插入的最终位置
	}

};