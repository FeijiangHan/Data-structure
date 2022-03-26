#pragma once
#include<cmath>
#include<iostream>
#include<vector>
#include"Heap.h"
#include"Compare.h"
#include<cassert>

/*  �ѣ��ڲ�����Ļ����ϵõ���ֵ��ԭ����ͨ�����ʱ���������*/
constexpr int DEFAULT_CAPACITY = 8;


template<class T>
class BinaryHeap : public Heap<T>
{
private:

	int capacity;
	int m_size;
	T* danamicArray;
	Compare cmp;

public:
	BinaryHeap() {
		m_size = 0;
		capacity = DEFAULT_CAPACITY;
		danamicArray = new T[capacity];
	}

	BinaryHeap(std::vector<T> ele) {

		if (ele.empty()) BinaryHeap();
		else {
			capacity = DEFAULT_CAPACITY >= ele.size() ? DEFAULT_CAPACITY : ele.size();
			m_size = ele.size();
			danamicArray = new T[capacity];
			for (int i = 0; i < ele.size(); i++) {
				this->danamicArray[i] = (T)ele[i];
			}

			heapify();
		}
	}


	void clear()
	{
		delete[] danamicArray;
		m_size = 0;
		danamicArray = new T[capacity];
		//for (int i = 0; i < size; i++) {
		//	delete danamicArray[i];
		//}
	}

	int size()
	{
		return m_size;
	}

	bool empty() {
		return m_size == 0;
	}

	void add(T Ele) {
		/* �����һ����Ԫ�ص�β�� */
		ensureCapacity(m_size + 1);

		/* �����Ԫ�ص��ѵ����һ��λ�� */
		danamicArray[m_size] = Ele;
		m_size++;

		/* ���Ϲ��� */
		int index = m_size - 1; // ������һ��Ԫ�ؽ���
		siftUp(index);
	}



	T get() {
		return danamicArray[0];
	}


	T remove() {

		// �õ��Ѷ������ڷ���
		T deleEle = get();

		/* size��һ��Ϊ�˱������һ��Ԫ�ض�ʧ�����临�Ƶ��Ѷ� */
		danamicArray[0] = danamicArray[--m_size];

        /* ���ڿ�����ɶѶ�С�����ߴ�ĸ�֣����ԶԶѶ��������Ʋ���*/
		int index = 0;
		// ֻ�з�Ҷ�ӽڵ��������
		siftDown(index);

		return deleEle;
	}



	T replace(T Ele) {
		//assert(m_size > 0);
		if (m_size > 0) {
			T e = danamicArray[0];
			danamicArray[0] = Ele;
			siftDown(0);
			return e;
		}
	}



	/* ����С���ѵ�ǰk�����ֵɸѡ */
	void TopK_smallHeap(T* A, int n, int k) {
		for (int i = 0; i < n; i++) {
			if (m_size < k) {
				add(A[i]); // logk
			}
			else if(A[i] > this->get()) { // ���϶���С��������С��Ԫ��
				replace(A[i]);  // logn
			}
		}
	}




	void printArray() {
		if (m_size == 0) {
			std::cout << "Heap is empty!" << std::endl;
			return;
		}

		for (int i = 0; i < m_size; i++) {
			std::cout << danamicArray[i] << "(" << i << ")" << ' ';
		}
		std::cout << std::endl;
	}


	void heapify()
	{
		// ���¶��ϵ�����
        // �����һ����Ҷ�ӽڵ㿪ʼ

		for (int index = (m_size >> 1) - 1; index >= 0; index--)
		{
            siftDown(index);
		}
	}


	private:
		
		void siftDown(int index)
		{

			// ���������ƽڵ����ֵ
			T e = danamicArray[index];
			// ��Ҷ�ӽڵ���������Ʋ���
			int no_leaf_number = (m_size >> 1); // ��Ҷ�ӽڵ����

			while (index < no_leaf_number)
			{

				int left = index << 1 + 1;
				int right = index << 1 + 2;
				T leftValue = danamicArray[left];
				T rightValue = danamicArray[right];
				bool cmpVal = cmp(rightValue, leftValue);

				// �õ�����ӽڵ�λ�ú���ֵ
				int nextIndex = cmpVal ? left : right;
				T maxNextVal = cmpVal ? leftValue : rightValue;

				if (cmp(maxNextVal, e)) break;
				// ����������������ֵ
				danamicArray[index] = danamicArray[nextIndex];
				index = nextIndex;

			}

			danamicArray[index] = e;
		} 



		/// <summary>
		/// ����ĳ�ڵ�����������丸�׽ڵ�����
		/// <param name="index"></param>
		/// <���ظ��ڵ�����></returns>
		int Pindex(int index) {
			if (index == 0) return -1;
			if (index % 2 == 0) return (index - 2) / 2;
			return (index - 1) / 2;
		}


		/// <summary>
		/// ��������Ƿ�Ϸ�
		/// </summary>
		/// <param name="index"></param>
		void CheckIndex(int index)
		{
			if (index < 0 || index >= m_size)
				throw std::exception("index is inviled!");
		}


		/// <summary>
		/// ���˲���
		/// ����ӵĴ�Ԫ�����ϴ���
		/// ���÷ǽ�����ʽ�����ٸ�ֵ����
		/// <param name="index"></param>
		void siftUp(int index) {
			CheckIndex(index);

			T e = danamicArray[index]; // ��������ӵ�Ԫ��ֵ

			while (index > 0)
			{
				int pindex = Pindex(index); // ���㸸�ڵ�����
				T oldE = danamicArray[pindex]; // �õ����ڵ����ֵ

				if (cmp(e, oldE)) break; // �Ƚϸ��ڵ������ӽڵ�Ĵ�С
										 // �������ӵ�Ԫ��ֵ < ���ڵ� ��break
				danamicArray[index] = danamicArray[pindex]; // ����Ѹ��ڵ��ֵ���¸�ֵ
				index = pindex; // ��������Ϊԭ�����ڵ������
			}
			// ���index��λ�þ�������Ԫ���������˺��λ�ã����и�ֵ���ɡ�
			danamicArray[index] = e; 
		}


		/// <summary>
		/// ��̬����
		/// </summary>
		/// <param name="capa"></�ٶ�����>
		void ensureCapacity(int capa)
		{
			int oldCapacity = capa;
			if (oldCapacity <= capacity) return;

			// ����capacity
			capacity = capacity + (capacity >> 1);
			T* newArray = new T[capacity];

			for (int i = 0; i < capa; i++)
			{
				newArray[i] = (T)danamicArray[i];
			}

			delete[] danamicArray;
			danamicArray = newArray;
		}

};