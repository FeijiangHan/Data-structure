#pragma once
#include "BinaryTree.h"
#include"Compare.h"
#include<cmath>





using namespace std;

// ***********************************************************************


template<class T>
class RBTree : public BinaryTree<T>
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
			black(this->m_root);
			return;
		}

		int cmp = 0;
		Node<T>* node = this->m_root;
		Node<T>* parent = this->m_root;

		// red(node);  �������˼����ǣ���д�����̶̵Ĵ����������˰��Сʱbug
	
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
		//black(this->m_root);

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

		if (replacement != NULL)
			replacement->parent = node->parent;

			// ����parent��left��right��ָ��
			if (node->parent == NULL) {  // node�Ƕ�Ϊ1�Ľڵ㲢���Ǹ��ڵ�
				Node<T>* temp = this->m_root;
				this->m_root = replacement;
				this->afterRemove(this->m_root, replacement);
				delete temp;
				return;
			}
			else if (node == node->parent->left) {
				node->parent->left = replacement;
			}
			else { 
				node->parent->right = replacement;
			}

		//	node����֮ǰ������
		this->afterRemove(node, replacement);

		delete node;
		node = NULL;
		this->m_size--;
	}




	// ��Ϊ2�Ľڵ�Ԥ����
	void remove(Node<T>* node) {

		if (node->Have2Children())  // ɾ�����ȵ㣺 �滻Ԫ�أ��ȼ�Ϊɾ��1/0�ȵ�
		{
			Node<T>* sucnode = this->successor(node);
			node->Element = sucnode->Element;
			remove1(sucnode);    // ע�⣬����node = prenode
		}
		else  remove1(node);
	}


//*****************************AVLTree*************************************//

	void afterAdd(Node<T>* node) {

		Node<T>* parent = node->parent;
		// ��һ����Ӹ��ڵ����grand���絽���ڵ�

		if (parent == NULL) {
			black(node);
			return;
		}

		Node<T>* grand = parent->parent;

		// 1.��ӵ���ɫ�ڵ�
		if (isBlack(parent) || grand == NULL) return;

		Node<T>* uncle = parent->Sibling();

		if (isRed(uncle)) {
			// 3.��ӵ���ɫ�ڵ㣬�Һ�ɫ�ڵ��uncle�Ǻ�ɫ�ڵ�
			black(parent);
			black(uncle);

			/*grandȾ�ɺ�ɫ�������½ڵ���д���*/
			red(grand);
			afterAdd(grand);
			// ���游�ڵ�Ⱦ������½ڵ����絽��һ��
			return;
		}
	

			// 2.��ӵ���ɫ�ڵ㣬�Һ�ɫ�ڵ��uncle��null����ɫ��
				if (parent->IsLeft()) { // L
					red(grand);
					if (node->IsLeft()) { // LL
						this->black(parent);	
					}
					else { // LR
						this->black(node);		
						rotateLeft(parent);
						
					}
					rotateRight(grand);
				}
				else { // R
					red(grand);
					if (node->IsLeft()) { // RL
						this->black(node);		
						rotateRight(parent);
	
					}
					else { // RR
						this->black(parent);
					}
					rotateLeft(grand);
				}

	}



	void afterRemove(Node<T>* node,Node<T>* replacement) {
		if (node == NULL) return;

		//1.ɾ����ɫ�ڵ�

		//2.ɾ��2�Ⱥ�ɫ��

		//3.ɾ��1�Ⱥ�ɫ��

		/*ɾ����ɫҶ�ӽڵ� -- ����� */
		//4.�ֵ��Ǻ�ɫ

		//5.�ֵ��Ǻ�ɫ---
 		               // a���к�ɫ�ӽڵ�  
					  
		               // b���޺�ɫ�ӽڵ�
		                      // parent�Ǻ�ɫ���Ǻ�ɫ

		if (isRed(node)) {
			return;
		}

		if (isRed(replacement)) {
			black(replacement);
			return;
		}

		Node<T>* parent = node->parent;
		if (!parent) return;



		// ����0�Ⱥ�ɫ�ڵ����
		bool left = parent->left == NULL || node->IsLeft();
		Node<T>* sibling = left ? parent->right : parent->left;

		if (left) {
			if (isRed(sibling)) {
				/*����Ⱦ�죬�ֵ�Ⱦ�ڣ�����ת���׽ڵ㣬ˢ���ֵ�*/
				red(parent);
				black(sibling);
				rotateLeft(parent);

				sibling = parent->right;
			}  //  �˲���֮�󣬱�Ϊ�ֵ�Ϊ�ڵ����

			if (red(sibling->left) || red(sibling->right))
			{
				/*�����ұ�ɾ�ڵ㣬���������������LR����ת��ת��ΪLL��ע����ת�����sibling*/
				if (isBlack(sibling->right)) {
					rotateRight(sibling);
					sibling = parent->right;
				}
				// LR֮�������������ΪLL
				color(sibling, colorOf(parent));
				black(parent);
				black(sibling->right);
				/*��Ⱦɫ����ת��sibling��ԭ��parent��ɫһ�£���ת�������ӽڵ㶼Ⱦ�ɺ�ɫ*/
				rotateLeft(parent);
			}
			else {

				black(parent);
				red(sibling);
				if (isBlack(parent)) {
					afterRemove(parent,NULL);
				}
			}

		}
		else {  // ��ɾ����ɫҶ�ӽڵ����ұ�
			if (isRed(sibling)) {
				/*����Ⱦ�죬�ֵ�Ⱦ�ڣ�����ת���׽ڵ㣬ˢ���ֵ�*/
				red(parent); 
				black(sibling);
				rotateRight(parent);

				sibling = parent->left;
			}  //  �˲���֮�󣬱�Ϊ�ֵ�Ϊ�ڵ����

			if (red(sibling->left) || red(sibling->right))
			{
				/*�����ұ�ɾ�ڵ㣬���������������LR����ת��ת��ΪLL��ע����ת�����sibling*/
				if (isBlack(sibling->left)) {
					rotateLeft(sibling);
					sibling = parent->left;
				}
				// LR֮�������������ΪLL
				color(sibling, colorOf(parent));
				black(parent);
				black(sibling->left);
				/*��Ⱦɫ����ת��sibling��ԭ��parent��ɫһ�£���ת�������ӽڵ㶼Ⱦ�ɺ�ɫ*/
				rotateRight(parent);
			}
			else {

				black(parent);
				red(sibling);
				if (isBlack(parent)) {
					afterRemove(parent,NULL);
				}
			}
		}


	}




	// ����������ʵ����ת
	void rotateRight(Node<T>* grand)
	{
		Node<T>* parent = grand->left;
		Node<T>* child = parent->right;

		grand->left = parent->right;
		parent->right = grand;

		afterRotate(grand, parent, child);
	}

	void rotateLeft(Node<T>* grand)
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
		}
	}



	bool isBalanced(Node<T>* node) {
		return abs(node->balanceFactor()) <= 1;
	}



	Node<T>* color(Node<T>* node, bool color) {
		if (node == NULL) {
			return node;
		}

		node->color = color;
		return node;
	}

	Node<T>* red(Node<T>* node) {
		return color(node, RED);
	}

	Node<T>* black(Node<T>* node) {
		return color(node, BLACK);
	}


	bool colorOf(Node<T>* node) {
		return (node == NULL) ? BLACK : node->color;
	}

	bool isBlack(Node<T>* node) {
		return colorOf(node) == BLACK;
	}

	bool isRed(Node<T>* node) {
		return colorOf(node) == RED;
	}

private:
	Compare compare;  //�Ƚ�����ʵ�ֲ�ͬ�������ݵıȽϲ���
};