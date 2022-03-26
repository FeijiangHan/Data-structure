#pragma once
#include"RBTree.h"

template<class T>
class TreeSet
{
public:
	RBTree<T>* tree = new RBTree<T>;


	int size()
	{
		return tree->size();
	}

	bool isEmpty()
	{
		return tree->IsEmpty();
	}

	void clear()
	{
		tree->clear();
	}



	bool Contains(T Ele)
	{
		return tree->Contains(Ele);
	}


	void add(T Ele)
	{
		tree->add(Ele);
	}


	void remove(T Ele)
	{
		cout << "删除集合中元素： " << Ele << endl;
		tree->remove(Ele);
	}


	void traversal()
	{
		cout << "链式集合： ";
		tree->inorder();

		cout << endl;

	}
};