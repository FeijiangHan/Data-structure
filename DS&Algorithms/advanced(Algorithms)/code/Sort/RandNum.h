#pragma once
#include<vector>
#include <ctime>
#include<random>
using namespace std;


/* random_device（）目的就是产生生成真随机数，
rand（）函数用的线性同余法生成随机数，但是这个随机数实际上是一个伪随机数。

std::mt19937是伪随机数产生器，用于产生高性能的随机数, C++11引入。'
返回值为unsigned int。std::mt19937接收一个unsigned int数作为种子

rand()随机数范围：0~32767
mt19937随机数范围：无限制，但是可以自己设定
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