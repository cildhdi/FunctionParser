#include <MinusFunction.h>

namespace cl
{

MinusFunction::MinusFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs) : _lhs(lhs), _rhs(rhs), BaseFunction(T_MINUS_FUNCTION)
{
}

std::string MinusFunction::str() const
{
    return "(" + _lhs->str() + "-" + _rhs->str() + ")";
}

double MinusFunction::value(double x) const
{
    return _lhs->value(x) - _rhs->value(x);
}

BaseFunctionPtr MinusFunction::derivative() const
{
    return std::make_shared<MinusFunction>(_lhs->derivative(), _rhs->derivative());
}

} // namespace cl
