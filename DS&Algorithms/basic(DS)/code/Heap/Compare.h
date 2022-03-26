#pragma once

class Compare
{
public:

	template<class T>
	bool operator()(T a, T b)
	{
		return (a < b) ? true : false;
	}
};