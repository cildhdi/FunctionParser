#include <MultiplyFunction.h>
#include <AddFunction.h>

namespace cl
{

MultiplyFunction::MultiplyFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs) : _lhs(lhs), _rhs(rhs), BaseFunction(T_MULTIPLY_FUNCTION)
{
}

std::string MultiplyFunction::str() const
{
    return "(" + _lhs->str() + "*" + _rhs->str() + ")";
}

double MultiplyFunction::value(double x) const
{
    return _lhs->value(x) * _rhs->value(x);
}

BaseFunctionPtr MultiplyFunction::derivative() const
{
    return std::make_shared<AddFunction>(std::make_shared<MultiplyFunction>(_lhs->derivative(), _rhs), std::make_shared<MultiplyFunction>(_lhs, _rhs->derivative()));
}

} // namespace cl
