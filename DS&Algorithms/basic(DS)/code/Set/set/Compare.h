#pragma once
#include<assert.h>
/*
�ȽϺ���-�º���
- ģ�崫��
- ��ͬ�������ؼ��������
*/

class Compare
{
public:

	template<class T>
	T operator()(T a, T b)
	{
		return (a > b) ? 1 : ((a == b) ? 0 : -1); // �ü������׳�����
	}

};

template<class T>
void IsComparable(T Ele1,T Ele2) {
	std::cout << "����ISCOmparable" << std::endl;
	assert(Ele1 > Ele2 || Ele1 <= Ele2);
}


//���������� ���ؼ���
//int operator-(Student& a, Student& b)
//{
//	return a.scores - b.scores;
//}
//
//int operator-(Man& a, Man& b)
//{
//	return a.money - b.money;
//}