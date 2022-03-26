#pragma once

/*
操作函数-仿函数
- 添加不同数据类型的操作
- 模式选择  mode0默认输出操作
- 自由改变遍历停止节点
*/
class Operate
{
private:
	int mode;

public:
	bool state;
	Operate() { state = false; }

	//template<class K>
	//bool operator()(K key)
	//{
	//		std::cout << key << ' ';
	//		return (key == 99) ? true : false;
	//}

	/*设置遍历模式*/
	void setMode(int myMode = 0)
	{
		mode = myMode;
	}

	template<class K,class V>
	bool operator()(K key, V value)
	{
		if (mode == 0) {
			std::cout << key << '_' << value << ' ';

			return (key == 99) ? true : false;
		}
		else if (mode == 1)
		{
			std::cout << key << ' ';

			return (key == 99) ? true : false;
		}
		else return false;
	}
};