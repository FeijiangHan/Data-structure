#pragma once

/*
��������-�º���
- ��Ӳ�ͬ�������͵Ĳ���
- ģʽѡ��  mode0Ĭ���������
- ���ɸı����ֹͣ�ڵ�
*/
class Operate
{
public:
	Operate() { state = false; }

	//�����������Ͳ���
	template<class T>
	bool operator()(T Ele, int mode = 0)
	{
		
		if (mode == 0) {
			std::cout << typeid(Ele).name() << '_' << Ele << ' ';

			return (Ele == 999) ? true : false;
		}
		return false;
	}

	//�����������ʹ���

	bool state;
};