# FunctionParser

[![Build Status](https://travis-ci.com/cildhdi/FunctionParser.svg?branch=master)](https://travis-ci.com/cildhdi/FunctionParser)

提取字符串中的表达式，并能对表达式连续求导


## 支持
- +-*/^
- ln,sin,cos,tan
- 支持分段函数
- 可使用括号指定优先级

## 如何build
### linux
先安装gtest（不需要测试可以不安装，可直接使用scripts/install_gtest.sh）与cmake，然后直接运行scripts/build.sh，成功后得库文件与测试程序均在build文件夹内。
### windows
对gtest与cmake的要求和linux相同，可以使用[vcpkg](https://github.com/Microsoft/vcpkg)来快速安装gtest，然后cmake时指定CMAKE_TOOLCHAIN_FILE的值（安装完vcpkg后会给出vcpkg.cmake文件的路径）。

## 用法

函数：

```c++
BaseFunctionPtr FunctionParser::parse(std::string func_str);
```

示例：

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

