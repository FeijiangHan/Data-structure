#include<iostream>
#include<cassert>
#include"BiCircleLinkedList.h"
#include"CircleLinkedList.h"
using namespace std;


int main()
{
	//BiCircleLinkedList<int> list;
	//list.add(1);
	//list.add(3);
	//list.add(6);
	//list.add(11);
	//list.add(14);
	//list.add(18);
	//list.add(20);
	//list.add(32);
	//list.Print();
	//list.Insertion(13);
	//list.Insertion(0);
	//list.Insertion(-1);
	//list.Insertion(29);
	//list.Print();

	CircleLinkedList list;
	list.add(1);
	list.add(11);
	list.add(12);
	list.add(14);
	list.add(17);
	list.add(19);
	list.add(21);
	list.reset();
	while (list.m_size != 0) {
		list.next();
		list.next();
		cout << list.remove_current() << endl;
	}
	system("pause");
	return 0;
}