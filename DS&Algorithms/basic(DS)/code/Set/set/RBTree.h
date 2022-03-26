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

	//添加
	void add(T Ele)
	{
		//添加第一个节点
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

		// red(node);  大离谱了家人们，多写了这句短短的代码让我找了半个小时bug
	
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
		//black(this->m_root);

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

		if (replacement != NULL)
			replacement->parent = node->parent;

			// 更改parent的left、right的指向
			if (node->parent == NULL) {  // node是度为1的节点并且是根节点
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

		//	node销毁之前做运算
		this->afterRemove(node, replacement);

		delete node;
		node = NULL;
		this->m_size--;
	}




	// 度为2的节点预处理
	void remove(Node<T>* node) {

		if (node->Have2Children())  // 删除两度点： 替换元素，等价为删除1/0度点
		{
			Node<T>* sucnode = this->successor(node);
			node->Element = sucnode->Element;
			remove1(sucnode);    // 注意，不可node = prenode
		}
		else  remove1(node);
	}


//*****************************AVLTree*************************************//

	void afterAdd(Node<T>* node) {

		Node<T>* parent = node->parent;
		// 第一次添加根节点或者grand上溢到根节点

		if (parent == NULL) {
			black(node);
			return;
		}

		Node<T>* grand = parent->parent;

		// 1.添加到黑色节点
		if (isBlack(parent) || grand == NULL) return;

		Node<T>* uncle = parent->Sibling();

		if (isRed(uncle)) {
			// 3.添加到红色节点，且红色节点的uncle是红色节点
			black(parent);
			black(uncle);

			/*grand染成红色，当做新节点进行处理*/
			red(grand);
			afterAdd(grand);
			// 把祖父节点染红后当做新节点上溢到上一层
			return;
		}
	

			// 2.添加到红色节点，且红色节点的uncle是null（黑色）
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

		//1.删除红色节点

		//2.删除2度黑色点

		//3.删除1度黑色点

		/*删除黑色叶子节点 -- 下溢出 */
		//4.兄弟是红色

		//5.兄弟是黑色---
 		               // a、有红色子节点  
					  
		               // b、无红色子节点
		                      // parent是红色，是黑色

		if (isRed(node)) {
			return;
		}

		if (isRed(replacement)) {
			black(replacement);
			return;
		}

		Node<T>* parent = node->parent;
		if (!parent) return;



		// 对于0度黑色节点分析
		bool left = parent->left == NULL || node->IsLeft();
		Node<T>* sibling = left ? parent->right : parent->left;

		if (left) {
			if (isRed(sibling)) {
				/*父亲染红，兄弟染黑，右旋转父亲节点，刷新兄弟*/
				red(parent);
				black(sibling);
				rotateLeft(parent);

				sibling = parent->right;
			}  //  此操作之后，变为兄弟为黑的情况

			if (red(sibling->left) || red(sibling->right))
			{
				/*对于右边删节点，有三种情况，其中LR左旋转后转换为LL，注意旋转后更新sibling*/
				if (isBlack(sibling->right)) {
					rotateRight(sibling);
					sibling = parent->right;
				}
				// LR之后所有情况都视为LL
				color(sibling, colorOf(parent));
				black(parent);
				black(sibling->right);
				/*先染色再旋转：sibling和原先parent颜色一致，旋转后两个子节点都染成黑色*/
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
		else {  // 待删除黑色叶子节点在右边
			if (isRed(sibling)) {
				/*父亲染红，兄弟染黑，右旋转父亲节点，刷新兄弟*/
				red(parent); 
				black(sibling);
				rotateRight(parent);

				sibling = parent->left;
			}  //  此操作之后，变为兄弟为黑的情况

			if (red(sibling->left) || red(sibling->right))
			{
				/*对于右边删节点，有三种情况，其中LR左旋转后转换为LL，注意旋转后更新sibling*/
				if (isBlack(sibling->left)) {
					rotateLeft(sibling);
					sibling = parent->left;
				}
				// LR之后所有情况都视为LL
				color(sibling, colorOf(parent));
				black(parent);
				black(sibling->left);
				/*先染色再旋转：sibling和原先parent颜色一致，旋转后两个子节点都染成黑色*/
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




	// 单纯的两步实现旋转
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
	Compare compare;  //比较器：实现不同类型数据的比较操作
};