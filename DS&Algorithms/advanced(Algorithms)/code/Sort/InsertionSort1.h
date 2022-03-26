#pragma once
#include"Sort.h"

template<class T>
class InsertionSort1 : public Sort<T>
{
public:
	// 类似打牌，把后面小的牌插到前面
	//void sort_()
	//{
	//	for (int begin = 1; begin < this->arraySize; begin++)
	//	{
	//		T val = (*this->arr)[begin]; // 保存begin的数值
	//		int cur = begin;  // 保存begin的数值

	//		// 把元素后移，同时找到最后一次后移的位置cur
	//		while (cur > 0 && this->cmp_val(val, (*this->arr)[cur - 1]) < 0)
	//		{
	//			(*this->arr)[cur] = (*this->arr)[cur - 1];
	//			cur--;
	//		}

	//		(*this->arr)[cur] = val; // 把begin位置元素插入到index
	//	}
	//}

	void sort_()
	{
		for (int begin = 1; begin < this->arraySize; begin++)
		{
			// 找到需要插入的位置
			int insertIndex = GetInsertIndex(begin);

	        // 移动元素，留出插入位置的空位并把新元素插入
			MovingEle(begin, insertIndex);
		}
	}



	void MovingEle(int begin,int dest)
	{
		T val = (*this->arr)[begin]; // 保存begin的数值

		for (int i = begin; i > dest; i--)
		{
			(*this->arr)[i] = (*this->arr)[i - 1];
		}

		(*this->arr)[dest] = val; // 把begin位置元素插入到index
	}


	int GetInsertIndex(int index)
	{
		int cur = index;  // 保存begin的数值
        // 把元素后移，同时找到最后一次后移的位置cur
		while (cur > 0 && this->cmp_(index, cur - 1) < 0)
		{
			cur--;
		}
		return cur;
	}

};