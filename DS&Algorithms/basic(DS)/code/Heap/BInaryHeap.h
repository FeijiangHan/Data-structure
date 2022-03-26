#pragma once
#include<cmath>
#include<iostream>
#include<vector>
#include"Heap.h"
#include"Compare.h"
#include<cassert>

/*  堆：在不排序的基础上得到最值，原理是通过添加时的上溢操作*/
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
		/* 先添加一个新元素到尾部 */
		ensureCapacity(m_size + 1);

		/* 添加新元素到堆的最后一个位置 */
		danamicArray[m_size] = Ele;
		m_size++;

		/* 向上过滤 */
		int index = m_size - 1; // 针对最后一个元素进行
		siftUp(index);
	}



	T get() {
		return danamicArray[0];
	}


	T remove() {

		// 得到堆顶，用于返回
		T deleEle = get();

		/* size减一，为了避免最后一个元素丢失，把其复制到堆顶 */
		danamicArray[0] = danamicArray[--m_size];

        /* 现在可能造成堆顶小、两边大的格局，所以对堆顶进行下移操作*/
		int index = 0;
		// 只有非叶子节点才能下溢
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



	/* 基于小顶堆的前k个最大值筛选 */
	void TopK_smallHeap(T* A, int n, int k) {
		for (int i = 0; i < n; i++) {
			if (m_size < k) {
				add(A[i]); // logk
			}
			else if(A[i] > this->get()) { // 不断丢掉小顶堆中最小的元素
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
		// 自下而上的下滤
        // 从最后一个非叶子节点开始

		for (int index = (m_size >> 1) - 1; index >= 0; index--)
		{
            siftDown(index);
		}
	}


	private:
		
		void siftDown(int index)
		{

			// 保留待下移节点的数值
			T e = danamicArray[index];
			// 有叶子节点则进行下移操作
			int no_leaf_number = (m_size >> 1); // 非叶子节点个数

			while (index < no_leaf_number)
			{

				int left = index << 1 + 1;
				int right = index << 1 + 2;
				T leftValue = danamicArray[left];
				T rightValue = danamicArray[right];
				bool cmpVal = cmp(rightValue, leftValue);

				// 得到最大子节点位置和数值
				int nextIndex = cmpVal ? left : right;
				T maxNextVal = cmpVal ? leftValue : rightValue;

				if (cmp(maxNextVal, e)) break;
				// 更新索引，覆盖数值
				danamicArray[index] = danamicArray[nextIndex];
				index = nextIndex;

			}

			danamicArray[index] = e;
		} 



		/// <summary>
		/// 根据某节点的索引计算其父亲节点索引
		/// <param name="index"></param>
		/// <返回父节点索引></returns>
		int Pindex(int index) {
			if (index == 0) return -1;
			if (index % 2 == 0) return (index - 2) / 2;
			return (index - 1) / 2;
		}


		/// <summary>
		/// 检测索引是否合法
		/// </summary>
		/// <param name="index"></param>
		void CheckIndex(int index)
		{
			if (index < 0 || index >= m_size)
				throw std::exception("index is inviled!");
		}


		/// <summary>
		/// 上滤操作
		/// 将添加的大元素向上传递
		/// 采用非交换形式，减少赋值次数
		/// <param name="index"></param>
		void siftUp(int index) {
			CheckIndex(index);

			T e = danamicArray[index]; // 保留新添加的元素值

			while (index > 0)
			{
				int pindex = Pindex(index); // 计算父节点索引
				T oldE = danamicArray[pindex]; // 得到父节点的数值

				if (cmp(e, oldE)) break; // 比较父节点和新添加节点的大小
										 // 如果新添加的元素值 < 父节点 ，break
				danamicArray[index] = danamicArray[pindex]; // 否则把父节点的值向下赋值
				index = pindex; // 更新索引为原来父节点的索引
			}
			// 最后index的位置就是新添元素最终上滤后的位置，进行赋值即可。
			danamicArray[index] = e; 
		}


		/// <summary>
		/// 动态扩容
		/// </summary>
		/// <param name="capa"></假定容量>
		void ensureCapacity(int capa)
		{
			int oldCapacity = capa;
			if (oldCapacity <= capacity) return;

			// 更新capacity
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