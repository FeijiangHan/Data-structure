#pragma once
#include"Student.h"



/*
�ȽϺ���-�º���
- ģ�崫��
- ��ͬ�������ؼ��������
*/
template<class T>
class Compare
{
public:
	int operator()(T a, T b)
	{
		return a-b;
	}
};


//���������� ���ؼ���
int operator-(Student& a,Student& b)
{
	return a.scores - b.scores;
}

int operator-(Man& a,Man& b)
{
	return a.money - b.money;
}