#include <iostream>
#include"CircleLinkedList.h"
using namespace std;

int main()
{
	CircleLinkedList list;
	// ���Ԫ��
	for (int i = 1; i <= 8; i++)
	{
		list.add(i);
	}

	// ʹ��currentָ��ָ��ͷ���
	list.reset();

	int n;
	cout << "���������룺" << endl;
	cin >> n;

	while (!list.isEmpty())
	{
		// �����n��
		for(int i = 0; i < n-1;i++)
		{
			list.next();
		}
		cout << list.remove() << endl;
	}

	system("pause");
	return 0;
}
