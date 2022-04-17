# 一、题目来源

**最长连续子序列和**

https://leetcode-cn.com/problems/maximum-subarray/

# 二、题目描述



![image-20220411123043015](https://cdn.jsdelivr.net/gh/hanfeijiang/CS-Sources/img/image-20220411123043015.png)



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

  **最长连续子序列和问题强调连续性，因此dp的定义是以.xx.结尾的最xxx，下面在来两道和连续性有关的问题：**



## 1.最长上升子序列（一维）

leetcode_300： https://leetcode-cn.com/problems/longest-increasing-subsequence/

![image-20220412154849044](https://cdn.jsdelivr.net/gh/hanfeijiang/CS-Sources/img/image-20220412154849044.png)

#### 分析：

  问题具有最优子结构和无后效性，考虑动态规划。且问题具有连续性，即“上升”是一个连续的过程，因此dp数组定义为以xxx结尾的最值。

◼**dp(i) 是以 nums[i] 结尾的最长上升子序列的长度，i ∈ [0, nums.length)**，以xxx为结尾说明这个序列必须包含xxx。

◼ 状态的初始值

* **所有的 dp(i) 默认都初始化为 1**

◼ 状态转移方程

遍历 j ∈ [0,i）

* 当 nums[i] > nums[j]
  ✓ **nums[i] 可以接在 nums[j] 后面**，形成一个比 dp(j) 更长的上升子序列，长度为 dp(j) + 1
  ✓ **dp(i) = max { dp(i), dp(j) + 1 }**

* 当 nums[i] ≤ nums[j]
  ✓ nums[i] 不能接在 nums[j] 后面，**跳过此次遍历（continue）**



#### 代码实现

```
#pragma once
#include<vector>
#include<iostream>
using namespace std;
// 状态假设：dp(i) 是以 nums[i] 结尾的最长上升子序列的长度，i ∈ [0, nums.length)
// 初始条件: 所有的 dp(i) 默认都初始化为 1（最短是1，可以拼接到前面）
// 状态转变：dp(i) = max{dp(j) | j在i之前、nums[i]>nums[j]} + 1
// 最终结果：max{dp(i) | i from 0 to size-1}

int LenthOFLIS_(vector<int> nums)
{
	if (nums.size() == 0) return 0;
	vector<int> dp(nums.size());
	int max = dp[0] = 1;
	for (int i = 1; i < nums.size(); i++)
	{
		dp[i] = 1;
		// i之前所有比nums[i]小的nums[j]
		for (int j = 0; j < i; j++)
		{
			if (nums[i] > nums[j])
			{
				dp[i] = std::max(dp[j] + 1, dp[i]);
			}
		}
		max = std::max(dp[i], max);
	}
	return max;
}
```



#### 优化

使用二分查找





## 2.最长公共子串（二维）

![image-20220411130349282](https://cdn.jsdelivr.net/gh/hanfeijiang/CS-Sources/img/image-20220411130349282.png)

#### 分析

字符串也是连续性的，因此如果使用动态规划定义dp数组也是以.xx.结尾的最xxx。

◼ 假设 2 个字符串分别是 str1、str2
i ∈ [1, str1.length]
j ∈ [1, str2.length]

◼ **假设 dp(i, j) 是以 str1[i – 1]（第i个字符）、str2[j – 1]（第j个字符） 结尾的最长公共子串长度**
dp(i, 0)、dp(0, j) 初始值均为 0
如果 str1[i – 1] = str2[j – 1]，那么 dp(i, j) = dp(i – 1, j – 1) + 1
如果 str1[i – 1] ≠ str2[j – 1]，那么 dp(i, j) = 0
◼ 最长公共子串的长度是所有 dp(i, j) 中的最大值 max { dp(i, j) }



#### **二维dp数组实现：**

```cpp

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

![image-20220412123706218](https://cdn.jsdelivr.net/gh/hanfeijiang/CS-Sources/img/image-20220412123706218.png)



画出图像，然后考虑进行优化：因为每次计算时只会用到左上角的元素值，因此不需要整个二维dp数组即可实现。

而且不能像最长连续子序列那样只用一个变量来替代，我们至少需要一个长度为min{len(Str1),len(Str2)} + 1的数组。

具体思路如下图：

假设红圈就是我们选择的数组，我们要使用一行数组去求下一行的数组，求出来的新值要覆盖掉原来数组中那个位置的元素。例如下图计算出（2,1）位置的数值为1，则应该用1替代原来数组中的0；

![image-20220412124104517](https://cdn.jsdelivr.net/gh/hanfeijiang/CS-Sources/img/image-20220412124104517.png)

现在数组就变成这样了：

![image-20220412124349042](https://cdn.jsdelivr.net/gh/hanfeijiang/CS-Sources/img/image-20220412124349042.png)

然后我们像继续计算（2,2）位置的值，此时因为B ！= A ，所以就是0；计算完成后我们需要用0覆盖上面位置的1；

![image-20220412124547244](https://cdn.jsdelivr.net/gh/hanfeijiang/CS-Sources/img/image-20220412124547244.png)

然后我们计算（2,3）位置的值，此时因为B = B，所以这个值等于（1,2）的值 + 1，但是再前一步计算中（1,2）原来的值已经被（2,2）的值覆盖了，因此无法正确求出（2,3）的值。

  问题出在我们从左到右进行覆盖，而右边的计算又依托于左上角的元素值，如果覆盖了就没办法计算。提出两个解决方法：

1. **提前保留左上角的值**
2. **从右到左覆盖**



#### 一维数组实现

**提前保留leftTop**

```cpp
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
		int cur = 0; // 初始的左上角元素值一定为0
		for (int j = 1; j <= s2.size(); j++)
		{
			int leftTop = cur; // cur此时指向本次计算的元素的左上角，赋值给leftTop，然后把cur更新
			cur = dp[j]; // cur 更新为下一个元素左上角的值
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
```



**从右到左覆盖版本**

```cpp
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
```

![image-20220412125325010](https://cdn.jsdelivr.net/gh/hanfeijiang/CS-Sources/img/image-20220412125325010.png)

如图，从右到左覆盖是一个非常好的方法。假设（2,5）、（2，4）已经覆盖了数组最后两个位置，接下来计算（2,3）时需要用到(1,2)的值，因为是从右到左覆盖数组，所以（1,2）的值还存在数组中，可以正确求出（2,3）的值。

#### 代码整合

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





# 八、收获与套路

1. 分析最优子结构和无后效性，判断动态规划
2. 假设初始含义、定义dp数组的含义
3. 确定dp数组的特殊值
4. 枚举所有分支、所有可能，写出状态转移方程
5. 循环计算dp数组的值
6. 如果难以正向推导dp数组，则考虑使用递归，定义dp（）函数，函数的返回值就是我们初始假设的含义
7. 接第6步，如果使用递归，则需要两个函数求解，一个函数负责递归计算dp，一个负责调用递归
8. 画出一维或者二维图，正向或反向推导，考虑前驱关系，进行空间的优化： **一维数组变单个变量，二维数组变一维数组，反向覆盖，滑动数组**
9. **连续性dp数组的定义：以。。为结尾的最值**



