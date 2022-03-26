#pragma once
#include<iostream>
using namespace std;


class MyExpection
{
public:
	const char*what();
};

const char* MyExpection::what()
	{
		return "This Step Is Wrong!";
	}


class Assert
{
public:
	static void test(bool val);
};


void Assert::test(bool val)
	{
		try
		{
			if(!val) throw MyExpection();
		}
		catch(MyExpection& e)
		{
			cout << e.what() << endl;
		}
	}