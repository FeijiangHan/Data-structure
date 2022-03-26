#pragma once
#include"LinkedList.h"
#include"Operate.h"

template<class T>
class Set
{
public:
	Operate m_op;

	Set() {
		
	}

	virtual int size() = 0;

	virtual bool isEmpty() = 0;

	virtual void clear() = 0;

	virtual bool Contains(T Ele) = 0;


	virtual void add(T Ele) = 0;


	virtual void remove(T Ele) = 0;


	virtual void traversal() = 0;

};



