#pragma once
#include<iostream>

using namespace std;
#define ELEMENT int
#define DEFAULT_CAPACITY 10
#define ELEMENT_NOT_FOUND -1

template<class T>
class ArrayList
{
public:
		ArrayList(int capaticy = DEFAULT_CAPACITY);

	  /**
	   * �������Ԫ��
	   */
	  void clearNormal() ;
	  void clearHeap() ;

	/**
	 * Ԫ�ص�����
	 * @return
	 */
	   int size();

    /**
	 *�ж��Ƿ�Ϊ��
	 *empty -> 1
	 *not -> 0
	 */
	bool Is_Empty();
	/**
	 *Find the Index of the Element
	 */
	int IndexOf(T Ele);
	/**
	 * ��ȡindexλ�õ�Ԫ��
	 * @param index
	 * @return
	 */
	T get(int index) ;

	/**
	 * �Ƿ����ĳ��Ԫ��
	 * @param element
	 * @return
	 */
	bool contains(T Ele);


    /**
	 * ����indexλ�õ�Ԫ��
	 * @param index
	 * @param element
	 * @return ԭ����Ԫ��
	 */
	T set(int index,T element) ;

	//add
	void add();
	void add(T Ele);

	void add(int index ,T Ele ,int num = 1);

	 void ensureCapacity(int n);
	 void trim();

	T Dele_ArrayForIndex(int index);

	void Dele_ArrayForElement(int Ele);

	T Dele_Array_Heap(int index);
	



public:
	int m_size;
	T * m_elements;
	int m_capacity;
	
};


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
		if(index < 0 || index >= m_size)
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
		 if(n <= m_capacity)
			 return;
		 int new_capacity = m_capacity + (m_capacity >> 1);

		 T * NewArray = new T[new_capacity];
		 for(int i = 0;i < m_size;i++)
		 {
			 NewArray[i] = this->m_elements[i];
		 }   //o(n)
		 delete[] this->m_elements;
	     cout <<"old_capacity:"<< m_capacity <<"--->new_capacity:"<< new_capacity << endl;
		 m_capacity = new_capacity;
		 this->m_elements = NewArray;
	 }

//��С�����������������������������������ɣ������Ӷ���

template<class T>
void ArrayList<T>::trim()
{
	int new_capacity = m_capacity >> 1;
	if(m_size >= new_capacity || new_capacity < DEFAULT_CAPACITY)  return;
		T * new_array = new T[new_capacity];

		for(int i = 0; i < m_size; i++)
		{
			new_array[i] = this->m_elements[i];
		}

	    cout <<"old_capacity:"<< m_capacity <<"--->new_capacity:"<< new_capacity << endl;
		m_capacity = new_capacity;
		delete[] this->m_elements;
		this->m_elements = new_array;

}


	//�������Ӷȣ���Сindex=size O��1�������O��n����ƽ��1+2+3+...+n/n=O(n) 
template<class T>
	T ArrayList<T>::Dele_ArrayForIndex(int index)
	{
		trim();
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


		ostream& operator<<(ostream& cout,ArrayList<ELEMENT>& array)
	{
		cout << "[ ";
		for(int i = 0;i< array.m_size ;i++)
		{
			if(i != 0) cout << ",";
			cout << array.m_elements[i];
		}
		cout << " ]" <<endl;
		return cout ;
	}

	//ostream& operator<<(ostream& cout,ArrayList<Person*>& array)
	//{
	//	cout << "[ ";
	//	for(int i = 0;i< array.m_size ;i++)
	//	{
	//		if(i != 0) cout << ",";
	//		cout <<"(" <<array.m_elements[i]->year <<","<<array.m_elements[i]->name << ")";
	//	}
	//	cout << " ]" <<endl;
	//	return cout ;
	//}