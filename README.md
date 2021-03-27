# C++TMP-Scheme

用C++模板元编程实现Scheme语言（的子集）。

## 与Scheme的区别

作为比较的Scheme假定为SICP中的Scheme解释器对应的语言。现实中的Scheme语言所包含的各种额外特性均不考虑。

- 因为C++不能用浮点数作为模板参数，所以没有浮点类型。
- C++模板的数据结构是不可变的。因此，所有数据结构不可变，也没有 `set-car!` 这样的函数。
- 没有引用的概念，也没有 `eq?` 内建函数。
- 环境也是不可变的。这意味着：
  - `define` 和 `set!` 都只是增加/修改一个变量绑定；
  - 闭包在捕获环境的时候，只能捕获此刻的环境，之后增加/修改的绑定不会改变捕获时的环境；
  - 无法直接实现递归（需要使用预定义的Y组合子）。
  - 函数调用永远不会改变环境（不包括参数的计算）。
- 不提供 `let` ，因为 `define` 具有同样的性质。

## 对应关系

Scheme表达式 | C++模板 | 辅助宏
--- | --- | ---
`#t` | `Bool<true>` | `boolean(true)`
`1` | `Int<1>` | `num(1)`
`"str"` | `String<'s', 't', 'r'>` | `str("str")`
`name` | `Symbol<'n', 'a', 'm', 'e'>` | `sym("name")`
`()` | `Nil` | `S()`
`(A B C)` | `Cons<A, Cons<B, Cons<C, Nil>>>` | `S(A, B, C)`

此外，还提供了一些进一步简化编写的宏：

Scheme表达式 | 原始的辅助宏 | 简化宏
--- | --- | ---
`(define x A)` | `S(sym("define"), sym("x"), A)` | `define("x", A)`
`(set! x A)` | `S(sym("set!"), sym("x"), A)` | `set("x", A)`
`(lambda X A)` | `S(sym("lambda"), X, A)` | `lambda(X, A)`
`(if A B C)` | `S(sym("if"), A, B, C)` | `ifelse(A, B, C)`
`(f ...)` | `S(sym("f"), ...)` | `call("f", ...)`
`'A` | `S(sym("quote"), A)` | `q(A)`
`,A` | `S(sym("unquote"), A)` | `uq(A)`
`` `A`` | `S(sym("quasiquote"), A)` | `qq(A)`
`(define (f ...) ...)` | `define("f", call("Y", lambda(S(sym("f")), lambda(..., ...))))` | `defun(f, ..., ...)`
`(cond (A B) ... (else C))` | `ifelse(A, B, ifelse(... C))` | `cond(A, B, ..., C)`

## 标准函数

使用 `empty_env` 获得空环境，使用 `std_env` 获得包含了标准函数的环境。

标准函数包括一部分内建函数，以及一部分预定义的函数。

函数名 | 参数数量 | 含义 | 预定义/内建
--- | --- | --- | ---
`apply` | 2 | 用第二个参数（列表）作为调用的参数，调用第一个参数 | 内建
`eval` | 1 | 将参数作为命令执行 | 内建
`atom?` | 1 | 是否是原子 | 内建
`bool?` | 1 | 是否是布尔值 | 内建
`int?` | 1 | 是否是整数 | 内建
`string?` | 1 | 是否是字符串 | 内建
`symbol?` | 1 | 是否是符号 | 内建
`pair?` | 1 | 是否是Cons结构 | 内建
`list?` | 1 | 是否组成列表结构 | 内建
`car` | 1 | 返回Cons的表头部分 | 内建
`cdr` | 1 | 返回Cons的表尾部分| 内建
`cons` | 2 | 构造Cons结构 | 内建
`list` | N | 构造列表 | 内建
`+` | N | 整数加法 | 内建
`-` | 2 | 整数减法 | 内建
`*` | N | 整数乘法 | 内建
`/` | 2 | 整数除法 | 内建
`%` | 2 | 整数取模（C意义） | 内建
`not` | 1 | 取反 | 内建
`and` | N | 与（非短路） | 内建
`or` | N | 或（非短路） | 内建
`equal?` | 2 | 判断两个表达式是否相同 | 内建
`=` | 2 | 判断整数相等 | 内建
`>` | 2 | 判断整数大于 | 内建
`<` | 2 | 判断整数小于 | 预定义
`>=` | 2 | 判断整数大于等于 | 预定义
`<=` | 2 | 判断整数小于等于 | 预定义
`!=` | 2 | 判断整数不等 | 预定义
`Y` | 1 | Y组合子 | 预定义

## 使用

用辅助宏和简化宏来编写代码。就像下面这样：

```c++
using code = S(
    defun("fib",
        S(sym("n")),
        cond(
            call("=", sym("n"), num(0)), num(0),
            call("=", sym("n"), num(1)), num(1),
            call("+", call("fib", call("-", sym("n"), num(1))),
                      call("fib", call("-", sym("n"), num(2))))
        )),
    call("fib", num(5)));
```

使用 `print<T>()` 来打印表达式：

```c++
print<code>();
```

使用`scheme<T>()` 来执行语句：

```c++
print<scheme<code>>(); // 5
```

## 更多例子

- [numerics.cpp](src/numerics.cpp) SICP第一章的一些例子，包括斐波那契数、最大公因数、素性检验；
- [lists.cpp](src/lists.cpp) SICP 2.1里的一些例子，简单的列表操作；
- [scheme.cpp](src/scheme.cpp) SICP 4.1，Scheme解释器 **没写完，编译器内存不够炸了，不写了**