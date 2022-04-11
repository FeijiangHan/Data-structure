#pragma once
#include<iostream>
constexpr auto NOT_CONTAINS = -1;

template<class E>
struct Node
{
	E element;
	Node* prev;
	Node* next;
	Node() { }
	Node(Node* p, E ele, Node* n) : prev(p), element(ele), next(n) {}
};


template<class E>
class BiCircleLinkedList
{

private:
	int m_size;
	Node<E>* head;

public:
	BiCircleLinkedList();
	~BiCircleLinkedList();

	int size();
	void Print();
	bool empty();
	int IndexOf(E ele);
	bool Contains(E ele);

	void add(int Ele);
	void add(int index, int Ele);
	int remove(int index);
	int Insertion(E val);
	void clear();
	E Update(int index,E ele);

protected:
	Node<E>* node(int index);

};




template<class E>
BiCircleLinkedList<E>::BiCircleLinkedList()
{
	m_size = 0;
	head = new Node<E>(NULL, 0, NULL);
	head->next = head;
	head->prev = head;
}




template<class E>
BiCircleLinkedList<E>::~BiCircleLinkedList()
{
	Node<E>* node = head;

	for (int i = 0; i < m_size; i++)
	{
		Node<E>* dele = node;
		node = node->next;
		delete dele;
	}
}




template<class E>
void BiCircleLinkedList<E>::clear()
{
	m_size = 0;
	Node<E>* node = head->next;

	for (int i = 0; i < m_size; i++)
	{
		Node<E>* dele = node;
		node = node->next;
		delete dele;
	}
}




template<class E>
int BiCircleLinkedList<E>::IndexOf(E ele)
{
	Node<E>* node = head->next;
	for (int i = 0; i < m_size; i++) {
		if (node->element == ele) {
			return i;
		}	
		node = node->next;
	}
	return NOT_CONTAINS;
}




template<class E>
bool BiCircleLinkedList<E>::Contains(E ele)
{
	return IndexOf(ele) != NOT_CONTAINS;
}



template<class E>
int BiCircleLinkedList<E>::size()
{
	return m_size;
}



template<class E>
void BiCircleLinkedList<E>::Print()
{
	Node<E>* p = head->next;
	for (int i = 0; i < m_size;i++) {
		std::cout << p->element << ' ';
		p = p->next;
	}
	std::cout << std::endl;
}



template<class E>
bool BiCircleLinkedList<E>::empty()
{
	return m_size == 0;
}



template<class E>
E BiCircleLinkedList<E>::Update(int index,E ele)
{
	E oldEle = node(index)->element;
	node(index)->element = ele;
	return oldEle;
}



template<class E>
Node<E>* BiCircleLinkedList<E>::node(int index)
{
	// ͷ����index=-1�����һ���ڵ��index=size-1���������ڵ㶼����Ϊǰ���ڵ㣬�����Ҫ���ݡ�
	if (index <= -2 || index >= m_size) return nullptr;

	Node<E>* node = head; // ��ʼָ��ͷ���
	/* �����ǰ�벿�֣��ʹ�ͷ��������index+1���ҵ�Ŀ��ڵ�*/
	if (index <= (m_size >> 1))
	{
		for (int i = 0; i <= index; i++) // index=-1ʱ������ѭ������˼�����ͷ�ڵ�
		{
			node = node->next;
		}
	}
	else // ������Ȱ�node��Ϊ���һ���ڵ㣬Ȼ��Ӻ���ǰ����size - 1 - index��
	{
		node = head->prev;
		for (int i = 0; i < m_size - 1 - index; i++) // index=size-1ʱ������ѭ������˼��������һ���ڵ�
		{
			node = node->prev;
		}
	}
	// ���index = -1���򷵻�ͷ���
	// ���index = size-1���򷵻����һ���ڵ�
	return node; 
} 




template<class E>
void BiCircleLinkedList<E>::add(int Ele)
{
	add(m_size, Ele);
}



template<class E>
void BiCircleLinkedList<E>::add(int index, int Ele)
{
	/* ���ǰ����� */
	Node<E>* prevNode = node(index - 1); // ע�⣺ǰ���ڵ�һ�����ڣ����Ǻ�̽ڵ㲻һ�����ڣ����Ӧ����ǰ���ƺ��
	Node<E>* nextNode = prevNode->next;
	/* �����½ڵ� */
	Node<E>* newNode = new Node<E>(prevNode, Ele, nextNode);
	/* ��ȫ���� */
	nextNode->prev = newNode;
	prevNode->next = newNode;
	m_size++;
}



template<class E>
int BiCircleLinkedList<E>::remove(int index)
{
	Node<E>* prevNode = node(index - 1);
	Node<E>* deleNode = prevNode->next;
	Node<E>* nextNode = prevNode->next->next;

	prevNode->next = nextNode;
	nextNode->prev = prevNode;
	m_size--;
	E oldVal = deleNode->element;
	delete deleNode;

	return oldVal;
}



template<class E>
int BiCircleLinkedList<E>::Insertion(E val)
{
	Node<E>* cur = head->next;
	int curIndex = m_size;
	while(cur != head && cur->next != head)
	{
		if (val >= cur->element && val < cur->next->element)
		{
			curIndex = IndexOf(cur->next->element);
		}
		cur = cur->next;
	}
	add(curIndex,val);
	std::cout << val << "�Ĳ���λ�ã� " << curIndex << std::endl;
	return curIndex;
}