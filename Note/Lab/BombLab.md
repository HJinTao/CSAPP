# BombLab

## 1.GDB 基础

### 1. 启动与运行

```bash
gdb <program>
```

- `<program>` ：你要调试的可执行文件（比如 `./bomb`）。

在 gdb 内运行：

```gdb
run [args]
```

- `args` ：传给程序的命令行参数（Bomb Lab 通常没有）。

- 可以用 `< file` 让程序从文件读取输入，例如：

  ```gdb
  run < input.txt
  ```

------

### 2. 断点（breakpoint）

格式：

```gdb
break [location]
```

常见 `location` 写法：

- `break function_name` → 在函数入口处停下
- `break *0xADDR` → 在指定内存地址停下
- `break filename:line` → 在某源文件某行停下（需要有源码调试信息）

相关命令：

```gdb
delete [num]   # 删除断点（num 是断点编号，不写就是全部）
info break     # 显示所有断点
```

------

### 3. 单步执行

- **机器指令级**：

  ```gdb
  stepi (或 si)     # 执行一条指令，进入函数
  nexti (或 ni)     # 执行一条指令，遇到 call 不进入
  continue (或 c)   # 继续运行，直到下一个断点
  ```

------

### 4. 查看寄存器

```gdb
info registers [reg ...]
```

- `[reg ...]` ：可选，列出具体寄存器名（如 `rdi rsi rax`）。不写则显示所有。

```gdb
print $reg
```

- `$reg` ：寄存器名，用 `$` 引用（如 `$rax`）。显示整数值。

```gdb
x/s $reg
```

- `x` = examine 内存
- `/s` = 按 C 字符串显示（从寄存器里取出地址并打印字符串）

------

### 5. 查看内存

通用语法：

```gdb
x/[N][F][U] <expr>
```

- `N` ：要显示多少个单元（默认 1）
- `F` ：显示格式
  - `x` (十六进制), `d` (十进制), `s` (字符串), `i` (反汇编指令)
- `U` ：单元大小
  - `b` (字节), `h` (2 字节), `w` (4 字节), `g` (8 字节)
- `<expr>` ：地址或寄存器表达式

例子：

```gdb
x/16gx $rsp   # 查看栈顶16个8字节
x/s 0x402400  # 把0x402400处内容当字符串显示
x/4i $rip     # 从rip开始反汇编4条指令
```

------

### 6. 反汇编

```gdb
disassemble [function | addr[,addr]]
```

- `function` ：函数名（如 `disas phase_2`）
- `addr` ：地址范围（如 `disas 0x400f50,0x400f80`）



## 2.Bomb





# maduiersnfotvbyl	















