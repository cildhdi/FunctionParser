#include "function_parsing.h"
#include <iostream>
int main()
{
	auto func1 =
		std::make_shared<fp::multiply_function>(std::make_shared<fp::constant_function>(32), std::make_shared<fp::independent_variable>("x"));
	auto func = std::make_shared<fp::power_function>(std::make_shared<fp::independent_variable>("x"), func1);
	std::cout << "f(x)=" << func->str() << std::endl;
	std::cout << "f(5)=" << func->value(2);
	system("pause");
	return 0;
}
/*
	第一行			第二行			期望输出
	3*x+1			5				16
	x^2+2*x+1		4				25
	3*x^2/(2x+1)	1				1
*/