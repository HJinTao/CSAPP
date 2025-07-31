# DataLab Note



## 1.Lab说明



## 2.bits.c

### 1. bitXor

- #### Description

	* **int bitXor(int x,int y)**

	* bitXor - x^y using only ~ and &

	* Example: bitXor(4, 5) = 1

	* **Legal ops: ~ &**

	* **Max ops: 14**

	* Rating: 1

	**只用合法运算符实现异或运算**

- #### Analysis

	由离散数学主析取范式与命题运算可知

- #### Solution

	```c
	int bitXor(int x, int y) {
	  return ~(~(~x & y) & ~(~y & x));
	}
	```

​	

### 2. tmin

- #### Description

	* **int tmin(void)**

	* tmin - return minimum two's complement integer 

	* **Legal ops: ! ~ & ^ | + << >>**

	* **Max ops: 4**

	* Rating: 1

	 **只用合法运算符返回TMin_32**

- #### Analysis

	由补码知识可知，`(TMin_32)INT_32`编码范围为
	$$
	-2^{31} \le x \le 2^{31} - 1
	$$
	正溢出会映射到负数，也就是
	$$
	TMin_{32} = -2^{31} = 2^{31} - 2^{32}
	$$
	

- #### Solution

	```c
	int tmin(void) {
	  return 1 << 31;
	}
	```



### 3. isTmax

- #### Description

	 - **int isTmax(int x)**
	 - isTmax - returns 1 if x is the maximum, two's complement number, and 0 otherwise 
	 - **Legal ops: ! ~ & ^ | +**
	 - **Max ops: 10**
	 - Rating: 1

	**判断x是否是TMax_32，是的话返回1，不是的话返回0**

- #### Analysis

	我们知道**TMin_32** 和 **TMax_32**的补码表示如下

$$
TMax_{32} = \verb|0x7FFFFFFF|
\\
TMin_{32}=\verb|0x80000000|
\\
$$



​		因而引出**TMax_32**的两个性质
$$
TMax_{32} + 1 = TMin_{32} 
\\ 
TMax_{32} + TMin{32}=\verb|0xFFFFFFFF|
$$
​				

- #### Solution

	```c
	int isTmax(int x) {
	  //通过!运算将~sum转换为只有一个有效数字的 0x00000001 方便后面的&操作
	  // !!min 是为了避免x=-1也就是0xFFFFFFF时min == 0的情况
	  int min = x + 1;
	  int sum = min + x;   
	  return !(~sum) & !!min; 
	}
	```



### 4.allOddBits





