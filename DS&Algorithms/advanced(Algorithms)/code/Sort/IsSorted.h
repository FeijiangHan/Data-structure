#pragma once
#include<vector>
template<class T>
class IsSorted
{
public:
	bool operator()(std::vector<T>& arr)
	{
		bool sorted = true;
		for (int i = 1; i <= arr.size() - 1; i++)
		{
			if (arr[i] < arr[i - 1])
			{
				sorted = false;
			}
		}
		return sorted;
	}
};