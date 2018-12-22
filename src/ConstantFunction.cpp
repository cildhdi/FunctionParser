#include <ConstantFunction.h>

namespace cl
{

ConstantFunction::ConstantFunction(double c) : _c(c), BaseFunction(T_CONSTANT_FUNCTION)
{
}

std::string ConstantFunction::str() const
{
    auto str = std::to_string(_c);
    while ((!str.empty()) && str.at(str.size() - 1) == '0')
    {
        str.pop_back();
    }
    if (!str.empty() && str.at(str.size() - 1) == '.')
    {
        str.pop_back();
    }
    return str;
}

double ConstantFunction::value(double x) const
{
    return _c;
}

BaseFunctionPtr ConstantFunction::derivative() const
{
    return std::make_shared<ConstantFunction>(0);
}

} // namespace cl
