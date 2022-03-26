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
				// ��֤���ȶ�����ѡ�����һ�����ķŵ����
				if (Sort<T>::cmp_(index,begin) <= 0)
				{
					index = begin;
				}
			}
			Sort<T>::swap_(index,end);
		}
	}

};