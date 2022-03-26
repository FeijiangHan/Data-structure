#pragma once

#include<string>
#include<queue>
#include"Operate.h"
#include"Compare.h"


#define RED false
#define BLACK true


/*
基于RBTree的Map：
1.建一个独特的节点，包含键值两个元素
2.添加时以key为比较因素，要求key是可比较的
3.每次更新节点都要同时更新key和value，new节点也要传入两个值
4.node查找也只基于key的比较
*/

template<class K, class V>
class Node {
public:

	K key;
	V value;
	Node* left;
	Node* right;
	Node* parent;

	bool color = RED;  // RBTree 特有属性

	Node() { }

	Node(K key,V value,Node* parent)
	{
		this->key = key;
		this->value = value;
		this->parent = parent;
		left = NULL;
		right = NULL;
	}

	bool Have2Children()
	{
		return (this->left != NULL && this->right != NULL);
	}

	bool IsLeaf()
	{
		return (this->left == NULL && this->right == NULL);
	}

	// 判断左右
	bool IsLeft()
	{
		return (parent != NULL && this == parent->left);
	}

	bool IsRight()
	{
		return (parent != NULL && this == parent->right);
	}


	// 判断兄弟姐妹节点存在
	 // RBTree 特有属性
	bool IsSibling(Node* node)
	{
		if (node == NULL) {
			return false;
		}
		if (node->IsLeft() && node->parent->Have2Children()) return true;
		if (node->IsRight() && node->parent->Have2Children()) return true;

		return false;
	}

	// 得到兄弟姐妹节点
	 // RBTree 特有属性

	Node* Sibling()
	{
		if (IsLeft()) return this->parent->right;
		if (IsRight()) return this->parent->left;
		return NULL;
	}


	// get叔父节点
	 // RBTree 特有属性
	Node* Uncle()
	{
		return parent->Sibling();
	}
};



template<class K, class V>
class TreeMap : private Node<K, V>
{

private:
	int m_size;
	Node<K, V>* m_root;  //根节点
	Operate m_op;  //操作器：对遍历的数据进行自定义操作
	Compare m_compare;  //比较器：实现不同类型数据的比较操作

public:

	TreeMap() {
		m_size = 0;
		m_root = NULL;
	}


	int size()
	{
		return m_size;
	}

	bool isEmpty()
	{
		return m_size == 0;
	}

	void clear() {
		m_size = 0;
		m_root = NULL;
	}


	V add(K key, V value) {

		if (this->m_root == NULL) {
			Node<K, V>* NewNode = new Node<K, V>(key, value, NULL);
			this->m_root = NewNode;
			this->m_size++;
			black(this->m_root);
			return NULL;
		}

		int cmp = 0;
		Node<K, V>* node = this->m_root;
		Node<K, V>* parent = this->m_root;

		while (node != NULL) {

			cmp = m_compare(key, node->key); //记录最后一次是左还是右

			parent = node; // 记录最后一次的parent节点
			if (cmp > 0) {
				node = node->right;
			}
			else if (cmp < 0) {
				node = node->left;
			}
			else {
				V oldValue = node->value;
				node->value = value;
				return oldValue;
			}
		}

		Node<K, V>* NewNode = new Node<K, V>(key, value, parent);
		if (cmp > 0) {
			parent->right = NewNode;
		}
		else if (cmp < 0) {
			parent->left = NewNode;
		}
		this->m_size++;

		afterAdd(NewNode);
		return NULL;
	}



	V get(K key) {
		return node(key)->value;
	}

	V remove(K key) {

		Node<K,V>* deleNode = node(key);
		if (deleNode == NULL) return NULL;

		return remove2(deleNode);
	}



	bool containsKey(K key) {
		return node(key) != NULL;
	}


	bool containsValue(V value) {
		if (m_root == NULL) return false;

		queue<Node<K,V>*> que;
		que.push(m_root);
		
		while (!que.empty()) {
			Node<K, V>* eleNode = que.front();
			V val = eleNode->value;
			que.pop();  // c++ 和 Java差异： pop函数没有返回值！

			if (val == value) return true;

			if (eleNode->left != NULL) que.push(eleNode->left);
			if (eleNode->right != NULL) que.push(eleNode->right);
		}

		return false;
	}


	void traversal() {
		//刷新状态
		m_op.state = false;
		inorder(m_root);

		printf("\n");
	}

	void setMode()
	{
		int newMode = 1;
		m_op.setMode(newMode);
	}

/*以下是基于红黑树的代码*/
private:

	// 	***用于删除度为1和度为0的节点
	V remove1(Node<K, V>* node) {

		Node<K, V>* replacement = (node->left != NULL ? node->left : node->right);

		if (replacement != NULL)
			replacement->parent = node->parent;

		if (node->parent == NULL) {
			Node<K, V>* temp = this->m_root;
			this->m_root = replacement;
			this->afterRemove(this->m_root, replacement);
			V oldValue = temp->value;
			delete temp;
			return oldValue;
		}
		else if (node == node->parent->left) {
			node->parent->left = replacement;
		}
		else {
			node->parent->right = replacement;
		}

		//	node销毁之前做运算
		this->afterRemove(node, replacement);

		V oldValue = node->value;
		delete node;
		node = NULL;
		this->m_size--;

		return oldValue;
	}

	// 度为2的节点预处理
	V remove2(Node<K, V>* node) {

		if (node->Have2Children())  // 删除两度点： 替换元素，等价为删除1/0度点
		{
			Node<K, V>* sucnode = this->successor(node);
			node->key = sucnode->key;
			node->value = sucnode->value;
			return remove1(sucnode);    // 注意，不可node = prenode
		}
		else  return remove1(node);
	}

	void inorder(Node<K,V>* node)
	{
		if (node == NULL || m_op.state) return;

		inorder(node->left);

		if (m_op.state)  return;
		m_op.state = m_op(node->key, node->value);

		inorder(node->right);
	}


	Node<K,V>* successor(Node<K,V>* node)
	{
		if (node == NULL)  return NULL;

		Node<K, V>* rightnode = node->right;
		// 有右子树
		if (rightnode != NULL) {
			while (rightnode->left != NULL)  //! leftnode->right 
			{
				rightnode = rightnode->left;
			}
			return rightnode;
		}

		while (node->parent != NULL && node->parent->right == node)
		{
			node = node->parent;
		}
		return node->parent;
	}


	Node<K, V>* node(K key)
	{
		Node<K, V>* node = this->m_root;

		while (node != NULL)
		{
			int cmp = m_compare(key, node->key);

			if (cmp == 0) return node;
			if (cmp < 0) {
				node = node->left;
			}
			else {
				node = node->right;
			}
		}
		return NULL;
	}



	void afterAdd(Node<K,V>* node) {

		Node<K, V>* parent = node->parent;

		if (parent == NULL) {
			black(node);
			return;
		}

		Node<K, V>* grand = parent->parent;

		if (isBlack(parent) || grand == NULL) return;

		Node<K, V>* uncle = parent->Sibling();

		if (isRed(uncle)) {
		
			black(parent);
			black(uncle);

		
			red(grand);
			afterAdd(grand);
			
			return;
		}

		if (parent->IsLeft()) { 
			red(grand);
			if (node->IsLeft()) { 
				this->black(parent);
			}
			else { 
				this->black(node);
				rotateLeft(parent);

			}
			rotateRight(grand);
		}
		else { 
			red(grand);
			if (node->IsLeft()) { 
				this->black(node);
				rotateRight(parent);

			}
			else {
				black(parent);
			}
			rotateLeft(grand);
		}

	}



	 void afterRemove(Node<K, V>* node, Node<K, V>* replacement) {
		if (node == NULL) return;

		if (isRed(node)) {
			return;
		}

		if (isRed(replacement)) {
			black(replacement);
			return;
		}

		Node<K, V>* parent = node->parent;
		if (!parent) return;

	
		bool left = parent->left == NULL || node->IsLeft();
		Node<K, V>* sibling = left ? parent->right : parent->left;
		if (left) {
			if (isRed(sibling)) {
				
				red(parent);
				black(sibling);
				rotateLeft(parent);

				sibling = parent->right;
			}  

			if (red(sibling->left) || red(sibling->right))
			{
				
				if (isBlack(sibling->right)) {
					rotateRight(sibling);
					sibling = parent->right;
				}
				
				color(sibling, colorOf(parent));
				black(parent);
				black(sibling->right);
				
				rotateLeft(parent);
			}
			else {

				black(parent);
				red(sibling);
				if (isBlack(parent)) {
					afterRemove(parent, NULL);
				}
			}

		}
		else {  
			if (isRed(sibling)) {
			
				red(parent);
				black(sibling);
				rotateRight(parent);

				sibling = parent->left;
			} 

			if (red(sibling->left) || red(sibling->right))
			{
			
				if (isBlack(sibling->left)) {
					rotateLeft(sibling);
					sibling = parent->left;
				}
				
				color(sibling, colorOf(parent));
				black(parent);
				black(sibling->left);
		
				rotateRight(parent);
			}
			else {

				black(parent);
				red(sibling);
				if (isBlack(parent)) {
					afterRemove(parent, NULL);
				}
			}
		}


	}

	
	void rotateRight(Node<K, V>* grand)
	{
		Node<K, V>* parent = grand->left;
		Node<K, V>* child = parent->right;

		grand->left = parent->right;
		parent->right = grand;

		afterRotate(grand, parent, child);
	}

	 void rotateLeft(Node<K, V>* grand)
	{
		Node<K, V>* parent = grand->right;
		Node<K, V>* child = parent->left;

		grand->right = parent->left;
		parent->left = grand;

		afterRotate(grand, parent, child);
	}


	 void afterRotate(Node<K, V>* grand, Node<K, V>* parent, Node<K, V>* child)
	{
		
		parent->parent = grand->parent;
		if (grand->IsLeft()) {
			grand->parent->left = parent;
		}
		else if (grand->IsRight()) {
			grand->parent->right = parent;
		}
		else {
			m_root = parent;
		}

		
		grand->parent = parent;

		
		if (child != NULL) {
			child->parent = grand;
		}
	}

     Node<K, V>* color(Node<K, V>* node, bool color) {
		if (node == NULL) {
			return node;
		}

		node->color = color;
		return node;
	}

	 Node<K, V>* red(Node<K, V>* node) {
		return color(node, RED);
	}

	 Node<K, V>* black(Node<K, V>* node) {
		return color(node, BLACK);
	}


	 bool colorOf(Node<K, V>* node) {
		return (node == NULL) ? BLACK : node->color;
	}

	 bool isBlack(Node<K, V>* node) {
		return colorOf(node) == BLACK;
	}

	 bool isRed(Node<K, V>* node) {
		return colorOf(node) == RED;
	}

	 bool isBalanced(Node<K, V>* node) {
		return abs(node->balanceFactor()) <= 1;
	}


};