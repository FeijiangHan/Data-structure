#pragma once
#define DEFAULT_CAPACITY 10

template<class T>
class CircleDeque
{

public:
	friend ostream& operator<<(std::ostream& out ,CircleDeque<int> &que);
	
	
	//��ʼ��
	CircleDeque();

	//β�����
	void enqueue(T Ele);
	//����ӳ��
	int TrueIndex(int index);
	//ͷ������
	T dequeue();
	//��ȡͷԪ��
	T front();

	//��ȡβ��Ԫ��
	T rear();
	//β��ɾ��
	T dequeueRear();

	//ͷ�����
	T enqueueFront(T Ele);

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
CircleDeque<T>::CircleQueue()
{
	m_size = 0;
	m_front = 0;
	m_capacity = DEFAULT_CAPACITY;
	m_element = new T[m_capacity]();  
	//ע�ⲻҪ�������±�����
};


std::ostream& operator<<(std::ostream& out ,CircleDeque<int> &que)
{
	std::cout << "" << << std::endl;
	for(int i = 0; i< que.m_capacity; i++)
	{
		out << que.m_element[i] << ' ';
	}
	return out;
}


	//β�����
template<class T>
	void CircleDeque<T>::enqueue(T Ele)
	{
		this->DanaCapacity(m_size+1);
		this->m_element[TrueIndex(m_size)] = Ele;
		m_size++;

	}



	//����ӳ��
	template<class T>
	int CircleDeque<T>::TrueIndex(int index)
	{
	    index += m_front;
		//index < 0 :��һ��capacity
		//index > 0 : �����������һ����С��capacity�����ֲ���
		//һ���Ǵ���capacity��Ҫ��һ��capacity
		//Ŀ�ģ��Ѳ���0-capacity��������ڵ�����ӳ�����һ������

		if(index < 0)
			return index + m_capacity;
		else {
		   return (index < m_capacity) ? index : index - m_capacity;
		}
		//ģ�����Ż���2mcapacity > index + front��
	}

	//ͷ������
	template<class T>
	T CircleDeque<T>::dequeue()
	{
	   T temp = m_element[m_front];
	   this->m_element[m_front] = NULL;
	   m_front = TrueIndex(1);
	   m_size--;
	   return temp;
	}

	//��ȡͷԪ��
	template<class T>
	T CircleDeque<T>::front()
	{
     	return this->m_element[m_front];
	}

	//��̬����
	template<class T>
	void CircleDeque<T>::DanaCapacity(int capa)
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

	
	//��ȡβ��Ԫ��
	template<class T>
	T CircleDeque<T>::rear()
	{
		return m_element[TrueIndex(m_size - 1)];
	}


	//β��ɾ��
	template<class T>
	T CircleDeque<T>::dequeueRear()
	{
	   int rear = TrueIndex(m_size - 1);
	   T temp = m_element[rear];
	   this->m_element[rear] = NULL;
	   m_size--;
	   return temp;
	}

	//ͷ�����
	template<class T>
	T CircleDeque<T>::enqueueFront( T Ele )
	{
		this->DanaCapacity(m_size + 1);
		m_front = index(-1);
		this->m_element[m_front] = Ele;
		m_size++;
	}

