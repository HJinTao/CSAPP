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

- #### Description

	 - **int allOddBits(int *x*)**
	 - allOddBits - return 1 if all odd-numbered bits in word set to 1 where bits are numbered from 0 (least significant) to 31 (most significant)
	 - Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
	 - **Legal ops: ! ~ & ^ | + << >>**
	 - Max ops: 12
	 - Rating: 2

	**判断x的奇数位上是否都是1，如果是则返回1，不是的话返回0**

- #### Analysis

	我们首先引入 **掩码** **(mask)** 的概念

	考虑如下真值表

	| x    | y    | x & y |
	| ---- | ---- | ----- |
	| 0    | 0    | 0     |
	| 0    | 1    | 0     |
	| 1    | 0    | 0     |
	| 1    | 1    | 1     |

	我们可以发现，当 `x` 为 0 时，无论 `y` 为什么，`x & y` 都为 0；当 `x` 为 1 时，无论 `y` 为什么，`x & y` 都为 `y`。

	基于这个特性，我们可以构造一个 `mask`，以之对某个数进行 `&` 运算，从而实现将某些位清零，而保留其他位不变的目的。

​		基于此思想，我们可以构造 **mask** `0xAAAAAAAA`  来提取**x的奇数位**

- #### Solution

	```c
	int allOddBits(int x) {
		// 构造补码0xAAAAAAAA同时利用a~a == 0的性质  同时注意运算符优先级
		int mask = (0xAA << 8) + (0xAA << 16) + (0xAA << 24) + 0xAA;
		int check = mask & x;
		return !(check ^ mask);
	}
	```



### 5.negate

- #### Description

	 - **int negate(int *x*)**
	 - **negate - return -x** 
	 - Example: negate(1) = -1.
	 - **Legal ops: ! ~ & ^ | + << >>**
	 - Max ops: 5
	 - Rating: 2

​		**返回 -x**

- #### Solution

	```c
	int negate(int x) {
		// 负数的补码是正数的反码加1
	  	return ~x + 1;
	}
	```

	

### 6.isAsciiDigit

- #### Description

	 - int isAsciiDigit(int *x*)
	 - **isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')**
	 - Example: isAsciiDigit(0x35) = 1.
	 - isAsciiDigit(0x3a) = 0.
	 - isAsciiDigit(0x05) = 0.
	 - **Legal ops: ! ~ & ^ | + << >>**
	 - Max ops: 15
	 - Rating: 3

	**返回 0x30 <= x <= 0x39** 

- #### Analysis

	依旧利用 **mask** ，详解见注释

- #### Solution

	```c
	int isAsciiDigit(int x) {
		// 将x分为两部分判断,如x == 0x000000c1时,判断0x0000 00c 和 0x0000 0001
		int check1 = !((x >> 4) ^ 0x3);    // check1 == 1 -> 右移4位后是0x3000 0000
		int check2 = (x >> 3) & 0x1; 	   // check2 == 1 -> x的第3位(从0位开始)是1
		int check3 = ((x >> 1) | 0x0) | ((x >> 2) | 0x0);   // check3 == 1 -> x的第1位和第二位里面至少有一个是1
		int check4 = !(check2 & check3);  				// check4 == 1  -> HEX下的x的第0位数字 < a
		return check1 & check4;
	}
	```

	





