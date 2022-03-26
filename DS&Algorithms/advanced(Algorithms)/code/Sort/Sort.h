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
	// �Ƚϴ���
	long cmpCount;
    // ��������
	long swapCount;
	// �ȽϺ�ʱ
	double fp_ms;
	// �����㷨����
	string subName;

	bool stable;

	vector<T>* arr;
	int arraySize;

	virtual void sort_() = 0;


	friend void cmpSortsAlgorithm(vector<Sort<T>*>& sorts); // �㷨��������
	friend bool cmp(Sort<T>*& o1, Sort<T>*& o2);

	// ��arr�����ڲ����������sort_()������
	void sort(vector<T>& arr)
	{
		// ����Ԫ����������Ƚ�
		if (arr.size() <= 1)  return;
		this->arr = &arr; // �õ�arr��ַ������������в���
		this->arraySize = arr.size(); // �õ�arr�ĳ���

		// ���������
		subName = typeid(*this).name() + 6;

		// ���ʱ��
		auto startTime = std::chrono::high_resolution_clock::now();
		sort_();
		auto endTime = std::chrono::high_resolution_clock::now();
		fp_ms = (chrono::duration<double, std::milli>(endTime - startTime)).count();
	}

	// ��ӡ�����㷨������
	void Print()
	{
		cout << "**---------------"<< subName <<"�����ܷ���------------------ * *" << endl;
		cout << subName << " :" << fp_ms << "ms" << endl
			<< "�Ƚϴ����� " << numberString(cmpCount) << endl
			<< "���������� " << numberString(swapCount) << endl;
	}

    string numberString(long number) {
		if (number < 10000) return "" + std::to_string(number);

		if (number < 100000000) return std::to_string(number / 10000.0) + "��";
		return std::to_string(number / 100000000.0) + "��";
	}

	// ���������Ƚ�
	int cmp_(int i1, int i2) {
		cmpCount++;
		//return (*arr)[i1] < (*arr)[i2] ? -1 : ((*arr)[i1] > (*arr)[i2] ? 1 : 0);
		return (*arr)[i1] - (*arr)[i2];
	}

	// �Ƚ���ֵ������bool
	bool cmp_val_bool(T a, T b)
	{
		cmpCount++;
		return (a < b) ? true : false;
	}

	// �Ƚ���ֵ
	int cmp_val(T a, T b)
	{
		cmpCount++;
		// return (a < b) ? -1 : ((a > b) ? 1 : 0);
		return a - b;
	}

	// ����������������
	void swap_(int a, int b) {
		swapCount++;
		T tmp = (*arr)[a];
		(*arr)[a] = (*arr)[b];
		(*arr)[b] = tmp;
	}



};

// �㷨���ܱȽ�
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


