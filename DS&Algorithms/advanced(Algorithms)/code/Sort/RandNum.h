#pragma once
#include<vector>
#include <ctime>
#include<random>
using namespace std;


/* random_device����Ŀ�ľ��ǲ����������������
rand���������õ�����ͬ�෨�����������������������ʵ������һ��α�������

std::mt19937��α����������������ڲ��������ܵ������, C++11���롣'
����ֵΪunsigned int��std::mt19937����һ��unsigned int����Ϊ����

rand()�������Χ��0~32767
mt19937�������Χ�������ƣ����ǿ����Լ��趨
*/
template<typename T>
vector<T> randomNum(T range_from, T range_to,int n) {
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<T>    distr(range_from, range_to);
    
    vector<T> vec;
    for (int i = 0; i < n; i++)
    {
        vec.push_back(distr(generator));
    }
    return vec;
}