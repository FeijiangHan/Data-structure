#pragma once

template<class K,class V>
class Map {
public:

	virtual int size() = 0;
	virtual bool isEmpty() = 0;
	virtual void clear() = 0;

	virtual V add(K key, V value) = 0;
	virtual V get(K key) = 0;
	virtual V remove(K key) = 0;
	virtual bool containsKey(K key) = 0;
	virtual bool containsValue(V value) = 0;

	virtual void traversal() = 0;
};