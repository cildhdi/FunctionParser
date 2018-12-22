#include <AddFunction.h>

namespace cl
{

AddFunction::AddFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs) : _lhs(lhs), _rhs(rhs), BaseFunction(T_ADD_FUNCTION)
{
}

std::string AddFunction::str() const
{
    return "(" + _lhs->str() + "+" + _rhs->str() + ")";
}

double AddFunction::value(double x) const
{
    return _lhs->value(x) + _rhs->value(x);
}

BaseFunctionPtr AddFunction::derivative() const
{
    return std::make_shared<AddFunction>(_lhs->derivative(), _rhs->derivative());
}

} // namespace cl
