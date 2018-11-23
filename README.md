# FunctionParser

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/eeee632c2a044e4fa52ad7d0b86dfcb3)](https://app.codacy.com/app/cildhdi/function_parsing?utm_source=github.com&utm_medium=referral&utm_content=cildhdi/function_parsing&utm_campaign=Badge_Grade_Dashboard)
[![Build Status](https://travis-ci.com/cildhdi/function_parsing.svg?branch=master)](https://travis-ci.com/cildhdi/function_parsing)

提取字符串中的表达式，并能对表达式连续求导


## 支持

- +-*/^
- ln,sin,cos,tan
- 支持分段函数
- 可使用括号指定优先级

## 用法

函数：

```c++
BaseFunctionPtr FunctionParser::parse(std::string func_str);
```

main.cpp:

```c++
#include "FunctionParser.h"
#include <iostream>
using namespace cl;
int main()
{
	std::string str;
	std::cout << "input f(x)= ";
	std::cin >> str;
	try
	{
        FunctionParser parser;
		auto f = parser.parse(str);
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

