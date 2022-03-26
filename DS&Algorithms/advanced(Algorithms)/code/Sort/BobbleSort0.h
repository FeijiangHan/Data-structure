#pragma once
#include"Sort.h"

template<class T>
class BobbleSort0 : public Sort<T>
{
public:

	void sort_()
	{
		//cout << "Bobb0" << endl;
		for (int end = this->arraySize - 1; end >= 1; end--)
		{
			for (int begin = 1; begin <= end; begin++)
			{
				if (this->cmp_(begin,begin-1) < 0)
				{
					this->swap_(begin, begin - 1);
				}
			}
		}
	}

};