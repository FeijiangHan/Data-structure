

#  分治算法

Integer Multiplication -- 递归的优化

Matrix multiplication-Strassen’s algorithm -- 递归的优化

Chess-board coverage -- 子问题与原问题的统一

Find the k-th smallest element -- 快排思想

Closest pair of points -- 

Tournament scheduling -- 子问题的分解



# 大数乘法

```python
def mul(num1:int,num2:int) -> int:
    if num1 < 10 or num2 < 10:
        return num1 * num2
    
    strNum1  = str(num1)
    strNum2  = str(num2)
    
    len1 : int = len(strNum1)
    len2 : int = len(strNum2)
    
    subLen = max(len1,len2) // 2
    
    num1_first = int(strNum1[0:len1 - subLen])
    num2_first = int(strNum2[0:len2 - subLen])
    num1_second = int(strNum1[len1 - subLen:])
    num2_second = int(strNum2[len2 - subLen:])
    
    a : int = mul(num1_first,num2_first)
    b : int = mul(num1_second,num2_second)
    c : int = mul(num1_first+num1_second,num2_first+num2_second) - a - b
    
    return a*10**(2*subLen) + c*10**subLen + b
```



```python
from math import log2, ceil
 
# 补零操作
def pad(string: str, real_len: int, max_len: int) -> str:
  pad_len: int = max_len - real_len
  return f"{'0' * pad_len}{string}"
 
 
def kara(n1: int, n2: int) -> int:
  if n1 < 10 or n2 < 10:
    return n1 * n2
  n1_str: str = str(n1)
  n2_str: str = str(n2)
  n1_len: int = len(n1_str)
  n2_len: int = len(n2_str)
  real_len: int = max(n1_len, n2_len)
  
  # 对其长度进行补零
  max_len: int = 2 ** ceil(log2(real_len)) #得到最接近子串长度的2^n长度
  mid_len: int = max_len >> 1
  n1_pad: str = pad(n1_str, n1_len, max_len)
  n2_pad: str = pad(n2_str, n2_len, max_len)
  
  p: int = int(n1_pad[:mid_len])
  q: int = int(n1_pad[mid_len:])
  r: int = int(n2_pad[:mid_len])
  s: int = int(n2_pad[mid_len:])
  
  u: int = kara(p, r)
  v: int = kara(q+p, r+s)
  w: int = kara(q, s)
  return u * 10 ** max_len + (v-u-w) * 10 ** mid_len + w
```

```c++
long mul(long num1, long num2)
{


	if (num1 < 10 || num2 < 10)
	{
		return num1*num2;
	}

	string strNum1 = to_string(num1);
	string strNum2 = to_string(num2);
	int len1 = strNum1.length();
	int len2 = strNum2.length();

	int halfLen = max(len1,len2) / 2;

	string num1_first, num1_second, num2_first, num2_second;
	num1_first = strNum1.substr(0,len1 - halfLen);
	num2_first = strNum2.substr(0,len2 - halfLen);
	num1_second = strNum1.substr(len1 - halfLen);
	num2_second = strNum2.substr(len2 - halfLen);
	// cout << "1f: " << num1_first << "  2f: " << num2_first << "  1s: " << num1_second << "  2s: " << num2_second << endl;
	long u = stol(num1_first);
	long v = stol(num2_first);
	long w = stol(num1_second);
	long x = stol(num2_second);
	// cout << "u: " << u << "  v: " << v << "  w: " << w << "  x: " << x <<  endl;
	long a = mul(u,v);
	long b = mul(w,x);
	long c = mul((u+w),(v+x)) - a - b; // 注意顺序不要错了
	// cout << "a: " << a << "  b: " << b << "  c: " << c << '  ' << endl;
	return (a * (long)pow(10, 2 * halfLen) + c * (long)pow(10, halfLen) + b);
}
```

```java
/**
 * Karatsuba乘法
 */
public static long karatsuba(long num1, long num2){
    //递归终止条件
    if(num1 < 10 || num2 < 10) return num1 * num2;

    // 计算拆分长度
    int size1 = String.valueOf(num1).length();
    int size2 = String.valueOf(num2).length();
    int halfN = Math.max(size1, size2) / 2;

    /* 拆分为a, b, c, d */
    long a = Long.valueOf(String.valueOf(num1).substring(0, size1 - halfN));
    long b = Long.valueOf(String.valueOf(num1).substring(size1 - halfN));
    long c = Long.valueOf(String.valueOf(num2).substring(0, size2 - halfN));
    long d = Long.valueOf(String.valueOf(num2).substring(size2 - halfN));

    // 计算z2, z0, z1, 此处的乘法使用递归
    long z2 = karatsuba(a, c);
    long z0 = karatsuba(b, d);
    long z1 = karatsuba((a + b), (c + d)) - z0 - z2;

    return (long)(z2 * Math.pow(10, (2*halfN)) + z1 * Math.pow(10, halfN) + z0);
}
```



# 棋盘问题

```cpp
const int maxNum = 1 << 10;
// 棋盘
int chess[maxNum][maxNum];
// L型牌编号
int number;

// row和colum用于定位正在处理哪个区块
void chessBoard(int row, int column,int x, int y, int siz) {
    // 递归出口
    if (siz == 1) {
        return;
    }

    // 对半划分成2^(siz - 1) * 2^(siz - 1)的棋盘
    int s = siz / 2;
    // L型牌编号自增
    int t = ++number;
    // 中间点，以此判别(x,y)在哪个子棋盘中
    int centerRow = row + s;
    int centerColumn = column + s;
    // 黑色方格在左上子棋盘
    if (x < centerRow && y < centerColumn) {
        chessBoard(row, column, x, y, s);
    }
    else {
        // 不在则填充左上子棋盘的右下角
        chess[centerRow - 1][centerColumn - 1] = t;
        // 然后覆盖其他格子，注意这时(x,y)要看做已填充位置
        chessBoard(row, column, centerRow - 1, centerColumn - 1, s);
    }

    // 黑色方格在右上子棋盘
    if (x < centerRow && y >= centerColumn) {
        chessBoard(row, centerColumn, x, y, s);
    }
    else {
        // 不在则填充右上子棋盘的左下角
        chess[centerRow - 1][centerColumn] = t;
        // 然后覆盖其他格子，注意这时(x,y)要看做已填充位置
        chessBoard(row, centerColumn, centerRow - 1, centerColumn, s);
    }

    // 黑色方格在左下子棋盘
    if (x >= centerRow && y < centerColumn) {
        chessBoard(centerRow, column, x, y, s);
    }
    else {
        // 不在则填充左下子棋盘的右上角
        chess[centerRow][centerColumn - 1] = t;
        // 然后覆盖其他格子，注意这时(x,y)要看做已填充位置
        chessBoard(centerRow, column, centerRow, centerColumn - 1, s);
    }

    // 黑色方格在右下子棋盘
    if (x >= centerRow && y >= centerColumn) {
        chessBoard(centerRow, centerColumn, x, y, s);
    }
    else {
        // 不在则填充右下子棋盘的左上角
        chess[centerRow][centerColumn] = t;
        // 然后覆盖其他格子，注意这时(x,y)要看做已填充位置
        chessBoard(centerRow, centerColumn, centerRow, centerColumn, s);
    }

}


int main()
{


    // 大小，黑色方格位置
    int siz, x, y;
    while (true) {
        cout << "(x,y)从(0,0)开始,输入数据为0 0 0即结束程序。" << endl;
        cout << "请输入棋盘大小和黑色方格位置(x,y)：";
        cin >> siz >> x >> y;
        // 退出条件
        if (siz == 0) {
            break;
        }
        // 涂黑(x,y)，初始化L型牌编号
        chess[x][y] = number = 1;

        // 分治法填满棋盘，默认初始选中左上区块，定位为（0,0）
        chessBoard(0,0,x, y, siz);

        // 输出该棋盘
        for (int i = 0; i < siz; i++) {
            for (int j = 0; j < siz; j++) {
                cout << chess[i][j] << "\t";
            }
            cout << endl << endl << endl;
        }
    }
	system("pause");
	return 0;
}
```

* 类似的坐标分析- - 螺旋数组

  ```cpp
  class Solution {
  public:
      vector<vector<int>> generateMatrix(int n) {
          vector<vector<int>> ret(n, vector<int>(n));
  
          int top = 0, bottom = n - 1, left = 0, right = n - 1;
          int num = 0;
  
          while (num <= n * n) {
              /* 从左到右 、从上到下 i都是增加的*/
              for (int i = left; i <= right; i++) 
              {
                  ret[top][i] = ++num;
              }
              top++;
  
              for (int i = top; i <= bottom; i++)
              {
                  ret[i][right] = ++num;
              }
              right--;
  
              /* 从右到左、从下到上 i都是减少的*/
              for (int i = right; i >= left; i--)
              {
                  ret[bottom][i] = ++num;
              }
              bottom--;
  
              for (int i = bottom; i >= top; i--) 
              {
                  ret[i][left] = ++num;
              }
              left++;
  
          }
          return ret;
      }
  };
  ```

  # 第k个最大值