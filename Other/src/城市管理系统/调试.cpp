#include<iostream>
#include"CityManager.h"
#include"BiCircleLinkedList.h"
using namespace std;



void menu()
{
	CityManager citymanager;
	int choice = 9;
	while (true)
	{
		cout << "******��ӭ�����������ݹ���ϵͳ******" << endl;
		cout << "������Ҫ���еĲ�����" << endl
			<< "0. ���ļ��������ݣ���������" << endl
			<< "1. ȫ���������ݻ�ȡ" << endl
			<< "2. �������ݲ�ѯ" << endl
			<< "3. ��ӳ�����Ϣ" << endl
			<< "4. ɾ��������Ϣ" << endl
			<< "5. �޸ĳ�����Ϣ" << endl
			<< "6. ���м�����ѯ" << endl
			<< "7. ���м���ѯ(������)" << endl
			<< "8. ���о����ѯ����������" << endl
			<< "9. ���±����ļ���Ϣ����������" << endl
			<< "10. �˳�ϵͳ" << endl;
		// ��ͼ���빦��
		// ����������Ϣ��ѯ
		// ͬ�����ݿ�

		cin >> choice;

		switch (choice)
		{
		case 0:
			system("cls");
			//���csv�ļ���txt�ļ����ж�ȡ������csv�ļ���;�ָtxt�ļ�������������ŷָ�
			break;
		case 1:
			system("cls");
			citymanager.Print();
			break;
		case 2:
			system("cls");
			citymanager.Search();
			break;
		case 3:
			system("cls");
			citymanager.addCityMessages();
			break;
		case 4:
			system("cls");
			citymanager.Remove();
			break;
		case 5:
			system("cls");
			citymanager.UpdateBaseMessage();
			break;
		case 6:
			system("cls");
			citymanager.CacuDist();
			break;
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		case 10:
			system("cls");
			// ����ѡ��д��txt�ļ�����csv�ļ�
			return;
		default:
			break;
		}
	}
}



int main()
{
	menu();
	system("pause");
	return 0;
}