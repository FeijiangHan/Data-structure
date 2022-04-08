#pragma once
#include<iostream>
#include"City.h"
constexpr auto NOT_CONTAINS = -2;


struct Node
{
	City element;
	Node* prev;
	Node* next;
	Node() { }
	Node(Node* p, City ele, Node* n) : prev(p), element(ele), next(n) {}
};



class BiCircleLinkedList
{

private:
	int m_size;
	Node* head;

public:
	BiCircleLinkedList();
	~BiCircleLinkedList();

	int size();
	void Print_Node(Node* p);
	void Print();
	bool empty();
	int IndexOf(std::string name);
	bool Contains(std::string name);

	void add(City Ele);
	void add(int index, City Ele);
	City remove(int index);
	void clear();
	//City Update(int index, City ele);
	Node* node(int index);

};




BiCircleLinkedList::BiCircleLinkedList()
{
	m_size = 0;
	head = new Node(NULL, City(), NULL);
	head->next = head;
	head->prev = head;
}




BiCircleLinkedList::~BiCircleLinkedList()
{
	Node* node = head;

	for (int i = 0; i < m_size; i++)
	{
		Node* dele = node;
		node = node->next;
		delete dele;
	}
}



void BiCircleLinkedList::clear()
{
	m_size = 0;
	Node* node = head->next;

	for (int i = 0; i < m_size; i++)
	{
		Node* dele = node;
		node = node->next;
		delete dele;
	}
}




int BiCircleLinkedList::IndexOf(std::string name)
{
	Node* node = head->next;
	for (int i = 0; i < m_size; i++) {
		if (node->element.getName() == name) {
			return i;
		}
		node = node->next;
	}
	return NOT_CONTAINS;
}





bool BiCircleLinkedList::Contains(std::string name)
{
	return IndexOf(name) != NOT_CONTAINS;
}




int BiCircleLinkedList::size()
{
	return m_size;
}




void BiCircleLinkedList::Print_Node(Node* p)
{
	if (p == nullptr) return;

	std::cout << "\t   �����л�����Ϣ��" << std::endl
		<< "-������-��" << p->element.getName()
		<< "  ���ȣ�" << p->element.getLocation().getLatitude()
		<< "  γ�ȣ�" << p->element.getLocation().getLongitude()
		<< "  ��λ��" << p->element.getLocation().getOrient() << std::endl << std::endl;

	std::cout << "\t   ���˿���Ϣ��" << std::endl
		<< "���       -�˿�����-" << std::endl;
	for (auto j : p->element.getPopulation())
	{
		std::cout << j.first << "      " << j.second << std::endl;
	}

	std::cout << std::endl;
	std::cout << "\t   ��GDP��Ϣ��" << std::endl
		<< "���       -GPD��ֵ-" << std::endl;
	for (auto k : p->element.getGDP())
	{
		std::cout << k.first << "      " << k.second << std::endl;
	}
}



void BiCircleLinkedList::Print()
{
	Node* p = head->next;
	for (int i = 0; i < m_size; i++) {
		Print_Node(p);
		p = p->next;
	}
	std::cout << std::endl;
}


bool BiCircleLinkedList::empty()
{
	return m_size == 0;
}



Node* BiCircleLinkedList::node(int index)
{
	// ͷ����index=-1�����һ���ڵ��index=size-1���������ڵ㶼����Ϊǰ���ڵ㣬�����Ҫ���ݡ�
	if (index <= -2 || index >= m_size) return nullptr;

	Node* node = head; // ��ʼָ��ͷ���
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





void BiCircleLinkedList::add(City Ele)
{
	add(m_size, Ele);
}



void BiCircleLinkedList::add(int index, City Ele)
{
	/* ���ǰ����� */
	Node* prevNode = node(index - 1); // ע�⣺ǰ���ڵ�һ�����ڣ����Ǻ�̽ڵ㲻һ�����ڣ����Ӧ����ǰ���ƺ��
	Node* nextNode = prevNode->next;
	/* �����½ڵ� */
	Node* newNode = new Node(prevNode, Ele, nextNode);
	/* ��ȫ���� */
	nextNode->prev = newNode;
	prevNode->next = newNode;
	m_size++;
}



City BiCircleLinkedList::remove(int index)
{
	Node* prevNode = node(index - 1);
	Node* deleNode = prevNode->next;
	Node* nextNode = prevNode->next->next;

	prevNode->next = nextNode;
	nextNode->prev = prevNode;
	m_size--;
	City oldVal = deleNode->element;
	delete deleNode;

	return oldVal;
}

