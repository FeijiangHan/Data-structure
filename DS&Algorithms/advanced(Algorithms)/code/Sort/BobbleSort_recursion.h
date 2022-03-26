#pragma once
#include"Sort.h"

template<class T>
class BubbleSort_Recur : public Sort<T>
{
public:

	void sort_()
	{
		BubbleSort(1, this->arraySize - 1);
	}

	void BubbleSort(int begin, int end)
	{
		if (end == 0) return;

		if (end >= begin)
		{
			for (int i = begin; i <= end; i++)
			{
				if (this->cmp_(i,i-1) < 0)
				{
					this->swap_(i,i-1);
				}
			}
		}
		BubbleSort(begin, end - 1);
	}

};

