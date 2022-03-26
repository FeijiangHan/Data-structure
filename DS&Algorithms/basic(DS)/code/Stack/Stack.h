#pragma once
#include"Danamic_Array.h"

template <class T>
class Stack : public ArrayList<T>
{

public:
	void clear() {
	  clearNormal();
	}



	void push(T Ele)
	{
		add(Ele);
	}


	T pop()
	{
		return Dele_ArrayForIndex(m_size - 1);
	}


	T top()
	{
		return get(m_size - 1);
	}




};