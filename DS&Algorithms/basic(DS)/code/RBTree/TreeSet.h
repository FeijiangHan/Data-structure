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
		cout << "ɾ��������Ԫ�أ� " << Ele << endl;
		tree->remove(Ele);
	}


	void traversal()
	{
		cout << "��ʽ���ϣ� ";
		tree->inorder();

		cout << endl;

	}
};