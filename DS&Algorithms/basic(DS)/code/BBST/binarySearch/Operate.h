#pragma once
#include<string>
#include"Student.h"
#include<typeinfo>
#include<iostream>
/*
��������-�º���
- ��Ӳ�ͬ�������͵Ĳ���
- ģʽѡ��  mode0Ĭ���������
- ���ɸı����ֹͣ�ڵ�
*/


class Operate
{
public:
	Operate() { state = false; }

	//�����������Ͳ���
	template<class T>
	bool operator()(T& Ele, int mode = 0)
	{
		if (mode == 0) {
			std::cout << typeid(Ele).name() << '_' << Ele << ' ';

			return (0) ? true : false;
		}
		return false;
	}


	//�����������ʹ���
	bool operator()(Student& per, int mode = 0)
	{
		if (mode == 0) {
			std::cout << typeid(per).name() << '_' << per.name << '_' << per.scores << ' ';
			return (per.name == "chase") ? true : false; // ֹͣ����
		}
		return false;
	}


	bool operator()(Man& per, int mode = 0)
	{
		if (mode == 0) {
			std::cout << typeid(per).name() << '_' << per.name << '_' << per.year << ' ';
			return (per.year == 45) ? true : false; // ֹͣ����

		}
		return false;
	}

	bool state;
};


