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
	system("pause");
	return 0;
}