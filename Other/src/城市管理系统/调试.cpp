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
		cout << "******欢迎来到城市数据管理系统******" << endl;
		cout << "输入需要进行的操作：" << endl
			<< "0. 从文件载入数据（待开发）" << endl
			<< "1. 全部城市数据获取" << endl
			<< "2. 城市数据查询" << endl
			<< "3. 添加城市信息" << endl
			<< "4. 删除城市信息" << endl
			<< "5. 修改城市信息" << endl
			<< "6. 城市间距离查询" << endl
			<< "7. 城市简介查询(待开发)" << endl
			<< "8. 城市景点查询（待开发）" << endl
			<< "9. 重新保存文件信息（带开发）" << endl
			<< "10. 退出系统" << endl;
		// 地图载入功能
		// 地铁公交信息查询
		// 同步数据库

		cin >> choice;

		switch (choice)
		{
		case 0:
			system("cls");
			//针对csv文件和txt文件进行读取，其中csv文件是;分割，txt文件可以是任意符号分割
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
			// 可以选择写入txt文件还是csv文件
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