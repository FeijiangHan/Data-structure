#include <iostream>
#include"CircleLinkedList.h"
using namespace std;

int main()
{
	CircleLinkedList list;
	// 添加元素
	for (int i = 1; i <= 8; i++)
	{
		list.add(i);
	}

	// 使得current指针指向头结点
	list.reset();

	int n;
	cout << "输入间隔距离：" << endl;
	cin >> n;

	while (!list.isEmpty())
	{
		// 向后走n步
		for(int i = 0; i < n-1;i++)
		{
			list.next();
		}
		cout << list.remove() << endl;
	}

	system("pause");
	return 0;
}
