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

	//���
	void add(T Ele)
	{
		//��ӵ�һ���ڵ�
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

			cmp = compare(Ele, node->Element); //��¼���һ����������

			parent = node; // ��¼���һ�ε�parent�ڵ�
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

		//ѭ����Ϻ�node��null��parent�����һ�εĽڵ㣬cmp�����һ�αȽϵĽ��

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




	//����

	bool Contains(T Ele)
	{
		return node(Ele) != NULL;
	}


	// ����
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


	// ɾ���ڵ�

	void remove(T ele) {

		Node<T>* deleNode = node(ele);
		if (deleNode == NULL) return;

		remove(deleNode);
	}


	// 	***����ɾ����Ϊ1�Ͷ�Ϊ0�Ľڵ�
	void remove1(Node<T>* node) {

		Node<T>* replacement = (node->left != NULL ? node->left : node->right);

		if (replacement != NULL) { // node�Ƕ�Ϊ1�Ľڵ�

			// ����parent
			replacement->parent = node->parent;

			// ����parent��left��right��ָ��
			if (node->parent == NULL) {  // node�Ƕ�Ϊ1�Ľڵ㲢���Ǹ��ڵ�
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
		else if (node->parent == NULL) { // node��Ҷ�ӽڵ㲢���Ǹ��ڵ�
		
		}
		else if (node == node->parent->left) {
			node->parent->left = NULL;
		
		}
		else { // node == node.parent.right
			node->parent->right = NULL;
		
		}

		//	node����֮ǰ������
		this->afterRemove(node);

		delete node;
		node = NULL;
		this->m_size--;
	}




	// ��Ϊ2�Ľڵ�Ԥ����
	void remove(Node<T>* node) {

		if (node->Have2Children())  // ɾ�����ȵ㣺 �滻Ԫ�أ��ȼ�Ϊɾ��1/0�ȵ�
		{
			Node<T>* prenode = this->predecessor(node);  // ɾ�����ȵ�ʱ����ǰ���ڵ����
			node->Element = prenode->Element;
			remove1(prenode);    // ע�⣬����node = prenode
		}
		else  remove1(node);
	}


//*****************************AVLTree*************************************//

	void afterAdd(Node<T>* node) {
		while ((node = node->parent) != NULL) {
			if (isBalanced(node)) {
				// ���¸߶�
				node->updateHeight();
			}
			else {
				// �ָ�ƽ��
				rebalance(node);
				// �������ָ�ƽ��
				break;
			}
		}
	}

	void afterRemove(Node<T>* node) {
		while ((node = node->parent) != NULL) {
			if (isBalanced(node)) {
				// ���¸߶�
				node->updateHeight();
			}
			else {
				// �ָ�ƽ��
				rebalance(node);
			}
		}
	}

	// ******��һ����ת�߼�	�� ���������ֱ�ӱ���***********
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
		Node<T>* r, // �����ĸ��ڵ�
		Node<T>* b, Node<T>* c,
		Node<T>* d,
		Node<T>* e, Node<T>* f) {
		// ��d��Ϊ��������ĸ��ڵ�
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



	// ******�ڶ�����ת�߼�	�� ��������***********
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

	// ����������ʵ����ת
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

	// ʵ����ת������ԭ��parent�Ĺ���
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

		// ���¸߶�
		grand->updateHeight();
		parent->updateHeight();
	}


	bool isBalanced(Node<T>* node) {
		return abs(node->balanceFactor()) <= 1;
	}


private:
	Compare compare;  //�Ƚ�����ʵ�ֲ�ͬ�������ݵıȽϲ���
};