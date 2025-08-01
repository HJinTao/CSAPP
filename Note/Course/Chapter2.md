# Chapter 2 信息的表示和处理

## 一、整数

### 1.整数表示

整数类型分为两类，**补码(two's-complement)**表示的**有符号数**和**无符号数编码(unsigned)**的**无符号数**

在进行探究之前，我们先引入位数位**w**的位向量 **x**
$$
\vec{x}  = [x_{w-1},x_{w-2},\cdots ,x_{0}]
$$

>  位向量是计算机位级上的表示，我们可以把它看成一个二进制数字，但是要与补码数字 **B2T(x)** 与 无符号数  **B2U(x)** 进行区分(这也是容易产生混淆的点)



### a.无符号数 unsigned

$$
B2U_w(\vec{x} )= \sum_{i=0}^{w-1}x_iw_i
$$

该函数是一个**双射函数**，因而存在反函数 **U2B** 。值域如下
$$
Range(B2U_w)  =[0,2^{w-1}]
\\
UMax_w = 2^{w-1}
$$


### b.补码 two's-complement

$$
B2T_w(\vec{x} )= -2^{w-1} x_{w-1}+ \sum_{i=0}^{w-2}x_iw_i 
$$

该函数也是一个**双射函数**，因而存在反函数 **T2B** 。值域如下
$$
Range(B2T_w)  =[-2^{w-2},2^{w-2} - 1]
\\
TMax_w = 2^{w-2} - 1
\\
TMin_w = -2^{w-2}
$$

> 这里注意 **TMax 的**两个性质 ，在 DataLab 中 **isTMax**函数的实现中会用到
>
> ①TMax + TMin = -1
>
> ②Tmax + 1 = Tmin





### c.无符号数与有符号数之间的相互转换

#### 应用场景：

C语言允许各种不同的数字数据类型之间做**类型转换**，分为 **强制类型转换** 和 **隐式类型转换** 

> 当一个运算的运算数同时存在有符号数和无符号数时，C语言会隐式地将**有符号数隐式类型转换为无符号数**

**类型转换的结果是保持位向量也就是位值不变，只是改变了解释这些位的方式**



#### 数学原理：

#####  **T2U**

由二元关系的复合运算，我们定义有符号数转换为无符号数函数 **T2U** 
$$
T2U = T2B \circ B2U
$$
该函数的直接定义可由**补码与无符号编码对同一位向量的不同解释**得来，也就是
$$
\begin{equation}
  T2U_w(\vec{x}) =
  \begin{cases}
    x + 2^w & TMin_w\le x < 0
\\
    x & 0 \le x \le TMax_w
  \end{cases}
\end{equation}
$$

> 式子右侧的**x**是**符号数x**，为了方便所以进行简写



##### U2T

同理
$$
\begin{equation}
  U2T_w(\vec{x}) =
  \begin{cases}
    x & 0 \le x \le TMax
\\
    x - 2^w & TMax_w + 1 \le x \le UMax_w
  \end{cases}
\end{equation}
$$




### d.拓展一个数字的位表示

#### 应用场景：

​	一个常见的运算是在不同字长的整数之间切换，同时又保持数值不变，从一个字长较小的数据类型转换为字长较大的数据类型就需要拓展一个数字的位表示

#### 数学原理

##### 无符号数的零拓展

$$
\vec{x}  = [x_{w-1},x_{w-2},\cdots ,x_{0}]
\\
\vec{y}  = [0,0,0,\cdots ,x_{w-1},x_{w-2},\cdots ,x_{0}]
$$



##### 符号数的符号拓展

$$
\vec{x}  = [x_{w-1},x_{w-2},\cdots ,x_{0}]
\\
\vec{y}  = [x_{w-1},x_{w-1},x_{w-1},\cdots ,x_{w-1},x_{w-2},\cdots ,x_{0}]
$$

> 符号扩展的具体数学原理可由等比数列的求和得出，不再赘述



#### 注

值得一提的是。**从一个数据字长到另一个数据字长的转换**，以及**无符号和有符号之间的转换**，这两个转换的相对顺序能够影响一个程序的行为。

```c
short sx = -12345;
unsigned uy = sx;    // 这里实际等价于 (unsigned)(int) sx 而不等价于(unsigned)(unsigned short) sx

printf("uy = %u:\t",uy);
```



### e.截断数字

#### 应用场景：

```c
int x = 53191;
short sx = (short) x;    // -12345 
int y = sx;       //-12345
```



#### 数学原理

##### 无符号数的截断

将**w位的位向量x**截断为**k位的位向量y**
$$
\vec{x}  = [x_{w-1},x_{w-2},\cdots ,x_{0}]
\\
\vec{y}  = [x_{k-1},x_{w-2},\cdots ,x_{0}]
$$
于是我们有
$$
B2U_k(\vec{x} ) = B2U_w(\vec{x} ) \bmod 2^k
$$
**LHS**就是被截断后的无符号数十进制表示



##### 有符号数的截断

与无符号数相似，不同的是要将**最高位(k-1)**转换成符号位
$$
\vec{x}  = [x_{w-1},x_{w-2},\cdots ,x_{0}]
\\
\vec{y}  = [x_{k-1},x_{w-2},\cdots ,x_{0}]
$$


由于无符号数和有符号数的位级表示也就是位向量是一致的，所以我们可以先假设为**无符号数的截断**，之后再进行**无符号数到有符号数的转换**即可。也就是
$$
B2T_k(\vec{x} ) = U2T_k(B2U_w(\vec{x}) \bmod 2^k)
$$


### 2. 整数运算

#### a.加法

##### 无符号加法

对于无符号的加法，我们引入新二元运算符
$$
^u_w+
$$
由位向量相加的性质我们可得
$$
\begin{equation}
  x^u_w+y =
  \begin{cases}
    x+y & 0 \le x \le TMax_w & \text{正常} 
\\
    x+y-2^w & TMax_w <  x < 2^{w+1}  & \text{溢出} 
  \end{cases}
\end{equation}
$$
也就是当溢出的时候，会**截断**位向量 **x + y** 的 **第w位**

> 注，无符号数x+y的范围如下
> $$
> [0,2^{w+1} - 2]
> $$



基于此，我们有

```c
/*判断x+y是否溢出，若溢出则返回0，反之返回1*/
int udd_ok(unsigned x,unsigned y){
    unsigned sum = x + y;
    return sum >= x;
}
```



##### 无符号减法

模数加法形成了阿贝尔群，它有一个单位元0，并且每个元素有一个加法逆元，也就是存在
$$
^u_w-x + ^u_wx = 0
$$
由位向量的性质，我们有
$$
\begin{equation}
  ^u_w-x =
  \begin{cases}
    x & x=0
\\
    2^w - x & 0 < x \le UMax_w
  \end{cases}
\end{equation}
$$


##### 补码加法

两个数的 **w** 位补码之和与无符号之和有完全相同的位级表示，因此我们有
$$
\begin{equation}
  x^t_w+y =
  \begin{cases}
    x +y- 2^w & 2^{w-1} \le x+y \le 2^w - 2 & \text{正溢出} 
\\
    x+y & TMin_w \le x + y \le TMax_w & \text{正常} 
\\
    x+y+2^w &  -2^w \le  x + y < -2^{w-1}  & \text{负溢出} 
  \end{cases}
\end{equation}
$$

> 注，符号数x+y的范围如下
> $$
> [-2^w,2^{w} - 2]
> $$



基于此，我们有

```c
/*判断x+y是否溢出，若溢出则返回0，反之返回1*/
int udd_ok(int x,int y){
    int sum = x + y;
    return (sum >= 0 && x>= 0 && y >= 0) && (sum <= 0 && x <= 0 && y <= 0);
}
```



##### 补码减法

与无符号减法同理，我们有
$$
\begin{equation}
  ^t_w-x =
  \begin{cases}
    TMin_w & x=TMin_w
\\
     - x & TMin_w < x \le TMax_w
  \end{cases}
\end{equation}
$$


> 对于补码减法的位级表示，我们有
> $$
> \sim \vec{x} +\vec{1} = -\vec{x}
> $$
> 



### b.乘法

#### 无符号乘法

#### 无符号除法

#### 补码乘法

#### 补码除法







