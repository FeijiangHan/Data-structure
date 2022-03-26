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

	// 找到字符串对应的最后一个节点
		Node<T>* node = root;
		for (auto it : str)
		{

			if (node->children.count(it) == 0) { // node->children.find(it) == node->children.end()
				Node<T>* childNode = new Node<T>(it,node); // possible memory leak?
				node->children[it] = childNode;
			}

			node = node->children[it];
		}


		// 已经存在此单词，只修改其value
		// 如果不需要储存val，就直接让color为true即可，不需要讨论
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


	// 根据字符串你找到最后一个字符的节点
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
		// 找到最后一个节点
		Node<T>* deNode = node(word);
		if (deNode == nullptr) {
			throw exception("NOT EXIT THIS WORD!");
		}
		cout << "开始删除" << endl;
		// 不是结尾
		if (deNode == nullptr || deNode->color == false)
		{
			cerr << "未找到字符串" << endl;
			return NULL;
		}
	
		T oldVal = deNode->value;
		// if还有子节点
		if (!deNode->children.empty())
		{
			cout << "有子节点" << endl;
			deNode->color = false;
			deNode->value = NULL;
			return oldVal;
		}

		// 没有子节点
		Node<T>* parent = nullptr;
		while ((parent = deNode->parent) != nullptr)
		{
			cout << "节点"<< deNode->c <<  "开始删除" << endl;
			parent->children.erase(deNode->c);
			if (parent->children.size() > 0 || parent->color) break;
			deNode = parent;
		}

		cout << "删除结束" << endl;
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