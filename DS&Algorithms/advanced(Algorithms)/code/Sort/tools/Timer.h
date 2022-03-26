#pragma once
#include<ctime>
#include<iostream>
#include<string>

class Timer
{
private:
	clock_t startT;
	bool isEnd = false;

public:
	double costTime;
	std::string discribe;

	Timer(std::string discribe = "Time") {
		time_t time = 0;
		std::time(&time);

		startT = clock();
		this->discribe = discribe;
		isEnd = false;
		//std::cout << "开始时间： " << std::ctime(&time) ;
	}


	~Timer()
	{
		if (!isEnd) {
			clock_t endT = clock();
			costTime = (double)(endT - startT);
			//std::cout << "结束时间： " << std::ctime(&time) << std::endl;
			//std::cout << discribe << "  :" << costTime/CLOCKS_PER_SEC << "s(" << costTime << "ms)" << std::endl;

		}
	}


	void End() {
		clock_t endT = clock();
		costTime = (double)(endT - startT);
		// std::cout << "结束时间： " << std::ctime(&time) << std::endl;
		//std::cout << discribe << ": " << costTime / CLOCKS_PER_SEC << "s(" << costTime << "ms)" << std::endl;
		isEnd = true;
	}
};