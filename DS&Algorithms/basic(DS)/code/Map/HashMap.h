#pragma once
#include<iostream>
#include<string>
#include<queue>
#include<vector>
#include<unordered_map>
#include"Operate.h"
#include"Compare.h"
using namespace std;
#define RED false
#define BLACK true

namespace FNV_1a {
	/*
	> **offset_basis：**初始的哈希值
	> **FNV_prime：**FNV用于散列的质数
	> **octet_of_data：**8位数据（即一个字节）

	 **FNV-1a描述：**
	hash = ***offset_basis
	for each octet_of_data to be hashed
	hash = hash xor octet_of_data
	hash = hash * FNV_prime
	return hash
	*/

	constexpr size_t offset_basis = 14695981039346656037ULL;  // 初始hash值
	constexpr size_t FNV_prime = 1099511628211ULL; // FNV用于散列的质数

	// accumulate range [_First, _First + _Count) into partial FNV-1a hash _Val
	_NODISCARD inline size_t fnv_64a_realize(const unsigned char* const Contents, const size_t _Count)
	{
		size_t hashVal = offset_basis;
		for (size_t _Idx = 0; _Idx < _Count; ++_Idx) {
			hashVal ^= static_cast<size_t>(Contents[_Idx]); // 8位数据（即一个字节）
			hashVal *= FNV_prime;
		}

		return hashVal;
	}


	template <class K>
	_NODISCARD size_t fnv_64a(const K& key) noexcept
	{
		return fnv_64a_realize(&reinterpret_cast<const unsigned char&>(key), sizeof(K));
	}  // 替代&reinterpret_cast<const unsigned char&>

}


namespace MyHash {
	template <class K>
	struct myhash
	{
		size_t operator()(const K& key) const noexcept
		{
			return FNV_1a::fnv_64a(key);
		}
	};

	template <>
	struct myhash<float> {
		size_t operator()(const float K) const noexcept {
			return FNV_1a::fnv_64a(K == 0.0F ? 0.0F : K);
		}
	};

	template <>
	struct myhash<double> {
		size_t operator()(const double K) const noexcept {
			return FNV_1a::fnv_64a(K == 0.0 ? 0.0F : K);
		}
	};

	template <>
	struct myhash<long double> {
		size_t operator()(const long double K) const noexcept {
			return FNV_1a::fnv_64a(K == 0.0L ? 0.0L : K);
		}
	};

#include<cstddef>
	// nullptr_t 是一个基本数据类型，代表各种类型的空指针nullptr，可以作为模板参数且不会被识别为T*。必须需要头文件<cstddef>
	// noexcept 说明函数中没有异常，便于编译器优化
	// void* 泛指指针类型，各种数据类型的指针都可以用void* 表示。指针是_64ptr类型数据
	// {} 是初始化，c++11可以用{}直接初始化，相当于void* Null = nullptr
	// 模板元编程，全特化，偏特化
	/*
	如果特化版本中，所有的模板参数都被替换成了具体类型，那么就叫做全特化
template<>
struct Stack<int*, Array>
{
	...
};

	如果参数中还有非具体类型，那么就叫做部分特化或者偏特化，例如：
template<typename T>
struct Stack<T, Array>
{
	...
}；
	*/

	template <>
	struct myhash<nullptr_t> {
		size_t operator()(nullptr_t) const noexcept {
			void* Null{}; // 可以将C++11提供的大括号初始化作为统一的初始化方式
			return FNV_1a::fnv_64a(Null);
		}
	};


	template <>
	struct myhash<std::string> {
		size_t operator()(const std::string K) const noexcept {
			return FNV_1a::fnv_64a_realize(reinterpret_cast<const unsigned char*>(K.c_str()), K.size());
		}
	};
	/* c++17 实现了string 的hash */

	//using u16string = basic_string<char16_t, char_traits<char16_t>, allocator<char16_t>>;
	//using u32string = basic_string<char32_t, char_traits<char32_t>, allocator<char32_t>>;

	//template <class _Elem, class _Traits, class _Alloc>
	//struct hash<basic_string<_Elem, _Traits, _Alloc>> {
	//	_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef basic_string<_Elem, _Traits, _Alloc> _ARGUMENT_TYPE_NAME;
	//	_CXX17_DEPRECATE_ADAPTOR_TYPEDEFS typedef size_t _RESULT_TYPE_NAME;

	//	_NODISCARD size_t operator()(const basic_string<_Elem, _Traits, _Alloc>& _Keyval) const noexcept {
	//		return _Hash_array_representation(_Keyval.c_str(), _Keyval.size());
	//	}
	//};

}


class HashVal
{
public:
	//计算种子数值
	template<typename T>
	inline void hash_combine(size_t& seed, const T& val)
	{
		seed ^= MyHash::myhash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	//递归调用出口
	template<typename T>
	inline void hash_value(size_t& seed, const T& val)
	{
		hash_combine(seed, val);
	}

	template<typename T, typename... Types>
	inline void hash_value(size_t& seed, const T& val, const Types&... args)
	{
		//重新计算种子值
		hash_combine(seed, val);
		//递归调用
		hash_value(seed, args...);
	}

	// unsigned __int64
	template<typename... Types>
	inline size_t hash_value(const Types&... args)
	{
		size_t seed = 0;
		hash_value(seed, args...);
		return seed;
	}
};

template<class K,class V>
class HashNode : public HashVal
{
public:

	K key;
	V value;
	HashNode* left;
	HashNode* right;
	HashNode* parent;
	size_t hashcode;

	bool color = RED;

	HashNode() { }

	HashNode(K key, V value, HashNode* parent)
	{
		hashcode = HashVal::hash_value(key);
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

	bool IsLeft()
	{
		return (parent != NULL && this == parent->left);
	}

	bool IsRight()
	{
		return (parent != NULL && this == parent->right);
	}

	bool IsSibling(HashNode* HashNode)
	{
		if (HashNode == NULL) {
			return false;
		}
		if (HashNode->IsLeft() && HashNode->parent->Have2Children()) return true;
		if (HashNode->IsRight() && HashNode->parent->Have2Children()) return true;

		return false;
	}

	HashNode* Sibling()
	{
		if (IsLeft()) return this->parent->right;
		if (IsRight()) return this->parent->left;
		return NULL;
	}

	HashNode* Uncle()
	{
		return parent->Sibling();
	}
};


class CompareTo
{
public:
	// 进到这一步，index必定相同
	template<class T>
	size_t operator()(T Key1,T Key2, size_t hash1, size_t hash2)
	{
		// hashcode不等，一定key不同
		//key相等 -> hashcode相等 == hashcode不等 -> key不同
		if (hash1 != hash2) {
			return hash1 - hash2;
		}

		// hashcode相等 -> key不确定
		return (Key1 > Key2) ? 1 : (( Key1 == Key2) ? 0 : -1);
		
	}

	size_t operator()(std::string a, std::string b, size_t hash1, size_t hash2)
	{
		// 不是同一块的
		if (hash1 != hash2) {
			return hash1 - hash2;
		}

		return a.compare(b);
	}

};


template<class K,class V>
class HashMap : private HashNode<K,V>
{
public:
	HashNode<K,V>** hashtable;

	int bucket_capacity;
	int bucket_size;

	int table_size;

	Compare m_cmp;

public:
	HashMap()
	{
		hashtable = new HashNode<K, V>*[16];
	    bucket_capacity = 16;
		bucket_size = 0;
		table_size = 0;

		for (int i = 0; i < bucket_capacity; i++)
		{
			hashtable[i] = nullptr;
		}
	}

	void HashMap_Initial()
	{
		tableSize = 0;
		bucket_size = 0;
		bucket_capacity = 8;
		hashtable = new HashNode<K,V>* [8];
	}

	int bucketSize() {
		return bucket_size;
	}

	int tableSize()
	{
		return table_size;
	}


	bool isEmpty() {
		return bucket_size == 0;
	}



	void clear() {
		bucket_size = 0;

		for (int i = 0; i < bucket_capacity; i++) {
			delete[] hashtable;
			hashtable[i] = NULL;
		}
	}


	void add(K key, V value) {

		HashNode<K, V>* root = hashtable[GetIndex(key)];

		if (root == NULL) {
			hashtable[GetIndex(key)] = new HashNode(key, value, NULL);
			this->bucket_size++;
			this->table_size++;
			black(hashtable[GetIndex(key)]);
			return;
		}


		int cmp = 0;
		HashNode<K,V>* node = root;
		HashNode<K,V>* parent = root;

		while (root != NULL) {
			cmp = m_cmp(key, root->key);

			parent = node;

			if (cmp > 0) {
				node = node->right;
			}
			else if (cmp < 0) {
				node = node->left;
			}
			else { 
				node->value = value;
				node->key = key;
				node->hashcode = this->hash_value(key);
				return;
			}
		}

		HashNode<K,V>* newNode = new HashNode(key, value, parent);
		if (cmp > 0) {
			(parent)->right = newNode;
		}
		else if (cmp < 0) {
			(parent)->left = newNode;
		}

		this->table_size++;
		afterAdd(newNode);
	}


	void test()
	{
		size_t a = HashVal::hash_value("chase");
		size_t b = HashVal::hash_value("chase");
		HashNode<K, V>* node1 = root("chase");

		HashNode<K, V>* node2 = root("chase");
		cout << node1 << ' ' << node2 << endl;
		/*cout << a << ' ' << b << endl;
		int c = m_cmp(a, b);
		cout << c << endl;*/
	}

	//V remove(K key) {

	//	HashNode<K,V>* deleHashNode = HashNode(key);
	//	if (deleHashNode == NULL) return -1;

	//	return remove2(deleHashNode);
	//}


	V get(K key) {
		return node(key)->value;
	}

	//V remove(K key) 
	bool containsKey(K key)
	{
		return node(key) != NULL;
	}

	bool containsValue(V value)
	{
		if (bucket_size == 0) return false;

		queue<HashNode<K, V>*> queue;
		for (int i = 0; i < bucket_capacity; i++) {
			if (hashtable[i] == NULL) continue;
			queue.push(hashtable[i]);

			while (!queue.empty()) {

				HashNode<K, V>* node = queue.front();
				queue.pop();

				if (!m_cmp(value,node->value)) return true;

				if (node->left != NULL) {
					queue.push(node->left);
				}
				if (node->right != NULL) {
					queue.push(node->right);
				}
			}
		}
		return false;
	}


	void traversal()
	{
		if (hashtable == NULL || bucket_size == 0) return;
		for (int i = 0; i < bucket_capacity; i++)
		{
			HashNode<K, V>* root = hashtable[0];
			PrintNodeByLevel(root);
			cout << "-------------------------------------------------- - " << endl;
			cout << "-------------------------------------------------- - " << endl;
			cout << "-------------------------------------------------- - " << endl;
		}
	}


	//void output_impl(HashNode<K, V>* n, bool left, std::string& indent)
	//{
	//	if (n->right)
	//	{
	//		std::string str = indent + (left ? "|     " : "      ");
	//		output_impl(n->right, false, str);
	//	}

	//	cout << indent;
	//	cout << (left ? '\\' : '/');
	//	cout << "-----";
	//	cout << n->value << endl;

	//	if (n->left)
	//	{
	//		std::string str = indent + (left ? "|     " : "      ");
	//		output_impl(n->left, true, str);
	//	}

	//}

	//void Print_Recurrence(HashNode<K, V>* m_root)
	//{
	//	std::string begin = "";  // 初始字符串

	//	if (m_root->right)
	//	{
	//		output_impl(m_root->right, false, begin);
	//	}

	//	cout << m_root->value << endl;

	//	if (m_root->left)
	//	{
	//		output_impl(m_root->left, true, begin);
	//	}
	//}


	//  ***************************************


	void inorderTraversal(HashNode<K, V>* node, vector<HashNode<K, V>*>& v)
	{
		if (node == NULL) return;

		inorderTraversal(node->left, v);

		v.push_back(node);

		inorderTraversal(node->right, v);
	}


	void PrintNodeByLevel(HashNode<K,V>* rnode) {
		if (rnode == NULL) {
			cout << "空树！" << endl;
			return;
		}

		vector<HashNode<K,V>*> intv;

		inorderTraversal(rnode, intv);
		string template_str;
		int location = 0;

		typedef unordered_map<HashNode<K,V>*, int> hashmap;
		hashmap first_locations;


		for (auto& i : intv) {

			location = static_cast<int>(template_str.size());

			template_str += to_string(i->value) + "    ";

			first_locations[i] = location;
		}


		for (auto& i : template_str)  i = '    ';

		queue<HashNode<K,V>*> q;
		q.push(rnode);

		while (!q.empty()) {

			int currentLevelSize = static_cast<int>(q.size());
			int cur_loc = 0;

			string tmp_str1 = template_str, tmp_str2 = template_str,
				tmp_str3 = template_str,
				tmp_str4 = template_str,
				tmp_str5 = template_str;


			for (int i = 1; i <= currentLevelSize; ++i) {

				auto node = q.front();
				q.pop();
				cur_loc = first_locations[node];


				string addmessage1 = node->parent ? to_string(node->parent->value) : "null";

				string addmessage4 = node->color ? "黑" : "红"; 
				string num_str = to_string(node->value);
				//string appendMessage1 =	"P[" + addmessage1 + "]";
				//string appendMessage1 = "H{" + addmessage2 + "}";
				 //string appendMessage1 = "B:" + addmessage3 ;
				string appendMessage1 = addmessage4;

				if (node->left) {
					q.push(node->left);

					int first_loc = first_locations[node->left] + 1;
					tmp_str2[first_loc - 1] = '/';
					tmp_str3[first_loc] = '/';

					first_loc++;

					while (first_loc < cur_loc)
						tmp_str1[first_loc++] = '_';
				}

				int temploc = cur_loc;
				for (int j = 0; j < num_str.length(); ++j) {
					tmp_str1[cur_loc++] = num_str[j];
				}

				for (int j = 0; j < appendMessage1.length(); ++j) {
					tmp_str3[temploc] = appendMessage1[j];
					temploc++;
				}

				if (node->right) {
					q.push(node->right);

					int last_loc = first_locations[node->right] - 1;

					tmp_str2[last_loc + 1] = '\\';
					tmp_str3[last_loc] = '\\';
					while (cur_loc < last_loc) {
						tmp_str1[cur_loc++] = '_';
					}
				}

			}

			std::cout << tmp_str1 << std::endl;
			std::cout << tmp_str3 << std::endl;
			std::cout << tmp_str2 << std::endl;
		}
	}


	private:
	int GetIndex(K key)
	{
		size_t hashValue = this->hash_value(key);
		int index = static_cast<int>(hashValue) & (bucket_capacity - 1);
		return index;
	}


private:
	//V remove1(HashNode<K,V>* node) {
	//	int index = this->GetIndex(node->key);
	//	HashNode<K, V>* m_root = bucket[index];

	//	HashNode<K,V>* replacement = (HashNode->left != NULL ? HashNode->left : HashNode->right);

	//	if (replacement != NULL)
	//		replacement->parent = node->parent;

	//	if (node->parent == NULL) {
	//		HashNode<K,V>* temp = m_root;
	//		m_root = replacement;
	//		this->afterRemove(m_root, replacement);
	//		V oldValue = temp->value;
	//		delete temp;
	//		return oldValue;
	//	}
	//	else if (HashNode == HashNode->parent->left) {
	//		HashNode->parent->left = replacement;
	//	}
	//	else {
	//		HashNode->parent->right = replacement;
	//	}

	//	this->afterRemove(HashNode, replacement);

	//	V oldValue = HashNode->value;
	//	delete HashNode;
	//	HashNode = NULL;
	//	this->m_size--;

	//	return oldValue;
	//}

	//V remove2(HashNode<K,V>* HashNode) {

	//	if (HashNode->Have2Children())
	//	{
	//		HashNode<K,V>* sucNode = this->successor(node);
	//		node->key = sucNode->key;
	//		node->value = sucNode->value;
	//		return remove1(sucNode);
	//	}
	//	else  return remove1(node);
	//}

	//void inorder(HashNode<K,V>* node)
	//{
	//	if (node == NULL || m_op.state) return;

	//	inorder(node->left);

	//	if (m_op.state)  return;
	//	m_op.state = m_op(node->key, node->value);

	//	inorder(node->right);
	//}


	//HashNode<K,V>* successor(HashNode<K,V>* node)
	//{
	//	if (node == NULL)  return NULL;

	//	HashNode<K,V>* rightnode = node->right;

	//	if (rightnode != NULL) {
	//		while (rightnode->left != NULL)
	//		{
	//			rightnode = rightnode->left;
	//		}
	//		return rightnode;
	//	}

	//	while (node->parent != NULL && node->parent->right == node)
	//	{
	//		node = node->parent;
	//	}
	//	return node->parent;
	//}



	HashNode<K, V>* root(K key)
	{
		return hashtable[GetIndex(key)];
	}


	// 根据key找到红黑树节点，不是找到根节点
	HashNode<K,V>* node(K key)
	{
		HashNode<K,V>* node = root(key);

		while (node != NULL)
		{
			int cmp = m_cmp(key,node->key);

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


	void afterAdd(HashNode<K,V>* node) {

		HashNode<K,V>* parent = node->parent;

		if (parent == NULL) {
			black(node);
			return;
		}

		HashNode<K,V>* grand = parent->parent;

		if (isBlack(parent) || grand == NULL) return;

		HashNode<K,V>* uncle = parent->Sibling();

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



	//void afterRemove(HashNode<K,V>* node, HashNode<K,V>* replacement) {
	//	if (node == NULL) return;

	//	if (isRed(node)) {
	//		return;
	//	}

	//	if (isRed(replacement)) {
	//		black(replacement);
	//		return;
	//	}

	//	HashNode<K,V>* parent = node->parent;
	//	if (!parent) return;


	//	bool left = parent->left == NULL || node->IsLeft();
	//	HashNode<K,V>* sibling = left ? parent->right : parent->left;
	//	if (left) {
	//		if (isRed(sibling)) {

	//			red(parent);
	//			black(sibling);
	//			rotateLeft(parent);

	//			sibling = parent->right;
	//		}

	//		if (red(sibling->left) || red(sibling->right))
	//		{

	//			if (isBlack(sibling->right)) {
	//				rotateRight(sibling);
	//				sibling = parent->right;
	//			}

	//			color(sibling, colorOf(parent));
	//			black(parent);
	//			black(sibling->right);

	//			rotateLeft(parent);
	//		}
	//		else {

	//			black(parent);
	//			red(sibling);
	//			if (isBlack(parent)) {
	//				afterRemove(parent, NULL);
	//			}
	//		}

	//	}
	//	else {
	//		if (isRed(sibling)) {

	//			red(parent);
	//			black(sibling);
	//			rotateRight(parent);

	//			sibling = parent->left;
	//		}

	//		if (red(sibling->left) || red(sibling->right))
	//		{

	//			if (isBlack(sibling->left)) {
	//				rotateLeft(sibling);
	//				sibling = parent->left;
	//			}

	//			color(sibling, colorOf(parent));
	//			black(parent);
	//			black(sibling->left);

	//			rotateRight(parent);
	//		}
	//		else {

	//			black(parent);
	//			red(sibling);
	//			if (isBlack(parent)) {
	//				afterRemove(parent, NULL);
	//			}
	//		}
	//	}


	//}


	void rotateRight(HashNode<K,V>* grand)
	{
		HashNode<K,V>* parent = grand->left;
		HashNode<K,V>* child = parent->right;

		grand->left = parent->right;
		parent->right = grand;

		afterRotate(grand, parent, child);
	}

	void rotateLeft(HashNode<K,V>* grand)
	{
		HashNode<K,V>* parent = grand->right;
		HashNode<K,V>* child = parent->left;

		grand->right = parent->left;
		parent->left = grand;

		afterRotate(grand, parent, child);
	}


	void afterRotate(HashNode<K,V>* grand, HashNode<K,V>* parent, HashNode<K,V>* child)
	{

		parent->parent = grand->parent;
		if (grand->IsLeft()) {
			grand->parent->left = parent;
		}
		else if (grand->IsRight()) {
			grand->parent->right = parent;
		}
		else {
			K key = grand->key;
			HashNode<K,V>* m_root = root(key);
			m_root = parent;
		}

		grand->parent = parent;

		if (child != NULL) {
			child->parent = grand;
		}
	}


	HashNode<K,V>* color(HashNode<K,V>* Node, bool color) {
		if (Node == NULL) {
			return Node;
		}

		Node->color = color;
		return Node;
	}

	HashNode<K,V>* red(HashNode<K,V>* Node) {
		return color(Node, RED);
	}

	HashNode<K,V>* black(HashNode<K,V>* Node) {
		return color(Node, BLACK);
	}


	bool colorOf(HashNode<K,V>* Node) {
		return (Node == NULL) ? BLACK : Node->color;
	}

	bool isBlack(HashNode<K,V>* Node) {
		return colorOf(Node) == BLACK;
	}

	bool isRed(HashNode<K,V>* Node) {
		return colorOf(Node) == RED;
	}

};


