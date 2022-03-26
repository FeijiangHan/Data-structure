#pragma once

#include<iostream>
#include<memory>
#define NOT_CONTAINS -1

using namespace std;

template<class T>
class ListNode
{
public:
	T element;
	//shared_ptr<Node> next;
	ListNode* next;
	ListNode(){}
	ListNode(T ele, ListNode* n) :element(ele), next(n) {}
};


template<class T>
class LinkedList : private ListNode<T>
{
public:

	LinkedList()
	{
		first = new ListNode<T>;
		m_size = 0;
	}


	void clear();

	ListNode<T>* node(int index);

	int IndexOf(T Ele);

	T get(int index);

	bool contains(T Ele);

	T set(int index, T element);

	void add(T Ele);

	void add(int index, T Ele);

	T Dele_ForIndex(int index);

	int size();

	bool isEmpty()
	{
		return m_size == 0;
	}

	T Dele_ForElement(T Ele);

public:
	int m_size;
	ListNode<T>* first;
};


/**
 * �������Ԫ��
 */
template<class T>
void LinkedList<T>::clear()
{
	m_size = 0;
	ListNode<T>* node = first->next;

	while (node != nullptr)
	{
		ListNode<T>* dele = node;
		node = node->next;
		delete dele;
	}
}

template<class T>
int LinkedList<T>::size()
{
	return this->m_size;
}


//���O(1)�� �����size���Ľڵ�O��n����ƽ��O��n��
template<class T>
ListNode<T>* LinkedList<T>::node(int index)
{

	ListNode<T>* node = first->next;
	for (int i = 0; i < index; i++)
	{
		node = node->next;
	}
	return (index != -1) ? node : first;
}


template<class T>
int LinkedList<T>::IndexOf(T Ele)
{
	ListNode<T>* node = first->next;
	if (node == NULL) return NOT_CONTAINS;

	for (int i = 0; i < m_size; i++) {
		if (node->element == Ele)
			return i;
		node = node->next;
	}
	return NOT_CONTAINS;
}

/**
 * ��ȡindexλ�õ�Ԫ��
 * @param index
 * @return
 */

template<class T>
T LinkedList<T>::get(int index)
{
	//Node* node = first->next;
	//for(int i = 0;i < index; i++)
	//{
	//	node = node->next;
	//}
	/*return (node->element);*/
	return node(index)->element;
}


/**
 * �Ƿ����ĳ��Ԫ��
 * @param element
 * @return
 */
template<class T>
bool LinkedList<T>::contains(T Ele)
{
	return IndexOf(Ele) != NOT_CONTAINS;
}


/**
 * ����indexλ�õ�Ԫ��
 * @param index
 * @param element
 * @return ԭ����Ԫ��
 */
template<class T>
T LinkedList<T>::set(int index, T element)
{
	ListNode<T>* old = node(index);
	node(index)->element = element;
	return old->element;
}

////add
//void add()
//void add(T Ele);

template<class T>
void LinkedList<T>::add(T Ele)
{
	add(m_size, Ele);
}


//O��n��
template<class T>
void LinkedList<T>::add(int index, T Ele)
{
	ListNode<T>* p = node(index - 1);  //����ֱ����node������ֵ,��Ϊ��ͷ�ڵ㣬����ͳһ����
	p->next = new ListNode<T>(Ele, p->next);
	m_size++;
}

//o(n)
template<class T>
T LinkedList<T>::Dele_ForIndex(int index)
{
	ListNode<T>* prv = node(index - 1);
	ListNode<T>* node = prv->next;
	prv->next = prv->next->next;
	m_size--;
	return node->element;
}


template<class T>
T LinkedList<T>::Dele_ForElement(T Ele)
{
	int index = this->IndexOf(Ele);
	return this->Dele_ForIndex(index);
}


template<class T>
ostream& operator<<(ostream& cout, LinkedList<T>& list)
{
	cout << "�������";
	ListNode<T>* p = list.first->next;
	while (p != nullptr)
	{
		if (p != list.first->next)
			cout << "-";
		cout << p->element;
		p = p->next;
	}
	return cout;
}
