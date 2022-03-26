#pragma once
#include<assert.h>
/*
比较函数-仿函数
- 模板传参
- 不同类型重载减法运算符
*/

class Compare
{
public:

	template<class T>
	T operator()(T a, T b)
	{
		return (a > b) ? 1 : ((a == b) ? 0 : -1); // 用减法容易出问题
	}

};

template<class T>
void IsComparable(T Ele1,T Ele2) {
	std::cout << "调用ISCOmparable" << std::endl;
	assert(Ele1 > Ele2 || Ele1 <= Ele2);
}


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