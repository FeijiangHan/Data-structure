#pragma once
#include<iostream>
using namespace std;


struct Node
 {
	int element;
	//shared_ptr<Node> next;
	Node* prev;
	Node* next;
	Node(Node* p, int ele, Node* n) : prev(p), element(ele), next(n){}
 };


class BiLinkedList
{
public:
//	friend ostream& operator<<(ostream& out, BiLinkedList& ob);

	BiLinkedList()
	{
		m_size = 0;
        first = NULL;
        last = NULL;
	}

	/*
	-根据下标找到节点
	-两种匹配模式，下标小从前往后找，下标大从后往前找
	-返回下标
	*/
	Node* GetFirst()
	{
		return first;
	}


	Node* GetLast()
	{
		return last;
	}


	Node* node(int index)
	{
		if(index <= (m_size >> 1))
		{
		Node* node = first;
		for(int i = 0; i < index; i++)
		{
			node = node->next; 
		}
		      return node;
		}
		else
		{
			Node* node = last;
			//for(int i = m_size-1; i > index; i--)
			for(int i = 0; i <= m_size - index - 1; i++)
			{
				node = node->prev;
			}
			   return node;
		}

	}



	void add(int Ele)
	{
		add(m_size,Ele);
	}

	void add(int index,int Ele)
	{
		if(index == m_size)
		{
			Node* old_last = last;
			last = new Node(old_last,Ele,nullptr);

			if(old_last == nullptr)
				first = last;
			else
				old_last->next = last;
		

		}else{

		Node* next = node(index);
		Node* prev = next->prev;

		Node* node = new Node(prev,index,next);
		next->prev = node;

		if(index != 0){
			prev->next = node;
		   }else{
			 first = node; //在第一个节点插入
		   }

	    }
		m_size++;

	}

int remove(int index)
{
	Node* dele_node = node(index);

	Node* prev = dele_node->prev;
	Node* next = dele_node->next;

	if(next != nullptr && prev != nullptr )  //index = m_size-1
		prev->next = next;
	else
		last = prev;  //last points the front node of this dele_node

	if(next != nullptr && prev != nullptr )  //index = 0
		next->prev = prev;
	else 
		first = next;  //first points the next note of dele_note

	m_size--;
	int val = dele_node->element;
	delete dele_node;
	return val;
}

void clear()
{
	Node* temp = first->next;
	while(temp != NULL)
	{
		delete temp->prev;
		temp = temp->next;
	}
	m_size = 0;
}

public:
int m_size;
Node* first;
Node* last;
};


