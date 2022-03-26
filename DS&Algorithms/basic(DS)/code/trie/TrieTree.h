#pragma once
#include<unordered_map>
#include<string>
#include<iostream>
#include<cassert>
using namespace std;


template<class T>
struct Node
{
	unordered_map<char, Node*> children;
	T value;
	char c;
	bool color;
	Node* parent;

	Node() {}
	Node(char c ,Node* p) {
		this->c = c;
		this->children = {};
		this->parent = p;
		this->color = false;
	}
};

template<class T>
class Trie : private Node<T>
{
private:
	Node<T>* root;
	int m_size;
	
public:

	int size()
	{
		return m_size;
	}


	bool empty()
	{
		return m_size == 0;
	}



	void StrCheck(string str) {
		assert(!str.empty());

		if (str.empty())
		{
			throw exception("str is empty!");
		}
	}


	T get(string str)
	{
		Node<T>* getNode = node(str);
		return getNode != nullptr && getNode->color ? getNode->value : NULL;
	}


	T add(string str,T val)
	{
		StrCheck(str);

		if (root == nullptr)
		{
			root = new Node<T>;
		}

	// �ҵ��ַ�����Ӧ�����һ���ڵ�
		Node<T>* node = root;
		for (auto it : str)
		{

			if (node->children.count(it) == 0) { // node->children.find(it) == node->children.end()
				Node<T>* childNode = new Node<T>(it,node); // possible memory leak?
				node->children[it] = childNode;
			}

			node = node->children[it];
		}


		// �Ѿ����ڴ˵��ʣ�ֻ�޸���value
		// �������Ҫ����val����ֱ����colorΪtrue���ɣ�����Ҫ����
		if (node->color) {
			T oldVal = node->value;
			node->value = val;
			return oldVal;
		}

		node->color = true;
		node->value = val;
		m_size++;
		return NULL;
	}


	// �����ַ������ҵ����һ���ַ��Ľڵ�
	Node<T>* node(string str)
	{
		StrCheck(str);

		int len = str.size();
		Node<T>* node = root;
		for (auto it : str) {
			if (node == nullptr || node->children.count(it) == 0) return nullptr;
			node = node->children[it];
		}
		return node;
	}



	T remove(string word)
	{
		// �ҵ����һ���ڵ�
		Node<T>* deNode = node(word);
		if (deNode == nullptr) {
			throw exception("NOT EXIT THIS WORD!");
		}
		cout << "��ʼɾ��" << endl;
		// ���ǽ�β
		if (deNode == nullptr || deNode->color == false)
		{
			cerr << "δ�ҵ��ַ���" << endl;
			return NULL;
		}
	
		T oldVal = deNode->value;
		// if�����ӽڵ�
		if (!deNode->children.empty())
		{
			cout << "���ӽڵ�" << endl;
			deNode->color = false;
			deNode->value = NULL;
			return oldVal;
		}

		// û���ӽڵ�
		Node<T>* parent = nullptr;
		while ((parent = deNode->parent) != nullptr)
		{
			cout << "�ڵ�"<< deNode->c <<  "��ʼɾ��" << endl;
			parent->children.erase(deNode->c);
			if (parent->children.size() > 0 || parent->color) break;
			deNode = parent;
		}

		cout << "ɾ������" << endl;
		this->m_size--;
		return oldVal;
	}

	void traversal()
	{


	}


	bool contains(string str)
	{
		Node<T>* endNode = node(str);
		return ((endNode != nullptr) && (endNode->color));
	}


	bool findPrefix(string prefix)
	{
		return node(prefix) != nullptr;
	}

};