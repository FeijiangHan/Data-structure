#pragma once
#include<string>
/*
�ȽϺ���-�º���
- ģ�崫��
- ��ͬ�������ؼ��������
//*/
//class Man
//{
//public:
//	int year;
//	string name;
//	Man(int y, string n)
//	{
//		year = y;
//		name = n;
//	}
//};

class Compare
{
public:

	template<class T>
	T operator()(T a, T b)
	{
		return (a > b) ? 1 : ((a == b) ? 0 : -1); // �ü������׳�����
	}

	int operator()(std::string a, std::string b)
	{
		return a.compare(b);
	}

	//bool operator()(const Man& c1, const Man& c2) const
	//{
	//	return !c1.name.compare(c2.name) && c1.year == c2.year;
	//}

};


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