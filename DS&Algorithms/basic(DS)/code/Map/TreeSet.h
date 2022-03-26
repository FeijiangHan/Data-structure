#pragma once
#include"TreeMap.h"

template<class T>
class TreeSet
{
private:
	TreeMap<T, T>* map;

public:
	TreeSet() {
		map = new TreeMap<T, T>;
	}

	int size()
	{
		return map->size();
	}

	bool isEmpty()
	{
		return map->isEmpty();
	}

	void clear()
	{
		map->clear();
	}

	bool contains(T Ele)
	{
		return map->containsKey(ELe);
	}


	void add(T Ele)
	{
		map->add(Ele, Ele);
	}


	T remove(T Ele)
	{
		return map->remove(Ele);
	}

	void traverse()
	{
		map->setMode();
		map->traversal();
	}

};