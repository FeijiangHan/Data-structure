#pragma once
#include"Student.h"



/*
比较函数-仿函数
- 模板传参
- 不同类型重载减法运算符
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


//二叉搜索树 重载减法
int operator-(Student& a,Student& b)
{
	return a.scores - b.scores;
}

int operator-(Man& a,Man& b)
{
	return a.money - b.money;
}