#include<iostream>
#include<vector>
#include<array>
#include"BinarySearchTree.h"
#include"Student.h"
using namespace std;

void test01()
{
		int data[] =  {7, 4, 9, 2, 5, 8, 11, 3, 12, 1};
		int dataLength = sizeof(data) / sizeof(int);

		BinarySearchTree<int>* bst = new BinarySearchTree<int>();
		for (int i = 0; i < dataLength; i++) {
			bst->add(data[i]);
		}

	bst->preorder(); 
	cout << endl;
	bst->inorder();
	cout << endl;
	bst->postorder();
	cout <<endl;
	bst->levelOrder();

    Student sdata[] = {
		Student("a",18,100),
		Student("b",19,67),
		Student("chase",18,96),
		Student("d",17,92),
		Student("e",20,83),
	};
		int sdataLength = sizeof(sdata) / sizeof(sdata[0]);

		BinarySearchTree<Student>* sbst = new BinarySearchTree<Student>();
		for (int i = 0; i < sdataLength; i++) {
			sbst->add(sdata[i]);
		}
    cout << endl;
	sbst->preorder(); 
	cout << endl;
	sbst->inorder();
	cout << endl;
	sbst->postorder();
	cout <<endl;
	sbst->levelOrder();


	  Man mdata[] = {
		Man("a",89,1000),
		Man("b",29,2500),
		Man("c",45,3500),
		Man("d",17,900),
		Man("e",20,600),
	};
		int mdataLength = sizeof(mdata) / sizeof(mdata[0]);  // c++ 和 Java差异：c++没有直接获取数组长度的方法！

		BinarySearchTree<Man>* mbst = new BinarySearchTree<Man>();
		for (int i = 0; i < mdataLength; i++) {
			mbst->add(mdata[i]);
		}
    cout << endl;
	mbst->preorder(); 
	cout << endl;
	mbst->inorder();
	cout << endl;
	mbst->postorder();
	cout <<endl;
	mbst->levelOrder();
}


void test02()
{
		int data[] =  {6,3,8,1,5,7,9,0,2,4};
		int dataLength = sizeof(data) / sizeof(int);


		BinarySearchTree<int> bst1;
		BinarySearchTree<int>* bst = new BinarySearchTree<int>();
		for (int i = 0; i < dataLength; i++) {
			bst->add(data[i]);
		}
		bst->Print_Recurrence();
		cout <<"\n\n\n\n";
		bst->PrintNodeByLevel();
		cout <<"\n";
		cout << bst->hight() << endl;
		cout << bst->IsCompeteBinary();
}


int main()
{
    test02();
	return 0;
}