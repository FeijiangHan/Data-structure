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

		Node<T>* NewNode = new Node<T>(Ele, parent);
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


	void inorderTraversal(Node<T>* node, vector<Node<T>*>& v)
	{
		if (node == NULL) return;

		inorderTraversal(node->left,v);
		
		v.push_back(node);

		inorderTraversal(node->right,v);
	}

	//**�������**//
	void PrintNodeByLevel() {

		if (m_root == NULL) {
			cout << "������" << endl;
			return;
		}
		vector<Node<T>*> intv;

		inorderTraversal(m_root, intv);//��������ڵ�����
		string template_str;//ģ��string����ʾÿ�д�ӡstring�ĳ���
		
		int location = 0;

		typedef unordered_map<Node<T>*, int> hashmap;
		hashmap first_locations;//�洢�ڵ��Ӧ�ڱ���string�е���λ��
		
		
		for (auto& i : intv) {

			location = template_str.size();

			template_str += to_string(i->Element) + "    " ;

			first_locations[i] = location;
		}


		for (auto& i : template_str)  i = '    ';//��ģ��ȫ����Ϊ�ո񷽱����ʹ��


		//�������
		queue<Node<T>*> q;
		q.push(m_root);

		while (!q.empty()) {

			int currentLevelSize = q.size();
			int cur_loc = 0;

			string tmp_str1 = template_str, tmp_str2 = template_str;//1Ϊ�ڵ������У�2Ϊ����һ��


			for (int i = 1; i <= currentLevelSize; ++i) {

				auto node = q.front();
				q.pop();
				cur_loc = first_locations[node];

				// ���ڵ���Ϣ
				string addmessage = node->parent ? to_string(node->parent->Element) : "null";

				string num_str = to_string(node->Element) 
					+ "(" + addmessage + ")";


				//��ߣ�����������ӣ���ô�ڵڶ��ж�Ӧλ�ô�ӡ'/'���ڵ�һ�в���'_'
				if (node->left) {
					q.push(node->left);

					int first_loc = first_locations[node->left] + 1;
					tmp_str2[first_loc++] = '/';
					
					while (first_loc < cur_loc )
						tmp_str1[first_loc++] = '_';
				}


	//			�м�,��Ӧλ�ô�ӡ�ڵ�ֵ���п���Ϊ��λ����
				for (int j = 0; j < num_str.length(); ++j) {
					tmp_str1[cur_loc++] = num_str[j];
				}


				//�ұߣ���������Һ��ӣ���ô�ڵڶ��ж�Ӧλ�ô�ӡ'\'���ڵ�һ�в���'_'
				if (node->right) {
					q.push(node->right);

					int last_loc = first_locations[node->right] - 1;
					tmp_str2[last_loc] = '\\';

					while (cur_loc < last_loc) {
						tmp_str1[cur_loc++] = '_';
					}
				}

			}


			//��ӡ����
			std::cout << tmp_str1 << std::endl;
			std::cout << tmp_str2 << std::endl;
		}
	}




	//������ĸ߶�
	//****�ݹ�ʵ��
	void PrintHight()
	{
		cout << "������� , ���ĸ߶�Ϊ�� " << hight() << endl;
	}

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
			else {    //�� != 0 �� ==0--------�Ҳ�ȫ��Ҷ�ӣ���=0����=0 ------�Ҳ�ȫ��Ҷ��
				IsLeaf = true;
				if (n->left != NULL) que.push(n->left); // int data[] =  {6,3,8}; ͷ������-����-����Ԫ�ز����-ѭ������-true
			}

		} // end while
		return true;
	}

	// �Ľ��� ��д��������߼� ��ı�

	void PrintIsCompeteBinary()
	{
		if (IsCompeteBinary_promote()) cout << "������ϣ� ����ȫ������" << endl;
		if (!IsCompeteBinary_promote()) cout << "������ϣ� ������ȫ������" << endl;
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
			else IsLeaf = true;  // �� != 0 �� ==0--------�Ҳ�ȫ��Ҷ�ӣ���=0����=0 ------�Ҳ�ȫ��Ҷ��
		} // end while
		return true;
	}

	//****************************************************

	// ĳ�ڵ��ǰ���ڵ�
	Node<T>* predecessor(Node<T>* node)
	{
		if (node == NULL)  return NULL;

		Node<T>* leftnode = node->left;
		// ��������
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


	// ĳ�ڵ�ĺ�׺�ڵ�
	Node<T>* successor(Node<T>* node)
	{
		if (node == NULL)  return NULL;

		Node<T>* rightnode = node->right;
		// ��������
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

	// **************��ת������*************
	void VerseTree()
	{
		cout << "*****ʹ�õݹ�ǰ�������ת��******" << endl << endl;
		VerseTree(m_root);
	}

	// �ڵ�node���ָ��ľ��ǽ������ĸ��ڵ�
	void VerseTree(Node<T>* node)  // �ݹ�ʵ��
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
		cout << "*****ʹ�õ�����α�����ת��******" << endl << endl;
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

	// ɾ���ڵ�

	void remove(T ele) {

		if (BSTSearch(m_root, ele) == NULL) return;

		remove(BSTSearch(m_root, ele));
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
		else if (node->parent == NULL) { // node��Ҷ�ӽڵ㲢���Ǹ��ڵ�
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

	// ��Ϊ2�Ľڵ�Ԥ����
	void remove(Node<T>* node) {

		if (node->Have2Children())  // ɾ�����ȵ㣺 �滻Ԫ�أ��ȼ�Ϊɾ��1/0�ȵ�
		{
			Node<T>* prenode = predecessor(node);  // ɾ�����ȵ�ʱ����ǰ���ڵ����
			node->Element = prenode->Element;
			remove1(prenode);    // ע�⣬����node = prenode
		}
		else  remove1(node);

	}


		//if (node->IsLeaf()) {  // ɾ��0�ȵ�

		//	if (node->parent == NULL)
		//	{
		//		delete m_root;   // ɾ���������ڵ�
		//		m_root = NULL;
		//		return temp;

		//	} else if (node->parent->left == node) {  // ɾ���Ľڵ�����ڵ�

		//		node->parent->left = deleNode;

		//	} else {  // ɾ���Ľڵ����ҽڵ�

		//		node->parent->right = deleNode;

		//	}

		//	node->parent = NULL;
		//	
		//}
		//else { // һ�Ƚڵ�
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
	Node<T>* m_root;  //���ڵ�

	Operate m_op;  //���������Ա��������ݽ����Զ������
	Compare compare;  //�Ƚ�����ʵ�ֲ�ͬ�������ݵıȽϲ���
};


template<class T>
std::ostream& operator << (std::ostream& out, BinarySearchTree<T>& bst)
{
	bst.PrintTree(out);
	return out;
}