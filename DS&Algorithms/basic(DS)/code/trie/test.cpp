#include"TrieTree.h"
#include<iostream>
#include<unordered_map>
#include<cassert>
using namespace std;




int main()
{
	Trie<int> trie;

	trie.add("abc",121);
	trie.add("aaa", 22);
	trie.add("adc", 33);
	trie.add("efef", 44);
	assert(trie.contains("abc"));
	assert(trie.contains("efef"));
	assert(trie.findPrefix("efe"));
	assert(trie.size() == 4);
	trie.remove("efef");
	assert(trie.contains("abc"));
	assert(!trie.contains("efef"));
	assert(!trie.findPrefix("efe"));
	assert(trie.size() == 3);
	assert(trie.get("aaa") == 22);
	trie.add("hfj20020709", 999);
	trie.add("hfj200213", 998);
	assert(trie.size() == 5);

	trie.remove("hfj20020709");
	assert(!trie.contains("hfj20020709"));
	assert(trie.findPrefix("hfj2002"));

	//cout << trie.contains("abc") << endl;
	//cout << trie.contains("abc") << endl;

	//cout << trie.remove("abc") << endl;
	//cout << trie.contains("abc") << endl;

	system("pause");
	return 0;
}