#pragma once
#include<string>
#include"Student.h"
#include<typeinfo>
#include<iostream>
/*
操作函数-仿函数
- 添加不同数据类型的操作
- 模式选择  mode0默认输出操作
- 自由改变遍历停止节点
*/


class Operate
{
public:
	Operate() { state = false; }

	//基本数据类型操作
	template<class T>
	bool operator()(T& Ele, int mode = 0)
	{
		if (mode == 0) {
			std::cout << typeid(Ele).name() << '_' << Ele << ' ';

			return (0) ? true : false;
		}
		return false;
	}


	//特殊数据类型处理
	bool operator()(Student& per, int mode = 0)
	{
		if (mode == 0) {
			std::cout << typeid(per).name() << '_' << per.name << '_' << per.scores << ' ';
			return (per.name == "chase") ? true : false; // 停止条件
		}
		return false;
	}


	bool operator()(Man& per, int mode = 0)
	{
		if (mode == 0) {
			std::cout << typeid(per).name() << '_' << per.name << '_' << per.year << ' ';
			return (per.year == 45) ? true : false; // 停止条件

		}
		return false;
	}

	bool state;
};


