# function_parsing

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/eeee632c2a044e4fa52ad7d0b86dfcb3)](https://app.codacy.com/app/cildhdi/function_parsing?utm_source=github.com&utm_medium=referral&utm_content=cildhdi/function_parsing&utm_campaign=Badge_Grade_Dashboard)
[![Build Status](https://travis-ci.com/cildhdi/function_parsing.svg?branch=master)](https://travis-ci.com/cildhdi/function_parsing)

提取字符串中的表达式，并能对表达式连续求导


## 支持

- +-*/^
- ln,sin,cos
- 可使用括号指定优先级

## 用法

函数：

```c++
BaseFunctionPtr function_parse(std::string func_str);
```

传入表达式字符串，返回一个基础函数对象指针：

```c++
using BaseFunctionPtr = std::shared_ptr<BaseFunction>;
```

基础函数声明：

```c++
class BaseFunction
{
public:
	virtual std::string str() = 0;//返回转换后的表达式字符串
	virtual double value(double x) = 0;//返回自变量为x时表达式的值
	virtual BaseFunctionPtr derivative() = 0;//返回导函数
};
```



## 示例

main.cpp  

```c++
#include "function_parsing.h"
#include <iostream>
int main()
{
	std::string str;
	std::cout << "input f(x)= ";
	std::cin >> str;
	try
	{
		auto f = fp::function_parse(str);
		auto fd = f->derivative();
		std::cout << "f(x)=" << f->str() << std::endl;
		std::cout << "f'(x)=" << fd->str() << std::endl;
		double x;
		std::cout << "input x= ";
		std::cin >> x;
		std::cout << "f(" << x << ")=" << f->value(x) << std::endl;
		std::cout << "f'(" << x << ")=" << fd->value(x) << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "fail to parse:" << e.what();
	}
	return 0;
}
```

输入x+x*sin(x+1)/3 与 3，则有输出：

```
input f(x)= x+x*sin(x+1)/3
f(x)=(x+((x*(sin(x+1)))/3))
f'(x)=(1+(((((1*(sin(x+1)))+(x*((cos(x+1))*(1+0))))*3)-((x*(sin(x+1)))*0))/(3*3)))
input x= 3
f(3)=2.2432
f'(3)=0.0940889
```

