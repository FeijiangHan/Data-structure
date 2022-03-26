#pragma once
#define DEFAULT_CAPACITY 10

template<class T>
class CircleDeque
{

public:
	friend ostream& operator<<(std::ostream& out ,CircleDeque<int> &que);
	
	
	//初始化
	CircleDeque();

	//尾部入队
	void enqueue(T Ele);
	//索引映射
	int TrueIndex(int index);
	//头部出队
	T dequeue();
	//获取头元素
	T front();

	//获取尾部元素
	T rear();
	//尾部删除
	T dequeueRear();

	//头部入队
	T enqueueFront(T Ele);

	//动态扩容
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



	//初始化
template<class T>
CircleDeque<T>::CircleQueue()
{
	m_size = 0;
	m_front = 0;
	m_capacity = DEFAULT_CAPACITY;
	m_element = new T[m_capacity]();  
	//注意不要再声明新变量了
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


	//尾部入队
template<class T>
	void CircleDeque<T>::enqueue(T Ele)
	{
		this->DanaCapacity(m_size+1);
		this->m_element[TrueIndex(m_size)] = Ele;
		m_size++;

	}



	//索引映射
	template<class T>
	int CircleDeque<T>::TrueIndex(int index)
	{
	    index += m_front;
		//index < 0 :加一个capacity
		//index > 0 : 分两种情况，一种是小于capacity，保持不变
		//一种是大于capacity，要减一个capacity
		//目的：把不在0-capacity这个区间内的数都映射回这一段区间

		if(index < 0)
			return index + m_capacity;
		else {
		   return (index < m_capacity) ? index : index - m_capacity;
		}
		//模运算优化，2mcapacity > index + front的
	}

	//头部出队
	template<class T>
	T CircleDeque<T>::dequeue()
	{
	   T temp = m_element[m_front];
	   this->m_element[m_front] = NULL;
	   m_front = TrueIndex(1);
	   m_size--;
	   return temp;
	}

	//获取头元素
	template<class T>
	T CircleDeque<T>::front()
	{
     	return this->m_element[m_front];
	}

	//动态扩容
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

		//注意更新容量和头指针
		m_capacity = NewCapacity;
		m_front = 0;

	}

	
	//获取尾部元素
	template<class T>
	T CircleDeque<T>::rear()
	{
		return m_element[TrueIndex(m_size - 1)];
	}


	//尾部删除
	template<class T>
	T CircleDeque<T>::dequeueRear()
	{
	   int rear = TrueIndex(m_size - 1);
	   T temp = m_element[rear];
	   this->m_element[rear] = NULL;
	   m_size--;
	   return temp;
	}

	//头部入队
	template<class T>
	T CircleDeque<T>::enqueueFront( T Ele )
	{
		this->DanaCapacity(m_size + 1);
		m_front = index(-1);
		this->m_element[m_front] = Ele;
		m_size++;
	}

