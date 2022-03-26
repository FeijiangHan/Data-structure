#include"Danamic_Array.h"
#include"Person.h"


template<class T>
		ArrayList<T>::ArrayList(int capaticy = DEFAULT_CAPACITY) {
		m_capacity = (capaticy < DEFAULT_CAPACITY) ? DEFAULT_CAPACITY : capaticy;
		m_elements = new T[m_capacity];
		m_size = 0;
	}

	  /**
	   * �������Ԫ��
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
	 * Ԫ�ص�����
	 * @return
	 */
	  
template<class T>
	   int ArrayList<T>::size() {
		return m_size;
	}

    /**
	 *�ж��Ƿ�Ϊ��
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
	 * ��ȡindexλ�õ�Ԫ��
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
	 * �Ƿ����ĳ��Ԫ��
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
	 * ����indexλ�õ�Ԫ��
	 * @param index
	 * @param element
	 * @return ԭ����Ԫ��
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
	
	//������Ҫ���ݣ�o��1��
	//��Ҫ���ݣ�o��n��
	//��̯���Ӷȣ�o��1��һ������������ͬ ��11111111119���Ӷ�ͻ��ʱ��
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
		//@important .. ���ټ���������Ż�
		//�������Ӷȣ���Сindex=size O��1�������O��n����ƽ��1+2+3+...+n/n=O(n)
		this->m_elements[index] = Ele;
		m_size++;
	}

	//�������Ѱ��λ�ø��Ӷ�1������������Ӷ�n
	//�������Ѱ��λ�ø��Ӷ�n������������Ӷ�1
	//�ۺ���������̬�������������ɾ������ʱ�临�Ӷȶ���n���Ҷ�̬�����set��getʱ�临�Ӷ�Ϊ1�����ò��ң����������Ϊn����Ҫ���ң�
	//���ǣ�����Կռ�������ʸ���

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



	//�������Ӷȣ���Сindex=size O��1�������O��n����ƽ��1+2+3+...+n/n=O(n) 
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

		//@important �����˼�����������
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



	//�쳣���Ż�delete��add�������