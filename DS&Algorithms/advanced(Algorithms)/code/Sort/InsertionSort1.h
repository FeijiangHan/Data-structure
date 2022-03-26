#pragma once
#include"Sort.h"

template<class T>
class InsertionSort1 : public Sort<T>
{
public:
	// ���ƴ��ƣ��Ѻ���С���Ʋ嵽ǰ��
	//void sort_()
	//{
	//	for (int begin = 1; begin < this->arraySize; begin++)
	//	{
	//		T val = (*this->arr)[begin]; // ����begin����ֵ
	//		int cur = begin;  // ����begin����ֵ

	//		// ��Ԫ�غ��ƣ�ͬʱ�ҵ����һ�κ��Ƶ�λ��cur
	//		while (cur > 0 && this->cmp_val(val, (*this->arr)[cur - 1]) < 0)
	//		{
	//			(*this->arr)[cur] = (*this->arr)[cur - 1];
	//			cur--;
	//		}

	//		(*this->arr)[cur] = val; // ��beginλ��Ԫ�ز��뵽index
	//	}
	//}

	void sort_()
	{
		for (int begin = 1; begin < this->arraySize; begin++)
		{
			// �ҵ���Ҫ�����λ��
			int insertIndex = GetInsertIndex(begin);

	        // �ƶ�Ԫ�أ���������λ�õĿ�λ������Ԫ�ز���
			MovingEle(begin, insertIndex);
		}
	}



	void MovingEle(int begin,int dest)
	{
		T val = (*this->arr)[begin]; // ����begin����ֵ

		for (int i = begin; i > dest; i--)
		{
			(*this->arr)[i] = (*this->arr)[i - 1];
		}

		(*this->arr)[dest] = val; // ��beginλ��Ԫ�ز��뵽index
	}


	int GetInsertIndex(int index)
	{
		int cur = index;  // ����begin����ֵ
        // ��Ԫ�غ��ƣ�ͬʱ�ҵ����һ�κ��Ƶ�λ��cur
		while (cur > 0 && this->cmp_(index, cur - 1) < 0)
		{
			cur--;
		}
		return cur;
	}

};