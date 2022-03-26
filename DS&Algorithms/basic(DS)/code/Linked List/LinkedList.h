#pragma once
#include<iostream>
constexpr auto NOT_CONTAINS = -1; // ��������Ԫ��ʱ���صĴ�����


template<class T>
class Node
 {
 public:
	T element;
	//shared_ptr<Node> next;
	Node* next;
	Node() {}
	Node(T ele,Node* n):element(ele),next(n){}
 };


template<class T>
class LinkedList : private Node<T>
{
private:
	int m_size;
	Node<T>* first;

public:
	/* ���캯�� �� ��������*/
	LinkedList();
	~LinkedList();

	/* ���ʲ���������ı�Ԫ��*/
	int size();
	bool empty();
	int IndexOf(T Ele);
	T get(int index);
	bool contains(T Ele);
	void Print();

	/* ���ɾ������޸�*/
	void add(T Ele);
	void add(int index, T Ele);
	T Remove_ForIndex(int index);
	T Remove_ForElement(T Ele);
	void clear();
	T Update(int index,T element);

private:
	/* ���������ҵ��ڵ� */
	Node<T>* node(int index);

};



template<class T>
LinkedList<T>::LinkedList()
{
	first = new Node(0, NULL);
	m_size = 0;
}


template<class T>
LinkedList<T>::~LinkedList()
{
	Node<T>* node = first;
	while (node != nullptr)
	{
		Node<T>* dele = node;
		node = node->next;
		delete dele;
	}
}


template<class T>
void LinkedList<T>::clear() 
{
	m_size = 0;
	Node<T>* node = first->next;

	while(node != nullptr)
	{
	Node<T>* dele = node;
	node = node->next;
	delete dele;
	}
}



template<class T>
bool LinkedList<T>::empty()
{
	return m_size == 0;
}



template<class T>
int LinkedList<T>::size()
	 {
		 return this->m_size;
	 }


template<class T>
Node<T>* LinkedList<T>::node(int index)
{
	// �쳣�������ͷ��ؿ�ָ��
	if (index <= -2 || index >= m_size) return nullptr;

	Node<T>* node = first; // ��ͷ��㿪ʼ����index+1�εõ�Ŀ��ڵ�
	for(int i = 0; i <= index; i++) 
	{
		node = node->next; 
	}
	return node; // ��index=-1ʱ������ͷ��㣻��������ǰ���ڵ�Ĳ���
}



template<class T>
int LinkedList<T>::IndexOf(T Ele)
	{
		Node<T>* node = first->next;
		while(node != nullptr) {
			if(node->element == Ele)
				return i;
			node = node->next;
		}
		return NOT_CONTAINS;
	}


template<class T>
	T LinkedList<T>::get(int index)
	{
		return node(index)->element;
	}
	

template<class T>
	bool LinkedList<T>::contains(T Ele)
	{
		return IndexOf(Ele) != NOT_CONTAINS;
	}



template<class T>
	T LinkedList<T>::Update(int index,T element)
	{
		T oldEle = node(index)->element;
		node(index)->element = element;
		return oldEle;
	}



template<class T>
	void LinkedList<T>::add(T Ele)
	{
	  add(m_size,Ele);
	}



template<class T>
	void LinkedList<T>::add(int index ,T Ele)
	{
		Node<T>* prev = node(index-1); 
		prev->next = new Node(Ele,prev->next);
		m_size++;
	}



template<class T>
	T LinkedList<T>::Remove_ForIndex(int index)
	{
		Node<T>* prev = node(index-1);
		Node<T>* deleNode = prev->next;
		delete prev->next;

		prev->next = prev->next->next;
		m_size--;
	    return deleNode->element;
	}



template<class T>
T LinkedList<T>::Remove_ForElement(T Ele)
{
	int index = this->IndexOf(Ele);
	return this->Remove_ForIndex(index);
}



template<class T>
void LinkedList<T>::Print()
{
	Node<T>* p = first->next;
	while (p != nullptr)
	{
		if (p != first->next)
			std::cout << "-";
		cout << p->element;
		p = p->next;
	}
	std::cout << std::endl;
}