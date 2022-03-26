#pragma once
#include<string>

class Student
{
public:
	int year;
	int scores;
	std::string name;
	Student(){}
	Student(std::string name,int a,int b):name(name),year(a),scores(b){}
};


class Man
{
public:
	int year;
	int money;
	std::string name;
	Man(){}
	Man(std::string name,int a,int b):name(name),year(a),money(b){}
};