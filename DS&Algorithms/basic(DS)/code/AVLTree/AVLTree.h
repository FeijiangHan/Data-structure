#pragma once
#include"BinaryTree.h"
#include"Compare.h"
#include<cmath>

using namespace std;

// ***********************************************************************


template<class T>
class AVLTree : public BinaryTree<T>
{
public:

	//添加
	void add(T Ele)
	{
		//添加第一个节点
		if (this->m_root == NULL) {
			Node<T>* NewNode = new Node<T>(Ele, NULL);
			this->m_root = NewNode;
			this->m_size++;
			afterAdd(NewNode);
			return;
		}

		int cmp = 0;
		Node<T>* node = this->m_root;
		Node<T>* parent = this->m_root;

		while (node != NULL) {

			cmp = compare(Ele, node->Element); //记录最后一次是左还是右

			parent = node; // 记录最后一次的parent节点
			if (cmp > 0) {
				node = node->right;
			}
			else if (cmp < 0) {
				node = node->left;
			}
			else {
				node->Element = Ele;
				return;
			}
		}

		//循环完毕后node是null，parent是最后一次的节点，cmp是最后一次比较的结果

		Node<T>* NewNode = new Node<T>(Ele, parent);
		if (cmp > 0) {
			parent->right = NewNode;
		}
		else if (cmp < 0) {
			parent->left = NewNode;
		}
		this->m_size++;

		afterAdd(NewNode);

	}




	//搜索

	bool Contains(T Ele)
	{
		return node(Ele) != NULL;
	}


	// 查找
	Node<T>* node(T Ele)
	{
		Node<T>* node = this->m_root;

		while (node != NULL)
		{
			int cmp = compare(Ele, node->Element);

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


	Node<T>* BSTSearch(Node<T>* node,T data) {
		int cmp = compare(data, node->Element);
		if (node == NULL || cmp == 0) {
			return node;
		}
		else {
			if (cmp > 0) {
				BSTSearch(node->right, data);
			}
			else {
				BSTSearch(node->left, data);
			}
		}
	}


	// 删除节点

	void remove(T ele) {

		Node<T>* deleNode = node(ele);
		if (deleNode == NULL) return;

		remove(deleNode);
	}


	// 	***用于删除度为1和度为0的节点
	void remove1(Node<T>* node) {

		Node<T>* replacement = (node->left != NULL ? node->left : node->right);

		if (replacement != NULL) { // node是度为1的节点

			// 更改parent
			replacement->parent = node->parent;

			// 更改parent的left、right的指向
			if (node->parent == NULL) {  // node是度为1的节点并且是根节点
				delete node;
				node = replacement;
				return;
			}
			else if (node == node->parent->left) {
				node->parent->left = replacement;
				
			}
			else { // node == node.parent.right
				node->parent->right = replacement;
			
			}

		}
		else if (node->parent == NULL) { // node是叶子节点并且是根节点
		
		}
		else if (node == node->parent->left) {
			node->parent->left = NULL;
		
		}
		else { // node == node.parent.right
			node->parent->right = NULL;
		
		}

		//	node销毁之前做运算
		this->afterRemove(node);

		delete node;
		node = NULL;
		this->m_size--;
	}




	// 度为2的节点预处理
	void remove(Node<T>* node) {

		if (node->Have2Children())  // 删除两度点： 替换元素，等价为删除1/0度点
		{
			Node<T>* prenode = this->predecessor(node);  // 删除两度点时候用前驱节点替代
			node->Element = prenode->Element;
			remove1(prenode);    // 注意，不可node = prenode
		}
		else  remove1(node);
	}


//*****************************AVLTree*************************************//

	void afterAdd(Node<T>* node) {
		while ((node = node->parent) != NULL) {
			if (isBalanced(node)) {
				// 更新高度
				node->updateHeight();
			}
			else {
				// 恢复平衡
				rebalance(node);
				// 整棵树恢复平衡
				break;
			}
		}
	}

	void afterRemove(Node<T>* node) {
		while ((node = node->parent) != NULL) {
			if (isBalanced(node)) {
				// 更新高度
				node->updateHeight();
			}
			else {
				// 恢复平衡
				rebalance(node);
			}
		}
	}

	// ******第一种旋转逻辑	： 根据最后结果直接变形***********
	void rebalance2(Node<T>* grand) {
		Node<T>* parent = grand->tallerChild();
		Node<T>* node = parent->tallerChild();

		if (parent->IsLeft()) { // L
			if (node->IsLeft()) { // LL
				rotate(grand, node, node->right, parent, parent->right, grand);
			}
			else { // LR
				rotate(grand, parent, node->left, node, node->right, grand);
			}
		}
		else { // R
			if (node->IsLeft()) { // RL
				rotate(grand, grand, node->left, node, node->right, parent);
			}
			else { // RR
				rotate(grand, grand, parent->left, parent, node->left, node);
			}
		}
	}


	void rotate(
		Node<T>* r, // 子树的根节点
		Node<T>* b, Node<T>* c,
		Node<T>* d,
		Node<T>* e, Node<T>* f) {
		// 让d成为这棵子树的根节点
		d->parent = r->parent;
		if (r->IsLeft()) {
			r->parent->left = d;
		}
		else if (r->IsRight()) {
			r->parent->right = d;
		}
		else {
			this->m_root = d;
		}

		//b-c
		b->right = c;
		if (c != NULL) {
			c->parent = b;
		}
		b->updateHeight();

		// e-f
		f->left = e;
		if (e != NULL) {
			e->parent = f;
		}
		f->updateHeight();

		// b-d-f
		d->left = b;
		d->right = f;
		b->parent = d;
		f->parent = d;
		d->updateHeight();
	}



	// ******第二种旋转逻辑	： 分类讨论***********
	void rebalance(Node<T>* grand) {
		Node<T>* parent = grand->tallerChild();
		Node<T>* node = parent->tallerChild();

		if (parent->IsLeft()) { // L
			if (node->IsLeft()) { // LL
				rotateLeft(grand);
			}
			else { // LR
				rotateLeft(parent);
				rotateRight(grand);
			}
		}
		else { // R
			if (node->IsLeft()) { // RL
				rotateRight(parent);
				rotateLeft(grand);
			}
			else { // RR
				rotateRight(grand);
			}
		}
	}

	// 单纯的两步实现旋转
	void rotateLeft(Node<T>* grand)
	{
		Node<T>* parent = grand->left;
		Node<T>* child = parent->right;

		grand->left = parent->right;
		parent->right = grand;

		afterRotate(grand, parent, child);
	}

	void rotateRight(Node<T>* grand)
	{
		Node<T>* parent = grand->right;
		Node<T>* child = parent->left;

		grand->right = parent->left;
		parent->left = grand;

		afterRotate(grand, parent, child);
	}

	// 实现旋转后建立与原有parent的关联
	void afterRotate(Node<T>* grand, Node<T>* parent, Node<T>* child)
	{
		// parent
		parent->parent = grand->parent;
		if (grand->IsLeft()) {
			grand->parent->left = parent;
		}
		else if (grand->IsRight()) {
			grand->parent->right = parent;
		}
		else {
			this->m_root = parent;
		}

		// grand
		grand->parent = parent;
		
		// child
		if (child != NULL) {
			child->parent = grand;
			child->updateHeight();
		}

		// 更新高度
		grand->updateHeight();
		parent->updateHeight();
	}


	bool isBalanced(Node<T>* node) {
		return abs(node->balanceFactor()) <= 1;
	}


private:
	Compare compare;  //比较器：实现不同类型数据的比较操作
};