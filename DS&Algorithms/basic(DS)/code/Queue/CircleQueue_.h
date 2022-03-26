#pragma once
#define DEFAULT_CAPACITY 10



template<class T>
class CircleQueue
{
public:

	template<class T>
	friend std::ostream& operator<<(std::ostream& out ,CircleQueue<T> &que);
	
	
	//��ʼ��
	CircleQueue();

	//β�����
	void enqueue(T Ele);
	//����ӳ��
	int TrueIndex(int index);
	//ͷ������
	T dequeue();
	//��ȡͷԪ��
	T front();

	//��̬����
	void DanaCapacity(int capa);

	//size
	int size()
	{
		return m_size;
	}

	//empty
	bool IsEmpty()
	{
		return m_size == 0;
	}


private:
	int m_front;
	int m_size;
	int* m_element;
	int m_capacity;
};



	//��ʼ��
template<class T>
CircleQueue<T>::CircleQueue()
{
	m_size = 0;
	m_front = 0;
	m_capacity = DEFAULT_CAPACITY;
	m_element = new T[m_capacity]();  //ע�ⲻҪ�������±����ˣ�
}

	//β�����
template<class T>
	void CircleQueue<T>::enqueue(T Ele)
	{
		this->DanaCapacity(m_size+1);
		this->m_element[TrueIndex(m_size)] = Ele;
		m_size++;

	}



	//����ӳ��
	template<class T>
	int CircleQueue<T>::TrueIndex(int index)
	{
		index += m_front;
		return (index < m_capacity) ? index : index - m_capacity;
		//ģ�����Ż���2mcapacity > index + front��
	}

	//ͷ������
	template<class T>
	T CircleQueue<T>::dequeue()
	{
	   T temp = m_element[m_front];
	   this->m_element[m_front] = NULL;
	   m_front = TrueIndex(1);
	   m_size--;
	   return temp;
	}

	//��ȡͷԪ��
	template<class T>
	T CircleQueue<T>::front()
	{
     	return this->m_element[m_front];
	}

	//��̬����
	template<class T>
	void CircleQueue<T>::DanaCapacity(int capa)
	{
		int oldCapa = this->m_capacity;
		if(capa <= oldCapa) return;

		int NewCapacity = m_capacity + (m_capacity >> 1);
		T* NewEle = new T[NewCapacity]();

		for(int i = 0; i < m_size ; i++)
		{
			NewEle[i] = this->m_element[TrueIndex(i)];
		}

		delete[] this->m_element;
		this->m_element = NewEle;

		//ע�����������ͷָ��
		m_capacity = NewCapacity;
		m_front = 0;

	}

template<class T>
std::ostream& operator<<(std::ostream& out ,CircleQueue<T> &que)
{
	for(int i = 0; i< que.m_capacity; i++)
	{
		out << que.m_element[i] << ' ';
	}
	return out;
}