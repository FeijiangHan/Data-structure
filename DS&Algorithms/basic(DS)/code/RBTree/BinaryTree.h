#pragma once
#include"Student.h"
#include"Operate.h"
#include<queue>
#include<string>
#include <algorithm> 
#include<vector>
#include<unordered_map>
using namespace std;

template<class T>
class Node
{
public:

	T Element;
	Node* left;
	Node* right;
	Node* parent;
	int height = 1;

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

	// 判断左右
	bool IsLeft()
	{
		return (parent != NULL && this == parent->left);
	}

	bool IsRight()
	{
		return (parent != NULL && this == parent->right);
	}

	// 更新高度
	void updateHeight() {
		int leftHeight = left == NULL ? 0 : left->height;
		int rightHeight = right == NULL ? 0 : right->height;
		height = 1 + max(leftHeight, rightHeight);
	}


	// 平衡因子

	int balanceFactor() {
		int leftHeight = left == NULL ? 0 : left->height;
		int rightHeight = right == NULL ? 0 : right->height;
		return leftHeight - rightHeight;
	}

	// 最高子树
	// 根据不平衡点得到父节点和node，进而得知是那种旋转模式。
	Node<T>* tallerChild() {
		int leftHeight = left == NULL ? 0 : left->height;
		int rightHeight = right == NULL ? 0 : right->height;
		if (leftHeight > rightHeight) return left;
		if (leftHeight < rightHeight) return right;

		return this->IsLeft() ? left : right;
	}

};


template<class T>
class BinaryTree : protected Node<T>
{
public:
	int m_size;
	Node<T>* m_root;  //根节点
	Operate m_op;  //操作器：对遍历的数据进行自定义操作


public:

	BinaryTree()
	{
		m_size = 0;
		m_root = NULL;
	}

	Node<T>* root()
	{
		return m_root;
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
			string str = indent + (left ? "|     " : "      ");
			output_impl(n->right, false, str);
		}

		cout << indent;
		cout << (left ? '\\' : '/');
		cout << "-----";
		cout << n->Element << endl;

		if (n->left)
		{
			string str = indent + (left ? "|     " : "      ");
			output_impl(n->left, true, str);
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


	void inorderTraversal(Node<T>* node, vector<Node<T>*>& v)
	{
		if (node == NULL) return;

		inorderTraversal(node->left, v);

		v.push_back(node);

		inorderTraversal(node->right, v);
	}

	//**层序遍历**//
	void PrintNodeByLevel( )
	{
		PrintNodeByLevel(m_root);
	}

	void PrintNodeByLevel(Node<T>* rnode) {
		if (rnode == NULL) {
			cout << "空树！" << endl;
			return;
		}

		vector<Node<T>*> intv;

		inorderTraversal(rnode, intv);//中序遍历节点数组
		string template_str;//模板string，表示每行打印string的长度

		int location = 0;

		typedef unordered_map<Node<T>*, int> hashmap;
		hashmap first_locations;//存储节点对应在本行string中的首位置


		for (auto& i : intv) {

			location = template_str.size();

			template_str += to_string(i->Element) + "    ";

			first_locations[i] = location;
		}


		for (auto& i : template_str)  i = '    ';//把模板全部置为空格方便后续使用


		//层序遍历
		queue<Node<T>*> q;
		q.push(rnode);

		while (!q.empty()) {

			int currentLevelSize = q.size();
			int cur_loc = 0;

			string tmp_str1 = template_str, tmp_str2 = template_str,
				   tmp_str3 = template_str,
				   tmp_str4 = template_str,
				   tmp_str5 = template_str;//1为节点所在行，2为其下一行


			for (int i = 1; i <= currentLevelSize; ++i) {

				auto node = q.front();
				q.pop();
				cur_loc = first_locations[node];

				// 父节点信息
				string addmessage1 = node->parent ? to_string(node->parent->Element) : "null";
				string addmessage2 = to_string(hight(node));
				string addmessage3 = to_string(node->balanceFactor());

				string num_str = to_string(node->Element);
				//string appendMessage1 =	"P[" + addmessage1 + "]";
				string appendMessage1 = "H{" + addmessage2 + "}";
				 //string appendMessage1 = "B:" + addmessage3 ;


				//左边，如果存在左孩子，那么在第二行对应位置打印'/'，在第一行补上'_'
				if (node->left) {
					q.push(node->left);

					int first_loc = first_locations[node->left] + 1;
					tmp_str2[first_loc - 1] = '/';
					tmp_str3[first_loc] = '/';
					//tmp_str4[first_loc -1] = '/';
					//tmp_str5[first_loc -2] = '/';
					first_loc++;

					while (first_loc < cur_loc)
						tmp_str1[first_loc++] = '_';
				}


				//			中间,对应位置打印节点值（有可能为多位数）
				int temploc = cur_loc;
				for (int j = 0; j < num_str.length(); ++j) {
					tmp_str1[cur_loc++] = num_str[j];
				}

				for (int j = 0; j < appendMessage1.length(); ++j) {
					tmp_str3[temploc] = appendMessage1[j];
					temploc++;
				}

			/*	for (int j = 0; j < appendMessage2.length(); ++j, temploc++) {
					tmp_str4[temploc] = appendMessage2[j];
				}
				for (int j = 0; j < appendMessage3.length(); ++j, temploc++) {
					tmp_str5[temploc] = appendMessage3[j];
				}*/


				//右边，如果存在右孩子，那么在第二行对应位置打印'\'，在第一行补上'_'
				if (node->right) {
					q.push(node->right);

					int last_loc = first_locations[node->right] - 1;

					tmp_str2[last_loc + 1] = '\\';
					tmp_str3[last_loc] = '\\';
					//tmp_str4[last_loc + 1] = '\\';
					//tmp_str5[last_loc + 2] = '\\';

					//last_loc++;
					while (cur_loc < last_loc) {
						tmp_str1[cur_loc++] = '_';
					}
				}

			}

			std::cout << tmp_str1 << std::endl;
			std::cout << tmp_str3 << std::endl;
			//std::cout << tmp_str4 << std::endl;
			//std::cout << tmp_str5 << std::endl;
			std::cout << tmp_str2 << std::endl;
		}
	}




	//获得树的高度
	//****递归实现
	void PrintHight()
	{
		cout << "计算完毕 , 树的高度为： " << hight() << endl;
	}

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
			else {    //左 != 0 右 ==0--------右侧全是叶子，左=0，右=0 ------右侧全是叶子
				IsLeaf = true;
				if (n->left != NULL) que.push(n->left); // int data[] =  {6,3,8}; 头结点入队-出队-其他元素不入队-循环跳出-true
			}

		} // end while
		return true;
	}

	// 改进版 先写层序遍历逻辑 后改编

	void PrintIsCompeteBinary()
	{
		if (IsCompeteBinary_promote()) cout << "测试完毕： 是完全二叉树" << endl;
		if (!IsCompeteBinary_promote()) cout << "测试完毕： 不是完全二叉树" << endl;
	}

	bool IsCompeteBinary_promote()
	{

		if (m_root == NULL) return false;

		queue<Node<T>*> que;
		que.push(m_root);
		bool IsLeaf = false;

		while (!que.empty()) {
			Node<T>* n = que.front();
			que.pop();
			if (IsLeaf && !n->IsLeaf()) return false;

			if (n->left != NULL)  que.push(n->left);
			else if (n->right != NULL) return false;

			if (n->right != NULL)  que.push(n->right);
			else IsLeaf = true;  // 左 != 0 右 ==0--------右侧全是叶子，左=0，右=0 ------右侧全是叶子
		} // end while
		return true;
	}

	//****************************************************

	// 某节点的前驱节点
	Node<T>* predecessor(Node<T>* node)
	{
		if (node == NULL)  return NULL;

		Node<T>* leftnode = node->left;
		// 有左子树
		if (leftnode != NULL) {
			while (leftnode->right != NULL)  //! leftnode->right 
			{
				leftnode = leftnode->right;
			}
			return leftnode;
		}

		while (node->parent != NULL && node->parent->left == node)
		{
			node = node->parent;
		}
		return node->parent;
	}


	// 某节点的后缀节点
	Node<T>* successor(Node<T>* node)
	{
		if (node == NULL)  return NULL;

		Node<T>* rightnode = node->right;
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

	// **************翻转二叉树*************
	void VerseTree()
	{
		cout << "*****使用递归前序遍历反转树******" << endl << endl;
		VerseTree(m_root);
	}

	// 节点node最后指向的就是交换完后的根节点
	void VerseTree(Node<T>* node)  // 递归实现
	{
		if (node == NULL) return;

		Node<T>* n = node->left;
		node->left = node->right;
		node->right = n;

		VerseTree(node->left);
		VerseTree(node->right);
	}

	void VerseTree2()
	{
		cout << "*****使用迭代层次遍历反转树******" << endl << endl;
		if (m_root == NULL) return;

		queue<Node<T>*> que;
		que.push(m_root);

		while (!que.empty()) {
			Node<T>* node = que.front();
			que.pop();

			Node<T>* n = node->left;
			node->left = node->right;
			node->right = n;

			if (node->left != NULL) que.push(node->left);
			if (node->right != NULL) que.push(node->right);
		}

	}

};
