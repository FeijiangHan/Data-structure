#include"LinkedList.h"


struct Node;

	void LinkedList::Initial()
	{
		m_size = 0;
		first = new Node(nullptr,nullptr);
	}
	  /**
	   * �������Ԫ��
	   */
	 void LinkedList::clear() 
	  {
		  m_size = 0;
		  Node* node = first->next;

		  while(node != nullptr)
		  {
			Node* dele = node;
		    node = node->next;
			delete dele;
		  }
	  }
//���O(1)�� �����size���Ľڵ�O��n����ƽ��O��n��
	Node* LinkedList::node(int index)
	{
		Node* node = first->next;
		for(int i = 0; i < index; i++)
		{
			node = node->next; 
		}
		return node;
	}
	

	int LinkedList::IndexOf(int Ele)
	{
		Node* node = first->next;
		for(int i = 0; i< m_size; i++){
			if(node->element == Ele)
				return i;
			node = node->next;
		}

	}
	/**
	 * ��ȡindexλ�õ�Ԫ��
	 * @param index
	 * @return
	 */
	int LinkedList::get(int index)
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
	bool LinkedList::contains(int Ele)
	{
		Node* node = first->next;
		while(node != nullptr)
		{
			if(node->element == Ele)
				return true;
		}
		return false;
	}


    /**
	 * ����indexλ�õ�Ԫ��
	 * @param index
	 * @param element
	 * @return ԭ����Ԫ��
	 */
	int LinkedList::set(int index,int element)
	{
		Node* old = node(index);
		node(index)->element = element;
		return old->element;
	}

	////add
	//void add()
	//void add(T Ele);


	void LinkedList::add(int Ele)
	{
	  add(m_size,Ele);
	}


	//O��n��
	void LinkedList::add(int index ,int Ele)
	{
		//if(index == 0)  //@important
		//{
		//	first->next =new Node(Ele,first->next);
		//}

		//else
		//{
		//Node* p = node(index-1);  //����ֱ����node������ֵ
		//p->next = new Node(Ele,p->next);
		//}

		Node* p = (index == 0) ? first->next : node(index-1);  //����ֱ����node������ֵ,��Ϊ��ͷ�ڵ㣬����ͳһ����
		p->next = new Node(Ele,p->next);
		m_size++;
	}

	//o(n)
	int LinkedList::Dele_ForIndex(int index)
	{
		//if(index == 0)
		//{
		//	Node* node = first;
		//	first->next = first->next->next;
		//	m_size--;
		//    return node->element;
		//}
		//else
		//{
		//Node* prv = node(index-1);
		//Node* node = prv->next;
		//prv->next = prv->next->next;
		//m_size--;
	 //   return node->element;
		//}
		
		Node* prv = (index == 0) ? first : node(index-1);
		Node* node = prv->next;
		prv->next = prv->next->next;
		m_size--;
	    return node->element;
	}


	//void Dele_ForElement(int Ele) = 0;

	ostream& operator<<(ostream& cout,LinkedList & list)
{
	Node* p = list.first->next;
	while(p != nullptr)
	{
		if(p != list.first->next)
			cout <<"-";
		cout << p->element;
		p = p->next;
	}
	return cout;
}