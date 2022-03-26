#pragma once
#include"Sort.h"

template<class T>
class InsertionSort0 : public Sort<T>
{
public:
	// 类似打牌，把后面小的牌插到前面
	void sort_()
	{
		for (int begin = 1; begin < this->arraySize; begin++)
		{
			while (begin > 0 && this->cmp_(begin, begin - 1) < 0) 
			{
				this->swap_(begin, begin - 1);
				begin--;
		    }
		}
	}

};