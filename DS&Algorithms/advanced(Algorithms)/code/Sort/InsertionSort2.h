#pragma once
#include"Sort.h"

template<class T>
class InsertionSort2 : public Sort<T>
{
public:
	// ���ƴ��ƣ��Ѻ���С���Ʋ嵽ǰ��
	void sort_()
	{
		for (int begin = 1; begin < this->arraySize; begin++)
		{
			int index = GetInsertIndex(begin); // �����begin����Ԫ��Ӧ�ò������ĸ�λ��
			MovingEle(begin, index); // ��begin������ֵ�ƶ���index��
		}
	}


	void MovingEle(int source,int dest)
	{
		T val = (*this->arr)[source]; // ����Ḳ�ǣ���ǰ������ֵ

		for (int i = source; i > dest; i--)
		{
			(*this->arr)[i] = (*this->arr)[i - 1];
		}

		(*this->arr)[dest] = val;
	}


	// �ҵ�valӦ�ò�����֮ǰ�Ѿ��ź�������е��ĸ�λ�á�
	// ����ͨ���ֲ��Ҳ�ͬ�������ҵ���ͬԪ�ز����أ����Ƕ��������Σ���֤���ȶ���
	int GetInsertIndex(int val_index)
	{
		int low = 0;
		int high = val_index; // begin֮ǰ���ź���

		while (low < high)
		{
			int mid = (low + high) >> 1;
			if (this->cmp_(val_index, mid) < 0)
			{
				high = mid;
			}
			else // ��Ⱥʹ��ڵ������ȥ�ұ��ң���֤���ȶ���
			{
				low = mid + 1;
			}
		}
		return low; // ���low=high������ľ��ǲ��������λ��
	}

};