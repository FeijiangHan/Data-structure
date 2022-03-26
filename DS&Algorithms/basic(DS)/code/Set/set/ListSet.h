#pragma once
#include"LinkedList.h"
#include"Set.h"

template<class T>
class ListSet : public Set<T>
{
public:
	LinkedList<T>* list = new LinkedList<T>;

	//ListSet() {
	//	list = new LinkedList<T>;
	//}

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
		if (list->contains(Ele)) return;

		list->add(Ele);
	}


	void remove(T Ele)
	{
		cout << "删除集合中元素： " << Ele << endl;
		list->Dele_ForElement(Ele);
	}


	void traversal()
	{
		this->m_op.state = false;
		cout << "链式集合： "; 
		int size = list->size();
		for (int i = 0; i < size; i++)
		{
			if (this->m_op.state == false) {
				this->m_op.state = this->m_op(list->get(i));
			}
			else {
				cout << endl;
				return;
			}
		}
		cout << endl;
		return;

	}

	int indexOf(T Ele)
	{
		return list->IndexOf(Ele);
	}
};

