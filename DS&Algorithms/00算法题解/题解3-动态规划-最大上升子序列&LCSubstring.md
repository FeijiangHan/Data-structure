# 一、题目来源

https://leetcode-cn.com/problems/maximum-subarray/

# 二、题目描述



![image-20220411123043015](C:\Users\29185\AppData\Roaming\Typora\typora-user-images\image-20220411123043015.png)



# 三、分析

  如果定义dp（i）为以第i个元素结尾的最大连续子序列之和，则此问题具有：

最优子结构： dp（i+1）的值代表i+1个元素结尾的最大连续子序列之和、dp（i）的值代表以第i个元素结尾的最大连续子序列之和，定义出来的每个子问题都是最优的。

无后效性：dp（i）= max{ dp（i-1）+ nums[i]，nums[i] } ，不论dp（i-1）的值是通过什么情况算出来的，由于最终拿到的dp（i-1）一定是当下的最优解，对下一步计算没有影响。同理，不论dp(i) 等于dp（i-1）+ nums[i]还是等于nums[i] ，对dp（i+1）的计算都没有影响。

因此考虑使用动态规划解决。



# 四、代码实现

动态规划需要如下几个操作：

1. 定义dp的含义：**因为是连续子序列，所以强调连续性**，因此假设 dp(i) 是**以 nums[i] 结尾**的最大连续子序列和（nums是整个序列）
2. 初始条件：dp(0) = nums[0]
3. 状态转移方程: dp(i) = max{ dp(i-1)+nums[i], nums[i]}，或者是下述表示
   如果 dp(i – 1) ≤ 0，那么 dp(i) = nums[i]
   如果 dp(i – 1) > 0，那么 dp(i) = dp(i – 1) + nums[i]
4. 最终的结果： dp[i] 中的最大值即为最大连续子序列

```cpp
int maxSubArray1(vector<int> nums)
{
	if (nums.size() == 0) return 0;
	vector<int> dp(nums.size());
	int max = dp[0] = nums[0];
	for (int i = 1; i < nums.size(); i++)
	{
		int prev = dp[i - 1];
		dp[i] = nums[i] + (prev > 0 ? prev : 0);
		if (dp[i] > max)
		{
			max = dp[i];
		}
		// max = std::max(dp[i],max);
	}
	return max;
}
```



# 五、优化思考

  状态转移方程：dp(i) = max{ dp(i-1)+nums[i], nums[i]} 

**因此每一项的计算只需要依赖于前一项就行了，不需要把前面所有的项都保留起来。**

```cpp
int maxSubArray2(vector<int> nums)
{
	if (nums.size() == 0) return 0;
	int dp;
	int max = dp = nums[0];
	for (int i = 1; i < nums.size(); i++)
	{
		dp = nums[i] + (dp > 0 ? dp : 0);
		if (dp > max)
		{
			max = dp;
		}
		// max = std::max(dp[i],max);
	}
	return max;
}
```





# 六、最长连续子序列代码整合

```cpp
#pragma once
#include<vector>
#include<iostream>
using namespace std;

// 假设 dp(i) 是以 nums[i] 结尾的最大连续子序列和（nums是整个序列）
// 初始态：dp(0) 的值是 nums[0]
// 状态转移方程：dp(i) =  nums[i] + dp(i – 1) > 0 ? dp(i – 1) : 0;
// 最终解：最大连续子序列和是所有 dp(i) 中的最大值 max { dp(i) }，i ∈ [0, nums.length)

int maxSubArray1(vector<int> nums)
{
	if (nums.size() == 0) return 0;
	vector<int> dp(nums.size());
	int max = dp[0] = nums[0];
	for (int i = 1; i < nums.size(); i++)
	{
		int prev = dp[i - 1];
		dp[i] = nums[i] + (prev > 0 ? prev : 0);
		if (dp[i] > max)
		{
			max = dp[i];
		}
		// max = std::max(dp[i],max);
	}
	return max;
}


int maxSubArray2(vector<int> nums)
{
	if (nums.size() == 0) return 0;
	int dp;
	int max = dp = nums[0];
	for (int i = 1; i < nums.size(); i++)
	{
		dp = nums[i] + (dp > 0 ? dp : 0);
		if (dp > max)
		{
			max = dp;
		}
		// max = std::max(dp[i],max);
	}
	return max;
}
```



# 七、类比扩展

  最长连续子序列和问题强调连续性，因此dp的定义是以.xx.结尾的最xxx，下面在来一道和连续性有关的问题：求LCSubstring

![image-20220411130349282](C:\Users\29185\AppData\Roaming\Typora\typora-user-images\image-20220411130349282.png)

字符串也是连续性的，因此如果使用动态规划定义dp数组也是以.xx.结尾的最xxx。

◼ 假设 2 个字符串分别是 str1、str2
i ∈ [1, str1.length]
j ∈ [1, str2.length]

◼ **假设 dp(i, j) 是以 str1[i – 1]（第i个字符）、str2[j – 1]（第j个字符） 结尾的最长公共子串长度**
dp(i, 0)、dp(0, j) 初始值均为 0
如果 str1[i – 1] = str2[j – 1]，那么 dp(i, j) = dp(i – 1, j – 1) + 1
如果 str1[i – 1] ≠ str2[j – 1]，那么 dp(i, j) = 0
◼ 最长公共子串的长度是所有 dp(i, j) 中的最大值 max { dp(i, j) }

```cpp
#pragma once
#include<string>
#include<vector>
#include<iostream>
using namespace std;



void test()
{
	string s1 = "asbkdxjbaslc";
	cout << typeid(s1[0]).name() << endl;
}



int LCString(string s1, string s2)
{
	if (s1.size() == 0 || s2.size() == 0) return 0;
	if (s1.size() < s2.size())
	{
		LCString(s2, s1);
	}
	// 列： s2
	vector<int> dp(s2.size() + 1);
	int maxNum = 0;
	for (int i = 1; i <= s1.size(); i++)
	{
		for (int j = s2.size(); j >= 1; j--)
		{
			if (s1[i - 1] != s2[j - 1])
			{
				dp[j] = 0;
				continue;
			}
			dp[j] = dp[j - 1] + 1;
			maxNum = max(maxNum, dp[j]);
		}
	}
	return maxNum;
}



int LCString2(string s1, string s2)
{
	if (s1.size() == 0 || s2.size() == 0) return 0;
	if (s1.size() < s2.size())
	{
		LCString(s2, s1);
	}
	// 列： s2
	vector<int> dp(s2.size() + 1,0);
	int maxNum = 0;
	for (int i = 1; i <= s1.size(); i++)
	{
		int cur = 0;
		for (int j = 1; j <= s2.size(); j++)
		{
			int leftTop = cur;
			cur = dp[j];
			if (s1[i - 1] == s2[j - 1])
			{
				dp[j] = leftTop + 1;
			}
			else
			{
				dp[j] = 0;
			}
			
			maxNum = max(maxNum, dp[j]);
		}
	}
	return maxNum;
}


int LCString1(string s1, string s2)
{
	if (s1.size() == 0 || s2.size() == 0) return 0;
	// 行： s1； 列： s2
	vector< vector<int>> dp(s1.size() + 1, vector<int>(s2.size() + 1));
	int maxNum = 0;
	for (int i = 1; i <= s1.size(); i++)
	{
		for (int j = 1; j <= s2.size(); j++)
		{
			if (s1[i - 1] != s2[j - 1]) continue;
			dp[i][j] = dp[i - 1][j - 1] + 1;
			maxNum = max(maxNum, dp[i][j]);
		}
	}
	return maxNum;
}

```

