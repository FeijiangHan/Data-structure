#pragma once
#include"City.h"
#include"BiCircleLinkedList.h"
#include<map>
using namespace std;

class CityManager
{
private:
	BiCircleLinkedList* cityList;
public:
	CityManager();


	void addCityMessages();


	void Print();


	void Remove();


	void Search();


	void UpdateBaseMessage();

	double CacuDist();


private:

	Node* FindCity(string name);


	void removeMessage(int index);



	void removeAll(int index);


	void removePopulation(int index);


	void removeGDP(int index);



	void removeLocation(int index);


	void addOtherMessages(map<int, long>& popu, map<int, double>& gdp);


	map<int, long> addCityPopulation();


	map<int, double> addCityGDP();

};



CityManager::CityManager()
{
	cityList = new BiCircleLinkedList;
}


void CityManager::addCityMessages()
{
	cout << "输入城市名称：" << endl;
	string cityName;
	cin >> cityName;

	cout << "输入城市位置信息 [经度、纬度、方位（northern\\southern）]" << endl;
	float y, x;
	string cityOrientation;
	cin >> y >> x >> cityOrientation;

	map<int, long> cityPopulation;
	map<int, double> cityGDP;
	addOtherMessages(cityPopulation, cityGDP);

	cityList->add(City(cityName, y, x, cityOrientation, cityPopulation, cityGDP));
}

void CityManager::Print()
{
	if (cityList->size() == 0)
	{
		cout << "城市信息为空，请载入信息或手动输入！" << endl;
		return;
	}
	cityList->Print();
}


void CityManager::Remove()
{
	cout << "输入要删除的城市名称： " << endl;
	std::string name;
	cin >> name;
	int deleIndex = cityList->IndexOf(name);
	removeMessage(deleIndex);
}



void CityManager::Search()
{
	cout << "输入待查询城市名： " << endl;
	string name;
	cin >> name;
	Node* city = FindCity(name);
	if (city != nullptr)
	{
		cout << "城市信息已找到，是否输出？[Y/N]" << endl;
		char choice;
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
		{
			cityList->Print_Node(city);
		}
		else
		{
			cout << "城市信息未找到，请添加或重新查询！" << endl;
			return;
		}
	}
}


void CityManager::UpdateBaseMessage()
{
	cout << "输入待查询城市名： " << endl;
	string name;
	cin >> name;
	Node* city = FindCity(name);
	cout << "输入此城市新的位置信息 [经度、纬度、方位（northern\\southern）]" << endl;
	float y, x;
	string cityOrientation;
	cin >> y >> x >> cityOrientation;
	city->element.setLocation(Location(y, x, cityOrientation));
}


double CityManager::CacuDist()
{
	cout << "输入城市1名称：" << endl;
	string name1;
	cin >> name1;

	cout << "输入城市2名称：" << endl;
	string name2;
	cin >> name2;

	Node* city1 = FindCity(name1);
	Node* city2 = FindCity(name2);


	const double earth_radius = 6371.0;//km 地球半径 平均值，千米
	const double pi = 3.1415926535897;//圆周率

	double rlat1, rlat2;
	double rlon1, rlon2;

	//角度转弧度
	rlat1 = city1->element.getLocation().getLatitude() * pi / 180;
	rlat2 = city2->element.getLocation().getLatitude() * pi / 180;
	rlon1 = city1->element.getLocation().getLongitude() * pi / 180;
	rlon2 = city2->element.getLocation().getLongitude() * pi / 180;

	//Haversine公式
	double h = pow(sin(abs(rlat1 - rlat2) / 2), 2) + cos(rlat1) * cos(rlat2) * pow(sin(abs(rlon1 - rlon2) / 2), 2);
	double distance = 2 * earth_radius * asin(sqrt(h));//atan2(sqrt(h),sqrt(1-h))

	cout << "两座城市之间的距离为： " << distance << endl;
	return distance;

}



	Node* CityManager::FindCity(string name)
	{
		Node* cityNode = cityList->node(cityList->IndexOf(name));
		return cityNode;
	}


	void CityManager::removeMessage(int index)
	{
		int choice = 0;
		while (true) {

			cout << "您还可以选择删除城市的数据： " << endl
				<< " 1. 删除所有城市信息 " << endl
				<< " 2. 删除城市人口数" << endl
				<< " 3. 删除城市GDP数据" << endl
				<< " 4. 删除城市位置信息 " << endl
				<< " 5. 退出删除操作 " << endl;

			cin >> choice;
			switch (choice)
			{
			case 1:
				system("cls");
				removeAll(index);
				break;
			case 2:
				system("cls");
				removePopulation(index);
				break;
			case 3:
				system("cls");
				removeGDP(index);
				break;
			case 4:
				system("cls");
				removeLocation(index);
				break;
			case 5:
				system("cls");
				return;
			default:
				system("cls");
				break;

			}
		}
	}



	void CityManager::removeAll(int index)
	{
		cityList->remove(index);
	}



	void CityManager::removePopulation(int index)
	{
		Node* deleCity = cityList->node(index);
		cout << " 输入需要删除几条人口信息 ？" << endl;
		int n;
		cin >> n;

		int year;
		if (n >= deleCity->element.getPopulation().size())
		{
			deleCity->element.setPopulation({});
		}
		else
		{
			map<int, long> population = deleCity->element.getPopulation();

			for (int i = 0; i < n; i++)
			{
				cout << "输入待删除的年份： " << endl;
				cin >> year;
				map<int, long>::iterator it = population.find(year);
				if (it == population.end())
				{
					cout << "输入年份不存在，删除失败！" << endl;
					return;
				}
				population.erase(it);
				deleCity->element.setPopulation(population);
			}
		}
	}


	void CityManager::removeGDP(int index)
	{
		Node* deleCity = cityList->node(index);
		cout << " 输入需要删除几条GDP信息 ？" << endl;
		int n;
		cin >> n;

		int year;
		if (n >= deleCity->element.getGDP().size())
		{
			deleCity->element.setGDP({});
		}
		else
		{
			map<int, double> gdp = deleCity->element.getGDP();
			for (int i = 0; i < n; i++)
			{
				cout << "输入待删除的年份： " << endl;
				cin >> year;
				map<int, double>::iterator it = gdp.find(year);
				if (it == deleCity->element.getGDP().end())
				{
					cout << "输入年份不存在，删除失败！" << endl;
					return;
				}
				gdp.erase(it);
				deleCity->element.setGDP(gdp);
			}
		}
	}



	void CityManager::removeLocation(int index)
	{
		Node* deleCity = cityList->node(index);
		deleCity->element.setLocation(Location());
	}


	void CityManager::addOtherMessages(map<int, long>& popu, map<int, double>& gdp)
	{
		int choice = 0;
		while (true) {

			cout << "您还可以选择添加城市人口和城市GDP，请先选择： " << endl
				<< " 1. 补充城市人口信息 " << endl
				<< " 2. 补充城市GDP信息" << endl
				<< " 3. 停止添加信息" << endl;

			cin.get();
			cin >> choice;

			switch (choice)
			{
			case 1:
				system("cls");
				popu = this->addCityPopulation();
				break;
			case 2:
				system("cls");
				gdp = this->addCityGDP();
				break;
			case 3:
				system("cls");
				return;
			default:
				system("cls");
				break;
			}
		}
	}


	map<int, long> CityManager::addCityPopulation()
	{
		cout << "请输入需要添加几个年份的数据： " << endl;
		int n;
		cin >> n;

		int year;
		long cityPopulation;
		map<int, long> popu;
		for (int i = 0; i < n; i++)
		{
			cout << "输入年份:" << endl;
			cin >> year;

			cout << "输入城市人口： " << endl;
			cin >> cityPopulation;

			popu.emplace(year, cityPopulation);
		}
		return popu;
	}



	map<int, double> CityManager::addCityGDP()
	{
		cout << "请输入需要添加几个年份的数据： " << endl;
		int n;
		cin >> n;

		int year;
		double cityGDP;
		map<int, double> gdp;
		for (int i = 0; i < n; i++)
		{
			cout << "输入年份:" << endl;
			cin >> year;

			cout << "输入此年度GDP总值： " << endl;
			cin >> cityGDP;

			gdp.emplace(year, cityGDP);
		}
		return gdp;
	}
