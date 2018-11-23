#include <IndependentVariable.h>
#include <ConstantFunction.h>

namespace cl
{

IndependentVariable::IndependentVariable(const std::string &iv) : _iv(iv), BaseFunction(T_INDEPENDENT_VARIABLE)
{
}

std::string IndependentVariable::str()
{
    return _iv;
}

double IndependentVariable::value(double x)
{
    return x;
}

BaseFunctionPtr IndependentVariable::derivative()
{
    return std::make_shared<ConstantFunction>(1);
}

} // namespace cl
