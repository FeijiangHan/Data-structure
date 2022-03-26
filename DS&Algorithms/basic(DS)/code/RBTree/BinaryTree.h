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

	// �ж�����
	bool IsLeft()
	{
		return (parent != NULL && this == parent->left);
	}

	bool IsRight()
	{
		return (parent != NULL && this == parent->right);
	}

	// ���¸߶�
	void updateHeight() {
		int leftHeight = left == NULL ? 0 : left->height;
		int rightHeight = right == NULL ? 0 : right->height;
		height = 1 + max(leftHeight, rightHeight);
	}


	// ƽ������

	int balanceFactor() {
		int leftHeight = left == NULL ? 0 : left->height;
		int rightHeight = right == NULL ? 0 : right->height;
		return leftHeight - rightHeight;
	}

	// �������
	// ���ݲ�ƽ���õ����ڵ��node��������֪��������תģʽ��
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
	Node<T>* m_root;  //���ڵ�
	Operate m_op;  //���������Ա��������ݽ����Զ������


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

		inorderTraversal(node->left, v);

		v.push_back(node);

		inorderTraversal(node->right, v);
	}

	//**�������**//
	void PrintNodeByLevel( )
	{
		PrintNodeByLevel(m_root);
	}

	void PrintNodeByLevel(Node<T>* rnode) {
		if (rnode == NULL) {
			cout << "������" << endl;
			return;
		}

		vector<Node<T>*> intv;

		inorderTraversal(rnode, intv);//��������ڵ�����
		string template_str;//ģ��string����ʾÿ�д�ӡstring�ĳ���

		int location = 0;

		typedef unordered_map<Node<T>*, int> hashmap;
		hashmap first_locations;//�洢�ڵ��Ӧ�ڱ���string�е���λ��


		for (auto& i : intv) {

			location = template_str.size();

			template_str += to_string(i->Element) + "    ";

			first_locations[i] = location;
		}


		for (auto& i : template_str)  i = '    ';//��ģ��ȫ����Ϊ�ո񷽱����ʹ��


		//�������
		queue<Node<T>*> q;
		q.push(rnode);

		while (!q.empty()) {

			int currentLevelSize = q.size();
			int cur_loc = 0;

			string tmp_str1 = template_str, tmp_str2 = template_str,
				   tmp_str3 = template_str,
				   tmp_str4 = template_str,
				   tmp_str5 = template_str;//1Ϊ�ڵ������У�2Ϊ����һ��


			for (int i = 1; i <= currentLevelSize; ++i) {

				auto node = q.front();
				q.pop();
				cur_loc = first_locations[node];

				// ���ڵ���Ϣ
				string addmessage1 = node->parent ? to_string(node->parent->Element) : "null";
				string addmessage2 = to_string(hight(node));
				string addmessage3 = to_string(node->balanceFactor());

				string num_str = to_string(node->Element);
				//string appendMessage1 =	"P[" + addmessage1 + "]";
				string appendMessage1 = "H{" + addmessage2 + "}";
				 //string appendMessage1 = "B:" + addmessage3 ;


				//��ߣ�����������ӣ���ô�ڵڶ��ж�Ӧλ�ô�ӡ'/'���ڵ�һ�в���'_'
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


				//			�м�,��Ӧλ�ô�ӡ�ڵ�ֵ���п���Ϊ��λ����
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


				//�ұߣ���������Һ��ӣ���ô�ڵڶ��ж�Ӧλ�ô�ӡ'\'���ڵ�һ�в���'_'
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

};
