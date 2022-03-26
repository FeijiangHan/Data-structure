#pragma once
#include"BinarySearchTree.h"
#include<string>
#include<queue>

//  ************* ���ͼ�ζ����� *************
template<class T>
void output_impl(Node<T>* n, bool left, std::string & indent)
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
template<class T>
void Print_Recurrence(Node<T> * m_root)
{
	std::string begin = "";  // ��ʼ�ַ���

	if (m_root->right)
	{
		output_impl(m_root->right, false, begin);
	}

	std::cout << m_root->Element << std::endl;

	if (m_root->left)
	{
		output_impl(m_root->left, true, begin);
	}
	}
//  ***************************************


//**�������**//
template<class T>
void PrintNodeByLevel(Node*<T> m_root) {
    queue<Node<T>*> Q;
    queue<std::string> C; 

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
            while(C.size() != 0) {
                cout << C.front() << " ";
                C.pop();
            }
            Q.push(0);
            cout << endl;
        }
    } while (!Q.empty());
}