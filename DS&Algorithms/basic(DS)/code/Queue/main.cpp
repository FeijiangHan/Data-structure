#include<iostream>
//#include"Bidriclinkedlist.h"
#include"CircleLinkedList.h"
using namespace std;


ostream& operator<<(ostream& cout, CircleLinkedList & list)
{
	Node* p = list.first;

	for (int i = 0; i<list.m_size; i++)
	{

		/***the previous one***/
		cout << p->prev->element <<'-';

		/***Itself ***/
		cout << p->element << '-';

		/***the next one***/
		p = p->next;
		cout << p->element <<' ';

	}

	return cout;
}




int main()
{
  CircleLinkedList list;

  list.add(0,10);
  list.add(1,20);
  list.add(2,30);
  list.add(11);
  list.add(22);
  list.add(33);

  list.remove_element(30);

  cout << list <<endl;

  list.reset();

  while(list.m_size != 0){
  list.next();
  list.next();

  cout << list.remove_current() << endl;
  }



  //cout << list << endl;
  //list.remove(list.first);
  //cout << list << endl;
  //list.remove(list.last);
  //cout << list << endl;
  //list.remove(0);
  //cout << list << endl;


  getchar();
  return 0;
}