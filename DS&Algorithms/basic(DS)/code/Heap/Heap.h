#pragma once


template<class T>
class Heap
{
public:
	virtual void add(T Ele) = 0;
	virtual T get() = 0;
	virtual T remove() = 0;
	virtual void clear() = 0;
	virtual int size() = 0;
	virtual bool empty() = 0;
	virtual T replace(T Ele) = 0;
	virtual void printArray() = 0;
};