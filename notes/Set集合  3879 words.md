**学完红黑树，我们已经把基本数据结构单元学完了。利用这些基本数据结构单元，我们可以改装为其他复合数据结构。接下来介绍Set和Map，这两种树结构都是基于链表或数组实现的，只需要拿以前的代码进行改装就行了。**





# Set集合

  我们以前高中数学就学过集合。集合内元素有三大特性： 确定性、互异性、无序性。前面学的链表、动态数组、各种树都没有强调数据的互异性，即一个容器内可以添加很多个相同元素。但是想想我们生活中有很多地方是需要用到去重容器的，比如计算一个文本中有多少单词、网站有多少个访问ip等。但是这些容器的基本操作和以前我们学过的那些数据结构几乎保持一致，所以我们只需要在前面那些数据结构上进行改进，使得原来那些容器有去重功能就好了。
    去重的关键在于添加，当添加时我们检测到添加的元素已经存在，则不用执行此操作。
    
接下来分析Set实现：
    

```cpp
#pragma once
#include"LinkedList.h"
#include"Operate.h"

template<class T>
class Set
{
public:
	Operate m_op;

	Set() {
		
	}

	virtual int size() = 0;

	virtual bool isEmpty() = 0;

	virtual void clear() = 0;

	virtual bool Contains(T Ele) = 0;


	virtual void add(T Ele) = 0;


	virtual void remove(T Ele) = 0;


	virtual void traversal() = 0;

};
```
我的思路是先建立一个Set抽象基类，然后用两个子类分别实现以链表为底层的LinkSet和以红黑树为底层的TreeSet。
**这两种实现可以利用声明私有成员实现：**
++LinkedList<T>* list = new LinkedList<T>;
RBTree<T>* tree = new RBTree<T>;++
外面看来我们用的是Set，但是数据实际上存在list和tree中，相关的操作也是基于我们以前写好的链表和红黑树操作实现的。


```cpp
// ListSet 实现
#pragma once
#include"LinkedList.h"
#include"Set.h"

template<class T>
class ListSet : public Set<T>
{
public:
	LinkedList<T>* list = new LinkedList<T>;

	//ListSet() {
	//	list = new LinkedList<T>;
	//}

	int size()
	{
		return list->size();
	}

	bool isEmpty()
	{
		return list->isEmpty();
	}

	void clear()
	{
		list->clear();
	}



	bool Contains(T Ele)
	{
		return list->contains(Ele);
	}


	void add(T Ele)
	{
		if (list->contains(Ele)) return;

		list->add(Ele);
	}


	void remove(T Ele)
	{
		cout << "删除集合中元素： " << Ele << endl;
		list->Dele_ForElement(Ele);
	}


	void traversal()
	{
		this->m_op.state = false;
		cout << "链式集合： "; 
		int size = list->size();
		for (int i = 0; i < size; i++)
		{
			if (this->m_op.state == false) {
				this->m_op.state = this->m_op(list->get(i));
			}
			else {
				cout << endl;
				return;
			}
		}
		cout << endl;
		return;

	}

	int indexOf(T Ele)
	{
		return list->IndexOf(Ele);
	}
};


```


```cpp
#pragma once
#include"Set.h"
#include"RBTree.h"


template<class T>
class TreeSet : public Set<T>
{
public:
	RBTree<T>* tree = new RBTree<T>;


	int size()
	{
		return tree->size();
	}

	bool isEmpty()
	{
		return tree->IsEmpty();
	}

	void clear()
	{
		tree->clear();
	}



	bool Contains(T Ele)
	{
		return tree->Contains(Ele);
	}


	void add(T Ele)
	{
		tree->add(Ele);
	}


	void remove(T Ele)
	{
		cout << "删除集合中元素： " << Ele << endl;
		tree->remove(Ele);
	}


	void traversal()
	{
		cout << "红黑树集合： ";
		tree->inorder();

		cout << endl;

	}


};
```
上面的代码很简单，只是要注意链表集合实现遍历操作时用循环，而红黑树集合实现遍历可以用树的中序遍历（输出时默认排序，比较有意义）。

下图是set文件结构，里面除了set，linkset，treeset，其他头文件都是以前写过的，并且几乎没有改动，故不再描述，可以去以前那两个专题看看。

![image.png](https://s2.loli.net/2022/03/16/RKAmc3O9drIMaUX.png)





# Map

接下来看map，map叫作映射，注意map不是图而是映射。我们数学里学函数时，定义函数就是从一个集合到另一个集合的映射mapping。因此要描述清楚map，就需要两组数据，第一组我们叫作键key，第二组我们叫作值value。学过c++ stl就知道里面有一个数据结构就是map，我们需要给出key和value才能建立出一个映射。
我们详细分析如何用红黑树实现映射，毕竟stl的map也是用红黑树实现的。

## 分析
我们前面的树节点声明只有一个elemrnt，因此我们需要建立一个新的树节点才能支持map，这个新节点内部必须有两个数据key和value；构造函数也需要同时初始化key和value。节点内的其他操作和原来保持一致。
**注意此时我们声明模板类时有两个模板参数，分别为K,V。后面声明Node时注意写为Node<K,V>**

```cpp
/*
基于RBTree的Map：
1.建一个独特的节点，包含键值两个元素
2.添加时以key为比较因素，要求key是可比较的
3.每次更新节点都要同时更新key和value，new节点也要传入两个值
4.node查找也只基于key的比较
*/

template<class K, class V>
class Node {
public:

	K key;
	V value;
	Node* left;
	Node* right;
	Node* parent;

	bool color = RED;  // RBTree 特有属性

	Node() { }

	Node(K key,V value,Node* parent)
	{
		this->key = key;
		this->value = value;
		this->parent = parent;
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


	// 判断兄弟姐妹节点存在
	 // RBTree 特有属性
	bool IsSibling(Node* node)
	{
		if (node == NULL) {
			return false;
		}
		if (node->IsLeft() && node->parent->Have2Children()) return true;
		if (node->IsRight() && node->parent->Have2Children()) return true;

		return false;
	}

	// 得到兄弟姐妹节点
	 // RBTree 特有属性

	Node* Sibling()
	{
		if (IsLeft()) return this->parent->right;
		if (IsRight()) return this->parent->left;
		return NULL;
	}


	// get叔父节点
	 // RBTree 特有属性
	Node* Uncle()
	{
		return parent->Sibling();
	}
};
```

因为Node节点整体都变了，因此我们干脆直接不用继承关系实现红黑树了，毕竟节点不一样，代码不能共用。**我们从原来红黑树的代码中复制一些代码到我们新建立的TreeMap类中，构建一个新类。**
下面是我们东拼西凑写出来的map类，底层是基于红黑树的：

```cpp
#pragma once

#include<string>
#include<queue>
#include"Operate.h"
#include"Compare.h"


#define RED false
#define BLACK true


/*
基于RBTree的Map：
1.建一个独特的节点，包含键值两个元素
2.添加时以key为比较因素，要求key是可比较的
3.每次更新节点都要同时更新key和value，new节点也要传入两个值
4.node查找也只基于key的比较
*/

template<class K, class V>
class Node {
public:

	K key;
	V value;
	Node* left;
	Node* right;
	Node* parent;

	bool color = RED;  // RBTree 特有属性

	Node() { }

	Node(K key,V value,Node* parent)
	{
		this->key = key;
		this->value = value;
		this->parent = parent;
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


	// 判断兄弟姐妹节点存在
	 // RBTree 特有属性
	bool IsSibling(Node* node)
	{
		if (node == NULL) {
			return false;
		}
		if (node->IsLeft() && node->parent->Have2Children()) return true;
		if (node->IsRight() && node->parent->Have2Children()) return true;

		return false;
	}

	// 得到兄弟姐妹节点
	 // RBTree 特有属性

	Node* Sibling()
	{
		if (IsLeft()) return this->parent->right;
		if (IsRight()) return this->parent->left;
		return NULL;
	}


	// get叔父节点
	 // RBTree 特有属性
	Node* Uncle()
	{
		return parent->Sibling();
	}
};



template<class K, class V>
class TreeMap : private Node<K, V>
{

private:
	int m_size;
	Node<K, V>* m_root;  //根节点
	Operate m_op;  //操作器：对遍历的数据进行自定义操作
	Compare m_compare;  //比较器：实现不同类型数据的比较操作

public:

	TreeMap() {
		m_size = 0;
		m_root = NULL;
	}


	int size()
	{
		return m_size;
	}

	bool isEmpty()
	{
		return m_size == 0;
	}

	void clear() {
		m_size = 0;
		m_root = NULL;
	}


	V add(K key, V value) {

		if (this->m_root == NULL) {
			Node<K, V>* NewNode = new Node<K, V>(key, value, NULL);
			this->m_root = NewNode;
			this->m_size++;
			black(this->m_root);
			return NULL;
		}

		int cmp = 0;
		Node<K, V>* node = this->m_root;
		Node<K, V>* parent = this->m_root;

		while (node != NULL) {

			cmp = m_compare(key, node->key); //记录最后一次是左还是右

			parent = node; // 记录最后一次的parent节点
			if (cmp > 0) {
				node = node->right;
			}
			else if (cmp < 0) {
				node = node->left;
			}
			else {
				V oldValue = node->value;
				node->value = value;
				return oldValue;
			}
		}

		Node<K, V>* NewNode = new Node<K, V>(key, value, parent);
		if (cmp > 0) {
			parent->right = NewNode;
		}
		else if (cmp < 0) {
			parent->left = NewNode;
		}
		this->m_size++;

		afterAdd(NewNode);
		return NULL;
	}



	V get(K key) {
		return node(key)->value;
	}

	V remove(K key) {

		Node<K,V>* deleNode = node(key);
		if (deleNode == NULL) return NULL;

		return remove2(deleNode);
	}



	bool containsKey(K key) {
		return node(key) != NULL;
	}


	bool containsValue(V value) {
		if (m_root == NULL) return false;

		queue<Node<K,V>*> que;
		que.push(m_root);
		
		while (!que.empty()) {
			Node<K, V>* eleNode = que.front();
			V val = eleNode->value;
			que.pop();  // c++ 和 Java差异： pop函数没有返回值！

			if (val == value) return true;

			if (eleNode->left != NULL) que.push(eleNode->left);
			if (eleNode->right != NULL) que.push(eleNode->right);
		}

		return false;
	}


	void traversal() {
		//刷新状态
		m_op.state = false;
		inorder(m_root);

		printf("\n");
	}

	void setMode()
	{
		int newMode = 1;
		m_op.setMode(newMode);
	}

/*以下是基于红黑树的代码*/
private:

	// 	***用于删除度为1和度为0的节点
	V remove1(Node<K, V>* node) {

		Node<K, V>* replacement = (node->left != NULL ? node->left : node->right);

		if (replacement != NULL)
			replacement->parent = node->parent;

		if (node->parent == NULL) {
			Node<K, V>* temp = this->m_root;
			this->m_root = replacement;
			this->afterRemove(this->m_root, replacement);
			V oldValue = temp->value;
			delete temp;
			return oldValue;
		}
		else if (node == node->parent->left) {
			node->parent->left = replacement;
		}
		else {
			node->parent->right = replacement;
		}

		//	node销毁之前做运算
		this->afterRemove(node, replacement);

		V oldValue = node->value;
		delete node;
		node = NULL;
		this->m_size--;

		return oldValue;
	}

	// 度为2的节点预处理
	V remove2(Node<K, V>* node) {

		if (node->Have2Children())  // 删除两度点： 替换元素，等价为删除1/0度点
		{
			Node<K, V>* sucnode = this->successor(node);
			node->key = sucnode->key;
			node->value = sucnode->value;
			return remove1(sucnode);    // 注意，不可node = prenode
		}
		else  return remove1(node);
	}

	void inorder(Node<K,V>* node)
	{
		if (node == NULL || m_op.state) return;

		inorder(node->left);

		if (m_op.state)  return;
		m_op.state = m_op(node->key, node->value);

		inorder(node->right);
	}


	Node<K,V>* successor(Node<K,V>* node)
	{
		if (node == NULL)  return NULL;

		Node<K, V>* rightnode = node->right;
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


	Node<K, V>* node(K key)
	{
		Node<K, V>* node = this->m_root;

		while (node != NULL)
		{
			int cmp = m_compare(key, node->key);

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



	void afterAdd(Node<K,V>* node) {

		Node<K, V>* parent = node->parent;

		if (parent == NULL) {
			black(node);
			return;
		}

		Node<K, V>* grand = parent->parent;

		if (isBlack(parent) || grand == NULL) return;

		Node<K, V>* uncle = parent->Sibling();

		if (isRed(uncle)) {
		
			black(parent);
			black(uncle);

		
			red(grand);
			afterAdd(grand);
			
			return;
		}

		if (parent->IsLeft()) { 
			red(grand);
			if (node->IsLeft()) { 
				this->black(parent);
			}
			else { 
				this->black(node);
				rotateLeft(parent);

			}
			rotateRight(grand);
		}
		else { 
			red(grand);
			if (node->IsLeft()) { 
				this->black(node);
				rotateRight(parent);

			}
			else {
				black(parent);
			}
			rotateLeft(grand);
		}

	}



	 void afterRemove(Node<K, V>* node, Node<K, V>* replacement) {
		if (node == NULL) return;

		if (isRed(node)) {
			return;
		}

		if (isRed(replacement)) {
			black(replacement);
			return;
		}

		Node<K, V>* parent = node->parent;
		if (!parent) return;

	
		bool left = parent->left == NULL || node->IsLeft();
		Node<K, V>* sibling = left ? parent->right : parent->left;
		if (left) {
			if (isRed(sibling)) {
				
				red(parent);
				black(sibling);
				rotateLeft(parent);

				sibling = parent->right;
			}  

			if (red(sibling->left) || red(sibling->right))
			{
				
				if (isBlack(sibling->right)) {
					rotateRight(sibling);
					sibling = parent->right;
				}
				
				color(sibling, colorOf(parent));
				black(parent);
				black(sibling->right);
				
				rotateLeft(parent);
			}
			else {

				black(parent);
				red(sibling);
				if (isBlack(parent)) {
					afterRemove(parent, NULL);
				}
			}

		}
		else {  
			if (isRed(sibling)) {
			
				red(parent);
				black(sibling);
				rotateRight(parent);

				sibling = parent->left;
			} 

			if (red(sibling->left) || red(sibling->right))
			{
			
				if (isBlack(sibling->left)) {
					rotateLeft(sibling);
					sibling = parent->left;
				}
				
				color(sibling, colorOf(parent));
				black(parent);
				black(sibling->left);
		
				rotateRight(parent);
			}
			else {

				black(parent);
				red(sibling);
				if (isBlack(parent)) {
					afterRemove(parent, NULL);
				}
			}
		}


	}

	
	void rotateRight(Node<K, V>* grand)
	{
		Node<K, V>* parent = grand->left;
		Node<K, V>* child = parent->right;

		grand->left = parent->right;
		parent->right = grand;

		afterRotate(grand, parent, child);
	}

	 void rotateLeft(Node<K, V>* grand)
	{
		Node<K, V>* parent = grand->right;
		Node<K, V>* child = parent->left;

		grand->right = parent->left;
		parent->left = grand;

		afterRotate(grand, parent, child);
	}


	 void afterRotate(Node<K, V>* grand, Node<K, V>* parent, Node<K, V>* child)
	{
		
		parent->parent = grand->parent;
		if (grand->IsLeft()) {
			grand->parent->left = parent;
		}
		else if (grand->IsRight()) {
			grand->parent->right = parent;
		}
		else {
			m_root = parent;
		}

		
		grand->parent = parent;

		
		if (child != NULL) {
			child->parent = grand;
		}
	}

     Node<K, V>* color(Node<K, V>* node, bool color) {
		if (node == NULL) {
			return node;
		}

		node->color = color;
		return node;
	}

	 Node<K, V>* red(Node<K, V>* node) {
		return color(node, RED);
	}

	 Node<K, V>* black(Node<K, V>* node) {
		return color(node, BLACK);
	}


	 bool colorOf(Node<K, V>* node) {
		return (node == NULL) ? BLACK : node->color;
	}

	 bool isBlack(Node<K, V>* node) {
		return colorOf(node) == BLACK;
	}

	 bool isRed(Node<K, V>* node) {
		return colorOf(node) == RED;
	}

	 bool isBalanced(Node<K, V>* node) {
		return abs(node->balanceFactor()) <= 1;
	}


};
```

大体看一下，map对外的接口如下，我们把这些函数在TreeMap类中声明为public，使外界可以直接调用。

```cpp
template<class K,class V>
class Map {
public:

	virtual int size() = 0;
	virtual bool isEmpty() = 0;
	virtual void clear() = 0;

	virtual V add(K key, V value) = 0;
	virtual V get(K key) = 0;
	virtual V remove(K key) = 0;
	virtual bool containsKey(K key) = 0;
	virtual bool containsValue(V value) = 0;

	virtual void traversal() = 0;
};
```
![image.png](https://s2.loli.net/2022/03/16/U1ORyKHZ9Cp3eBj.png)





上图显示出我们构建TreeMap需要的内容，我们从以前的代码中直接复制过来就行了。

单独拿出下面主要操作，注意传入的参数是key，所以我们以前的一些代码都要改一改，比如node函数，现在要 传入key找到对应节点。找到节点后我们就可以再访问节点的value。
**注意：
1.原来函数的所有节点更换为新节点
2.注意添加和删除时同时更新key和value**



```cpp
	V get(K key) {
		return node(key)->value;
	}

	V remove(K key) {

		Node<K,V>* deleNode = node(key);
		if (deleNode == NULL) return NULL;

		return remove2(deleNode);
	}



	bool containsKey(K key) {
		return node(key) != NULL;
	}


	bool containsValue(V value) {
		if (m_root == NULL) return false;

		queue<Node<K,V>*> que;
		que.push(m_root);
		
		while (!que.empty()) {
			Node<K, V>* eleNode = que.front();
			V val = eleNode->value;
			que.pop();  // c++ 和 Java差异： pop函数没有返回值！

			if (val == value) return true;

			if (eleNode->left != NULL) que.push(eleNode->left);
			if (eleNode->right != NULL) que.push(eleNode->right);
		}

		return false;
	}


	void traversal() {
		//刷新状态
		m_op.state = false;
		inorder(m_root);

		printf("\n");
	}
```

想在再想想以前的set，我们会发现set是可以基于map建立的，只需要让**键=值**就行了，map的key和value 就是一个set。
下面基于TreeMap建立TreeSet。


```cpp
#pragma once
#include"TreeMap.h"

template<class T>
class TreeSet
{
private:
	TreeMap<T, T>* map;

public:
	TreeSet() {
		map = new TreeMap<T, T>;
	}

	int size()
	{
		return map->size();
	}

	bool isEmpty()
	{
		return map->isEmpty();
	}

	void clear()
	{
		map->clear();
	}

	bool contains(T Ele)
	{
		return map->containsKey(ELe);
	}


	void add(T Ele)
	{
		map->add(Ele, Ele);
	}


	T remove(T Ele)
	{


		return map->remove(Ele);
	}

	void traverse()
	{
		map->setMode();
		map->traversal();
	}

};
```
看完代码会发现这个版本的TreeSet的遍历操作使用了一个setmode函数，这是一个TreeMap里面新加入的函数，目的是设置Operate类的对象中的模式为1， 进行模式1下的操作。
因此我们进行了如下进改进：

下面是我们operate类的改进实现：**加入了mode变量和setmode函数用于默认设置mode为0； 仿函数内部新增加了模式1， 用于TreeMap为底层的TreeSet的遍历输出。**

```c++
#pragma once

/*
操作函数-仿函数
- 添加不同数据类型的操作
- 模式选择  mode0默认输出操作
- 自由改变遍历停止节点
*/
class Operate
{
private:
	int mode;

public:
	bool state;
	Operate() { state = false; }

	//template<class K>
	//bool operator()(K key)
	//{
	//		std::cout << key << ' ';
	//		return (key == 99) ? true : false;
	//}

	/*设置遍历模式*/
	void setMode(int myMode = 0)
	{
		mode = myMode;
	}

	template<class K,class V>
	bool operator()(K key, V value)
	{
		if (mode == 0) {
			std::cout << key << '_' << value << ' ';

			return (key == 99) ? true : false;
		}
		else if (mode == 1)
		{
			std::cout << key << ' ';

			return (key == 99) ? true : false;
		}
		else return false;
	}
};
```

然后给TreeMap 加一个函数：用来设置模式1

```c++
	void setMode()
	{
		int newMode = 1;
		m_op.setMode(newMode);
	}
```
只要TreeMap成员调用这个函数，其之后调用遍历的操作就是模式1。
此时用TreeMap实现的TreeSet内部遍历代码就是：

```c++
 void traverse()
 {
		map->setMode();
		map->traversal();
	}
```



c++和java官方都是使用TreeMap实现TreeSet，然后TreeMap的代码实现是从红黑树。因为如果使用继承于链表或红黑树的Set，此时的文件结构非常臃肿，如果使用TreeMap则文件结构就很清晰了。

![image.png](https://s2.loli.net/2022/02/09/vD9JaHpCQElZdGB.png)

下面是使用红黑树TreeMap为底层的TreeSet：

![image.png](https://s2.loli.net/2022/02/09/JtF8jv7AMcCm396.png)



  用红黑树实现map使得添加删除查询操作的时间复杂度都是O(logn)级别，但是存在限制：key必须是可比较的数据。如果现在key是任意的，则我们应该用什么存放key呢？在java中这就需要使用hash table来实现map了，而c++因为数据类型不是类所以不能是任意类型。

   使用hashmap、unorderedmap的好处就是查找的时间复杂度为O(1),直接使用索引映射。