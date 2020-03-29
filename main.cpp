#include <iostream>

#include "include/FunctionParser.h"
using namespace cl;
int main() {
  std::string str;
  std::cout << "input f(x)= ";
  std::cin >> str;
  try {
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
  } catch (std::exception& e) {
    std::cout << "fail to parse:" << e.what();
  }
  return 0;
}