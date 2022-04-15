# 题目来源

 leetcode_1143_最长公共子序列：https://leetcode-cn.com/problems/longest-common-subsequence/

# 题目描述

![image-20220412191744538](C:\Users\29185\AppData\Roaming\Typora\typora-user-images\image-20220412191744538.png)

![image-20220413204150832](C:\Users\29185\AppData\Roaming\Typora\typora-user-images\image-20220413204150832.png)



# 题目分析

  对于两个输入的序列，其公共子序列不具有连续性的特征，因此如果考虑使用动态规划则dp数组定义和前面连续子串、连续上升、上升子序列等不同。

◼  假设 2 个序列分别是 nums1、nums2

* i ∈ [1, nums1.length]
* j ∈ [1, nums2.length]

◼  假设 dp(i, j) 是【nums1 前 i 个元素】与【nums2 前 j 个元素】的最长公共子序列长度

* dp(i, 0)、dp(0, j) 初始值均为 0

* 如果 nums1[i – 1] = nums2[j – 1]，那么 dp(i, j) = dp(i – 1, j – 1) + 1

* 如果 nums1[i – 1] ≠ nums2[j – 1]，那么 dp(i, j) = max { dp(i – 1, j), dp(i, j – 1) }



# 图解分析

  假设两个序列如图：

![image-20220413203948017](C:\Users\29185\AppData\Roaming\Typora\typora-user-images\image-20220413203948017.png)



下图是对应的三种可能：

![image-20220413203958579](C:\Users\29185\AppData\Roaming\Typora\typora-user-images\image-20220413203958579.png)





# 代码实现



## 思路一： 递归

```cpp
int LCS2(vector<int> s1, int n1, vector<int> s2, int n2)
{
	if (n1 == 0 || n2 == 0) return 0;

	if (s1[n1 - 1] != s2[n2 - 1])
	{
		return std::max(LCS2(s1, n1, s2, n2 - 1), LCS2(s1, n1 - 1, s2, n2));
	}
	return LCS2(s1, n1 - 1, s2, n2 - 1) + 1;
}


int LCS2(vector<int> s1, vector<int> s2)
{
	if (s1.size() == 0 || s2.size() == 0) return 0;
	return LCS2(s1, s1.size(), s2, s2.size());
}
```

![image-20220413204730605](C:\Users\29185\AppData\Roaming\Typora\typora-user-images\image-20220413204730605.png)

## 思路二： 二维数组

```cpp
int LCS1(vector<int> s1, vector<int> s2)
{
	if (s1.size() == 0 || s2.size() == 0) return 0;
	// s1的长度是行数，s2的长度是列数
	vector<vector<int>> dp(s1.size() + 1,vector<int>(s2.size()+1,0));
	// 保证内层是较短的序列，外层是较长的序列
	for (int rows = 1; rows <= s1.size(); rows++) //行
	{
		//cout <<"rows: " << rows << endl;
		for (int cols = 1; cols <= s2.size(); cols++) // 列
		{
			//cout << "cols:" << cols << endl;
			if (s1[rows - 1] == s2[cols - 1])
			{
				dp[rows][cols] = dp[rows - 1][cols - 1] + 1;
			}
			else
			{
				dp[rows][cols] = std::max(dp[rows - 1][cols], dp[rows][cols - 1]);
			}
		}
	}
	return dp[s1.size()][s2.size()];
}
```

![image-20220413204814274](C:\Users\29185\AppData\Roaming\Typora\typora-user-images\image-20220413204814274.png)





```cpp
#pragma once
#include<string>
#include<vector>
using namespace std;


/*
最终优化：
- 至少需要一个长度为min{s1.length,s2.length}的数组存放数据
- 引入cur和leftTop

*/
// 时间复杂度n2，空间复杂度min{s1.length,s2.length}
int LCS(vector<int> s1, vector<int> s2)
{
	if (s1.size() == 0 || s2.size() == 0) return 0;
	if (s1.size() > s2.size())
	{
		cout << "翻转调用" << endl;
		return LCS(s2, s1);
	}
	// 初始假设s1的长度小于s2
	vector<int> dp(s1.size() + 1);
	// 保证内层是较短的序列，外层是较长的序列
	for (int rows = 1; rows <= s2.size(); rows++)
	{
		// 计算每一层时，cur都从0开始；即每一行第一个元素的左上角元素都为0
		int cur = 0;
		for (int cols = 1; cols <= s1.size(); cols++)
		{
			// 获得本次计算需要的左上角元素
			int leftTop = cur;
			// 覆盖dp[cols]前要先保存，作为下一个dp[cols+1]的左上角元素
			cur = dp[cols];
			// 分类计算并覆盖储存
			if (s2[rows - 1] == s1[cols - 1])
			{
				dp[cols] = leftTop + 1;
			}
			else
			{
				dp[cols] = std::max(dp[cols - 1], dp[cols]);
			}
		}
	}
	return dp[s1.size()];
}

int LCS_str(string s1,string s2)
{
	if (s1.size() == 0 || s2.size() == 0) return 0;
	if (s1.size() > s2.size())
	{
		cout << "翻转调用" << endl;
		return LCS_str(s2, s1);
	}
	// 初始假设s1的长度小于s2
	vector<int> dp(s1.size() + 1);
	// 保证内层是较短的序列，外层是较长的序列
	for (int rows = 1; rows <= s2.size(); rows++)
	{
		int cur = 0;
		for (int cols = 1; cols <= s1.size(); cols++)
		{
			int leftTop = cur;
			cur = dp[cols];

			if (s2[rows - 1] == s1[cols - 1])
			{
				dp[cols] = leftTop + 1;
			}
			else
			{
				dp[cols] = std::max(dp[cols - 1], dp[cols]);
			}
		}
	}
	return dp[s1.size()];
}


/* 

滚动数组是DP中的一种编程思想。
简单的理解就是让数组滚动起来，每次都使用固定的几个存储空间，来达到压缩，节省存储空间的作用。
起到优化空间，主要应用在递推或动态规划中（如01背包问题）。
因为DP题目是一个自底向上的扩展过程，我们常常需要用到的是连续的解，前面的解往往可以舍去。
所以用滚动数组优化是很有效的。利用滚动数组的话在N很大的情况下可以达到压缩存储的作用。

取模运算的循环性可以使得有限空间在逻辑上无限化
dp问题的某一状态不依赖前面所有状态，只依赖一部分状态
*/

int LCS0(vector<int> s1, vector<int> s2)
{
	if (s1.size() == 0 || s2.size() == 0) return 0;
	// 使用两行数组即可
	// s2的长度是列数
	vector<vector<int>> dp(2, vector<int>(s2.size() + 1, 0));
	// 保证内层是较短的序列，外层是较长的序列
	for (int rows = 1; rows <= s1.size(); rows++) //行
	{
		//cout <<"rows: " << rows << endl;
		for (int cols = 1; cols <= s2.size(); cols++) // 列
		{
			//cout << "cols:" << cols << endl;
			if (s1[rows - 1] == s2[cols - 1])
			{
				dp[rows & 1][cols] = dp[(rows - 1) & 1][cols - 1] + 1;
			}
			else
			{
				dp[rows & 1][cols] = std::max(dp[(rows - 1) & 1][cols], dp[rows & 1][cols - 1]);
			}
		}
	}
	return dp[s1.size() & 1][s2.size()];
}




int LCS1(vector<int> s1, vector<int> s2)
{
	if (s1.size() == 0 || s2.size() == 0) return 0;
	// s1的长度是行数，s2的长度是列数
	vector<vector<int>> dp(s1.size() + 1,vector<int>(s2.size()+1,0));
	// 保证内层是较短的序列，外层是较长的序列
	for (int rows = 1; rows <= s1.size(); rows++) //行
	{
		//cout <<"rows: " << rows << endl;
		for (int cols = 1; cols <= s2.size(); cols++) // 列
		{
			//cout << "cols:" << cols << endl;
			if (s1[rows - 1] == s2[cols - 1])
			{
				dp[rows][cols] = dp[rows - 1][cols - 1] + 1;
			}
			else
			{
				dp[rows][cols] = std::max(dp[rows - 1][cols], dp[rows][cols - 1]);
			}
		}
	}
	return dp[s1.size()][s2.size()];
}



int LCS2(vector<int> s1, int n1, vector<int> s2, int n2)
{
	if (n1 == 0 || n2 == 0) return 0;

	if (s1[n1 - 1] != s2[n2 - 1])
	{
		return std::max(LCS2(s1, n1, s2, n2 - 1), LCS2(s1, n1 - 1, s2, n2));
	}
	return LCS2(s1, n1 - 1, s2, n2 - 1) + 1;
}


int LCS2(vector<int> s1, vector<int> s2)
{
	if (s1.size() == 0 || s2.size() == 0) return 0;
	return LCS2(s1, s1.size(), s2, s2.size());
}



```



# 代码改进

## 改进一：滚动二维数组

![image-20220413204922704](C:\Users\29185\AppData\Roaming\Typora\typora-user-images\image-20220413204922704.png)

计算dp数组任意一个位置的元素只需要用到左边、上面、左上角的三个位置的元素，而两行数组即可包含这三个元素，因此使用滚动数组实现空间压缩。

**模二运算 = 和1进行与运算；**

**原理是奇数模二运算为1，偶数模二运算为0；**

**奇数二进制的最后一位为1，和0001与运算为1，偶数二进制最后一位是0，和0001与运算为0 。 正好相对应。**

eg：

3%2=1

3(11)&1(01)=1(01)

6%2=0

6(110)&1(001)=0(000)



```cpp
/* 

滚动数组是DP中的一种编程思想。
简单的理解就是让数组滚动起来，每次都使用固定的几个存储空间，来达到压缩，节省存储空间的作用。
起到优化空间，主要应用在递推或动态规划中（如01背包问题）。
因为DP题目是一个自底向上的扩展过程，我们常常需要用到的是连续的解，前面的解往往可以舍去。
所以用滚动数组优化是很有效的。利用滚动数组的话在N很大的情况下可以达到压缩存储的作用。

取模运算的循环性可以使得有限空间在逻辑上无限化
dp问题的某一状态不依赖前面所有状态，只依赖一部分状态

*/


int LCS0(vector<int> s1, vector<int> s2)
{
	if (s1.size() == 0 || s2.size() == 0) return 0;
	// 使用两行数组即可
	// s2的长度是列数
	vector<vector<int>> dp(2, vector<int>(s2.size() + 1, 0));
	// 保证内层是较短的序列，外层是较长的序列
	for (int rows = 1; rows <= s1.size(); rows++) //行
	{
		//cout <<"rows: " << rows << endl;
		for (int cols = 1; cols <= s2.size(); cols++) // 列
		{
			//cout << "cols:" << cols << endl;
			if (s1[rows - 1] == s2[cols - 1])
			{
				dp[rows & 1][cols] = dp[(rows - 1) & 1][cols - 1] + 1;
			}
			else
			{
				dp[rows & 1][cols] = std::max(dp[(rows - 1) & 1][cols], dp[rows & 1][cols - 1]);
			}
		}
	}
	return dp[s1.size() & 1][s2.size()];
}
```



## 改进二：一维数组存储

  **有人认为只需要三个变量就可以求出所需要的值了，但是实际上是不行的。**

![image-20220413205652089](C:\Users\29185\AppData\Roaming\Typora\typora-user-images\image-20220413205652089.png)



* 这个优化类似于以前的那个公共子串问题，**至少需要一个一维数组，其长度为min{len(s1),len(s2)}，而且这个问题只能从左到右覆盖（右边变量依托于左边变量）**
* 下面的代码实现先判断哪个序列具有最小长度，初始默认s1具有最小长度，如果实际上s2更小则会在初始时就调用LCS(s2,s1)调换位置。

![image-20220413210654316](C:\Users\29185\AppData\Roaming\Typora\typora-user-images\image-20220413210654316.png)

```cpp
/*
最终优化：
- 至少需要一个长度为min{s1.length,s2.length}的数组存放数据
- 引入cur和leftTop
*/
// 时间复杂度n2，空间复杂度min{s1.length,s2.length}
int LCS(vector<int> s1, vector<int> s2)
{
	if (s1.size() == 0 || s2.size() == 0) return 0;
	if (s1.size() > s2.size())
	{
		cout << "翻转调用" << endl;
		return LCS(s2, s1);
	}
	// 初始假设s1的长度小于s2
	vector<int> dp(s1.size() + 1);
	// 保证内层是较短的序列，外层是较长的序列
	for (int rows = 1; rows <= s2.size(); rows++)
	{
		// 计算每一层时，cur都从0开始；即每一行第一个元素的左上角元素都为0
		int cur = 0;
		for (int cols = 1; cols <= s1.size(); cols++)
		{
			// 获得本次计算需要的左上角元素
			int leftTop = cur;
			// 覆盖dp[cols]前要先保存，作为下一个dp[cols+1]的左上角元素
			cur = dp[cols];
			// 分类计算并覆盖储存
			if (s2[rows - 1] == s1[cols - 1])
			{
				dp[cols] = leftTop + 1;
			}
			else
			{
				dp[cols] = std::max(dp[cols - 1], dp[cols]);
			}
		}
	}
	return dp[s1.size()];
}
```



# 相似问题

* LIC
* LCSubString