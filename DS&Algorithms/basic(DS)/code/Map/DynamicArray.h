#pragma once
#include<iostream>
#define ELEMENT int  //元素类型
#define DEFAULT_CAPACITY 10  //默认容量
#define ELEMENT_NOT_FOUND -1   //返回查找状态
using namespace std;

template<class T>
class ArrayList
{
public:

		ArrayList(int capaticy = DEFAULT_CAPACITY);


	void clearHeap();


	int size();

	bool Is_Empty();


	int IndexOf(T Ele);


	T get(int index);

	bool contains(T Ele);


	T set(int index, T element);

	void add(T Ele);
	void add(T Ele, int index);

	void ensureCapacity(int n);

	void trim(); //修剪

	T Dele_ArrayForIndex(int index);

	void Dele_ArrayForElement(int Ele);


public:
	int m_size; //有效位个数
	T* m_elements;  //元素指针，指向数组第一个元素地址
	int m_capacity;  //容量

};

template<class T>
ArrayList<T>::ArrayList(int capaticy) {
	m_capacity = (capaticy < DEFAULT_CAPACITY) ? DEFAULT_CAPACITY : capaticy;
	m_elements = new T[m_capacity];
	m_size = 0;
}

template<class T>
inline void ArrayList<T>::clearHeap()
{
	for (int i = 0; i < m_size; i++)
	{
		delete this->m_elements[i];
		this->m_elements[i] = nullptr;
	}
	m_size = 0;
}

template<class T>
int ArrayList<T>::size() {
	return m_size;
}

template<class T>
bool ArrayList<T>::Is_Empty()
{
	return m_size == 0;
	//return (m_size == 0) ? true : false;
}

template<class T>
int ArrayList<T>::IndexOf(T Ele)
{
	//兼容元素为null的情况
	if (Ele == NULL)
	{
		for (int i = 0; i < m_size; i++)
		{
			if (this->m_elements[i] == NULL)
				return i;
		}
	}

	for (int i = 0; i < m_size; i++)
	{
		if (Ele == m_elements[i])
			return i;
	}
	return ELEMENT_NOT_FOUND;
}

template<class T>
T ArrayList<T>::get(int index) {
	if (index < 0 || index >= m_size)  //下标判断
		throw "false,overflow!";
	else
		return m_elements[index];
}


template<class T>
bool ArrayList<T>::contains(T Ele)
{

	return IndexOf(Ele) != ELEMENT_NOT_FOUND;
}


template<class T>
T ArrayList<T>::set(int index, T element) {
	if (index < 0 || index !< m_size)
		throw "false,overflow!";  //边界判断
	T temp = this->m_elements[index];   //recreat =
	this->m_elements[index] = element;
	return temp;
}

template<class T>
inline void ArrayList<T>::add(T Ele)
{
	if (m_size == 0)
	{
		add(Ele, 0);
		return;
	}
	add(Ele, m_size - 1);
}


template<class T>
void ArrayList<T>::add(T Ele , int index)
{
	if (index < 0 || index > m_size)
		throw "false,overflow!";

	ensureCapacity(m_size + 1);

	for (int i = m_size - 1; i >= index; i--)
	{
		this->m_elements[i + 1] = this->m_elements[i];
	}
	this->m_elements[index] = Ele;
	m_size++;

}

template<class T>
void ArrayList<T>::ensureCapacity(int n) {
	//不需要扩容
	if (n <= m_capacity)
		return;

	int new_capacity = n * (1 + 0.5);

	T* NewArray = new T[new_capacity];
	for (int i = 0; i < m_size; i++)
	{
		NewArray[i] = this->m_elements[i];
	} 
	delete[] this->m_elements;
	cout << "old_capacity:" << m_capacity << "--->new_capacity:" << new_capacity << endl;
	m_capacity = new_capacity;
	this->m_elements = NewArray;
}

template<class T>
void ArrayList<T>::trim()
{
	//每次缩容一半
	int new_capacity = m_capacity >> 1;
	// int new_capacity = m_capacity*0.6;
  //有效元素位数大于容量的一半，或者容量的一半小于预设值，则不进行缩容
	if (m_size >= new_capacity || new_capacity < DEFAULT_CAPACITY)  return;

	T* new_array = new T[new_capacity];//此时size小于newcapacity

	for (int i = 0; i < m_size; i++)
	{
		new_array[i] = this->m_elements[i];
	}

	cout << "old_capacity:" << m_capacity << "--->new_capacity:" << new_capacity << endl;
	m_capacity = new_capacity;
	delete[] this->m_elements;
	this->m_elements = new_array;

}

template<class T>
T ArrayList<T>::Dele_ArrayForIndex(int index)
{
	if (index < 0 || index >= m_size - 1) {
		cout << "删除失败！" << endl;
		return;
	}

	T temp;
	temp = this->m_elements[index];

	for (int i = index + 1; i < m_size; i++)
	{
		this->m_elements[i - 1] = this->m_elements[i];
	}

	m_size--; //@important
	trim();
	return temp;
}

template<class T>
void ArrayList<T>::Dele_ArrayForElement(int Ele)
{
	this->Dele_ArrayForIndex(this->IndexOf(Ele));
}

ostream& operator<<(ostream& cout, ArrayList<ELEMENT>& array)
{
	cout << "[ ";
	for (int i = 0; i < array.m_size; i++)
	{
		if (i != 0) cout << ",";
		cout << array.m_elements[i];
	}
	cout << " ]" << endl;
	return cout;
}