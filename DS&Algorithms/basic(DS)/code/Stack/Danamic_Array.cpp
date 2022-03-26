#include"Danamic_Array.h"
#include"Person.h"


template<class T>
		ArrayList<T>::ArrayList(int capaticy = DEFAULT_CAPACITY) {
		m_capacity = (capaticy < DEFAULT_CAPACITY) ? DEFAULT_CAPACITY : capaticy;
		m_elements = new T[m_capacity];
		m_size = 0;
	}

	  /**
	   * 清除所有元素
	   */

template<class T>
	  void ArrayList<T>::clearNormal() {
	   m_size = 0;
	}
	  
template<class T>
	  void ArrayList<T>::clearHeap() {
		  for(int i = 0; i < m_size; i++)
		  {
			  delete this->m_elements[i];
			  this->m_elements[i] = nullptr;
		  }
	   m_size = 0;
	}

	/**
	 * 元素的数量
	 * @return
	 */
	  
template<class T>
	   int ArrayList<T>::size() {
		return m_size;
	}

    /**
	 *判断是否为空
	 *empty -> 1
	 *not -> 0
	 */
	   
template<class T>
	bool ArrayList<T>::Is_Empty()
	{
		return m_size == 0;

		//return (m_size == 0) ? true : false;
	}
	/**
	 *Find the Index of the Element
	 */
	
template<class T>
	int ArrayList<T>::IndexOf(T Ele)
	{
		if(Ele == NULL)
		{
			for(int i = 0; i < m_size; i++)
			{
				if(this->m_elements[i] == NULL)
					return i;
			}
		}
		for(int i = 0; i < m_size; i++)
		{
			if(Ele == m_elements[i])
				return i;
		}
		return ELEMENT_NOT_FOUND;
	}

	/**
	 * 获取index位置的元素
	 * @param index
	 * @return
	 */
	
template<class T>
	T ArrayList<T>::get(int index) {
		if(index < 0 || index !< m_size)
			throw "false,overflow!";
		else
			return m_elements[index];
	}

	/**
	 * 是否包含某个元素
	 * @param element
	 * @return
	 */
	
template<class T>
	bool ArrayList<T>::contains(T Ele)
	{
		//if(IndexOf(Ele) != -1)
		//	return true;
		//else
		//	return false;
		/*return (IndexOf(Ele) != -1) ? true : false; */
		return IndexOf(Ele) != ELEMENT_NOT_FOUND;
	}


    /**
	 * 设置index位置的元素
	 * @param index
	 * @param element
	 * @return 原来的元素
	 */
	
template<class T>
	T ArrayList<T>::set(int index,T element) {
		if(index < 0 || index !< m_size)
			throw "false,overflow!";
		T temp = this->m_elements[index];   //recreat =
		this->m_elements[index] = element;
		return temp ;	
	}

	//add
	
template<class T>
	void ArrayList<T>::add()
	{
		int num;
		T Ele;
		cin >> num;   //recreat >>
		int NewSpace = m_size+num;

		if(NewSpace < m_capacity || NewSpace == m_capacity)
		{
			for(int i = m_size ; i< NewSpace ; i++){
			cin >> Ele;
			this->m_elements[i] = Ele;
			m_size ++;   //@important
			}

		}
		else
		{ 
			T * NewArray = new T[NewSpace];
		    for(int i = 0;i < m_size ;i++)
			{
				NewArray[i] = this->m_elements[i];
			}
			for(int i = m_size ; i < NewSpace ; i++)
			{
				cin >> Ele;
				NewArray[i] = Ele;
			}
			m_size = NewSpace;//@important
			m_capacity = NewSpace;//@important
			delete[] this->m_elements;
			this->m_elements = NewArray;
			cout << "NewSpace has been created!" <<endl;
		}

	}
	
	//当不需要扩容：o（1）
	//需要扩容：o（n）
	//均摊复杂度：o（1）一般与最好情况相同 （11111111119复杂度突变时）
template<class T>
	void ArrayList<T>::add(T Ele)
	{
		add(m_size,Ele);   //give an initial number
	}

	
template<class T>
	void ArrayList<T>::add(int index ,T Ele ,int num = 1)
	{
    	if(index < 0 || index > m_size)
			throw "false,overflow!";

		ensureCapacity(m_size+1);  //expand 1.5

		//for(int i = m_size; i>=index+1 ;i--)
		//{
		//	this->m_elements[i] = this->m_elements[i-1];
		//}

		//for(int i = m_size-1; i>=index ;i--)
		//{
		//	this->m_elements[i+1] = this->m_elements[i];
		//}

		for(int i = m_size; i>index ;i--)
		{
			this->m_elements[i] = this->m_elements[i-1];
		}
		//@important .. 减少计算次数，优化
		//分析复杂度：最小index=size O（1），最大O（n），平均1+2+3+...+n/n=O(n)
		this->m_elements[index] = Ele;
		m_size++;
	}

	//数组插入寻找位置复杂度1，插入操作复杂度n
	//链表插入寻找位置复杂度n，插入操作复杂度1
	//综合来看，动态数组和链表插入和删除数据时间复杂度都是n。且动态数组的set和get时间复杂度为1（不用查找），而链表的为n（需要查找）
	//但是，链表对空间的利用率更高

template<class T>
	 void ArrayList<T>::ensureCapacity(int n){
		 if(n < m_capacity || n == m_capacity)
			 return;
		 m_capacity = m_capacity + (m_capacity >> 1);

		 T * NewArray = new T[m_capacity];
		 for(int i = 0;i < m_size;i++)
		 {
			 NewArray[i] = this->m_elements[i];
		 }   //o(n)
		 delete[] this->m_elements;
		 this->m_elements = NewArray;
		 cout << "1.5 Expand" << endl;
	 }



	//分析复杂度：最小index=size O（1），最大O（n），平均1+2+3+...+n/n=O(n) 
template<class T>
	T ArrayList<T>::Dele_ArrayForIndex(int index)
	{
		T temp;
		temp = this->m_elements[index];
		//for(int i = index;i <= m_size - 2; i++)
		//{
		//	this->m_elements[i] = this->m_elements[i+1];
		//}
		for(int i = index+1;i < m_size; i++)
		{
			this->m_elements[i-1] = this->m_elements[i];
		}

		//@important 减少了减法次数、、
		m_size--; //@important
		return temp;
	}

	template<class T>
	void ArrayList<T>::Dele_ArrayForElement(int Ele)
	{
		if(this->IndexOf(Ele) == ELEMENT_NOT_FOUND){
			cout << "Delete Wrong: Not Find This Element!" <<endl;
			return;
		}
		this->Dele_ArrayForIndex(this->IndexOf(Ele));
	}

	
template<class T>
	T ArrayList<T>::Dele_Array_Heap(int index)
	{
		T temp;
		temp = this->m_elements[index];
		for(int i = index;i <= m_size - 2; i++)
		{
			this->m_elements[i] = this->m_elements[i+1];
		}
		m_size--;
		delete this->m_elements[m_size];
		this->m_elements[m_size] = nullptr;
		return temp;
	}



	//异常，优化delete和add计算次数