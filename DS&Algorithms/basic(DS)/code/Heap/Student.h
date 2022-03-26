#pragma once
#include<string>

class Student
{
public:
	std::string name;
	int id;
	int scores;
	Student() {}
	Student(std::string n, int id, int s) : name(n), id(id), scores(s) {}

};