#pragma once
#include<iostream>
using namespace std;


struct CircleNode
{
	int element; // �ڵ��ڵ�����
	CircleNode* prev; // ָ��˽ڵ���һ���ڵ��ָ��
	CircleNode* next; // ָ����һ���ڵ��ָ��

	/*���캯��CircleNode
	 *�βΣ�prevָ�룬Ԫ����ֵ��nextָ��
	 *���ã�����node�ڵ�ʱ���ڳ�ʼ��
	 */
	CircleNode(CircleNode* p = NULL, int ele = 0, CircleNode* n = NULL) : prev(p), element(ele), next(n) {}
};




class CircleLinkedList
{
public:

	/*ѭ������Ĺ��캯����
	 *���ã���ʼ���������ڵ�ָ��ʹ�С
	 */

	CircleLinkedList() {
		m_size = 0;
		first = last = NULL;
	}



	/*���ã����������ҵ�ָ��˽ڵ��ָ��
	 *�βΣ�int ��������
	 *����ֵ��CircleNode* �ڵ�ָ��
	 */

	CircleNode* node(int index)
	{
		//��ǰ������
		if (index <= (m_size >> 1)) {

			CircleNode* node = first;

			for (int i = 0; i < index; i++) {
				node = node->next;
			}

			return node;

		}
		//�Ӻ���ǰ����
		else {

			CircleNode* node = last;

			for (int i = 0; i < m_size - index; i++) {
				node = node->prev;
			}
			return node;

		}//end else

	}//end if



	//Ĭ�����β�������
	void add(int Ele)
	{

		add(m_size, Ele);

	}



	void add(int index, int Ele)
	{
		//���β�������ʱ
		if (index == m_size)
		{

			CircleNode* old_last = last; // lastԭ��ָ��Ľڵ�
			last = new CircleNode(old_last, Ele, first); // lastָ���µĽڵ㣬����lastָ��

			//��ӵ��ǵ�һ���ڵ�ʱ
			//ʹ���½ڵ��prev��next��ָ���Լ�
			if (old_last == NULL) {

				first = last;
				old_last = last;

			}//end inner if
			else {

				old_last->next = last;
				first->prev = last;
			}//end inner else	
		}//end if

		else
		{

			CircleNode* next = node(index);
			CircleNode* prev = next->prev;
			CircleNode* node = new CircleNode(prev, index, next); // �½ڵ�

			next->prev = node;
			prev->next = node;

			//�ڵ�һ���ڵ����
			//��Ҫ����last��ָ��
			if (next == first)
				first = node;
		}

		m_size++;

	}//end function add



	int remove_index(int index)
	{

		if (index < 0 || index >= m_size)
			throw "wrong!overrange";

		else
			return remove_node(node(index));
	}


	int remove_element(int Ele)
	{
		return remove_index(indexOf(Ele));
	}


	int remove_node(CircleNode* dele_node)
	{
		//��ֻ��һ���ڵ�ʱ
		if (m_size == 1)
		{
			first = NULL;
			last = NULL;
		}

		//�ж���ڵ�ʱ
		CircleNode* prev = dele_node->prev;
		CircleNode* next = dele_node->next;
		prev->next = next;
		next->prev = prev;

		//ɾ�����һ��������lastָ��
		if (dele_node == last)
			last = prev;  //last points the front node of this dele_node

		// ɾ����һ��������firstָ��
		if (dele_node == first)
			first = next;  //first points the next note of dele_note

		m_size--;

		//�ͷŽڵ�ǰ���淵�صĽڵ�ֵ
		int val = dele_node->element;

		delete dele_node;
		return val;
	}



#define ELEMENT_NOT_FOUND -1

	int indexOf(int element)
	{
		//����Ԫ��ΪNULLʱ
		if (element == NULL)
		{

			CircleNode* node = first;

			for (int i = 0; i < m_size; i++)
			{
				if (node->element == NULL) return i;

				node = node->next;
			} // end for
		} // end if

		//һ�����
		else {

			CircleNode* node = first;

			for (int i = 0; i < m_size; i++)
			{
				if (node->element == element)
					return i;

				node = node->next;
			} // end for
		} // end else

		return ELEMENT_NOT_FOUND;
	} // end function indexOf




	void reset() {
		current = first;
	}



	//ʹ��currentָ������ָ����������ָ���ֵ
	int next() {
		if (current == NULL) return NULL;

		current = current->next;
		return current->element;
	}



	int remove_current()
	{

		if (current == NULL) return NULL;

		//��ǰ����
		CircleNode* next_node = current->next;
		int element = remove_node(current);

		if (m_size == 0) {
			current = NULL;
		}
		else {
			current = next_node;
		}

		return element;
	}



public:

	int m_size; // �����С
	CircleNode* first; // ָ�������һ���ڵ��ָ��
	CircleNode* last; // ָ�����һ���ڵ��ָ��
	CircleNode* current; // ָ��ǰ�ڵ��ָ��

};
