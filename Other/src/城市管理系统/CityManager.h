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
	cout << "����������ƣ�" << endl;
	string cityName;
	cin >> cityName;

	cout << "�������λ����Ϣ [���ȡ�γ�ȡ���λ��northern\\southern��]" << endl;
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
		cout << "������ϢΪ�գ���������Ϣ���ֶ����룡" << endl;
		return;
	}
	cityList->Print();
}


void CityManager::Remove()
{
	cout << "����Ҫɾ���ĳ������ƣ� " << endl;
	std::string name;
	cin >> name;
	int deleIndex = cityList->IndexOf(name);
	removeMessage(deleIndex);
}



void CityManager::Search()
{
	cout << "�������ѯ�������� " << endl;
	string name;
	cin >> name;
	Node* city = FindCity(name);
	if (city != nullptr)
	{
		cout << "������Ϣ���ҵ����Ƿ������[Y/N]" << endl;
		char choice;
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
		{
			cityList->Print_Node(city);
		}
		else
		{
			cout << "������Ϣδ�ҵ�������ӻ����²�ѯ��" << endl;
			return;
		}
	}
}


void CityManager::UpdateBaseMessage()
{
	cout << "�������ѯ�������� " << endl;
	string name;
	cin >> name;
	Node* city = FindCity(name);
	cout << "����˳����µ�λ����Ϣ [���ȡ�γ�ȡ���λ��northern\\southern��]" << endl;
	float y, x;
	string cityOrientation;
	cin >> y >> x >> cityOrientation;
	city->element.setLocation(Location(y, x, cityOrientation));
}


double CityManager::CacuDist()
{
	cout << "�������1���ƣ�" << endl;
	string name1;
	cin >> name1;

	cout << "�������2���ƣ�" << endl;
	string name2;
	cin >> name2;

	Node* city1 = FindCity(name1);
	Node* city2 = FindCity(name2);


	const double earth_radius = 6371.0;//km ����뾶 ƽ��ֵ��ǧ��
	const double pi = 3.1415926535897;//Բ����

	double rlat1, rlat2;
	double rlon1, rlon2;

	//�Ƕ�ת����
	rlat1 = city1->element.getLocation().getLatitude() * pi / 180;
	rlat2 = city2->element.getLocation().getLatitude() * pi / 180;
	rlon1 = city1->element.getLocation().getLongitude() * pi / 180;
	rlon2 = city2->element.getLocation().getLongitude() * pi / 180;

	//Haversine��ʽ
	double h = pow(sin(abs(rlat1 - rlat2) / 2), 2) + cos(rlat1) * cos(rlat2) * pow(sin(abs(rlon1 - rlon2) / 2), 2);
	double distance = 2 * earth_radius * asin(sqrt(h));//atan2(sqrt(h),sqrt(1-h))

	cout << "��������֮��ľ���Ϊ�� " << distance << endl;
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

			cout << "��������ѡ��ɾ�����е����ݣ� " << endl
				<< " 1. ɾ�����г�����Ϣ " << endl
				<< " 2. ɾ�������˿���" << endl
				<< " 3. ɾ������GDP����" << endl
				<< " 4. ɾ������λ����Ϣ " << endl
				<< " 5. �˳�ɾ������ " << endl;

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
		cout << " ������Ҫɾ�������˿���Ϣ ��" << endl;
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
				cout << "�����ɾ������ݣ� " << endl;
				cin >> year;
				map<int, long>::iterator it = population.find(year);
				if (it == population.end())
				{
					cout << "������ݲ����ڣ�ɾ��ʧ�ܣ�" << endl;
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
		cout << " ������Ҫɾ������GDP��Ϣ ��" << endl;
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
				cout << "�����ɾ������ݣ� " << endl;
				cin >> year;
				map<int, double>::iterator it = gdp.find(year);
				if (it == deleCity->element.getGDP().end())
				{
					cout << "������ݲ����ڣ�ɾ��ʧ�ܣ�" << endl;
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

			cout << "��������ѡ����ӳ����˿ںͳ���GDP������ѡ�� " << endl
				<< " 1. ��������˿���Ϣ " << endl
				<< " 2. �������GDP��Ϣ" << endl
				<< " 3. ֹͣ�����Ϣ" << endl;

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
		cout << "��������Ҫ��Ӽ�����ݵ����ݣ� " << endl;
		int n;
		cin >> n;

		int year;
		long cityPopulation;
		map<int, long> popu;
		for (int i = 0; i < n; i++)
		{
			cout << "�������:" << endl;
			cin >> year;

			cout << "��������˿ڣ� " << endl;
			cin >> cityPopulation;

			popu.emplace(year, cityPopulation);
		}
		return popu;
	}



	map<int, double> CityManager::addCityGDP()
	{
		cout << "��������Ҫ��Ӽ�����ݵ����ݣ� " << endl;
		int n;
		cin >> n;

		int year;
		double cityGDP;
		map<int, double> gdp;
		for (int i = 0; i < n; i++)
		{
			cout << "�������:" << endl;
			cin >> year;

			cout << "��������GDP��ֵ�� " << endl;
			cin >> cityGDP;

			gdp.emplace(year, cityGDP);
		}
		return gdp;
	}
