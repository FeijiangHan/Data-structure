#pragma once
#include<ctime>
#include<iostream>
#include<string>

class Timer
{
private:
	clock_t startT;
	bool isEnd = false;
	std::string discribe;

public:
	Timer(std::string discribe = "Time") {
		time_t time = 0;
		std::time(&time);

		startT = clock();
		this->discribe = discribe;
		isEnd = false;
		std::cout << "开始时间： " << std::ctime(&time) << std::endl;
	}

	~Timer()
	{
		if (!isEnd) {
			//time_t time = 0;
			//std::time(&time);

			clock_t endT = clock();
			double T = (double)(endT - startT) / CLOCKS_PER_SEC;
			//std::cout << "结束时间： " << std::ctime(&time) << std::endl;
			std::cout << discribe << ": " << T << "s" << std::endl;

		}
	}

	void End() {
		
		//time_t time = 0;
		//std::time(&time);

		clock_t endT = clock();
		double T = (double)(endT - startT) / CLOCKS_PER_SEC;
	// std::cout << "结束时间： " << std::ctime(&time) << std::endl;
		std::cout << discribe << ": " << T << "s" << std::endl;
		isEnd = true;
	}
};