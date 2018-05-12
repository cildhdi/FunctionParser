# function_parsing

提取字符串中的表达式，并能对表达式一次求导


## 支持以下操作符

- +-*/^

- 可使用括号指定优先级

## 用法

函数：

```c++
base_function_ptr function_parse(std::string func_str);
```

传入表达式字符串，返回一个基础函数对象指针：

```c++
using base_function_ptr = std::shared_ptr<base_function>;
```

基础函数声明：

```c++
class base_function
{
public:
	virtual std::string str() = 0;//返回转换后的表达式字符串
	virtual double value(double x) = 0;//返回自变量为x时表达式的值
	virtual base_function_ptr derivative() = 0;//返回导函数
};
```



## 示例

main.cpp  

```c++
#include "function_parsing.h"
#include <iostream>
int main()
{
	auto f = fp::function_parse("(x + 3) ^ 2 + x + 1");
	std::cout << "f(x)=" << f->str() << std::endl;
	std::cout << "f(3)=" << f->value(3) << std::endl;
	auto fd = f->derivative();
	std::cout << "f'(x)=" << fd->str() << std::endl;
	std::cout << "f'(3)=" << fd->value(3) << std::endl;
	return 0;
}
```

有输出：

```
f(x)=((((x+3)^2)+x)+1)
f(3)=40
f'(x)=(((((x+3)^2)*((0*(ln(x+3)))+(2*((1/(x+3))*(1+0)))))+1)+0)
f'(3)=13
```

