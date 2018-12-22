#include <IndependentVariable.h>
#include <ConstantFunction.h>

namespace cl
{

IndependentVariable::IndependentVariable(const std::string &iv) : _iv(iv), BaseFunction(T_INDEPENDENT_VARIABLE)
{
}

std::string IndependentVariable::str() const
{
    return _iv;
}

double IndependentVariable::value(double x) const
{
    return x;
}

BaseFunctionPtr IndependentVariable::derivative() const
{
    return std::make_shared<ConstantFunction>(1);
}

} // namespace cl
