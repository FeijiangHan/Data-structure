#pragma once
#include"Sort.h"

template<class T>
class BobbleSort2 : public Sort<T>
{
public:

	void sort_()
	{
		//cout << "Bobb2" << endl;
		for (int end = this->arraySize - 1; end >= 1; end--)
		{
			int index = 0;
			for (int begin = 1; begin <= end; begin++)
			{
				if (Sort<T>::cmp_(begin, begin - 1) < 0)
				{
					this->swap_(begin, begin - 1);
					index = begin;
				}
			}
			end = index;
		}
	}

};