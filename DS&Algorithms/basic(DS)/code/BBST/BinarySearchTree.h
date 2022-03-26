#pragma once
#include"Student.h"
#include"Operate.h"
#include"Compare.h"
#include<queue>
#include<string>
#include <algorithm> 

using namespace std;

//树节点
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

	//添加
	void add(T Ele)
	{
		//添加第一个节点
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

		Node<T>* NewNode = new Node(Ele, parent);
		if (cmp > 0) {
			parent->right = NewNode;
		}
		else if (cmp < 0) {
			parent->left = NewNode;
		}
		m_size++;

	}

	//删除


	//搜索

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


	//空状态判断
	bool IsEmpty()
	{
		return m_size == 0;
	}


	//size大小
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

	//先序遍历

	void preorder()
	{
		//刷新状态
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
	//中序遍历
	void inorder()
	{
		//刷新状态
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

	//后序遍历
	void postorder()
	{
		//刷新状态
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

	//层序遍历


	void levelOrder()
	{
		if (m_root == NULL) return;

		queue<Node<T>*> que;
		que.push(m_root);

		while (!que.empty()) {
			Node<T>* eleNode = que.front();
			que.pop();  // c++ 和 Java差异： pop函数没有返回值！

			if (m_op(eleNode->Element))  return;

			if (eleNode->left != NULL) que.push(eleNode->left);
			if (eleNode->right != NULL) que.push(eleNode->right);
		}

	}


	//	  ************* 输出图形二叉树 *************
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

	// 递归
	void Print_Recurrence()
	{
		string begin = "";  // 初始字符串

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

	//**层序遍历**//
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


	//获得树的高度
	//****递归实现

	int Hight()
	{
		return Hight(m_root);
	}
	/*
	一个节点的高度 = 1 + 这个节点左右节点的高度中的最大的那一个
	*/
	int Hight(Node<T>* node)
	{
		if (node == NULL) return 0;

		return 1 + max(Hight(node->left), Hight(node->right));
	}


	//** 循环实现----层序遍历
	int hight()
	{
		return hight(m_root);
	}

	int hight(Node<T>* node)
	{
		if (node == NULL) return 0;

		int hight = 0; // 高度
		int levelSize = 1; // 每层节点数
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



	//判断是否为完全二叉树compete binary----层序遍历

	bool IsCompeteBinary()
	{
		//左=0，右=0 ------右侧全是叶子

		//左 ！= 0,右 ！=0-------正常操作

		//左 = 0 右 ！=0--------右侧全是叶子

		//左 ！= 0 右=0-------不为完全二叉树

		if (m_root == NULL) return false;

		queue<Node<T>*> que;
		que.push(m_root);
		bool IsLeaf = false;

		while (!que.empty()) {
			Node<T>* n = que.front();
			que.pop();

			if (IsLeaf && !n->IsLeaf()) return false;  //（右侧应该是叶子，右侧实际上不是叶子）

			if (n->Have2Children()) {  	//左 ！= 0,右 ！=0-------正常操作
				que.push(n->left);
				que.push(n->right);
			}
			else if (n->left == NULL && n->right != NULL) { //左 == 0 右！=0-------不为完全二叉树
				return false;
			}
			else {    //左 = 0 右 ！=0--------右侧全是叶子，左=0，右=0 ------右侧全是叶子
				IsLeaf = true;
			}

		} // end while
		return true;
	}

private:

	int m_size;
	Node<T>* m_root;  //根节点

	Operate m_op;  //操作器：对遍历的数据进行自定义操作
	Compare<T> compare;  //比较器：实现不同类型数据的比较操作
};


template<class T>
std::ostream& operator << (std::ostream& out, BinarySearchTree<T>& bst)
{
	bst.PrintTree(out);
	return out;
}

