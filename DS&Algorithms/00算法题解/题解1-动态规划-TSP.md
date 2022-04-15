# 一、问题来源

问题来源：《算法分析与设计》

# 二、问题描述

![](https://img-blog.csdnimg.cn/20190407010818388.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xpbF9qdW5rbw==,size_16,color_FFFFFF,t_70)

**时间限制: 1000 ms**
**内存限制: 2 MB**
**代码长度限制: 16 KB**



# 三、问题分析

  旅行商问题可以使用O(n!)的复杂度找出所有欧拉回路来判断哪一个是最短的，这就是一个NP问题了。但是题目限制比较严，要求了比较小的空间和时间限制，所以采用动态规划求解。还有就是一般而言TSP问题都是对于完全图来说都，因为完全图才一定有欧拉回路，如果是非完全图则不一定有回路，我们还需要判断是否存在欧拉回路，此时就是一个np问题了。

![](https://img-blog.csdnimg.cn/8957b4c4eb7c4fa083b4019379a7a9f1.png?x-oss-process=image/watermark,type_d3F5LXplbmhlaQ,shadow_50,text_Q1NETiBAc29waGlsZXg=,size_18,color_FFFFFF,t_70,g_se,x_16)

如图：假设起点为1，经过2/3/4/5后回再次到1进而构成了一条回路，现在的目标是找出这条回路。

反着想： 最后回到1有四种情况，即从2回到1、从4回到1、从3回到1、从5回到1 。

 整个回路的长度也有对应的四种情况，**每种情况都需要把所有点遍历一次**：

+ 从1经过（3,4,5）到达2，再从2返回1
+ 从1经过（2,3,5）到达4，再从4回到1
+ 从1经过（2,4,5）到达3，再从3返回1
+ 从1经过（2,3,4）到达5，再从5返回1

对应的四个回路最短的路径长度，**枚举了四个情况以后，在这四个情况中取长度最短的那条就是我们要求的从1开始经过2/3/4/5后回再次到1进而构成了一条最短回路。**

（由两项组成，第一项是一个最短路径，第二项是一个直接相连的距离）：

 从1经过（3,4,5）到达2的最短路径 + dist（2,1）

 从1经过（2,3,5）到达4的最短路径 + dist（4,1）

 从1经过（2,4,5）到达3的最短路径 + dist（3,1）

 从1经过（2,3,4）到达5的最短路径 + dist（5,1）



第二项根据我们输入的邻接矩阵可以得到，很容易，比如像下面一样可以把图转换为一个矩阵：
![](https://img-service.csdnimg.cn/img_convert/94f6ff35f2284fefab8c314f3c8e97bd.png)

**第一项是需要我们仔细思考的 ：**

如何得到一个 从1经过（3,4,5）到达2的最短路径？

如何得到一个从1经过（3,4,5）到达2的最短路径 ？

如何得到一个 从1经过（2,3,5）到达4的最短路径 ？

如何得到一个 从1经过（2,4,5）到达3的最短路径？

如何得到一个 从1经过（2,3,4）到达5的最短路径 ？



就拿 **从1经过（3,4,5）到达2的最短路**径来举例子吧。 

其实此时把2当做终点，则又回到了最初那样思考：

**最后回到2有三种情况，从4回到2、从3回到2、从5回到2 。**

 整个路径的长度也有对应的四种情况 ：  **从1经过（3,4,5）到达2的最短路就是其中最短的那个**

+ 从1经过（3,5）到达4，再从4回到2
+ 从1经过（4, 5）到达3，再从3回到2
+ 从1经过（3，4）到达5，再从5回到2 

从1经过（3,4,5）到达2的最短路径    ==    从1经过（4,5）到达3的最短路径  + dist（3,2）

从1经过（3,4,5）到达2的最短路径    ==    从1经过（3,5）到达4的最短路径  + dist（3,2）

从1经过（3,4,5）到达2的最短路径    ==    从1经过（3,4）到达5的最短路径  + dist（5,2）

又是由两项组成，第二项依旧通过dist得到，第一项又是一个最短路径，不难看出这里递归的感觉。



继续推：

从1经过（4,5）到达3的最短路径 === 从1经过（5）到达4的最短路径 + dist（4,3）

从1经过（5）到达4的最短路径  ===  从1经过（）到达5的最短路径 + dist（5,4）

从1经过（）到达5的最短路径 === dist（1,5）

因此可以出递归出口是： 从1经过（）到达, j 的最短路径，即**从初始节点经过0个的中间节点到达j时，此时的最短路径直接就是dist（1，j）**





我们要解决的问题：从1 、经过（2,3,4,5）、然后回到1 的最短回路

这个问题在前面被拆结成两部分，**后半部分是直接相连的距离，前半部分是另一个最短距离**

仔细观察上面那一段文字描述：“从1 、经过（2,3,4,5）、然后回到1 的最短回路”，（2,3,4,5）是一个点集合，**代表除去起始点和终点之外没有经过的点**。编程的时候怎么表示这个点集合呢？虽然它看起来像一个元组Tuple，但是在c++系语言中是没有自带的元组结构的，而且我们只想知道还有哪些点没被访问、哪些点还能访问，因此我们想到使用一个数组来表示这个点集，只不过数组的是以二进制的形式表示是哪个点。下面逐步进行说明：

例子1：

n = 4时，2^(4-1) = 8  对应二进制 1000

n = 5时，2^(5-1) = 16 对应二进制 10000

**总结就是n等于几，对应的2^(n-1)表示为二进制就有几位。**

但是前面已经说过了，我们最终的目的从初始点出发是遍历除了初始点以外的所有点一次然后回到初始点。既然我们已经确定初始点了，那就没必要用n位二进制表示n个点了，只需要n-1位二进制表示除了初始点以外的n-1个点即可。**我们发现2^(n-1)  - 1恰好对应了n-1位二进制。**

例如：

n = 4时，2^(4-1)  - 1= 7 对应二进制 111 ， 有3个1

n = 5时，2^(5-1) - 1 = 15 对应二进制 1111，有4个1

**总结就是n等于几，对应的2^(n-1) - 1表示为二进制就有n-1位1。**

哦豁，与此同时我们发现了另一个巧合：我们可以使用1来表示某个点未被访问下次可以经过，使用0来表示某个点已经访问了下次不再经过。因此我们就可以使用长度为n-1的二进制表示除了初始点外还有哪些点可以访问，这就可以看成是一个点的集合，只不过存放的不是各个点的数值，而是状态。

例如：

n = 4时，2^(4-1)  - 1= 7 对应二进制 111 ， 有3个1，代表如果规模是4，则除了初始点位外还能访问的点有（1,2,3）

n = 5时，2^(5-1) - 1 = 15 对应二进制 1111，有4个1，代表如果规模是5，则除了初始点位外还能访问的点有（1,2,3,4）

**总结就是2^(n-1) - 1对应的二进制可以等价为一个点的集合，从右到左依次表示的是1、2、3、4.....2^n-1，表示除了初始的0以外的点都可以访问。**



假设有一个二维数组dp，dp\[i][j]代表从起始点开始经过点集合j 到达点i的最短路径，j是二进制表示的点集合。

假设二维dp数组的维度为( n, 2^(n-1) ), n代表问题规模，即图中有几个点**；2^(n-1) -1代表的二进制位数等于图中节点的个数**，即2^(n-1)的二进制位数为n位；

dp数组赋值的时候，第一个维度代表的是“从初始点到终止点”中的那个终止点；第二个维度带表在图的节点中除了初始节点和终止节点之外还有哪些点可以用。

dp\[3][011] : 从点0 经过点（1、2）到达3的最短路径

dp\[2][101]: 从点0经过点（1、3）到达2的最短路径

dp\[1][110]: 从点0经过点（2、3）到达2的最短路径

dp\[0][111]: 从点0 经过点（1,2,3）到达0的最短路径



动态规划两要素：

1. 最优子结构： 满足！ 每次枚举所有情况，然后去一个最短的作为最短路径
2. 无后效性： 无论选择哪一种种情况，最后一步都不受影响。例如从1经过（3,4,5）到达2，不论中间经过的是3还是4，最后到达 2以后再从2返回1的路径都是不变的。

动态规划dp\[i][j]的初始含义：从初始节点开始，经过点集合j，到达点i所花费的最小开销

动态规划的推导式：dp\[i][j] = min{dp\[i][点集j中删除点k] + dist\[i][k]}

最后的解答： minDist = min{dp\[0][除了点0和点k的点集] + dist\[k][0]}





# 四、代码实现

**计划：**

1. 通过一个函数求出dp数组（部分递归）dp\[i][j] = min{dp\[i][点集j中删除点k] + dist\[i][k]}，这里k是1到n-1，n是输入规模（图里面的个数）
2. 通过另一个函数循环求出minDist = min{dp\[0][除了点0和点k的点集] + dist\[k][0]}，这里k是从1到n-1的，n是输入规模（图里面的个数）



但是：在实现过程中发现，使用非递归的解法很难想到（想了不低于三个小时还是没写好），因此使用递归：

```cpp
// 问题规模
short scale;
// 初始输入的距离数组
vector<vector<short>> dist;
//dp[i][j]: 从0开始经过点集合j到i需要的距离
vector<vector<short>> dp;

// 从初始点经过passPoint这个点集合到达endPoint需要的最小花费
short Forward(short passPoint, short endPoint)
	{
		if (passPoint == 0)
		{
			return dist[0][endPoint];
		}
		short minNum = 15000, temp;
		for (short i = 1; i < scale; i++)
		{
			short sign = 1 << (i - 1);
			// 在路径中
			if ((passPoint & sign) != 0)
			{
				temp = dist[i][endPoint] + Forward(passPoint - sign, i);
				if (temp < minNum)
				{
					minNum = temp;
				}
			}
		}
		return minNum;
	}

// 从初始点经过passPoint这个点集合到达endPoint需要的最小花费 + endPoint到达初始点需要的最小花费 = 从初始点经过其他所有店回到初始点的最小花费
short circlePath()
	{
		short minNum = 15000;
		short temp;
		for (short i = 1; i < scale; i++)
		{
			temp = Forward((1 << (scale - 1)) - 1 - (1 << (i - 1)), i) + dist[i][0];
			if (temp < minNum)
			{
				minNum = temp;
			}
		}
		return minNum;
	}
```

**优化版本：使用dp数组存放Forward函数计算的结果，避免重复计算**

```cpp
#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<cmath>
using namespace std;


class Travel
{
public:
    // 问题规模
	short scale;
    // 初始输入的距离数组
	vector<vector<short>> dist;
	//dp[i][j]: 从0开始经过点集合j到i需要的距离
	vector<vector<short>> dp;

    // 初始化数组大小，元素初始都是0
	Travel()
	{
		dist = vector<vector<short>>(15, vector<short>(15));
		dp = vector<vector<short>>(15, vector<short>(16384));
	}

	// 从0开始经过点集合passPoint到endPoint需要的距离
    // passPoint是二进制对应的点集； endPoint是结束节点
	short Forward(short passPoint, short endPoint)
	{
        // 如果点集为空，就直接返回连接距离
		if (passPoint == 0)
		{
			return dist[0][endPoint];
		}
		short minNum = 15000, temp;
		for (short i = 1; i < scale; i++)
		{
			short sign = 1 << (i - 1);
			// 在路径中
			if ((passPoint & sign) != 0)
			{
				// 如果以前在dp算过了，直接用就行了，不需要再算
				if (dp[i][passPoint - sign] > 0)
					temp = dp[i][passPoint - sign] + dist[i][endPoint];
				else
                    // 如果此时passPoint - sign=0了，这一步就相当于dist[i][endPoint]+dist[0][i];
					temp = dist[i][endPoint] + Forward(passPoint - sign, i);

				if (temp < minNum)
				{
					minNum = temp;
				}
			}
		}
		// end点经过pass点集后回到终点的距离
		dp[endPoint][passPoint] = minNum;
		return minNum;
	}
    
    
    
    //算出 minDist ，midDist = min{dp[0][除了点0和点k的点集] + dist[k][0]}
	short circlePath()
	{
		short minNum = 15000;
		short temp;
		for (short i = 1; i < scale; i++)
		{
			temp = Forward((1 << (scale - 1)) - 1 - (1 << (i - 1)), i) + dist[i][0];
			if (temp < minNum)
			{
				minNum = temp;
			}
		}
		return minNum;
	}

    // 输入规模和dist数组
	void input()
	{
		std::ios::sync_with_stdio(false);
		cin >> scale;
		for (short tmp1 = 0; tmp1 < scale; tmp1++)
		{
			for (short tmp2 = 0; tmp2 < scale; tmp2++)
				cin >> dist[tmp1][tmp2];
		}
	}
};
```





# 五、执行结果

  可以发现使用数组辅助存储可以有效减少最终的递归调用次数，减少开销。

![优化前](C:\Users\29185\AppData\Roaming\Typora\typora-user-images\image-20220410130350892.png)



![优化后](C:\Users\29185\AppData\Roaming\Typora\typora-user-images\image-20220410130424410.png)

