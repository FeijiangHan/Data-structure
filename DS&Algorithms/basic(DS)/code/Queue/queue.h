#pragma once
#include<iostream>


template<class ValType>
class Node
 {
 public:
	ValType element;
	Node* prev;
	Node* next;
	Node(Node* p = NULL, ValType ele = NULL, Node* n = NULL) : prev(p), element(ele), next(n){}
 };

//�������������Node��ע��
//last = new Node<T>(old_last,Ele,nullptr);
//Node<T>* p = NULL;
//�ô�������ʵ��template<class T>
//Node<T>* Queue<T>::node(int index)

template<class T>
class Queue : private Node<T>  //�̳еĸ������Զ���Ϊprivate
{

public:

	template<class T>
	friend std::ostream& operator << (std::ostream& out ,Queue<T> que);

	Queue();

	/*
	-�����±��ҵ��ڵ�
	-����ƥ��ģʽ���±�С��ǰ�����ң��±��Ӻ���ǰ��
	-�����±�
	*/
	T front();
	T back();
	Node<T>* node(int index);
	int size();
    void enqueue(T Ele,int index = m_size);
    T dequeue(int index = m_size - 1);
    void clear();
    void print(std::ostream& out);

private:
static int m_size;
Node<T>* first;
Node<T>* last;

};

template<class T>
int Queue<T>::m_size = 0;

// ��̬��Ա��ʼ��Ĭ��Ϊ0


template<class T>
std::ostream& operator << (std::ostream& out ,Queue<T> que)
{
	que.print(out);
	return out;
}


template<class T>
Queue<T>::Queue()
	{
        first = nullptr;
        last = nullptr;
	}



template<class T>
T Queue<T>::front()
	{
		return first->element;
	}


template<class T>
T Queue<T>::back()
	{
		return last->element;
	}


template<class T>
Node<T>* Queue<T>::node(int index)
	{
		if(index <= (m_size >> 1))
		{
		Node<T>* node = first;
		for(int i = 0; i < index; i++)
		{
			node = node->next; 
		}
		      return node;
		}
		else
		{
			Node<T>* node = last;
			//for(int i = m_size-1; i > index; i--)
			for(int i = 0; i < m_size - index - 1; i++)
			{
				node = node->prev;
			}
			   return node;
		}

	}


template<class T>
int Queue<T>::size()
	{
		return this->m_size;
	}


template<class T>
void Queue<T>::enqueue(T Ele,int index)
	{
		if(index == m_size)  //ĩβ���
		{
			Node<T>* old_last = last;
			last = new Node<T>(old_last,Ele,nullptr);

			if(old_last == nullptr)
				first = last; // ��ӵ�һ��
			else
				old_last->next = last;
		

		}else{

		Node<T>* next = node(index);
		Node<T>* prev = next->prev;

		Node<T>* node = new Node<T>(prev,index,next);
		next->prev = node;


		if(index != 0){
			prev->next = node;
		   }else{
			 first = node; //�ڵ�һ���ڵ����
		   }

	    }
		m_size++;

	}


template<class T>
T Queue<T>::dequeue(int index)
{
	if(m_size == 0) throw "û�нڵ����ɾ���ˣ�";

	Node<T>* dele_node = node(index);
	Node<T>* prev = dele_node->prev;
	Node<T>* next = dele_node->next;


	if(m_size == 1)       //next == NULL; prev == NULL;
	{
	int val = dele_node->element;
	delete dele_node;
	first = last = NULL;  //**ע�⣡������ע�����ָ�룬�Ա����´����
	m_size--;       
	return val;
	} 


	if(index == m_size -1) {
		prev->next = next; // prev != NULL; next == NULL;
		last = prev; 
	}else if(index == 0) {
		next->prev = prev; // next !=NULL; prev == NULL;
		first = next;  
	} else                 // next != NULL; prev != NULL;
	{
	  prev->next = next;
	  next->prev = prev;
	}

	m_size--;
	int val = dele_node->element;
	delete dele_node;
	return val;
}

template<class T>
void Queue<T>::clear()
{
	Node<T>* temp = first;
	while(temp != NULL)
	{
		Node<T> *temp2 = temp->next; 
		delete temp;
		temp = temp2;
	}
	m_size = 0;
}


template<class T>
void Queue<T>::print(std::ostream& out)
{
	Node<T>* node = first;
	while(node != NULL) {
		out << node->element << ' ' ;
		node = node->next;
	}
}

