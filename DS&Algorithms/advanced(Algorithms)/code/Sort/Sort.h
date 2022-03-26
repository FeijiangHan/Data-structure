#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<typeinfo>
#include<Windows.h>
#include <chrono>
#include"TestMultiSortObj.h"
using namespace std;


template<class T>
class Sort
{


public:
	// 比较次数
	long cmpCount;
    // 交换次数
	long swapCount;
	// 比较耗时
	double fp_ms;
	// 子类算法名称
	string subName;

	bool stable;

	vector<T>* arr;
	int arraySize;

	virtual void sort_() = 0;


	friend void cmpSortsAlgorithm(vector<Sort<T>*>& sorts); // 算法优劣排序
	friend bool cmp(Sort<T>*& o1, Sort<T>*& o2);

	// 对arr排序，内部调用子类的sort_()函数。
	void sort(vector<T>& arr)
	{
		// 两个元素以下无需比较
		if (arr.size() <= 1)  return;
		this->arr = &arr; // 得到arr地址，传入子类进行操作
		this->arraySize = arr.size(); // 得到arr的长度

		// 子类的名字
		subName = typeid(*this).name() + 6;

		// 获得时间
		auto startTime = std::chrono::high_resolution_clock::now();
		sort_();
		auto endTime = std::chrono::high_resolution_clock::now();
		fp_ms = (chrono::duration<double, std::milli>(endTime - startTime)).count();
	}

	// 打印排序算法的属性
	void Print()
	{
		cout << "**---------------"<< subName <<"的性能分析------------------ * *" << endl;
		cout << subName << " :" << fp_ms << "ms" << endl
			<< "比较次数： " << numberString(cmpCount) << endl
			<< "交换次数： " << numberString(swapCount) << endl;
	}

    string numberString(long number) {
		if (number < 10000) return "" + std::to_string(number);

		if (number < 100000000) return std::to_string(number / 10000.0) + "万";
		return std::to_string(number / 100000000.0) + "亿";
	}

	// 根据索引比较
	int cmp_(int i1, int i2) {
		cmpCount++;
		//return (*arr)[i1] < (*arr)[i2] ? -1 : ((*arr)[i1] > (*arr)[i2] ? 1 : 0);
		return (*arr)[i1] - (*arr)[i2];
	}

	// 比较数值，返回bool
	bool cmp_val_bool(T a, T b)
	{
		cmpCount++;
		return (a < b) ? true : false;
	}

	// 比较数值
	int cmp_val(T a, T b)
	{
		cmpCount++;
		// return (a < b) ? -1 : ((a > b) ? 1 : 0);
		return a - b;
	}

	// 根据索引交换数组
	void swap_(int a, int b) {
		swapCount++;
		T tmp = (*arr)[a];
		(*arr)[a] = (*arr)[b];
		(*arr)[b] = tmp;
	}



};

// 算法性能比较
#include<algorithm>

template<class T>
bool cmp(Sort<T>*& o1, Sort<T>*& o2)
{
	if (o1->fp_ms < o2->fp_ms)
		return true;
	else if (o1->fp_ms == o2->fp_ms)
	{
		if (o1->cmpCount < o2->cmpCount)
			return true;
		else if (o1->cmpCount == o2->cmpCount)
		{
			if (o1->swapCount < o2->swapCount)
				return true;
			else if (o1->swapCount == o2->swapCount)
				return true;
			else return false;
		}
		else return false;

	}
	else return false;
}

template<class T>
void cmpSortsAlgorithm(vector<Sort<T>*>& sorts)
{
	sort(sorts.begin(), sorts.end(),cmp<T>);
}


