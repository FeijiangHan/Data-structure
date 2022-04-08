#pragma once
#include<string>
#include<map>
#define YEAR 5



class Location
{
protected:
	float longitude;
	float latitude;
	std::string orientation;
public:
	Location() {}
	Location(float lon, float lat, std::string orient)
	{
		longitude = lon; // 经度
		latitude = lat; // 纬度
		orientation = orient;
	}

	float getLongitude()
	{
		return longitude;
	}

	float getLatitude()
	{
		return latitude;
	}

	std::string getOrient()
	{
		return orientation;
	}

	void setLongitude(float lon)
	{
		longitude = lon;
	}

	void setLatitude(float lati)
	{
		latitude = lati;
	}

	void setOrient(std::string ori)
	{
		orientation = ori;
	}

	bool operator ==(Location& loc)
	{
		return this->latitude == loc.latitude && this->longitude == loc.longitude && this->orientation == loc.orientation;
	}

	void clear()
	{
		longitude = 0;
		latitude = 0;
		orientation = "null";
	}
};



class City
{
public:
	City() {};
	City(std::string n, Location l, std::map<int, long> pop = {}, std::map<int, double> gdp = {})
	{
		this->name = n;
		this->loca = l;
		population = pop;
		this->gdp = gdp;
	}
	City(std::string n, float lon, float lat, std::string orient, std::map<int, long> pop = {}, std::map<int, double> gdp = {})
	{
		this->name = n;
		this->loca = Location(lon, lat, orient);
		population = pop;
		this->gdp = gdp;
	}


	bool operator ==(City& city)
	{
		return this->name == city.name && this->loca == city.loca && this->population == this->population && this->gdp == city.gdp;
	}

	std::string getName()
	{
		return name;
	}

	Location& getLocation()
	{
		return loca;
	}


	std::map<int, long> getPopulation()
	{
		return population;
	}

	std::map<int, double> getGDP()
	{
		return gdp;
	}


	void setName(std::string n)
	{
		name = n;
	}

	void setPopulation(std::map<int, long> popu)
	{
		population = popu;
	}

	void setGDP(std::map<int, double> gd)
	{
		gdp = gd;
	}

	void setLocation(Location loc)
	{
		loca = loc;
	}
private:

	// 城市名字
	std::string name;
	// 位置信息（经度纬度、大体方位）
	Location loca;
	// 历年人口
	std::map<int, long> population;
	// 历年gdp
	std::map<int, double> gdp;
};
