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

	std::cout << "\t   【城市基本信息表】" << std::endl
		<< "-城市名-：" << p->element.getName()
		<< "  经度：" << p->element.getLocation().getLatitude()
		<< "  纬度：" << p->element.getLocation().getLongitude()
		<< "  方位：" << p->element.getLocation().getOrient() << std::endl << std::endl;

	std::cout << "\t   【人口信息】" << std::endl
		<< "年份       -人口数量-" << std::endl;
	for (auto j : p->element.getPopulation())
	{
		std::cout << j.first << "      " << j.second << std::endl;
	}

	std::cout << std::endl;
	std::cout << "\t   【GDP信息】" << std::endl
		<< "年份       -GPD总值-" << std::endl;
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
	// 头结点的index=-1，最后一个节点的index=size-1，这两个节点都可能为前驱节点，因此需要兼容。
	if (index <= -2 || index >= m_size) return nullptr;

	Node* node = head; // 初始指向头结点
	/* 如果在前半部分，就从头结点向后找index+1个找到目标节点*/
	if (index <= (m_size >> 1))
	{
		for (int i = 0; i <= index; i++) // index=-1时不进入循环，因此兼容了头节点
		{
			node = node->next;
		}
	}
	else // 否则就先把node改为最后一个节点，然后从后往前查找size - 1 - index次
	{
		node = head->prev;
		for (int i = 0; i < m_size - 1 - index; i++) // index=size-1时不进入循环，因此兼容了最后一个节点
		{
			node = node->prev;
		}
	}
	// 如果index = -1，则返回头结点
	// 如果index = size-1，则返回最后一个节点
	return node;
}





void BiCircleLinkedList::add(City Ele)
{
	add(m_size, Ele);
}



void BiCircleLinkedList::add(int index, City Ele)
{
	/* 获得前驱后继 */
	Node* prevNode = node(index - 1); // 注意：前驱节点一定存在，但是后继节点不一定存在，因此应该用前驱推后继
	Node* nextNode = prevNode->next;
	/* 创建新节点 */
	Node* newNode = new Node(prevNode, Ele, nextNode);
	/* 补全连接 */
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

