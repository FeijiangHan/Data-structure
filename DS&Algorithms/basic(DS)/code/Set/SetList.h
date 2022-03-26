#pragma once
#include"LinkedList.h"

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

			return (Ele == 7) ? true : false;
		}
		return false;
	}
	//�����������ʹ���

	bool state;
};


template<class T>
class ListSet
{
private:
	LinkedList<T>* list;
	Operate m_op;

public:
	ListSet() {
	   list = new LinkedList;
	  }

	int size()
	{
		return list->size();
	}
	
	bool isEmpty()
	{
		return list->isEmpty();
	}

	void clear()
	{
		list->clear();
	}

	

	bool Contains(T Ele)
	{
		return list->contains(Ele);
	}


	void add(T Ele)
	{
		int index = list->IndexOf(Ele);
		if (index != NOT_CONTAINS) {
			list->set(index, Ele);
		}
		else {
			add(Ele);
		}
	}


	T remove(T Ele)
	{
		return list->Dele_ForElement(Ele);
	}


	void traversal()
	{
		int size = list->size();
		for (int i = 0; i < size; i++)
		{
			if (m_op.state == false) {
				m_op.state = m_op(list->get(i));
			}
			else {
				return;
			}
		}

	}
};