#pragma once
#include<string>
/*
比较函数-仿函数
- 模板传参
- 不同类型重载减法运算符
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
		return (a > b) ? 1 : ((a == b) ? 0 : -1); // 用减法容易出问题
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


//二叉搜索树 重载减法
//int operator-(Student& a, Student& b)
//{
//	return a.scores - b.scores;
//}
//
//int operator-(Man& a, Man& b)
//{
//	return a.money - b.money;
//}