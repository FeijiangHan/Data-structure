#pragma once

/*
��������-�º���
- ��Ӳ�ͬ�������͵Ĳ���
- ģʽѡ��  mode0Ĭ���������
- ���ɸı����ֹͣ�ڵ�
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

	/*���ñ���ģʽ*/
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