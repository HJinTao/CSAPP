# DataLab Note



## 1.Lab说明

**NONE**

## 2.bits.c

### 1. bitXor

- #### Description

	* bitXor - x^y using only ~ and &
	* **Legal ops: ~ &**
	
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

	* tmin - return minimum two's complement integer 
	* **Legal ops: ! ~ & ^ | + << >>**
	
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

	  - isTmax - returns 1 if x is the maximum, two's complement number, and 0 otherwise 
	 - **Legal ops: ! ~ & ^ | +**
	
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

	  - allOddBits - return 1 if all odd-numbered bits in word set to 1 where bits are numbered from 0 (least significant) to 31 (most significant)
	 - Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
	 - **Legal ops: ! ~ & ^ | + << >>**
	
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

	  - **negate - return -x** 
	 - **Legal ops: ! ~ & ^ | + << >>**

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

	  - **isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')**
	 - **Legal ops: ! ~ & ^ | + << >>**
	
	**返回表达式 `0x30 <= x <= 0x39` 的值** 
	
- #### Analysis

  本题的本质是判断**x是否在某个区间里面**，我们可以采用作差后判断结果是否是负数的方法来确定。

  **注：可以通过差的补码最高位符号来判断正负**

- #### Solution

	```c
	int isAsciiDigit(int x) {
		int lower_bound = x + (~0x30 + 1);  // x - 0x30
	  	int upper_bound = 0x39 + (~x + 1); // 0x39 - x
	  	return !(lower_bound >> 31) & !(upper_bound >> 31);
	}
	```
	



### 7.conditional

- #### Description

	 * **conditional - same as x ? y : z** 
	 * Example: conditional(2,4,5) = 4
	 * Legal ops: ! ~ & ^ | + << >>

	**返回表达式 `x ? y : z ` 的值**

- #### Analysis

	我们可以通过构造**掩码`mask`** 的方式来**决定取y还是取z**

	我们注意到**mask = 0xFFFFFFF(-1)时代表取这个数的所有位，mask = 0x00000000(0)时代表一个位也不取**

	于是我们有如下**Solution**

- #### Solution

	```c
	int conditional(int x, int y, int z) {
		int mask = ~(!x) + 1;
		return (z & mask) | (y & ~mask);
	}
	```



### 8.isLessOrEqual

参考**6.isAsciiDigit**，不再赘述

```c
int isLessOrEqual(int x, int y) {
   /*作差后判断是否是负数,也就是最高位是否是0*/
	int diff = y + (~x + 1);
	return !(diff >> 31);
}
```



### 9.logicalNeg

- #### Description

	* **logicalNeg - implement the ! operator, using all of the legal operators except** 

	* Examples: logicalNeg(3) = 0, logicalNeg(0) = 1

	* Legal ops: ~ & ^ | + << >>

	**实现 ! 运算**

- #### Solution

	```c
	int logicalNeg(int x) {
	   /*根据 0和0的相反数 的补码最高位都是0这个特点*/
		return ((x | (~x + 1)) >> 31) + 1;
	}
	```



### 10.howManyBits

- #### Description

	* **howManyBits - return the minimum number of bits required to represent x in *two's complement***

	 *  Examples: howManyBits(12) = 5

	 *            howManyBits(298) = 10

	 *            howManyBits(-5) = 4

	 *            **howManyBits(0)  = 1**

	 *            **howManyBits(-1) = 1**

	 *            howManyBits(0x80000000) = 32
	 *            Legal ops: ! ~ & ^ | + << >>
	 *            Max ops: **90**

	**返回一个数的补码需要至少几位数字，注意-1(其实是所有负数)这个特殊情况，只需要补码 `1` 就可以表示**

- #### Analysis

	个人认为这是DataLab中难度系数最高的函数，由最大允许的操作符个数 **90** 可见一般
	
	解析见下
	
- #### Solution

  ```c
  int howManyBits(int x) {
     /*利用x^0xffffffff == ~x的性质对负数取反 之后利用二分法的思路寻找最高位1的位数*/
     int sign,b16,b8,b4,b2,b1,b0;
     sign = x >> 31;
     x ^= sign;
     b16 = !!(x >> 16) << 4;
     x >>= b16;
     b8 = !!(x >> 8) << 3;
     x >>= b8;
     b4 = !!(x >> 4) << 2;
     x >>= b4;
     b2 = !!(x >> 2) << 1;
     x >>= b2;
     b1 = !!(x >> 1) << 1;
     x >>= b1;
     b0 = x;
     return 1 + b0 + b1 + b2 + b4 + b8 + b16; 
  }
  ```



### 11.floatScale2

- #### Description

	- Return bit-level equivalent of expression 2 * f for floating point argument f.
	- When argument is NaN, return argument

	**返回2*f的结果**

- #### Analysis

	**float32** 的位表示是1个符号位，8个指数位，23个小数位。基于此，我们只需把各个部分的位表示提取出来再进行判断即可。

- #### Solution

	```c
	unsigned floatScale2(unsigned uf) {
	   unsigned exp,frac,sign,res;
	   exp = (uf >> 23) & 0xff;
	   frac = uf & 0x7FFFFF;
	   sign = uf >> 31;
	   if(!exp){
	      return (uf << 1) | (sign << 31);    //这里可以看出denorm的E = 1-Bias而不是E = -Bias的好处
	   }
	   else if(exp == 0xff){ 
	      return uf;
	   }
	   else{
	      exp += 1;
	      if(exp == 0xff){
	         return 0x7F800000 | (sign << 31);
	      }
	   }
	   res = (sign << 31) | (exp << 23) | frac;
	   return res;
	}
	```

	



### 12. floatFloat2Int

- #### Description

	* Return bit-level equivalent of **expression (int) f** for floating point argument **f**.
	* Argument is passed as unsigned int, but it is to be interpreted as the bit-level representation of a single-precision floating point value.
	* Anything out of range (including NaN and infinity) should return 0x80000000u.
	* Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while

	**实现 `(int) f` ，值得注意的是这里允许if else while的使用**

- #### Analysis

	**float32** 的位表示是1个符号位，8个指数位，23个小数位。基于此，我们只需把各个部分的位表示提取出来再进行判断即可。

- #### Solution

	```c
	int floatFloat2Int(unsigned uf) {
	   unsigned exp,Bias;
	   int E,frac,sign;
	   Bias = 127;
	   sign = uf & 0x80000000;
	   exp = (uf >> 23) & 0xff;
	   frac = uf & 0x7fffff;
	   E = exp - Bias;   
	
	   if(E >= 32){
	      return 0x80000000u;
	   }
	   else if(E < 0){   //包含了 denorm 的情况
	      return 0;
	   }
	   else{
	      return (frac | 0x800000 | (sign >> 7)) >> 23 << E;
	   }
	}
	```

	

### 13.floatPower2

- #### Description

	- floatPower2 - Return bit-level equivalent of the expression 2.0^x，(2.0 raised to the power x) for any 32-bit integer x.
	- If the result is too small to be represented as a denorm, return 0. If too large, return +INF.

	**返回2的整数次幂的float32位表示，如果是denorm，返回0，如果太大，返回+INF**

- #### Analysis

	无额外注意事项，同上述两题即可

- #### Solution

	```c
	unsigned floatPower2(int x) {
	   int exp = x + 127;
	   if(exp <= 0){
	      return 0;
	   }
	   else if(exp >= 0xff){
	      return 0xff << 23;
	   }
	   else{
	      return exp << 23;
	   }
	}
	```

	

