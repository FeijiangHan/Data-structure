# 枚举所有情况（限制、分支）+找最优

```cpp
		
// 找硬币
int minCost1 = std::min(coins1_solve(n - 5, dp), coins1_solve(n - 1, dp));
int minCost2 = std::min(coins1_solve(n - 20, dp), coins1_solve(n - 25, dp));
dp[n] = std::min(minCost1, minCost2) + 1;


// 最大连续子序列
int prev = dp[i - 1];
dp[i] = nums[i] + (prev > 0 ? prev : 0);
if (dp[i] > max)
{
    max = dp[i];
}

// 最长公共子序列
if (s1[rows - 1] == s2[cols - 1])
{
    dp[rows][cols] = dp[rows - 1][cols - 1] + 1;
}
else
{
    dp[rows][cols] = std::max(dp[rows - 1][cols], dp[rows][cols - 1]);
}

// 最长公共子串

if (s1[i - 1] != s2[j - 1]) continue;
dp[i][j] = dp[i - 1][j - 1] + 1;
maxNum = max(maxNum, dp[i][j]);


if (s1[i - 1] != s2[j - 1])
{
    dp[j] = 0;
    continue;
}
dp[j] = dp[j - 1] + 1;
maxNum = max(maxNum, dp[j]);


// 最长上升子序列
dp[i] = 1;
for (int j = 0; j < i; j++)
{
    if (nums[i] > nums[j])
    {
        dp[i] = std::max(dp[j] + 1, dp[i]);
    }
}
max = std::max(dp[i], max);



// 01背包问题
if (j < weight[i - 1])
{
    dp[i][j] = dp[i - 1][j];
}
else
{
    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i - 1]] + value[i - 1]);
}


// TSP问题
// 类似最长上升子序列，内层找一次最小，外层找一次最小。
if (dp[i][passPoint - sign] > 0)
    temp = dp[i][passPoint - sign] + dist[i][endPoint];
else
{
    cout << "1" << endl;
    temp = dist[i][endPoint] + Forward(passPoint - sign, i);
}
if (temp < minNum)
{
    minNum = temp;
}

-----------
 
temp = Forward((1 << (scale - 1)) - 1 - (1 << (i - 1)), i) + dist[i][0];
if (temp < minNum)
{
    minNum = temp;
}
```



# 初始化赋值

# 

```cpp
		
// 找硬币
int minCost1 = std::min(coins1_solve(n - 5, dp), coins1_solve(n - 1, dp));
int minCost2 = std::min(coins1_solve(n - 20, dp), coins1_solve(n - 25, dp));
dp[n] = std::min(minCost1, minCost2) + 1;


// 最大连续子序列
int prev = dp[i - 1];
dp[i] = nums[i] + (prev > 0 ? prev : 0);
if (dp[i] > max)
{
    max = dp[i];
}

// 最长公共子序列
if (s1[rows - 1] == s2[cols - 1])
{
    dp[rows][cols] = dp[rows - 1][cols - 1] + 1;
}
else
{
    dp[rows][cols] = std::max(dp[rows - 1][cols], dp[rows][cols - 1]);
}

// 最长公共子串

if (s1[i - 1] != s2[j - 1]) continue;
dp[i][j] = dp[i - 1][j - 1] + 1;
maxNum = max(maxNum, dp[i][j]);


if (s1[i - 1] != s2[j - 1])
{
    dp[j] = 0;
    continue;
}
dp[j] = dp[j - 1] + 1;
maxNum = max(maxNum, dp[j]);


// 最长上升子序列
dp[i] = 1;
for (int j = 0; j < i; j++)
{
    if (nums[i] > nums[j])
    {
        dp[i] = std::max(dp[j] + 1, dp[i]);
    }
}
max = std::max(dp[i], max);



// 01背包问题
if (j < weight[i - 1])
{
    dp[i][j] = dp[i - 1][j];
}
else
{
    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i - 1]] + value[i - 1]);
}


// TSP问题
// 类似最长上升子序列，内层找一次最小，外层找一次最小。
if (dp[i][passPoint - sign] > 0)
    temp = dp[i][passPoint - sign] + dist[i][endPoint];
else
{
    cout << "1" << endl;
    temp = dist[i][endPoint] + Forward(passPoint - sign, i);
}
if (temp < minNum)
{
    minNum = temp;
}

-----------
 
temp = Forward((1 << (scale - 1)) - 1 - (1 << (i - 1)), i) + dist[i][0];
if (temp < minNum)
{
    minNum = temp;
}
```







# dp数组的格式

