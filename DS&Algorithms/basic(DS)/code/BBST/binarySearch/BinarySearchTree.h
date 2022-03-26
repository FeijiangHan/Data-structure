#pragma once
#include"Student.h"
#include"Operate.h"
#include"Compare.h"
#include<queue>
#include<string>
#include <algorithm> 
#include<vector>
#include<unordered_map>

using namespace std;



// ***********************************************************************
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

// ***********************************************************************




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

		Node<T>* NewNode = new Node<T>(Ele, parent);
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

		inorderTraversal(node->left,v);
		
		v.push_back(node);

		inorderTraversal(node->right,v);
	}

	//**层序遍历**//
	void PrintNodeByLevel() {

		if (m_root == NULL) {
			cout << "空树！" << endl;
			return;
		}
		vector<Node<T>*> intv;

		inorderTraversal(m_root, intv);//中序遍历节点数组
		string template_str;//模板string，表示每行打印string的长度
		
		int location = 0;

		typedef unordered_map<Node<T>*, int> hashmap;
		hashmap first_locations;//存储节点对应在本行string中的首位置
		
		
		for (auto& i : intv) {

			location = template_str.size();

			template_str += to_string(i->Element) + "    " ;

			first_locations[i] = location;
		}


		for (auto& i : template_str)  i = '    ';//把模板全部置为空格方便后续使用


		//层序遍历
		queue<Node<T>*> q;
		q.push(m_root);

		while (!q.empty()) {

			int currentLevelSize = q.size();
			int cur_loc = 0;

			string tmp_str1 = template_str, tmp_str2 = template_str;//1为节点所在行，2为其下一行


			for (int i = 1; i <= currentLevelSize; ++i) {

				auto node = q.front();
				q.pop();
				cur_loc = first_locations[node];

				// 父节点信息
				string addmessage = node->parent ? to_string(node->parent->Element) : "null";

				string num_str = to_string(node->Element) 
					+ "(" + addmessage + ")";


				//左边，如果存在左孩子，那么在第二行对应位置打印'/'，在第一行补上'_'
				if (node->left) {
					q.push(node->left);

					int first_loc = first_locations[node->left] + 1;
					tmp_str2[first_loc++] = '/';
					
					while (first_loc < cur_loc )
						tmp_str1[first_loc++] = '_';
				}


	//			中间,对应位置打印节点值（有可能为多位数）
				for (int j = 0; j < num_str.length(); ++j) {
					tmp_str1[cur_loc++] = num_str[j];
				}


				//右边，如果存在右孩子，那么在第二行对应位置打印'\'，在第一行补上'_'
				if (node->right) {
					q.push(node->right);

					int last_loc = first_locations[node->right] - 1;
					tmp_str2[last_loc] = '\\';

					while (cur_loc < last_loc) {
						tmp_str1[cur_loc++] = '_';
					}
				}

			}


			//打印两行
			std::cout << tmp_str1 << std::endl;
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

	// 删除节点

	void remove(T ele) {

		if (BSTSearch(m_root, ele) == NULL) return;

		remove(BSTSearch(m_root, ele));
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
			}
			else if (node == node->parent->left) {
				node->parent->left = replacement;
				delete node;
				node = NULL;
			}
			else { // node == node.parent.right
				node->parent->right = replacement;
				delete node;
				node = NULL;
			}

		}
		else if (node->parent == NULL) { // node是叶子节点并且是根节点
			delete node;
			node = NULL;
		}
		else if (node == node->parent->left) {
			node->parent->left = NULL;
			delete node;
			node = NULL;
		}
		else { // node == node.parent.right
			node->parent->right = NULL;
			delete node;
			node = NULL;
		}

		m_size--;
	}

	// 度为2的节点预处理
	void remove(Node<T>* node) {

		if (node->Have2Children())  // 删除两度点： 替换元素，等价为删除1/0度点
		{
			Node<T>* prenode = predecessor(node);  // 删除两度点时候用前驱节点替代
			node->Element = prenode->Element;
			remove1(prenode);    // 注意，不可node = prenode
		}
		else  remove1(node);

	}


		//if (node->IsLeaf()) {  // 删除0度点

		//	if (node->parent == NULL)
		//	{
		//		delete m_root;   // 删除单独根节点
		//		m_root = NULL;
		//		return temp;

		//	} else if (node->parent->left == node) {  // 删除的节点是左节点

		//		node->parent->left = deleNode;

		//	} else {  // 删除的节点是右节点

		//		node->parent->right = deleNode;

		//	}

		//	node->parent = NULL;
		//	
		//}
		//else { // 一度节点
		//	if (node->parent == NULL) {
		//	
		//		m_root = deleNode;
		//		deleNode->parent = NULL;

		//	}

		//	else if (node->parent->left = node) {

		//		node->parent->left = deleNode;
		//		deleNode->parent = node->parent;
		//	
		//	}
		//	else {

		//		node->parent->right = deleNode;
		//		deleNode->parent = node->parent;

		//	}
		//}
		//delete node;
		//node = NULL;
		//m_size--;

private:

	int m_size;
	Node<T>* m_root;  //根节点

	Operate m_op;  //操作器：对遍历的数据进行自定义操作
	Compare compare;  //比较器：实现不同类型数据的比较操作
};


template<class T>
std::ostream& operator << (std::ostream& out, BinarySearchTree<T>& bst)
{
	bst.PrintTree(out);
	return out;
}