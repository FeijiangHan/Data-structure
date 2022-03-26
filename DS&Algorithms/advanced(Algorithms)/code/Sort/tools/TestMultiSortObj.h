#pragma once


class Student
{
public:

	int id;
	int score;
	Student(int i, int s) :id(i), score(s) {}
};


int operator-(Student& s1, Student& s2)
{
	return s1.score - s2.score;
}