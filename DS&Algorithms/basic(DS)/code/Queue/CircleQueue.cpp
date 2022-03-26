#include<iostream>
#include"CircleQueue_.h"
#include"CircleDeque.h"

void test01()
{

		CircleQueue<int> que;
	//0 1 2 3 4
	for(int i = 1; i< 6; i++)
	  que.enqueue(i);
	std::cout << que.front() << std::endl;
	std::cout << que << std::endl;

	que.dequeue();
	que.dequeue();
	//2 3 4
	std::cout << que.front() << std::endl;
	std::cout << que << std::endl;

	//2 3 4 5 6 7 8 9 10 11 12 13 14
	for(int i =90; i<= 99; i++)
	  que.enqueue(i);

	std::cout << que.front() << std::endl;
	std::cout << que << std::endl;
}



int main()
{
	CircleDeque<int> que;
	//0 1 2 3 4
	for(int i = 1; i< 6; i++)
	  que.enqueue(i);
	std::cout << que << std::endl;

	que.dequeue();
	que.dequeue();
	//2 3 4
	std::cout << que << std::endl;

	//2 3 4 5 6 7 8 9 10 11 12 13 14
	for(int i =90; i<= 99; i++)
	  que.enqueue(i);

	std::cout << que << std::endl;

	que.dequeueRear();
	que.dequeueRear();
	std::cout << que << std::endl;

	que.enqueueFront(88);
	que.enqueueFront(99);
	que.enqueueFront(100);
	que.enqueueFront(200);
	std::cout << que << std::endl;

	que.enqueue(999);
	std::cout << que << std::endl;

	system("pause");
	return 0;
}