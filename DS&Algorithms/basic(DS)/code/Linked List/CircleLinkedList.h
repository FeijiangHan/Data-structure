#pragma once
#include<iostream>
using namespace std;


struct CircleNode
{
	int element; // 节点内的数据
	CircleNode* prev; // 指向此节点上一个节点的指针
	CircleNode* next; // 指向下一个节点的指针

	/*构造函数CircleNode
	 *形参：prev指针，元素数值，next指针
	 *作用：创建node节点时用于初始化
	 */
	CircleNode(CircleNode* p = NULL, int ele = 0, CircleNode* n = NULL) : prev(p), element(ele), next(n) {}
};




class CircleLinkedList
{
public:

	/*循环链表的构造函数：
	 *作用：初始化链表类内的指针和大小
	 */

	CircleLinkedList() {
		m_size = 0;
		first = last = NULL;
	}



	/*作用：根据索引找到指向此节点的指针
	 *形参：int 类型索引
	 *返回值：CircleNode* 节点指针
	 */

	CircleNode* node(int index)
	{
		//从前向后查找
		if (index <= (m_size >> 1)) {

			CircleNode* node = first;

			for (int i = 0; i < index; i++) {
				node = node->next;
			}

			return node;

		}
		//从后往前查找
		else {

			CircleNode* node = last;

			for (int i = 0; i < m_size - index; i++) {
				node = node->prev;
			}
			return node;

		}//end else

	}//end if



	//默认向结尾添加数据
	void add(int Ele)
	{

		add(m_size, Ele);

	}



	void add(int index, int Ele)
	{
		//向结尾添加数据时
		if (index == m_size)
		{

			CircleNode* old_last = last; // last原来指向的节点
			last = new CircleNode(old_last, Ele, first); // last指向新的节点，更新last指向

			//添加的是第一个节点时
			//使得新节点的prev和next都指向自己
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
			CircleNode* node = new CircleNode(prev, index, next); // 新节点

			next->prev = node;
			prev->next = node;

			//在第一个节点插入
			//需要更新last的指向
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
		//当只有一个节点时
		if (m_size == 1)
		{
			first = NULL;
			last = NULL;
		}

		//有多个节点时
		CircleNode* prev = dele_node->prev;
		CircleNode* next = dele_node->next;
		prev->next = next;
		next->prev = prev;

		//删除最后一个：更新last指向
		if (dele_node == last)
			last = prev;  //last points the front node of this dele_node

		// 删除第一个：更新first指向
		if (dele_node == first)
			first = next;  //first points the next note of dele_note

		m_size--;

		//释放节点前保存返回的节点值
		int val = dele_node->element;

		delete dele_node;
		return val;
	}



#define ELEMENT_NOT_FOUND -1

	int indexOf(int element)
	{
		//兼容元素为NULL时
		if (element == NULL)
		{

			CircleNode* node = first;

			for (int i = 0; i < m_size; i++)
			{
				if (node->element == NULL) return i;

				node = node->next;
			} // end for
		} // end if

		//一般情况
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



	//使得current指针向下指，并返回其指向的值
	int next() {
		if (current == NULL) return NULL;

		current = current->next;
		return current->element;
	}



	int remove_current()
	{

		if (current == NULL) return NULL;

		//提前保存
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

	int m_size; // 链表大小
	CircleNode* first; // 指向链表第一个节点的指针
	CircleNode* last; // 指向最后一个节点的指针
	CircleNode* current; // 指向当前节点的指针

};
