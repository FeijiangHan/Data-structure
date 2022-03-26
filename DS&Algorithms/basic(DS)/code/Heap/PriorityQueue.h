#pragma once
#include"BInaryHeap.h"
#include"Heap.h"


template<class T>
class PriorityQueue
{
private:
	Heap<T>* heap = new BinaryHeap<T>;

public:


	bool empty()
	{
		return heap->empty();
	}


	T front()
	{
		return heap->get();
	}

	int size()
	{
		return heap->size();
	}

	void enqueue(T Ele)
	{
		heap->add(Ele);
	}

	T dequeue()
	{
		return heap->remove();
	}

	void clear()
	{
		heap->clear();
	}

	void print() {
		heap->printArray();
	}

};