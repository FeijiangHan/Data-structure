#include<iostream>
#include<string>

#include"HashMap.h"
using namespace std;


struct Bug
{
	int val;
	int key;
	Bug(int k,int v):key(k),val(v){}
	Bug(){}
};

class Test
{
public:
	int size;
	Bug** table;
	Test() {
		size = 0;
		table = new Bug* [16];
		for (int i = 0; i < 16; i++) {
			table[i] = new Bug(0,0);
		}
	}

	void add(int k,int v)
	{
		if (size == 0) {
			table[0] = new Bug(k,v);
			size++;
			return;
		}
		table[size] = new Bug(k, v);
		size++;
	}

	void test(int k)
	{
		Bug* bug = table[k + 1];
		bug = new Bug(99, 99);

		cout << table[k + 1] << "   " << bug << endl;
		cout << table[k + 1]->val << "   " << bug->val << endl;
		//table[k + 1] = new Bug(99, 99);
	}

	Bug* func(int k)
	{
		return table[k+1];
	}

	void test2()
	{

	}

	void print()
	{
		for (int i = 0; i < size; i++) {
			cout << table[i]->key << "-" << table[i]->val << ' ';
		}
		cout << endl;
	}
};

int main()
{
	//HashMap<string, int>* map = new HashMap<string,int>;
	//map->add("a", 1);
	Test* t = new Test;
	t->add(1, 10);
	t->add(2, 20);
	t->add(3, 30);
	t->add(4, 40);
	t->add(5, 50);
	t->add(6, 60);

	t->test(0);

	//map->add("chase", 19);
	//map->add("chase", 19);
	//map->add("chas", 119);
	//map->add("cha", 18);
	//map->add("a", 19);
	//map->add("cc", 999);
	//map->add("cc", 999);
	//map->add("cc", 999);
	//map->add("bd", 184);
	//map->add("bd", 184);
	//map->add("bd", 184);
	//map->add("bd", 184);


	//cout << map->bucketSize() << ' ' << map->tableSize() << endl;
	//for(int i = 0; i < map->bucket_size; i++)
	//   cout << map->hashtable[0]->key << endl;
	//map->add("chase", 19);
	//cout << map->bucketSize() << ' ' << map->tableSize() << endl;
	//map->traversal();


	system("pause");
	return 0;
}