#include <PowerFunction.h>
#include <MultiplyFunction.h>
#include <ConstantFunction.h>
#include <LnFunction.h>
#include <AddFunction.h>

namespace cl
{
PowerFunction::PowerFunction(BaseFunctionPtr lhs, BaseFunctionPtr rhs) : _lhs(lhs), _rhs(rhs), BaseFunction(T_POWER_FUNCTION)
{
}

std::string PowerFunction::str() const
{
    return "(" + _lhs->str() + "^" + _rhs->str() + ")";
}

double PowerFunction::value(double x) const
{
    return std::pow(_lhs->value(x), _rhs->value(x));
}

BaseFunctionPtr PowerFunction::derivative() const
{
    if (_rhs->_type == T_CONSTANT_FUNCTION)
    {
        return std::make_shared<MultiplyFunction>(std::make_shared<MultiplyFunction>(std::make_shared<ConstantFunction>(_rhs->value(0)),
                                                                                     std::make_shared<PowerFunction>(_lhs, std::make_shared<ConstantFunction>(_rhs->value(0) - 1))),
                                                  _lhs->derivative());
    }
    else
    {
        return std::make_shared<MultiplyFunction>(std::make_shared<PowerFunction>(_lhs, _rhs),
                                                  std::make_shared<AddFunction>(std::make_shared<MultiplyFunction>(_rhs->derivative(), std::make_shared<LnFunction>(_lhs)),
                                                                                std::make_shared<MultiplyFunction>(_rhs, std::make_shared<LnFunction>(_lhs)->derivative())));
    }
}

} // namespace cl
