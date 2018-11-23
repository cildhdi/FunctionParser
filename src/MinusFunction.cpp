#include <MinusFunction.h>

namespace cl
{

MinusFunction::MinusFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs) : _lhs(lhs), _rhs(rhs), BaseFunction(T_MINUS_FUNCTION)
{
}

std::string MinusFunction::str()
{
    return "(" + _lhs->str() + "-" + _rhs->str() + ")";
}

double MinusFunction::value(double x)
{
    return _lhs->value(x) - _rhs->value(x);
}

BaseFunctionPtr MinusFunction::derivative()
{
    return std::make_shared<MinusFunction>(_lhs->derivative(), _rhs->derivative());
}

} // namespace cl
