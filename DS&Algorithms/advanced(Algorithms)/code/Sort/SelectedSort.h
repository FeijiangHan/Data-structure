#pragma once
#include"Sort.h"

template<class T>
class SelectedSort : public Sort<T>
{
public:

	void sort_()
	{
		//cout << "select" << endl;
		for (int end = this->arraySize - 1; end >= 1; end--)
		{
			int index = 0;
			for (int begin = 1; begin <= end; begin++)
			{
				// 保证是稳定排序，选择最后一个最大的放到最后
				if (Sort<T>::cmp_(index,begin) <= 0)
				{
					index = begin;
				}
			}
			Sort<T>::swap_(index,end);
		}
	}

};