# trie前缀树

   Trie树，又称单词查找树或键树，是一种树形结构，是一种哈希树的变种。典型应用是用于统计和排序大量的字符串（但不仅限于字符串），所以经常被**搜索引擎系统用于文本词频统计**。它的优点是：**最大限度地减少无谓的字符串比较，查询效率比哈希表高**。

   ![image-20220316172919490](https://s2.loli.net/2022/03/16/2yRHjvqaxoWOkie.png)

比如上图，如果是普通树储存单词的话，查找does这个单词，需要从cat开始对每个节点的单词遍历，cat要和does比较，dog要和does比较，doggy要和does比较，最终才能比较出结果。这个过程中有很多重复的比较：因为字符串的比较是一个字符一个字符进行的，因此does和do、does、doggy比较其实都需要有‘d’和‘o’这两个字符的比较。在前缀树中，只需要比较一次 ‘d'和’o'，因此减少了多余的字符比较次数。



  就拿统计单词数量来说，首先要查到单词，然后每次查询都要给这个单词的数量加一，因此想让trie树可以保存一些字符串->值的对应关系。基本上，它跟 Java 的 HashMap 功能相同，都是 key-value 映射，只不过 Trie 的 key 只能是字符串。

  Trie 的强大之处就在于它的时间复杂度。它的插入和查询时间复杂度都为 O(k) ，其中 k 为 key 的长度，与 Trie 中保存了多少个元素无关。**Trie的核心思想是空间换时间。利用字符串的公共前缀来降低查询时间的开销以达到提高效率的目的。**

**Trie树的基本性质**可以归纳为：
（1）根节点不包含字符，除根节点意外每个节点只包含一个字符。
（2）从根节点到某一个节点，路径上经过的字符连接起来，为该节点对应的字符串。
（3）每个节点的所有子节点包含的字符串不相同。
**Trie树特性**：
1）根节点不包含字符，除根节点外每一个节点都只包含一个字符。
2）从根节点到某一节点，路径上经过的字符连接起来，为该节点对应的字符串。
3）每个节点的所有子节点包含的字符都不相同。
4）如果字符的种数为n，则每个结点的出度为n，这也是空间换时间的体现，浪费了很多的空间。
5）插入查找的复杂度为O(n)，n为字符串长度。

## 应用场景

  大文本单词数量统计。

## 结构图解：

  因为查询并统计单词的需求，我们想让trie树能够在每个单词的节点出储存单词的频率，所以使用hashmap（unordered_map）来构建trie树，因为hashmap可以通过键值去找到数值，这里键值就是单词，数值就是单词出现次数。

<img src="https://s2.loli.net/2022/03/16/v9oItC4Dg5PTjEh.png" alt="image-20220316171805176" style=";" />





## 代码实现

```cpp
#pragma once
#include<unordered_map>
#include<string>
#include<iostream>
#include<cassert>
using namespace std;

// 单词节点
template<class T>
struct Node 
{
    // 内置map，根据char找到下一个Node，命名为children代表的就是子节点
	unordered_map<char, Node*> children;
	T value; // 单词对应的储存数值
	char c; // 上一个节点通过c找到了这个节点，就让这个节点储存c
	bool color; // 标识存在
	Node* parent; // 指向父节点的指针

	Node() {}
	Node(char c ,Node* p) {
		this->c = c;
		this->children = {};
		this->parent = p;
		this->color = false; // 默认为false
	}
};


template<class T>
class Trie : private Node<T>
{
private:
	Node<T>* root; // 需要一个不存放有效数据的根节点,当然也可以存放单词总数量
	int m_size; 
	
public:

	int size()
	{
		return m_size;
	}


	bool empty()
	{
		return m_size == 0;
	}
    
    
// 根据字符串你找到最后一个字符的节点
	Node<T>* node(string str)
	{
		StrCheck(str);

		int len = str.size();
		Node<T>* node = root;
		for (auto it : str) {
            // 如果node是空的（可能是未添加任何元素是进行查找操作），或者node内置的hashmap中没有键值为it，此时返回空，代表未找到
			if (node == nullptr || node->children.count(it) == 0) return nullptr;
			node = node->children[it];
		}
		return node;
	}


        
// 查找单词是否存在：保证存在节点且为染色状态
	bool contains(string str)
	{
		Node<T>* endNode = node(str);
		return ((endNode != nullptr) && (endNode->color));
	}
    

// 获取单词对应的数值
T get(string str)
	{
        return contains(str) == nullptr ? -1 : node(str);
	}  
    
    
// 查找是否存在某个前缀：只需保证节点存在即可
	bool findPrefix(string prefix)
	{
		return node(prefix) != nullptr;
	}
    
    
  
 
// 检测空字符串，不能添加空单词
	void StrCheck(string str) {
		assert(!str.empty());
		if (str.empty())
		{
			throw exception("str is empty!");
		}
	} 

// 添加给定字符串，
// 并在最后一个字符处用color标记已添加此字符串,
// 并且在最后一个字符处用储存此字符串对应的数值value
// 如果单词已经存在，添加操作只能修改单词数值，返回值为原来的旧值；如果原来单词不存在，添加操作返回-1
	T add(string str,T val)
	{
		StrCheck(str);

		if (root == nullptr)
		{
			root = new Node<T>;
		}

	// 找到字符串对应的最后一个节点
		Node<T>* node = root;
		for (auto it : str)
		{
   // 找到字符串中不存在于trie的字符并以新节点的方式加入
            // 判断： 字符it是否为node内置hashmap的键值，如果是则代表这个字符以前添加过了无须再添加，否则就添加
			if (node->children.count(it) == 0) { // node->children.find(it) == node->children.end()
				Node<T>* childNode = new Node<T>(it,node); // 新的Node节点，内涵字符为it，父亲节点为node
				node->children[it] = childNode; // 给node内置的hashmap添加一个pair<it,childNode>，意思是通过it可以找到的下一个Node为childNode
			}

			node = node->children[it]; // 根据node内置hashMap的键值it找到下一个Node节点。
		}

		// 已经存在此单词，只修改其value
		// 如果不需要储存val，就直接让color为true即可，不需要讨论
		if (node->color) {
			T oldVal = node->value;
			node->value = val;
			return oldVal;
		}
        
        // 如果以前不存在，就让color为true使其存在
		node->color = true;
		node->value = val;
		m_size++;
		return -1;
	}

    
    

   // 删除某个单词
	T remove(string word)
	{
		// 找到最后一个节点
		Node<T>* deNode = node(word);
        
		// 不是结尾（只有被color为true才可以认为添加成功）
		if (deNode == nullptr || deNode->color == false)
		{
			cerr << "未找到字符串" << endl;
			return NULL;
		}
	
		T oldVal = deNode->value;
		// if还有子节点，代表这个单词节点是其他单词节点路径上的一个节点，此时无需删除只需把颜色去掉代表未添加即可。
        // 因为删除的话会影响其他单词
		if (!deNode->children.empty())
		{
			deNode->color = false;
			deNode->value = NULL;
			return oldVal;
		}

		// 没有子节点
		Node<T>* parent = nullptr;
        // parent从删除节点的父亲节点还是往上走
		while ((parent = deNode->parent) != nullptr)
		{
			parent->children.erase(deNode->c); // 删除hashmap中字符c对应的节点
            
             // 遇到多重分支或者parent就是单词节点时退出循环停止删除
             // 可能1： 链状删除，直到遇到染色节点停止删除
             // 可能2： 删除过程中没有遇到染色节点，但是遇到了分支根节点，也要停止删除
             // 这两种情况都代表这这个节点还用在别的单词中，不能删除
			if (parent->children.size() > 0 || parent->color) break;
			deNode = parent; // 更新待删除节点
		}

		this->m_size--;
		return oldVal;
	}



};
```

