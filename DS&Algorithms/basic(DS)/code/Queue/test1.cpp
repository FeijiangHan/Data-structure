#include"queue.h"
#include<iostream>
using namespace std;



int main()
{
	Queue<int> queue;
	for(int i = 0;i<5; i++) {
		queue.enqueue(i);
	}
  cout << queue << endl;
 cout <<"size: " << queue.size() << endl;

  queue.dequeue();
  queue.dequeue();
  queue.dequeue();
  queue.dequeue();
  queue.dequeue();
 // queue.dequeue();
  cout <<"size: " << queue.size() << endl;
//  queue.dequeue();

  queue.enqueue(100);
  queue.enqueue(200);

  cout << queue << endl;

  cout << "front: " << queue.front() << "  back: " << queue.back() << endl; 

	getchar();
	return 0;
}