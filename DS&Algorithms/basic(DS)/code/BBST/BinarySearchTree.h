#pragma once
#include"Student.h"
#include"Operate.h"
#include"Compare.h"
#include<queue>
#include<string>
#include <algorithm> 

using namespace std;

//���ڵ�
template<class T>
class Node
{
public:

	T Element;
	Node* left;
	Node* right;
	Node* parent;


	Node() {}

	Node(T ele, Node* parent = NULL) :Element(ele), parent(parent)
	{
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

};



//BST
template<class T>
class BinarySearchTree : private Node<T>
{

public:

	template<class T>
	friend std::ostream& operator << (std::ostream& out, const BinarySearchTree<T>& bst);

	BinarySearchTree()
	{
		m_size = 0;
		m_root = NULL;
	}


	Node<T>* root()
	{
		return m_root;
	}

	//���
	void add(T Ele)
	{
		//��ӵ�һ���ڵ�
		if (m_root == NULL) {
			Node<T>* NewNode = new Node<T>(Ele, NULL);
			m_root = NewNode;
			m_size++;
			return;
		}

		int cmp = 0;
		Node<T>* node = m_root;
		Node<T>* parent = m_root;

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

		Node<T>* NewNode = new Node(Ele, parent);
		if (cmp > 0) {
			parent->right = NewNode;
		}
		else if (cmp < 0) {
			parent->left = NewNode;
		}
		m_size++;

	}

	//ɾ��


	//����

	bool Contains(T Ele)
	{
		return node(Ele) != NULL;
	}


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


	//��״̬�ж�
	bool IsEmpty()
	{
		return m_size == 0;
	}


	//size��С
	int size()
	{
		return m_size;
	}


	//clear
	void clear()
	{
		m_root = NULL;
		m_size = 0;
	}

	//�������

	void preorder()
	{
		//ˢ��״̬
		m_op.state = false;
		preorder(m_root);
	}

	void preorder(Node<T>* node)
	{
		if (node == NULL || m_op.state)  return;

		if (m_op.state)  return;
		m_op.state = m_op(node->Element);
		preorder(node->left);
		preorder(node->right);

	}
	//�������
	void inorder()
	{
		//ˢ��״̬
		m_op.state = false;
		inorder(m_root);
	}

	void inorder(Node<T>* node)
	{
		if (node == NULL || m_op.state) return;

		inorder(node->left);

		if (m_op.state)  return;
		m_op.state = m_op(node->Element);

		inorder(node->right);

	}

	//�������
	void postorder()
	{
		//ˢ��״̬
		m_op.state = false;
		postorder(m_root);
	}

	void postorder(Node<T>* node)
	{
		if (node == NULL || m_op.state)  return;

		postorder(node->left);
		postorder(node->right);

		if (m_op.state)  return;
		m_op.state = m_op(node->Element);

	}

	//�������


	void levelOrder()
	{
		if (m_root == NULL) return;

		queue<Node<T>*> que;
		que.push(m_root);

		while (!que.empty()) {
			Node<T>* eleNode = que.front();
			que.pop();  // c++ �� Java���죺 pop����û�з���ֵ��

			if (m_op(eleNode->Element))  return;

			if (eleNode->left != NULL) que.push(eleNode->left);
			if (eleNode->right != NULL) que.push(eleNode->right);
		}

	}


	//	  ************* ���ͼ�ζ����� *************
	void output_impl(Node<T>* n, bool left, string& indent)
	{
		if (n->right)
		{
			output_impl(n->right, false, indent + (left ? "|     " : "      "));
		}
		cout << indent;
		cout << (left ? '\\' : '/');
		cout << "-----";
		cout << n->Element << endl;
		if (n->left)
		{
			output_impl(n->left, true, indent + (left ? "      " : "|     "));
		}
	}

	// �ݹ�
	void Print_Recurrence()
	{
		string begin = "";  // ��ʼ�ַ���

		if (m_root->right)
		{
			output_impl(m_root->right, false, begin);
		}

		cout << m_root->Element << endl;

		if (m_root->left)
		{
			output_impl(m_root->left, true, begin);
		}
	}
	//  ***************************************

	//**�������**//
	void PrintNodeByLevel() {
		queue<Node<T>*> Q;
		queue<string> C;

		Q.push(m_root);
		Q.push(0);
		do {
			Node<T>* node = Q.front();
			Q.pop();
			if (node) {
				cout << node->Element << " ";
				if (node->left) {
					Q.push(node->left);
					C.push("/");
				}
				if (node->right) {
					Q.push(node->right);
					C.push("\\");
				}
			}
			else if (!Q.empty()) {
				cout << endl;
				while (C.size() != 0) {
					cout << C.front() << " ";
					C.pop();
				}
				Q.push(0);
				cout << endl;
			}
		} while (!Q.empty());
	}


	//������ĸ߶�
	//****�ݹ�ʵ��

	int Hight()
	{
		return Hight(m_root);
	}
	/*
	һ���ڵ�ĸ߶� = 1 + ����ڵ����ҽڵ�ĸ߶��е�������һ��
	*/
	int Hight(Node<T>* node)
	{
		if (node == NULL) return 0;

		return 1 + max(Hight(node->left), Hight(node->right));
	}


	//** ѭ��ʵ��----�������
	int hight()
	{
		return hight(m_root);
	}

	int hight(Node<T>* node)
	{
		if (node == NULL) return 0;

		int hight = 0; // �߶�
		int levelSize = 1; // ÿ��ڵ���
		queue<Node<T>*> que;
		que.push(node);

		while (!que.empty()) {
			Node<T>* n = que.front();
			que.pop();
			levelSize--;

			if (n->left != NULL) que.push(n->left);
			if (n->right != NULL) que.push(n->right);

			if (levelSize == 0) {
				levelSize = que.size();
				hight++;
			} // end if
		} // end while

		return hight;
	}



	//�ж��Ƿ�Ϊ��ȫ������compete binary----�������

	bool IsCompeteBinary()
	{
		//��=0����=0 ------�Ҳ�ȫ��Ҷ��

		//�� ��= 0,�� ��=0-------��������

		//�� = 0 �� ��=0--------�Ҳ�ȫ��Ҷ��

		//�� ��= 0 ��=0-------��Ϊ��ȫ������

		if (m_root == NULL) return false;

		queue<Node<T>*> que;
		que.push(m_root);
		bool IsLeaf = false;

		while (!que.empty()) {
			Node<T>* n = que.front();
			que.pop();

			if (IsLeaf && !n->IsLeaf()) return false;  //���Ҳ�Ӧ����Ҷ�ӣ��Ҳ�ʵ���ϲ���Ҷ�ӣ�

			if (n->Have2Children()) {  	//�� ��= 0,�� ��=0-------��������
				que.push(n->left);
				que.push(n->right);
			}
			else if (n->left == NULL && n->right != NULL) { //�� == 0 �ң�=0-------��Ϊ��ȫ������
				return false;
			}
			else {    //�� = 0 �� ��=0--------�Ҳ�ȫ��Ҷ�ӣ���=0����=0 ------�Ҳ�ȫ��Ҷ��
				IsLeaf = true;
			}

		} // end while
		return true;
	}

private:

	int m_size;
	Node<T>* m_root;  //���ڵ�

	Operate m_op;  //���������Ա��������ݽ����Զ������
	Compare<T> compare;  //�Ƚ�����ʵ�ֲ�ͬ�������ݵıȽϲ���
};


template<class T>
std::ostream& operator << (std::ostream& out, BinarySearchTree<T>& bst)
{
	bst.PrintTree(out);
	return out;
}

